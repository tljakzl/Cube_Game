
#include "pch.h"
#include "engine/Window/Window.h"
#include "Shader.h"
#include "Database.h"
#include "World.h"
#include <thread>
#include <filesystem>
#include "Text.h"

std::string GetDebugInformation(int FPS)
{
    float chunkSize = 16.f;
    auto camera = Core::GetCamera();
    float num_x = camera->Position.x / chunkSize;
    int counter = 0;
    float num_z = camera->Position.z / chunkSize;

    if (num_x >= 0)
        counter = 1;
    else counter = -1;
    int chunk_x = (int)(camera->Position.x / chunkSize) + counter;

    if (num_z >= 0)
        counter = 1;
    else counter = -1;
    int chunk_z = (int)(camera->Position.z / chunkSize) + counter;

    std::stringstream buf ;
    buf << "Position:(" << camera->Position.x << "," << camera->Position.y << "," << camera->Position.z << ")" << std::endl;
    buf << "NumChunk:(" << chunk_x << ","  << chunk_z << ")" << std::endl;
    buf << "FPS: " + std::to_string(FPS) << std::endl;

    return buf.str();
}

int main()
{
    Core::InitGL();
	auto window = Core::CreateWindow();
	if (!window)
	{
		std::cout << "Failed to create window" << std::endl;
        Core::TerminateWindow();
		return -1;
	}
	auto settingsApply = Core::InitWindowSetting(window);
	if (!settingsApply)
    {
	    return -1;
    }

	namespace fs = std::filesystem;
	auto currentPath(fs::current_path());
    fs::path shaderPathVer{ "/shaders/Vertex.ver" };
    fs::path shaderPathFrag{ "/shaders/Frag.fg" };
    fs::path objectsPath{ "/objects/cube.obj" };
    
    auto shaderPath1 = currentPath;
    auto shaderPath2 = currentPath;
    auto databasePath = currentPath;

	shaderPath1 += shaderPathVer;
    shaderPath2 += shaderPathFrag;
    databasePath += objectsPath;

    //glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader shader_for_block(shaderPath1.u8string().c_str(), shaderPath2.u8string().c_str());
	Database database(databasePath.u8string().c_str());
	World world(&database);

    auto&& runIt = [&world]() {
        world.GetChunkManager().add_face_in_area(world.GetRenderMaster());
    };
    std::thread addFaces(runIt);

    Shader shader("shaders/text.vs", "shaders/text.fs");
    glm::mat4 projectionText = glm::ortho(0.0f, static_cast<float>(Core::SCR_WIDTH), 0.0f, static_cast<float>(Core::SCR_HEIGHT));
    Text testText;

	while (!glfwWindowShouldClose(window))
	{
	    int FPS = Core::ChangeDeltaTime();
		glfwPollEvents();
		Core::DoMovement();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDisable(GL_BLEND);
        auto camera = *Core::GetCamera();
		glm::mat4 model;
		const glm::mat4 projection = glm::perspective(camera.Zoom, static_cast<float>(Core::SCR_WIDTH) / Core::SCR_HEIGHT, 0.1f, 500.0f);
		const glm::mat4 view = camera.GetViewMatrix();

		// TODO нужно прибрать куда-то шейдер, все настройки для шейдера должны вызываться до отрисовки мира и после Use!!!
        shader_for_block.Use();
        shader_for_block.setInt("texture", 1);
		shader_for_block.setM4fv("model", model);
		shader_for_block.setM4fv("view", view);
		shader_for_block.setM4fv("projection", projection);

        world.Draw(&shader_for_block);

        glEnable(GL_BLEND);

        testText.RenderText(shader, GetDebugInformation(FPS), 0.0f, Core::SCR_HEIGHT - 70.f, 1.0f, glm::vec3(0.6, 0.8f, 0.9f), projectionText);
        //testText.RenderText(shader, , 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), projectionText);
        //testText.TestAtlas(shader, testText.GetCharacter('a').TextureID);



		/*if (false)
		{
			try 
			{
				float  alpha = camera.Pitch;
				float  beta = camera.Yaw;
				float  alpha_ = glm::radians(alpha);
				float  beta_ = glm::radians(beta);
                world.DeleteBlock(glm::vec3(camera.Position.x + cos(beta_) * cos(alpha_), camera.Position.y + sin(alpha_), cos(alpha_)*sin(beta_) + camera.Position.z));
			}
			catch (std::out_of_range t) {
				std::cout << t.what() << std::endl;
			}
			//flag = false;
		}*/

		glfwSwapBuffers(window);
	}
	addFaces.join();
	glfwTerminate();
	return 0;
}
