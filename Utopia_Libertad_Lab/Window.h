#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }
	GLfloat getmuevexHelicoptero() { return muevexHelicoptero; }
	GLfloat getLuzPointLigth() { return LuzPointLigth; }
	GLfloat getLuzFaro() { return LuzFaro; }
	GLfloat getcambioSpot() { return cambioSpot; }
	GLfloat getLuzHongo() { return LuzHongo; }
	GLfloat getcambiacamara() { return cambiacamara; }
	GLfloat getanguloL() { return anguloL; }
	GLint getlight() { return L; }



	GLfloat getmueveTototo() { return movTotoro; }
	GLfloat getrotaTototo() { return rotTotoro; }
	bool getmovPBTotoro() { return movPBTotoro; }

	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);
	}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	GLfloat muevexHelicoptero;
	GLfloat LuzPointLigth;
	GLfloat LuzHongo;
	GLfloat cambioSpot;
	GLfloat LuzFaro;
	GLfloat cambiacamara;
	GLint L = 0;
	GLfloat anguloL = 0.0f;



	GLfloat movTotoro;
	GLfloat rotTotoro;
	GLfloat movB1;
	GLfloat movB2;
	GLfloat movP1;
	GLfloat movP2;
	bool movPBTotoro;


	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

