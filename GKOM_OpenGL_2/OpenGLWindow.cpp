#include "OpenGLWindow.h"
#include "Camera.h"
#include "Gui.h"
#include "Utilities.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "RegularModel.h"
#include "InstancedModel.h"
#include "Explosion.h"
#include "ExplosionUBuffer.h"


void FramebufferSizeChangeCallback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

OpenGLWindow::OpenGLWindow()
{
	_window = nullptr;

    _deltaTime = 0;
    _vsyncEnabled = false;

    _windowResolution = glm::vec2(800, 600);
    _fieldOfView = 60;

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow((int)_windowResolution.x, (int)_windowResolution.y, "GKOM_OpenGL_2", NULL, NULL);
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
    _gui->initImGui();
}

void OpenGLWindow::InitScene()
{
    explosionProgram.Load("explosion_shader.vert", "explosion_shader.frag", "explosion_shader.geom");
    staticProgram.Load("simpleshader.vert", "simpleshader.frag");
}

void OpenGLWindow::MainLoop()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //ExplosionUBuffer explosionBuffer(_explosion);

    RegularMesh explosionPoint = LoadBoxMesh();
    InstancedMesh boxes = LoadBoxMeshInstanced();
    fs::path ratPath = "RAT/RAT.fbx";
    InstancedModel rat = InstancedModel(ratPath, getSampleInstanceMatrices());
    rat.applyTransformation(glm::scale(glm::mat4(1.0f), glm::vec3(0.01)));

    //RegularModel winter(fs::path("winter/scene.gltf"));

    int triangles = rat.getTriangleCount();
    
    while (!glfwWindowShouldClose(_window))
    {
        updateDeltaTime();

        glfwPollEvents();
        processInput();

        _gui->startNewFrame();
        _gui->createExplosionControlWindow(_explosion);
        _gui->createPerformanceOverlay(triangles);

        glClearColor(0.1, 0.2f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _explosion.updateTime(_deltaTime);

        //explosionBuffer.updateUniforms();

        _projectionMatrix = glm::perspective(glm::radians(_fieldOfView), _windowResolution.x / _windowResolution.y, 0.1f, 200.0f);

        _viewMatrix = glm::lookAt(_camera->getPosition(), _camera->getPosition() + _camera->getDirection(), _camera->getUp());

        explosionProgram.Activate();

        glUniform3fv(explosionProgram.GetUniformID("explosionOrigin"), 1, glm::value_ptr(_explosion.explosionOrigin));
        glUniform1f(explosionProgram.GetUniformID("explosionTime"), _explosion.explosionTime);
        glUniform1f(explosionProgram.GetUniformID("explosionStrength"), _explosion.explosionStrength);
        glUniformMatrix4fv(explosionProgram.GetUniformID("uViewMatrix"), 1, GL_FALSE, glm::value_ptr(_viewMatrix));
        glUniformMatrix4fv(explosionProgram.GetUniformID("uProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(_projectionMatrix));

        //rat.Draw(explosionProgram);
        boxes.Draw(explosionProgram);
        //winter.Draw(explosionProgram);
        
        // Draw point marking the explosion origin
        staticProgram.Activate();

        glUniformMatrix4fv(staticProgram.GetUniformID("uViewMatrix"), 1, GL_FALSE, glm::value_ptr(_viewMatrix));
        glUniformMatrix4fv(staticProgram.GetUniformID("uProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(_projectionMatrix));

        float explosionOriginScale = 0.3f;

        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), _explosion.explosionOrigin);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(explosionOriginScale));

        explosionPoint.setModelMatrix(modelMatrix);
        explosionPoint.Draw(staticProgram);

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
        _explosion.togglePause();
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