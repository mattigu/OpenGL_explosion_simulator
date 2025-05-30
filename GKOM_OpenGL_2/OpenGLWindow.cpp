#include "OpenGLWindow.h"
#include "Camera.h"
#include "Gui.h"
#include "Utilities.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "RegularModel.h"
#include "InstancedModel.h"



void FramebufferSizeChangeCallback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

OpenGLWindow::OpenGLWindow()
{
	_window = nullptr;

    _deltaTime = 0;
    _vsyncEnabled = false;

    explosionPaused = false;
    explosionSpeed = 1.0;
    explosionTime = 0.0;
    explosionOrigin = { 0.0f, 0.0f, 0.0 };


    objectVAO = 0;
    objectVAOPrimitive = 0;
    objectVAOVertexCount = 0;

    windowResolution = glm::vec2(800, 600);
    fieldOfView = 60;

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
    glfwSetWindowAspectRatio(_window, 4, 3);
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
    glfwSwapInterval(_vsyncEnabled ? 1 : 0);
    return true;
}

void OpenGLWindow::InitGui()
{
    _gui = std::make_unique<Gui>(_window);
}

void OpenGLWindow::InitScene()
{
    explosionProgram.Load("explosion_shader.vert", "explosion_shader.frag", "explosion_shader.geom");
    staticProgram.Load("simpleshader.vert", "simpleshader.frag");

    objectVAO = LoadBox(&objectVAOPrimitive, &objectVAOVertexCount);
}

void OpenGLWindow::MainLoop()
{
    glEnable(GL_DEPTH_TEST);

    _gui->initImGui();
    RegularMesh mesh = LoadBoxMesh();
    InstancedMesh imesh = LoadBoxMeshInstanced();
    //InstancedMesh imesh = InstancedMesh::fromRegularMesh(mesh, ...);
    fs::path ratPath = "RAT/RAT.fbx";
    //fs::path chiyoPath = "chiyo/chiyo.obj";
    //RegularModel rat = RegularModel(ratPath);
    InstancedModel rat = InstancedModel(ratPath, getSampleInstanceMatrices());
    //RegularModel chiyo = RegularModel(chiyoPath);
    while (!glfwWindowShouldClose(_window))
    {
        updateDeltaTime();

        glfwPollEvents();
        processInput();

        _gui->startNewFrame();
        _gui->createExplosionControlWindow(&explosionSpeed, &explosionTime, &explosionOrigin, &explosionPaused);
        _gui->createPerformanceOverlay();


        glClearColor(0.1, 0.2f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (!explosionPaused)
            explosionTime += explosionSpeed * _deltaTime;

        projectionMatrix = glm::perspective(glm::radians(fieldOfView), windowResolution.x / windowResolution.y, 0.1f, 100.0f);

        viewMatrix = glm::lookAt(_camera->getPosition(), _camera->getPosition() + _camera->getDirection(), _camera->getUp());

        explosionProgram.Activate();

        glUniform1i(explosionProgram.GetUniformID("useTexture"), 0); // Temporary until textures fully implemented
        glUniform3fv(explosionProgram.GetUniformID("explosionOrigin"), 1, glm::value_ptr(explosionOrigin));
        glUniform1f(explosionProgram.GetUniformID("explosionTime"), explosionTime);
        glUniformMatrix4fv(explosionProgram.GetUniformID("uViewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(explosionProgram.GetUniformID("uProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    
        for (int i = -2; i <= 2; i++)
        {
            for (int j = -2; j <= 2; j++)
            {
                modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(i * 3.0f, j * 3.0f, 0.0f));

                glUniformMatrix4fv(explosionProgram.GetUniformID("uModelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

                glBindVertexArray(objectVAO);
                glDrawArrays(objectVAOPrimitive, 0, objectVAOVertexCount);

                // Draw with the mesh class.
                //mesh.setModelMatrix(modelMatrix);
                //mesh.Draw(explosionProgram); 
            }
        }
        // Draw instanced
        //imesh.Draw(explosionProgram);
        // Draw loaded models
        rat.Draw(explosionProgram);
        //chiyo.Draw(explosionProgram);
        
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

void OpenGLWindow::updateDeltaTime()
{
    static double lastFrameTime;

    double currentFrameTime = glfwGetTime();
    _deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
}

void OpenGLWindow::toggleVsync()
{
    _vsyncEnabled = !_vsyncEnabled;
    glfwSwapInterval(_vsyncEnabled ? 1 : 0);
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

    // Explosion pause
    static bool wasSpacePressedLastFrame;
    bool spacePressedNow = glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS;
    if (spacePressedNow && !wasSpacePressedLastFrame)
    {
        explosionPaused = !explosionPaused;
    }
    wasSpacePressedLastFrame = spacePressedNow;

    static bool wasVPressedLastFrame;
    bool vPressedNow = glfwGetKey(_window, GLFW_KEY_V) == GLFW_PRESS;
    if (vPressedNow && !wasVPressedLastFrame)
    {
        toggleVsync();
    }
    wasVPressedLastFrame = vPressedNow;


    // Camera movement

    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
        _camera->processKeyboard(CameraMovement::Forward, _deltaTime);

    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
        _camera->processKeyboard(CameraMovement::Backward, _deltaTime);

    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
        _camera->processKeyboard(CameraMovement::Left, _deltaTime);

    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
        _camera->processKeyboard(CameraMovement::Right, _deltaTime);

    if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS)
        _camera->processKeyboard(CameraMovement::Down, _deltaTime);

    if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
        _camera->processKeyboard(CameraMovement::Up, _deltaTime);
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