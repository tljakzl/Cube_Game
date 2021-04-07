
#include "pch.h"
#include "engine/Window/Window.h"
#include "Shader.h"
#include "Database.h"
#include "World.h"
#include <thread>
#include <filesystem>


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

	Shader shader_for_block(shaderPath1.u8string().c_str(), shaderPath2.u8string().c_str());
	Database database(databasePath.u8string().c_str());
	World world(&database);

    auto&& runIt = [&world]() {
        world.GetChunkManager().add_face_in_area(world.GetRenderMaster());
    };
    std::thread addFaces(runIt);

	while (!glfwWindowShouldClose(window))
	{
	    Core::ChangeDeltaTime();
		glfwPollEvents();
		Core::DoMovement();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto camera = *Core::GetCamera();
		glm::mat4 model;
		const glm::mat4 projection = glm::perspective(camera.Zoom, static_cast<float>(Core::SCR_WIDTH) / Core::SCR_HEIGHT, 0.1f, 500.0f);
		const glm::mat4 view = camera.GetViewMatrix();
		
		shader_for_block.setM4fv("model", model);
		shader_for_block.setM4fv("view", view);
		shader_for_block.setM4fv("projection", projection);

        world.Draw(&shader_for_block);
		if (false)
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
		}
	
		glfwSwapBuffers(window);
	}
	addFaces.join();
	glfwTerminate();
	return 0;
}
