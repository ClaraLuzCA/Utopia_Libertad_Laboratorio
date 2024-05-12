#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	muevex = 2.0f;
	muevexHelicoptero = 0.0f;
	LuzPointLigth = 1.0f;
	LuzHongo = 1.0f;
	cambioSpot = 1.0f;
	LuzFaro = 1.0f;
	cambiacamara = 1.0f;

	movPBTotoro = false;
	movTotoro = 0.0f;
	rotTotoro = 0.0f;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Utopia Libertad", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_Y)
	{
		theWindow-> muevex += 1.0;
		theWindow->cambioSpot = 1.0f;
	}
	if (key == GLFW_KEY_U )
	{
		theWindow-> muevex -= 1.0;
		theWindow->cambioSpot = -1.0f;
	}
	/*if (key == GLFW_KEY_I && action == GLFW_PRESS)
	{
		theWindow->cambioSpot = -1.0f * theWindow->LuzPointLigth;
	}*/
	if (key == GLFW_KEY_I)
	{
		theWindow->muevexHelicoptero += 1.0;
	}
	if (key == GLFW_KEY_O)
	{
		theWindow->muevexHelicoptero -= 1.0;
	}
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		theWindow->LuzPointLigth = -1.0f*theWindow->LuzPointLigth;
	}
	if (key == GLFW_KEY_K && action == GLFW_PRESS)
	{
		theWindow->LuzHongo = -1.0f * theWindow->LuzHongo;
	}
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
		theWindow->LuzFaro = -1.0f * theWindow->LuzFaro;
	}

	if (key == GLFW_KEY_N && action == GLFW_PRESS)
	{
		theWindow->cambiacamara = 1.0;
	}
	if (key == GLFW_KEY_M && action == GLFW_PRESS)
	{
		theWindow->cambiacamara = -1.0;
	}
	if (key == GLFW_KEY_O)
	{
		theWindow->L = 1;
	}
	if (key == GLFW_KEY_P)
	{
		theWindow->L = 0;
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
	if (key == GLFW_KEY_Z)
	{
		theWindow->anguloL += 10.0;
	}

	if (key == GLFW_KEY_X)
	{
		theWindow->anguloL -= 10.0;
	}
	


	if (key == GLFW_KEY_Z) {
		theWindow->movTotoro += 1.0;
		theWindow->movPBTotoro = true;
	}
	else {
		//theWindow->movPBTotoro = false;
	}
	if (key == GLFW_KEY_X) {
		theWindow->movTotoro -= 1.0;
		theWindow->movPBTotoro = true;
	}
	else {
		//theWindow->movPBTotoro = false;
	}

	if (key == GLFW_KEY_C) {
		theWindow->rotTotoro += 2.0;
	}
	if (key == GLFW_KEY_V) {
		theWindow->rotTotoro -= 2.0;
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
