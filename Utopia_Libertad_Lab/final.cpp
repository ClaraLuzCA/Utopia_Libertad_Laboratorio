/*
Animación:
Sesión 1:
Simple o básica:Por banderas y condicionales (más de 1 transformación geométrica se ve modificada
Sesión 2
Compleja: Por medio de funciones y algoritmos.
Textura Animada
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"

#include "Texture.h"

#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//variables para animación

//skybox
float timer_skybox = 0.0f;

//Totoro
float rotTotoro;
float movOffsetTotoro;
float movBrazos;
float movBrazos2;
float movOffsetBrazos;
float movPies;
float movOffsetPies;
bool BanderaPIzq;
bool BanderaPDer;
float movPizq;
float movOffsetPIzq;
float movPDer;
float movOffsetPDer;

bool BanderaBrazos;
bool BanderaBrazos2;
bool BanderaPatas;


bool BanderaSinCara;
float movSinCara;
float movOffsetSinCara;
float rotSinCara;


float movCoche;
float movOffset;
float movHeli;
float movHeliOffset;
float rotllanta;
float rotllantaOffset;
bool avanza;
bool avanzaHeli;
float toffsetflechau = 0.0f;
float toffsetflechav = 0.0f;
float toffsetnumerou = 0.0f;
float toffsetnumerov = 0.0f;
float toffsetnumerocambiau = 0.0;
float angulovaria = 0.0f;


//animacion de heli
float heliAngle;
float heliOffset;
bool vuelta3;

//movimiento del globo 

float dHeight = 80.0f;
float dSpeed = 0.1f; // Velocidad de elevación/descenso
bool goingUp = true;

//Animacion Letras
float rot;
float rotOffset;
bool gira;

//planeta
float estatuaAngle1;
float estatuaOffset1;
bool vuelta1;



//animacion
float globoAngle;
float globoOffset;
bool  gl = true;

//estatua
float estatuaAngle;
float estatuaOffset;
bool vuelta;


//para la elise
float angularSpeed = 30.0f;
float angle = 0.0f;

//animacion de calcifer
bool BanderaCalcifer;
float creceCalcifer;
float creceOffset;
float rotCalcifer;

//animacion
bool Car;
float movCar;
float movOffsetCar;
float rotCar;

//animacion 
float movizqOffset;
float movizq;
bool contador;
bool pizquierda;

//animacion
float angulo_h;
float angulo_h_offset;
float mueve_h;
float mueve_h_offset;
bool avanza_h;
float mueve_h_X;
float gira_h;
bool vuelve_h_Z;




Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

//CAMARAS
Camera camera;

glm::mat4 camRot(1.0);
glm::vec3 camPos(0.0f);


//textura
Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture FlechaTexture;
Texture NumerosTexture;
Texture Numero1Texture;
Texture Numero2Texture;



Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;


Model Avion;
Model Aspa;
Model Carro;
Model Picnic;


Model Cuerpo_Totoro;
Model Brazo_Derecho_Totoro;
Model Brazo_Izquierda_Totoro;
Model Pata_Derecho_Totoro;
Model Pata_Izquierda_Totoro;

Skybox skybox_dia;
Skybox skybox_noche;





//aerostatico
Model aerostatico;
Model elise;

//modelo helicoptero
Model heli;
Model eliHeli;
Model eliHelia;



//flora
Model Momo;
Model antorha;
Model Pt;


Model tronco;
Model arbol;
Model Arbusto;
Model Hongo;
Model arb3;
Model arbol4;



//fauna
Model Heibai;
Model aang;
Model Bolita;
Model p1;
Model p2;



//Decoración
Model Lampara;
Model Corral;
Model Planeta;
Model Bancas;
Model antorcha;
Model Nafuego;
Model Naaire;
Model Natierra;
Model Naagua;



//edificios

Model T_Tierra;
Model Fuego;
Model Casa;
Model granja;
Model Domo;
Model Molino;

//calcifer y roca
Model Calcifer;
Model SinCara;
Model Roca;


Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight

PointLight pointLights[MAX_POINT_LIGHTS];
PointLight pointLights2[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";
// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};
	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};


	unsigned int flechaIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat flechaVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int scoreIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat scoreVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int numeroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat numeroVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		0.25f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		0.25f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(flechaVertices, flechaIndices, 32, 6);
	meshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(scoreVertices, scoreIndices, 32, 6);
	meshList.push_back(obj6);

	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(numeroVertices, numeroIndices, 32, 6);
	meshList.push_back(obj7);

}



void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}




int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/pasto.jpeg");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	FlechaTexture = Texture("Textures/flechas.tga");
	FlechaTexture.LoadTextureA();
	NumerosTexture = Texture("Textures/numerosbase.tga");
	NumerosTexture.LoadTextureA();
	Numero1Texture = Texture("Textures/numero1.tga");
	Numero1Texture.LoadTextureA();
	Numero2Texture = Texture("Textures/numero2.tga");
	Numero2Texture.LoadTextureA();



	

	//MODELOS

	//Totoro
	Cuerpo_Totoro = Model();
	Cuerpo_Totoro.LoadModel("Models/Cuerpo_Totoro.obj");
	Brazo_Derecho_Totoro = Model();
	Brazo_Derecho_Totoro.LoadModel("Models/Brazo_Derecho_Totoro.obj");
	Brazo_Izquierda_Totoro = Model();
	Brazo_Izquierda_Totoro.LoadModel("Models/Brazo_Izquierdo_Totoro.obj");
	Pata_Derecho_Totoro = Model();
	Pata_Derecho_Totoro.LoadModel("Models/Pata_Derecha_Totoro.obj");
	Pata_Izquierda_Totoro = Model();
	Pata_Izquierda_Totoro.LoadModel("Models/Pata_Izquierda_Totoro.obj");



	//MODELOS

	Calcifer = Model();
	Calcifer.LoadModel("Models/calcifer.obj");
	Roca = Model();
	Roca.LoadModel("Models/roca.obj");
	SinCara = Model();
	SinCara.LoadModel("Models/sin_cara.obj");



	Avion = Model();
	Avion.LoadModel("Models/Avion.obj");
	Aspa = Model();
	Aspa.LoadModel("Models/Aspa.obj");

	T_Tierra = Model();
	T_Tierra.LoadModel("Models/templo_de_tierra.obj");

	Fuego = Model();
	Fuego.LoadModel("Models/fuego.obj");

	Momo = Model();
	Momo.LoadModel("Models/momo.obj");

	tronco = Model();
	tronco.LoadModel("Models/tronco.obj");

	antorcha = Model();
	antorcha.LoadModel("Models/antorcha.obj");
	
	aerostatico = Model();

	aerostatico.LoadModel("Models/aerostatico_sin_elise.obj");

	elise = Model();
	elise.LoadModel("Models/elise.obj");

	aerostatico.LoadModel("Models/aerostatico.obj");


	arbol = Model();
	arbol.LoadModel("Models/11.obj");

	aang = Model();
	aang.LoadModel("Models/estatuaa.obj");

	Heibai = Model();
	Heibai.LoadModel("Models/heibai.obj");

	Lampara = Model();
	Lampara.LoadModel("Models/Lampara.obj");

	Corral = Model();
	Corral.LoadModel("Models/corral.obj");
	
	Planeta = Model();
	Planeta.LoadModel("Models/Planeta.obj");

	Picnic = Model();
	Picnic.LoadModel("Models/picnic.obj");

	Hongo = Model();
	Hongo.LoadModel("Models/hongo.obj");

	Bolita = Model();
	Bolita.LoadModel("Models/Bola.obj");

	p1 = Model();
	p1.LoadModel("Models/P1.obj");

	p2 = Model();
	p2.LoadModel("Models/P2.obj");


	Arbusto = Model();
	Arbusto.LoadModel("Models/arbusto.obj");

	Molino = Model();
	Molino.LoadModel("Models/Molino2.obj");

	Carro = Model();
	Carro.LoadModel("Models/Carro.obj");

	Casa = Model();
	Casa.LoadModel("Models/Casa_Totoro.obj");

	granja = Model();
	granja.LoadModel("Models/granja.obj");

	//modelos new
	arb3 = Model();
	arb3.LoadModel("Models/arbol3.obj");

	arbol4 = Model();
	arbol4.LoadModel("Models/arb4.obj");

	Nafuego = Model();
	Nafuego.LoadModel("Models/Nfuego.obj");

	Naaire = Model();
	Naaire.LoadModel("Models/Naire.obj");

	Natierra = Model();
	Natierra.LoadModel("Models/Ntierra.obj");

	Naagua = Model();
	Naagua.LoadModel("Models/Nagua.obj");


	Pt = Model();
	Pt.LoadModel("Models/PT2.obj");

	heli = Model();
	heli.LoadModel("Models/Heli.obj");

	eliHeli = Model();
	eliHeli.LoadModel("Models/eliseHeli.obj");

	eliHelia = Model();
	eliHelia.LoadModel("Models/eliseHelia.obj");




	/*

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);*/

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox_Dia/dia_1.jpg");
	skyboxFaces.push_back("Textures/Skybox_Dia/dia_3.jpg");
	skyboxFaces.push_back("Textures/Skybox_Dia/dia_down.jpg");
	skyboxFaces.push_back("Textures/Skybox_Dia/dia_up.jpg");
	skyboxFaces.push_back("Textures/Skybox_Dia/dia_4.jpg");
	skyboxFaces.push_back("Textures/Skybox_Dia/dia_2.jpg");

	skybox_dia = Skybox(skyboxFaces);

	std::vector<std::string> skyboxFaces2;

	skyboxFaces2.push_back("Textures/Skybox_Noche/noche_1.jpg");
	skyboxFaces2.push_back("Textures/Skybox_Noche/noche_3.jpg");
	skyboxFaces2.push_back("Textures/Skybox_Noche/noche_down.jpg");

	skyboxFaces2.push_back("Textures/Skybox_Noche/noche_up.jpg");

	skyboxFaces2.push_back("Textures/Skybox_Noche/noche_down.jpg");

	skyboxFaces2.push_back("Textures/Skybox_Noche/noche_4.jpg");
	skyboxFaces2.push_back("Textures/Skybox_Noche/noche_2.jpg");

	skybox_noche = Skybox(skyboxFaces2);


	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir

	/*mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.6f, 0.6f,
		0.0f, 0.0f, -1.0f);*/

	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	unsigned int pointLightCount2 = 0;
	unsigned int pointLightCount3 = 0;




	
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		1.0f, 130.0f,
		-10.0f, -1.5f, -99.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights2[0] = PointLight(0.0f, 0.0f, 0.0f,
		1.0f, 130.0f,
		-10.0f, -1.5f, -99.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount2++;


	
	// luz puntual
	pointLights[1] = PointLight(1.0f, 1.0f, 1.0f,
		1.0f, 130.0f,
		-107.0f, -12.0f, -25.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	//templo fuego 
	pointLights[2] = PointLight(1.0f, 0.0f, 0.0f,
		1.0f, 130.0f,
		120.0f, -3.5f, 70.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;







	unsigned int spotLightCount = 0;
	//luz nave
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		30.0f, 10.0f,
		-103.0f, -1.5f, 10.0f,
		0.0f, -1.0f, 0.0f,
		0.02f, 0.2f, 0.05f,
		15.0f);
	spotLightCount++;

	
	//luz avión
	spotLights[1] = SpotLight(1.0f, 0.0f, 1.0f,
		35.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.02f, 0.2f, 0.05f,
		30.0f);
	spotLightCount++;

	spotLights[2] = SpotLight(0.0f, 1.0f, 1.0f,
		35.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.02f, 0.2f, 0.05f,
		30.0f);
	spotLightCount++;


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
	uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);


	// animaciones 


	movCoche = 0.0f;
	movOffset = 0.3f;//velocidad del carro
	rotllanta = 0.0f;
	rotllantaOffset = 10.0f;
	avanza = true;
	movHeli = 0.0f;
	movHeliOffset = 10.0f;
	avanzaHeli = true;

	//animaciones de vuelta 
	rot = 0.0f;
	rotOffset = 0.5;
	gira = true;



	//planeta 
	estatuaAngle1 = 0.0f;
	estatuaOffset1 = 0.0f;

	
	//Estatua

	estatuaAngle = 0.0f;
	estatuaOffset = 0.9f;

	//aerostatico

	globoAngle = 0.0f;
	globoOffset = 50.0f;

	//animacion 
	heliAngle = 0.0f;
	heliOffset = 1.0f;

	//
	movizq = 0.0f;
	movizqOffset = 0.06;






	movBrazos = 0.0f;
	movBrazos2 = 50.0f;
	rotTotoro = 0.0f;
	movPies = 0.0f;
	BanderaBrazos = true;
	BanderaBrazos2 = true;
	BanderaPatas = true;
	movOffsetBrazos = 0.3f;
	movOffsetPDer = 0.3f;
	movOffsetPIzq = 0.3f;
	BanderaPDer = true;
	BanderaPIzq = true;

	BanderaSinCara = true;
	movOffsetSinCara = 0.3f;
	movSinCara = 0.0f;
	rotSinCara = 0.0f;

	BanderaCalcifer = true;
	creceCalcifer = 0.0f;
	creceOffset = 0.3f;
	rotCalcifer = 0.0f;


	//animacion
	angulo_h = 0.0f;
	angulo_h_offset = 5.0f;
	mueve_h = 0.0f;
	mueve_h_offset = 0.8f;
	avanza_h = true;
	gira_h = 0.0f;
	mueve_h_X = 0.0f;
	vuelve_h_Z = true;






	
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		timer_skybox += deltaTime;

		angulovaria += 0.5f*deltaTime;

		

		//animacion
		if (mueve_h < 250 && avanza_h == true && vuelve_h_Z == true) {

			mueve_h += mueve_h_offset * deltaTime;
			angulo_h += angulo_h_offset * deltaTime;
		}
		else
		{
			avanza_h = false;
			if (mueve_h_X > -200 && avanza_h == false && vuelve_h_Z == true) {
				gira_h = -90;
				mueve_h_X -= mueve_h_offset * deltaTime;
				angulo_h += angulo_h_offset * deltaTime;
			}
			else
			{
				vuelve_h_Z = false;
				if (mueve_h > 10 && avanza_h == false && vuelve_h_Z == false) {
					gira_h = 180;
					mueve_h -= mueve_h_offset * deltaTime;
					angulo_h += angulo_h_offset * deltaTime;
				}
				else
				{
					if (mueve_h_X < 0 && avanza_h == false && vuelve_h_Z == false) {
						gira_h = -160;
						mueve_h_X += mueve_h_offset * deltaTime;
						angulo_h += angulo_h_offset * deltaTime;
					}
					else
					{
						avanza_h = true;
						vuelve_h_Z = true;
						gira_h = 0.0;
					}

				}

			}
		}


		//puerta izquierda 

		if (pizquierda)
		{
			//abre
			if (movizq > -3.0f)
			{
				movizq -= movizqOffset * deltaTime;
			}
			else if (contador % 4 == 0)
			{
				pizquierda = false;
			}
		}
		else
		{
			//cierre
			if (movizq < 2.0f)
			{
				movizq += movizqOffset * deltaTime;
			}
			else if (contador % 4 == 0)
			{
				pizquierda = true;
			}
		}




		/*
		if (avanzaHeli) {
			if (movHeli > -100) {
				movHeli -= 0.05 * movHeliOffset * deltaTime;
			}
			else {
				avanzaHeli = !avanzaHeli;
			}
		}
		else {
			if (movHeli < 100) {
				movHeli += 0.05 * movHeliOffset * deltaTime;
			}
			else {
				avanzaHeli = !avanzaHeli;
			}

		}
		*/

		//animacion heli
		if (vuelta3) {
			if (heliAngle < 360.0f) {  // Cambiado a 360.0f para avanzar hasta una vuelta completa
				heliAngle += heliOffset * deltaTime;
			}
			else {
				heliAngle = 0.0f;  // Reiniciado a 0.0f para iniciar una nueva vuelta
			}
		}
		else {
			if (heliAngle > 0.0f) {
				heliAngle -= heliOffset * deltaTime;
			}
			else {
				heliAngle = 360.0f;  // Reiniciado a 360.0f para iniciar una nueva vuelta
			}
		}




		//animacion del planeta
		rot += rotOffset * deltaTime;



		//animacion de vuelta del planeta
		if (vuelta1) {
			if (estatuaAngle1 > 0.0f) {
				estatuaAngle1 -= estatuaOffset * deltaTime;
			}
			else {
				vuelta = false;
			}
		}
		else {
			if (estatuaAngle1 < 370.0f) {
				estatuaAngle1 += estatuaOffset1 * deltaTime;
			}
			else {
				vuelta1 = true;
			}
		}




		//estatua

		if (vuelta) {
			if (estatuaAngle > 0.0f) {
				estatuaAngle -= estatuaOffset * deltaTime;
			}
			else {
				vuelta = false;
			}
		}
		else {
			if (estatuaAngle < 370.0f) {
				estatuaAngle += estatuaOffset * deltaTime;
			}
			else {
				vuelta = true;
			}
		}



		//movimiento del globo aerostatico 

		if (goingUp) {
			// Si está subiendo y no ha alcanzado la altura máxima
			if (dHeight < 80.0f) {
				dHeight += dSpeed * deltaTime;
			}
			else {
				// Cambiar de dirección cuando alcanza la altura máxima
				goingUp = false;
			}
		}
		else {
			// Si está bajando y no ha alcanzado la altura mínima
			if (dHeight > 0.0f) {
				dHeight -= dSpeed * deltaTime;
			}
			else {
				// Cambiar de dirección cuando alcanza la altura mínima
				goingUp = true;
			}
		}

	

		//movimiento de la elise del avion 

		if (vuelta) {
			if (estatuaAngle > 0.0f) {
				estatuaAngle -= estatuaOffset * deltaTime;
			}
			else {
				vuelta = false;
			}
		}
		else {
			if (estatuaAngle < 370.0f) {
				estatuaAngle += estatuaOffset * deltaTime;
			}
			else {
				vuelta = true;
			}
		}




		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox_noche.DrawSkybox(camera.calculateViewMatrix(), projection);

		if (timer_skybox < 500.0f) {
			skybox_dia.DrawSkybox(camera.calculateViewMatrix(), projection);

			mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
				0.6f, 0.6f,
				0.0f, 0.0f, -1.0f);

		}
		else {
			if (timer_skybox < 1000.0f) {
				skybox_noche.DrawSkybox(camera.calculateViewMatrix(), projection);

				mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
					0.25f, 0.3f,
					0.0f, 0.0f, -1.0f);
			}
			else {
				timer_skybox = 0;
			}

		}

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		//spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());
		spotLights[0].SetPos(glm::vec3(120.0f, 30.5f, 37.5f)); //aerostático
		spotLights[1].SetPos(glm::vec3(-10.5f, 34.5f,70.0f)); //lampara fuego
		spotLights[2].SetPos(glm::vec3(-103.0f, 34.5f, 10.0f)); //lampara planetario
		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);


		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 modelauxTotoro(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));

		pisoTexture.UseTexture();
		//Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		//meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//TOTORO*************************************************************************


		//animación brazos y patas
		if (BanderaBrazos) {
			if (movBrazos > -50.0) {
				movBrazos -= 3.0 * movOffsetBrazos * deltaTime;


			}
			else {
				BanderaBrazos = !BanderaBrazos;
			}

		}
		else {
			if (movBrazos < 0.0) {
				movBrazos += 3.0 * movOffsetBrazos * deltaTime;
			}
			else {
				BanderaBrazos = !BanderaBrazos;
			}
		}

		if (BanderaBrazos2) {
			if (movBrazos2 > -50.0) {
				movBrazos2 -= 3.0 * movOffsetBrazos * deltaTime;
			}
			else {
				BanderaBrazos2 = !BanderaBrazos2;
			}


		}
		else {
			if (movBrazos2 < 0.0) {
				movBrazos2 += 3.0 * movOffsetBrazos * deltaTime;


			}
			else {
				BanderaBrazos2 = !BanderaBrazos2;
			}
		}



		//TOTORO
		//Cuerpo
		model = glm::mat4(1.0);

		model = glm::rotate(model, mainWindow.getrotaTototo() * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mainWindow.getmueveTototo() + 0.0f));

		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		modelauxTotoro = model;
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cuerpo_Totoro.RenderModel();

		//Pata Izquierda
		model = modelauxTotoro;
		model = glm::translate(model, glm::vec3(5.0, 0.0f, 0.5f));
		model = glm::rotate(model, movBrazos * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pata_Izquierda_Totoro.RenderModel();

		//Pata Derecha
		model = modelauxTotoro;
		model = glm::translate(model, glm::vec3(-7.0, 0.0f, 0.5f));
		model = glm::rotate(model, movBrazos2 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pata_Derecho_Totoro.RenderModel();

		//Brazo derecho
		model = modelauxTotoro;
		model = glm::translate(model, glm::vec3(-14.5, 40.0f, 0.5f));
		model = glm::rotate(model, movBrazos * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Brazo_Derecho_Totoro.RenderModel();

		//Brazo Izquierdi
		model = modelauxTotoro;
		model = glm::translate(model, glm::vec3(11.0, 40.0f, 0.5f));
		model = glm::rotate(model, movBrazos2 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Brazo_Izquierda_Totoro.RenderModel();


		//Vehículos **********************************************************
		
		//Avión 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-160.5f, 150.5f, 40.5f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Avion.RenderModel();

		//Aspa
		model = modelaux;
		model = glm::translate(model, glm::vec3(-158.5f, 150.5f, 18.5f));
		model = glm::rotate(model, estatuaAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aspa.RenderModel();

		// Carrito 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(250.0f + mueve_h_X, -2.0f, 25.0f + mueve_h));
		//model = glm::translate(model, glm::vec3(-120.0f, -2.0f, 170.0f));
		//model = glm::translate(model, glm::vec3(-170 + movca, -2.0f, 170.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, gira_h * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Carro.RenderModel();

		//aerostatico 3
		model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(6.0f, dHeight, -5.0f));
		//model = glm::translate(model, glm::vec3(25.5f, 50.5f, 37.5f));
		model = glm::translate(model, glm::vec3(120.0f, dHeight, 75.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, globoAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		aerostatico.RenderModel();


		model = modelaux;
		model = glm::translate(model, glm::vec3(120.0f, dHeight, 75.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, estatuaAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, globoAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		elise.RenderModel();

		//helicoptero y elise
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(heliAngle, 70.5f, -5.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, heliAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.1f, 5.1f, 5.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		heli.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(heliAngle, 70.5f, -5.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.1f, 5.1f, 5.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		eliHeli.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(heliAngle, 70.5f, -5.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.1f, 5.1f, 5.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		eliHelia.RenderModel();






		//Decoración ********************************************************* 

		//Lampara 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-103.0f, -1.5f, 10.0f));
		pointLights[0];
		model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara.RenderModel();

		//lampara casa de totoro
		model = modelaux;
		model = glm::translate(model, glm::vec3(-10.0f, -1.5f, -100.0f));
		model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara.RenderModel();
		
		//lampara abajo del templo del fuego 

		model = modelaux;
		model = glm::translate(model, glm::vec3(-10.0f, -1.6f, 70.0f));

		model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(45.0f, -1.6f, -100.0f));

		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara.RenderModel();


		//Corral  2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(120.0f, 0.4f, -60.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 3.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Corral.RenderModel();

		//Planeta  3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-106.0f, 8.0f, -25.0f));
		model = glm::rotate(model, rot * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Planeta.RenderModel();

		//Banca  4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 2.0f, 89.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Picnic.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(75.0f, 2.0f, 89.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Picnic.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(90.0f, 2.0f, 110.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Picnic.RenderModel();


		//Torre 5
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-45.0f, -2.2f, 9.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Molino.RenderModel();

		//antorcha

		//antorcha para el templo tierra


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.5f, -2.0f, -105.5f));

		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));//Primero acostado , segundo caras , tercero inclinado	
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		antorcha.RenderModel();


		model = modelaux;
		model = glm::translate(model, glm::vec3(36.0f, -2.0f, -105.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));	
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		antorcha.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(15.0f, -2.0f, -105.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		antorcha.RenderModel();

		model = modelaux;

		model = glm::translate(model, glm::vec3(8.0f, -2.0f, -105.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		antorcha.RenderModel();


		//bandera de la nacion del fuego 

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(47.0f, -2.0f, 78.0f));	
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Nafuego.RenderModel();

		//bandera de la nacion del aire 

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(57.0f, -2.0f, 78.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Naaire.RenderModel();

		//bandera de la nacion de tierra

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(67.0f, -2.0f, 78.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Natierra.RenderModel();

		//bandera de la nacion del agua

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(77.0f, -2.0f, 78.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Naagua.RenderModel();


		if (BanderaCalcifer) {
			if (creceCalcifer > -0.1) {
				creceCalcifer -= 0.01 * creceOffset * deltaTime;
				rotCalcifer += 1.0;
			}
			else {
				BanderaCalcifer = !BanderaCalcifer;
			}
		}
		else {
			if (creceCalcifer < 1.0) {
				creceCalcifer += 0.01 * creceOffset * deltaTime;
				rotCalcifer += 1.0;
			}
			else {
				BanderaCalcifer = !BanderaCalcifer;
			}
		}

		//Calcifer
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(120.0f, -1.0f, 70.0f));
		model = glm::rotate(model, (rotCalcifer) * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(creceCalcifer, creceCalcifer, creceCalcifer));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Calcifer.RenderModel();

		//roca
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, -2.0f, 40.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Roca.RenderModel();

		//sin cara
		if (BanderaSinCara) {
			if (movSinCara>-200.0) {
				movSinCara -= 1.0 * movOffsetSinCara * deltaTime;
				rotSinCara = 90.0;
			}
			else {
				BanderaSinCara = !BanderaSinCara;
			}
		}
		else {
			if (movSinCara < 0.0) {
				movSinCara += 1.0 * movOffsetSinCara * deltaTime;
				rotSinCara = 180.0;
			}
			else {
				BanderaSinCara = !BanderaSinCara;
			}
		}

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(110.0f+movSinCara, 2.0f, 20.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, rotSinCara, glm::vec3(0.0f, -1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SinCara.RenderModel();


		//Fauna ****************************************************************

		//Bolita 1
		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(150.0f, 2.0f, -20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bolita.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(150.0f, 2.5f, -20.0f));
		model = glm::rotate(model, movizq * toRadians, glm::vec3(1.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		p1.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(150.0f, 2.5f, -20.0f));
		model = glm::rotate(model, movizq * toRadians, glm::vec3(1.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		p2.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(140.0f, 2.0f, -20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bolita.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(140.0f, 2.5f, -20.0f));
		model = glm::rotate(model, movizq * toRadians, glm::vec3(1.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		p1.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(140.0f, 2.5f, -20.0f));
		model = glm::rotate(model, movizq * toRadians, glm::vec3(1.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		p2.RenderModel();



		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(160.0f, 2.0f, -30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bolita.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(160.0f, 2.5f, -30.0f));
		model = glm::rotate(model, movizq * toRadians, glm::vec3(1.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		p1.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(160.0f, 2.5f, -30.0f));
		model = glm::rotate(model, movizq * toRadians, glm::vec3(1.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		p2.RenderModel();


		//heibai
		model = glm::mat4(1.0);	
		model = glm::translate(model, glm::vec3(180.0f, -2.0f, -70.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));	
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));	
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));	
		Heibai.RenderModel();	

		//momo
		model = glm::mat4(1.0);	

		model = glm::translate(model, glm::vec3(160.0f, -2.0f, -80.0f));

		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));	
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));	
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));	
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));	
		Momo.RenderModel();	


		//aang
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(19.0f, -2.0f, 78.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, estatuaAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		aang.RenderModel();

		//personaje tierra
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(22.0f, -2.0f, -110.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		//model = glm::rotate(model, estatuaAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Pt.RenderModel();


		//Flora ****************************************************************

		//Hongo 1

		//hongo cerca de momo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(95.0f, 0.0f, 60.0f));

		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hongo.RenderModel();

		//hongo cerca de momo
		model = modelaux;
		model = glm::translate(model, glm::vec3(80.0f, 0.0f, 125.0f));

		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hongo.RenderModel();

		//hongo cerca de la casa de totoro

		
		model = modelaux;	
		model = glm::translate(model, glm::vec3(60.0f, 0.0f, 100.0f));

		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));	
		Hongo.RenderModel();	



		//arbusto 2

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(60.0f, 0.0f, 40.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto.RenderModel();

		//tronco 3

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(33.5f, -2.0f, 25.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		tronco.RenderModel();

		//pino

		//cerca de la lamparra del principio

		model = glm::mat4(1.0);	
		model = glm::translate(model, glm::vec3(-100.5f, -2.0f, -78.0f));	
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));	
		model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));	
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));	
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));	
		arbol.RenderModel();

		model = modelaux;	
		model = glm::translate(model, glm::vec3(-105.5f, -2.0f, -80.5f));	
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));	
		model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));	
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));	

		glUniform3fv(uniformColor, 1, glm::value_ptr(color));	

		arbol.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-98.5f, -40.0f, -5.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol.RenderModel();

		//arbol 2



		//cerca de la lampara donde esta momo y el templo del fuego

		model = modelaux;
		model = glm::translate(model, glm::vec3(-80.5f, -2.0f, 70.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-85.5f, -2.0f, 65.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.08f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-70.5f, -2.0f, 75.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol.RenderModel();


		//pino cerca de la casa de totoro

		model = modelaux;
		model = glm::translate(model, glm::vec3(-90.5f, -2.0f, -49.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		arbol.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-70.5f, -2.0f, -42.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-76.5f, -2.0f, -45.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-67.5f, -2.0f, -52.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol.RenderModel();

		//PINO ABAJO DE LA CASA DE TOTORO

		model = modelaux;
		model = glm::translate(model, glm::vec3(-12.5f, -2.0f, -52.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol.RenderModel();

		//PINO CERCA DEL TEMPLO DEL FUEGO ABAJO 

		model = modelaux;
		model = glm::translate(model, glm::vec3(1.5f, -2.0f, 70.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		arbol.RenderModel();

		//pino cerca del avatar 

		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.0f, -2.0f, 77.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-8.0f, -2.0f, 76.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol.RenderModel();

		//arbol3

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 0.0f, 60.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arb3.RenderModel();


		//arbol4

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, -2.0f, 79.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol4.RenderModel();


		//Edificio *************************************************************	

		//templo tierra


		model = glm::mat4(1.0);	
		model = glm::translate(model, glm::vec3(25.0f, -2.0f, -120.5f));	
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));	
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));	
		T_Tierra.RenderModel();	

		//templo fuego

		model = glm::mat4(1.0);	
		model = glm::translate(model, glm::vec3(-45.5f, -2.0f, 104.5f));	
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));	
		model = glm::scale(model, glm::vec3(0.15f, 0.25f, 0.15f));	
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));	
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));	
		Fuego.RenderModel();	

		//casa totoro
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-125.5f, -25.0f, 208.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casa.RenderModel();


		//granja

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(84.0f, -2.0f, -45.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		granja.RenderModel();


		//Avatar ***************************************************************



		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();




		glDisable(GL_BLEND);

		//



		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
