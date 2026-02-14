#include "debug.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <csignal>

static void APIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id,
							GLenum severity, GLsizei length, const GLchar* message,
							const void* userParam)
{
    // Ignore non-significant notification spam
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        return;

    std::cerr << "\n--- OpenGL Debug Message ---\n";
    std::cerr << "Message: " << message << "\n";

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:
            std::cerr << "Type: ERROR\n";
            if (type == GL_DEBUG_TYPE_ERROR) {
					#ifdef _MSC_VER
					__debugbreak();
					#else
					raise(SIGTRAP);
					#endif
				}
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cerr << "Type: UNDEFINED BEHAVIOR\n";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            std::cerr << "Type: PERFORMANCE\n";
            break;
        default:
            std::cerr << "Type: OTHER\n";
            break;
    }

    std::cerr << "---------------------------\n";
}

void GLDebugSetup()
{
	int flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(GLDebugCallback, nullptr);
		glDebugMessageControl(
		    GL_DONT_CARE,
		    GL_DONT_CARE,
		    GL_DONT_CARE,
		    0, nullptr,
		    GL_TRUE
		);
	}
}
