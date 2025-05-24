#include "OpenGLWindow.h"
#include "Camera.h"
#include "Gui.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


void FramebufferSizeChangeCallback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

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

    _camera = std::make_unique<Camera>(glm::vec3(0, 0, 20), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
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
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(_window, mouse_callback);
    glfwSetWindowUserPointer(_window, this);

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

void OpenGLWindow::InitGui()
{
    _gui = std::make_unique<Gui>(_window);
}

void OpenGLWindow::InitScene()
{
    transformationProgram.Load("explosion_shader.vert", "explosion_shader.frag", "explosion_shader.geom");
    staticProgram.Load("simpleshader.vert", "simpleshader.frag");

    objectVAO = LoadBox(&objectVAOPrimitive, &objectVAOVertexCount);
}

void OpenGLWindow::MainLoop()
{
    glEnable(GL_DEPTH_TEST);

    float lastFrameTime = 0.0;
    _gui->initImGui();
    while (!glfwWindowShouldClose(_window))
    {
        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        glfwPollEvents();
        processInput();

        _gui->startNewFrame();
        _gui->createExplosionControlWindow(&explosionSpeed, &explosionTime, &explosionOrigin, &explosionPaused);


        glClearColor(0.1, 0.2f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (!explosionPaused)
            explosionTime += explosionSpeed * deltaTime;

        projectionMatrix = glm::perspective(glm::radians(fieldOfView), windowResolution.x / windowResolution.y, 0.1f, 100.0f);

        viewMatrix = glm::lookAt(_camera->getPosition(), _camera->getPosition() + _camera->getDirection(), _camera->getUp());

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
        
        // Draw point marking the explosion origin
        staticProgram.Activate();
        float explosionOriginScale = 0.3f;

        modelMatrix = glm::translate(glm::mat4(1.0f), explosionOrigin);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(explosionOriginScale));

        glUniformMatrix4fv(staticProgram.GetUniformID("uViewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(staticProgram.GetUniformID("uProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        glUniformMatrix4fv(staticProgram.GetUniformID("uModelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

        glBindVertexArray(objectVAO);
        glDrawArrays(objectVAOPrimitive, 0, objectVAOVertexCount);

        _gui->renderGui();

        glfwSwapBuffers(_window);
    }
}

Camera* OpenGLWindow::getCamera()
{
    return _camera.get();
}

Gui* OpenGLWindow::getGui()
{
    return _gui.get();
}

void OpenGLWindow::processInput()
{
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(_window, true);
    }

    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }


    // Explosion control. Right now it works badly since it checks every frame.
    // If your click wasn't fast enough it will register as 2.
    if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        explosionPaused = !explosionPaused;
    }

    // Camera movement

    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
        _camera->processKeyboard(CameraMovement::Forward);

    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
        _camera->processKeyboard(CameraMovement::Backward);

    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
        _camera->processKeyboard(CameraMovement::Left);

    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
        _camera->processKeyboard(CameraMovement::Right);

    if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS)
        _camera->processKeyboard(CameraMovement::Down);

    if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
        _camera->processKeyboard(CameraMovement::Up);
}

void FramebufferSizeChangeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static float lastX = 400.0f;
static float lastY = 300.0f;
static bool firstMouse = true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS)
    {
        firstMouse = true;
        return;
    }

    OpenGLWindow* glWindow = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
    Camera* camera = glWindow->getCamera();
    if (!camera) return;
    if (glWindow->getGui()->wantCaptureMouse()) return;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera->processMouseMovement(xoffset, yoffset);
}