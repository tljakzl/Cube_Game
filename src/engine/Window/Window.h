#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"

namespace Core
{
    static const unsigned int SCR_WIDTH  = 16 * 100;
    static const unsigned int SCR_HEIGHT = 9 * 100;

    GLFWwindow* CreateWindow();
    void InitGL();
    void TerminateWindow();
    bool InitWindowSetting(GLFWwindow* window);
    void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void MousePosCallback(GLFWwindow* window, double x, double y);
    void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    Camera* GetCamera();
    int ChangeDeltaTime();
    void DoMovement();
    int CalculateFrameRate(float current);
}

