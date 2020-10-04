
#include "pch.h"
#include "main.h"
#include "Shader.h"
#include <iostream>
#include "Camera.h"
#include "Database.h"
#include "World.h"





Camera camera(glm::vec3(0.0f, 36.0f, 0.0f));

bool keys[1024];
float mouse_x = 0.0;
float mouse_y = 0.0;

GLfloat deltaTime = 0.0f;							 // Время, прошедшее между последним и текущим кадром
GLfloat lastFrame = 0.0f;  							 // Время вывода последнего кадра
GLfloat lastX = 00, lastY = 00;

bool flag = false;
double FPS = 0;





int main()
{
	//Инициализация GLFW
	glfwInit();
	//Настройка GLFW
	//Задается минимальная требуемая версия OpenGL. 
	//Мажорная 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//Минорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Game_nullptr", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(window, scroll_callback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
   


	Shader shader_for_block("shaders/Vertex.ver", "shaders/Frag.fg");
	




	const char* path = { "objects/cube.obj" };
	Database database(path);




	
	




	World world_test(&database);
	




	while (!glfwWindowShouldClose(window))
	{
		
		GLfloat currentFrame = glfwGetTime();
		

		calculate_frame_rate(currentFrame);
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		

		glfwPollEvents();
		do_movement();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		
		glm::mat4 model;
		const glm::mat4 projection = glm::perspective(camera.Zoom, static_cast<float>(SCR_WIDTH) / SCR_HEIGHT, 0.1f, 100.0f);
		const glm::mat4 view = camera.GetViewMatrix();
		const float length = static_cast<float>(glfwGetTime());

		
		shader_for_block.setM4fv("model", model);
		shader_for_block.setM4fv("view", view);
		shader_for_block.setM4fv("projection", projection);


		


		world_test.draw(&shader_for_block);
		if (flag)
		{
			try 
			{
				float  alpha = camera.Pitch;
				float  beta = camera.Yaw;
				float  alpha_ = glm::radians(alpha);
				float  beta_ = glm::radians(beta);
				world_test.delete_block(glm::vec3(camera.Position.x + cos(beta_) * cos(alpha_), camera.Position.y + sin(alpha_), cos(alpha_)*sin(beta_) + camera.Position.z));
			}
			catch (std::out_of_range t) {
				std::cout << t.what() << std::endl;
			}
			flag = false;
		}
	
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}



void calculate_frame_rate(GLfloat current)
{
	static double last = 0.0;
	++FPS;
	if (current - last > 1.0f)
	{
		std::cout << "FPS:" << FPS << std::endl;
		FPS = 0;
		last = current;
	}
}



void mouse_pos_callback(GLFWwindow* window, double x, double y)
{
	if (GLFW_CURSOR) 
	{
		mouse_x = (x - SCR_WIDTH / 2) / SCR_WIDTH * 2;
		mouse_y = -(y - SCR_HEIGHT / 2) / SCR_HEIGHT * 2;
	}
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

	
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		//camera.MovementSpeed += 0.5;
		double xpos, ypos;
		flag = true;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);
		mouse_x =  (xpos - SCR_WIDTH / 2) / SCR_WIDTH * 2;
		mouse_y = -(ypos - SCR_HEIGHT / 2) / SCR_HEIGHT * 2;
		//std::cout << "Cursor Position at (" << mouse_x << " : " << mouse_y <<")" << std::endl;
	}
}





void key_callback (GLFWwindow* window, int key, int scancode, int action, int mode)
{
	float  alpha = camera.Pitch;
	float  beta  = camera.Yaw;
	float  alpha_ = glm::radians(alpha);
	float  beta_ = glm::radians(beta);


	float num_x = camera.Position.x / 16;
	int counter = 0;
	float num_z = camera.Position.z / 16;

	if (num_x >= 0)
		counter = 1;
	else counter = -1;
	int chunk_x = (int)(camera.Position.x / 16) + counter;


	

	if (num_z >= 0)
		counter = 1;
	else counter = -1;
	int chunk_z = (int)(camera.Position.z / 16) + counter;



	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_1:

			std::cout << "Position:(" << camera.Position.x << "," << camera.Position.y << "," << camera.Position.z << ")" << std::endl;
			//std::cout << "Position dig:(" <<  cos(beta_) * cos(alpha_) << "," << sin(alpha_) << "," << cos(alpha_)*sin(beta_) << ")" << std::endl;
		
			
			std::cout << "NumChunk:(" << chunk_x << ","  << chunk_z << ")" << std::endl;
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case  GLFW_KEY_P:
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			break;
		case GLFW_KEY_F:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//	flag = true;
			break;
		case GLFW_KEY_L:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		default:;
		}
	}
	
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	const GLfloat xoffset = xpos - lastX;
	const GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

