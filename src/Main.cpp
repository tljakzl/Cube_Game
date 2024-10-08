﻿
#include "pch.h"
#include "engine/Window/Window.h"
#include "Shader.h"
#include "Database.h"
#include "World.h"
#include <thread>
#include <filesystem>
#include "Text.h"

extern bool flag;

std::string GetDebugInformation(int FPS)
{
    std::stringstream buf;

    if(auto camera = Core::GetCamera())
    {
        float chunkSize = 16.f;
        int counter = 0;
        auto position = camera->GetPosition();
        float num_x = position.x / chunkSize;
        float num_z = position.z / chunkSize;

        counter = (num_x >= 0) ? 1 : -1;
        int chunk_x = static_cast<int>(position.x / chunkSize) + counter;
        counter = (num_z >= 0) ? 1 : -1;
        int chunk_z = static_cast<int>(position.z / chunkSize) + counter;

        buf << "Position:(" << position.x << "," << position.y << "," << position.z << ")" << std::endl;
        buf << "NumChunk:(" << chunk_x << ","  << chunk_z << ")" << std::endl;
        buf << "FPS: " + std::to_string(FPS) << std::endl;
    }

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
        world.GetChunkManager().AddFaceInArea(world.GetRenderMaster());
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
		const glm::mat4 projection = glm::perspective(camera.GetZoom(), static_cast<float>(Core::SCR_WIDTH) / Core::SCR_HEIGHT, 0.1f, 500.0f);
		const glm::mat4 view = camera.GetViewMatrix();

		// TODO нужно прибрать куда-то шейдер, все настройки для шейдера должны вызываться до отрисовки мира и после Use!!!
        shader_for_block.Use();
        shader_for_block.SetInt("texture", 1);
		shader_for_block.SetM4fv("model", model);
		shader_for_block.SetM4fv("view", view);
		shader_for_block.SetM4fv("projection", projection);

        world.Draw(&shader_for_block);

        glEnable(GL_BLEND);
        testText.RenderText(shader, GetDebugInformation(FPS), 0.0f, Core::SCR_HEIGHT - 70.f, 1.0f, glm::vec3(0.6, 0.8f, 0.9f), projectionText);
        //testText.RenderText(shader, , 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), projectionText);
        //testText.TestAtlas(shader, testText.GetCharacter('a').TextureID);

		if (flag)
		{
			try 
			{
				float  alpha = camera.GetPitch();
				float  beta = camera.GetYaw();
				float  alpha_ = glm::radians(alpha);
				float  beta_ = glm::radians(beta);
                 world.DeleteBlock(glm::vec3(camera.GetPosition().x + cos(beta_) * cos(alpha_), camera.GetPosition().y + sin(alpha_), cos(alpha_) * sin(beta_) + camera.GetPosition().z));
			}
			catch (std::out_of_range t) {
				std::cout << t.what() << std::endl;
			}
			flag = false;
		}

		glfwSwapBuffers(window);
	}
	addFaces.join();
	glfwTerminate();
	return 0;
}
