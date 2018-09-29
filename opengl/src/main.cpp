#define GLEW_STATIC
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../inc/common.hpp"
#include "../inc/draw.hpp"
#include "../inc/buffer.hpp"
#include "../inc/shader.hpp"
#include "../inc/texture.hpp"
#include "../inc/renderer.hpp"
#include "../inc/window.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

static void
mainWindow()
{
	define_window_hints();

	if(!glfwInit())
		sys_error("mainWindow: glfwInit error");

	GLFWwindow *window = create_new_window(MW_WIDTH, MW_HEIGHT,
										   "Title of main window",
										   nullptr, nullptr);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(2);

	glewExperimental = GLEW_OK;
	if(glewInit() != GLEW_OK)
		sys_error("mainWinow: glewInit error");

	GLCALL( glViewport(0, 0, MW_WIDTH, MW_HEIGHT) );

	{
		int maxVertAttrib;
		GLCALL( glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertAttrib) );
		std::cout << "GL_VERSION:  " << glGetString(GL_VERSION)       << '\n'
				  << "GL_RENDERER: " << glGetString(GL_RENDERER)      << '\n'
				  << "Amount of vertex attributes: " << maxVertAttrib << std::endl;
	}

	{
		glm::mat4 proj(1.f);
		proj = glm::ortho(0.f, MW_WIDTH_F, 0.f, MW_HEIGHT_F, -1.f, 1.f);

		float rectangle[] = {
			0.f,   0.f,   0.f, 0.f, 0.f,
			100.f, 100.f, 0.f, 1.f, 1.f,
			100.f, 0.f,   0.f, 1.f, 0.f,
			0.f,   100.f, 0.f, 0.f, 1.f
		};

		uint32 rec_indices[] = {
			0, 1, 2,
			0, 1, 3			
		};

		GLCALL( glEnable(GL_BLEND) );
		GLCALL( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );
		
		VertexArray vao;
		VertexBuffer rec_buffer(rectangle, sizeof rectangle);

		VertexBufferLayout rec_layout;
		rec_layout.Push(3, MY_FLOAT);
		rec_layout.Push(2, MY_FLOAT);
		vao.AddBuffer(rec_buffer, rec_layout);

		IndexBuffer rec_index(rec_indices, sizeof rec_indices / sizeof *rec_indices);
		

		Texture rec_texture("../media/rec.png");
		Shader rec_shader("../shader/vert.vert", "../shader/frag.frag");
		rec_shader.Bind();
		rec_shader.SetUniform1i("Texture1", 0);
		rec_shader.SetUniformMatrix4fv("proj", 1, GL_FALSE, glm::value_ptr(proj));
		rec_shader.Unbind();

		vao.Unbind();
		rec_buffer.Unbind();
		rec_index.Unbind();
		
		Renderer rend;

		glm::vec3 position(500.f, 300.f, 0.f);

		while(!glfwWindowShouldClose(window))
		{
			glfwSetKeyCallback(window, key_callback);

			rend.Clear(0.35f, 0.7f, 0.3f, 1.f);

			DrawSpaceShip(rend, vao, rec_index, rec_shader, rec_texture, position);

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
	mainWindow();

	return 0;
}

