#include "OpenGLWindow.h"

int main()
{
    Program::setProgramsDirectory("../Resources/Shaders/");
    
    OpenGLWindow openglWindow;

    openglWindow.InitWindow();

    openglWindow.InitGui();

    openglWindow.InitScene();

    openglWindow.MainLoop();

    return 0;
}