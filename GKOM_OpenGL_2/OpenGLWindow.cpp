#include "OpenGLWindow.h"
#include "Gui.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


void FramebufferSizeChangeCallback(GLFWwindow* window, int width, int height);

OpenGLWindow::OpenGLWindow()
{
	_window = nullptr;

    deltaTime = 0;

    explosionPaused = false;
    explosionSpeed = 1.0;
    explosionTime = 0.0;
    explosionOrigin = { 0.0f, 0.0f, 0.0 };


    objectVAO = 0;
    objectVAOPrimitive = 0;
    objectVAOVertexCount = 0;

    windowResolution = glm::vec2(800, 600);
    fieldOfView = 45;

    cameraPosition = glm::vec3(0, 0, 20);
    cameraDirection = glm::vec3(0, 0, -1);
    cameraUp = glm::vec3(0, 1, 0);
    cameraSpeed = 0.05f;

}

OpenGLWindow::~OpenGLWindow()
{
    glfwTerminate();
}

bool OpenGLWindow::InitWindow()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW initialization failed!" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow((int)windowResolution.x, (int)windowResolution.y, "GKOM_OpenGL_2", NULL, NULL);

    if (_window == NULL)
    {
        std::cerr << "GLFW window creation failed!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(_window);

    if (glewInit())
    {
        std::cerr << "GLEW window creation failed!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwSetFramebufferSizeCallback(_window, FramebufferSizeChangeCallback);

    return true;
}

void OpenGLWindow::InitScene()
{
    transformationProgram.Load("transformationshader.vs", "transformationshader.fs", "geometryshader.gs");

    objectVAO = LoadBox(&objectVAOPrimitive, &objectVAOVertexCount);
}

void OpenGLWindow::MainLoop()
{
    glEnable(GL_DEPTH_TEST);

    Gui gui = Gui(_window);
    gui.initImGui();

    float lastFrameTime = 0.0;
    while (!glfwWindowShouldClose(_window))
    {
        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        glfwPollEvents();
        processInput();

        gui.startNewFrame();
        gui.createExplosionControlWindow(&explosionSpeed, &explosionOrigin, &explosionPaused);


        glClearColor(0.1, 0.2f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (!explosionPaused)
            explosionTime += explosionSpeed * deltaTime;

        projectionMatrix = glm::perspective(glm::radians(fieldOfView), windowResolution.x / windowResolution.y, 0.1f, 100.0f);

        viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraDirection, cameraUp);

        transformationProgram.Activate();

        glUniform3fv(transformationProgram.GetUniformID("explosionOrigin"), 1, glm::value_ptr(explosionOrigin));
        glUniform1f(transformationProgram.GetUniformID("explosionTime"), explosionTime);
        glUniformMatrix4fv(transformationProgram.GetUniformID("uViewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(transformationProgram.GetUniformID("uProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    
        // Draw objects
        for (int i = -2; i <= 2; i++)
        {
            for (int j = -2; j <= 2; j++)
            {
                modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(i * 3.0f, j * 3.0f, 0.0f));

                glUniformMatrix4fv(transformationProgram.GetUniformID("uModelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

                glBindVertexArray(objectVAO);
                glDrawArrays(objectVAOPrimitive, 0, objectVAOVertexCount);
            }
        }

        gui.renderGui();

        glfwSwapBuffers(_window);
    }
}

void OpenGLWindow::processInput()
{
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(_window, true);
    }

    // Explosion control. Right now it works badly since it checks every frame.
    // If your click wasn't fast enough it will register as 2.
    if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        explosionPaused = !explosionPaused;
    }

    // Camera movement

    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
    {
        // Move forward
        cameraPosition.z -= cameraSpeed;
    }

    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
    {
        // Move backward
        cameraPosition.z += cameraSpeed;
    }

    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        // Move left
        cameraPosition.x -= cameraSpeed;
    }

    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        // Move right
        cameraPosition.x += cameraSpeed;
    }

    if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        // Move up
        cameraPosition.y -= cameraSpeed;
    }

    if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
    {
        // Move down
        cameraPosition.y += cameraSpeed;
    }

    // Camera direction

    if (glfwGetKey(_window, GLFW_KEY_1) == GLFW_PRESS)
    {
        // Look forward
        cameraDirection = glm::vec3(0, 0, -1);
    }

    if (glfwGetKey(_window, GLFW_KEY_2) == GLFW_PRESS)
    {
        // Look backward
        cameraDirection = glm::vec3(0, 0, 1);
    }

    if (glfwGetKey(_window, GLFW_KEY_3) == GLFW_PRESS)
    {
        // Look left
        cameraDirection = glm::vec3(-1, 0, 0);
    }

    if (glfwGetKey(_window, GLFW_KEY_4) == GLFW_PRESS)
    {
        // Look right
        cameraDirection = glm::vec3(1, 0, 0);
    }
}

void FramebufferSizeChangeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}