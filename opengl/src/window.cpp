#include "../inc/window.hpp"

/* Window */
void
define_window_hints()
{
	glfwWindowHind(GLFW_RESIZABLE, GLFW_FALSE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow *
create_new_window(int width, int height, const char *title,
				  GLFWmonitor *monitor, GLFWwindow *share)
{
	GLFWwindow *win = glfwCreateWindow(width, height, title, monitor, share);
	if(!win)
	{
		glfwDestroyWindow(win);
		sys_error("create_new_window: glfwCreateWindow error");
	}

	return win;
}

void
framebuffer_size_callback(GLFWwindow *win, int width, int height)
{
	GLCALL( glViewport(0, 0, width, height) );
	(void)win;
}
/* END Window */

/* INPUT */
float postion_changing[3] = {0};

void
key_callback(GLFWwindow *win, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_F4 && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(win, true);
		return;
	}

	float position_changing_value = 0.25f;
	switch(key)
	{
	  case GLFW_KEY_UP:
		  if(action == GLFW_PRESS)
		  {
			  if(glfwGetKey(win, GLFW_KEY_Z) == GLFW_PRESS)
				  position_changing[2] = position_changing_value;
			  else
				  position_changing[1] = position_changing_value;
		  }
	  case GLFW_KEY_DOWN:
		  if(action == GLFW_PRESS)
		  {
			  if(glfwGetKey(win, GLFW_KEY_Z) == GLFW_PRESS)
				  position_changing[2] = -position_changing_value;
			  else
			  position_changing[1] = -position_changing_value;
		  }
	  case GLFW_KEY_RIGHT:
		  if(action == GLFW_PRESS)
			  position_changing[0] = position_changing_value;
	  case GLFW_KEY_LEFT:
		  if(action == GLFW_PRESS)
			  position_changing[0]  = -position_changing_value;
	}

	if( (key == GLFW_KEY_UP    || key == GLFW_KEY_DOWN  ||
		 key == GLFW_KEY_RIGHT || key == GLFW_KEY_LEFT) &&
		action == GLFW_RELEASE)
	{
		for(size_t i = 0; i < 3; ++i)
			position_changing[i] = 0;
	}

	(void)scancode;
	(void)mods;
}

/* END INPUT */
