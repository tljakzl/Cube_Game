//
// Created by kozlov-an on 07.04.2021.
//
#include <sstream>
#include "pch.h"
#include "Window.h"

// TODO избавится от статических переменных, вынести их в отдельбные объекты

static const float SCR_WIDTH_F = Core::SCR_WIDTH;
static const float SCR_HEIGHT_F = Core::SCR_HEIGHT;
static const char WINDOW_NAME[] = "Game_nullptr";

static float mouse_x = 0.0;
static float mouse_y = 0.0;
static bool keys[1024];
static float lastX = 0.0;
static float lastY = 0.0;
static float deltaTime = 0.0f;	// Время, прошедшее между последним и текущим кадром
static float lastFrame = 0.0f;  // Время вывода последнего кадра
static Camera camera(glm::vec3(5.0f, 121.0f, 26.0f));

extern bool flag = false;

namespace Core {

    Camera* GetCamera()
    {
        return &camera;
    }
    GLFWwindow* CreateWindow()
    {
        return glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    }

    void TerminateWindow()
    {
        glfwTerminate();
    }

    void InitGL()
    {
        //Инициализация GLFW
        glfwInit();

        //Настройка GLFW
        //Задается минимальная требуемая версия OpenGL.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);    //Мажорная
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);    //Минорная

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Установка профайла для которого создается контекст
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);                      //Выключение возможности изменения размера окна
    }

    bool InitWindowSetting(GLFWwindow* window)
    {
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
        glfwSetKeyCallback(window, KeyCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
        glfwSetCursorPosCallback(window, MouseCallback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetScrollCallback(window, ScrollCallback);
        //glfwSwapInterval( 0 ); Вертикальная сихронизация

        glewExperimental = GL_TRUE;

        if (glewInit() != GLEW_OK)
        {
            std::cout << "Failed to initialize GLEW" << std::endl;
            return false;
        }

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        return true;
    }


    void MousePosCallback(GLFWwindow* window, double x, double y)
    {
        if (GLFW_CURSOR)
        {
            mouse_x = (static_cast<float>(x) - SCR_WIDTH_F / 2.f) / SCR_WIDTH_F * 2.f;
            mouse_y = -(static_cast<float>(y) - SCR_HEIGHT_F / 2.f) / SCR_HEIGHT_F * 2.f;
        }
    }
    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            double xPos;
            double yPos;
            //getting cursor position
            glfwGetCursorPos(window, &xPos, &yPos);

            mouse_x =  (static_cast<float>(xPos) - SCR_WIDTH_F / 2.f) / SCR_WIDTH_F * 2.f;
            mouse_y = -(static_cast<float>(yPos) - SCR_HEIGHT_F / 2.f) / SCR_HEIGHT_F * 2.f;
        }
    }

    void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;

        if (action == GLFW_PRESS)
        {
            switch (key)
            {
                case GLFW_KEY_ESCAPE:
                    glfwSetWindowShouldClose(window, GL_TRUE);
                    break;
                case  GLFW_KEY_P:
                    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
                    break;
                case GLFW_KEY_F:
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    break;
                case GLFW_KEY_L:
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    break;
                case GLFW_KEY_R:
                     flag = true;
                    break;
                default:;
            }
        }

    }

    void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    void DoMovement()
    {
        // Camera controls
        if (keys[GLFW_KEY_W])
            camera.ProcessKeyboard(Camera::Movement::FORWARD, deltaTime);
        if (keys[GLFW_KEY_S])
            camera.ProcessKeyboard(Camera::Movement::BACKWARD, deltaTime);
        if (keys[GLFW_KEY_A])
            camera.ProcessKeyboard(Camera::Movement::LEFT, deltaTime);
        if (keys[GLFW_KEY_D])
            camera.ProcessKeyboard(Camera::Movement::RIGHT, deltaTime);
    }

    void MouseCallback(GLFWwindow* window, double xpos, double ypos)
    {
        static bool firstMouse = true;
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        const float xoffset = xpos - lastX;
        const float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }

    void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        camera.ProcessMouseScroll(yoffset);
    }

    int ChangeDeltaTime()
    {
        auto currentFrame = glfwGetTime();

        auto FPS = CalculateFrameRate(currentFrame);
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        return FPS;
    }

    int CalculateFrameRate(float current)
    {
        static double last = 0.0;
        static int FPS = 0;
        ++FPS;
        static int out_FPS = 0;
        if (current - last >= 1.0f)
        {
            out_FPS = FPS;
            std::cout << "FPS:" << out_FPS << std::endl;
            FPS = 0;
            last = current;
        }

        return out_FPS;
    }
}
