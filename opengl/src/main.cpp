#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../inc/common.hpp"
#include "../inc/window.hpp"
#include "../inc/buffer.hpp"
#include "../inc/shader.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define MW_WIDTH  1024
#define MW_HEIGHT 720

static void
mainWindow()
{
	define_window_hints();

	if(!glfwInit())
		sys_error("mainWindow: glfwInit error");

	GLFWwindow *window = create_new_winodw(MW_WIDTH, MW_HEIGHT,
										   "Title of main window",
										   nullptr, nullptr);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(2);

	glewExperimental = GLEW_OK;
	if(glewInit() != GLEW_OK)
		sys_error("mainWinow: glewInit error");

	GLCALL( glEnable(GL_DEPTH_TEST) );

	GLCALL( glViewport(0, 0, MW_WIDTH, MW_HEIGHT) );

	{
		int maxVertAttrib;
		GLCALL( glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertAttrib) );
		std::cout << "GL_VERSION:  " << glGetString(GL_VERSION)       << '\n'
				  << "GL_RENDERER: " << glGetString(GL_RENDERER)      << '\n'
				  << "Amount of vertex attributes: " << maxVertAttrib << std::endl;
	}

	{
		float rectangle[] = {
			-0.5f, -0.5f, 0, 0, 0,
			 0.5f,  0.5f, 0, 1, 1,
			 0.5f, -0.5f, 0, 1, 0,
			-0.5f, -0.5f, 0, 0, 1
		};

		float rec_index[] = {
			0, 1, 2,
			0, 1, 3			
		};

		

		glm::vec2 position(0);
		float z_view_position = 0;

		while(!glfwWindowShouldClose(window))
		{
			glfwSetKeyCallback(window, key_callback);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}

int
main()
{
	mainWinodw();

	return 0;
}

