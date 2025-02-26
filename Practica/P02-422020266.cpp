//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá
static const char* vShaderVerde = "shaders/shaderVerde.vert";
static const char* vShaderAzul = "shaders/shaderAzul.vert";
static const char* vShaderVerdeOscuro = "shaders/shaderVerdeOscuro.vert";
static const char* vShaderRojo = "shaders/shaderRojo.vert";
static const char* vShaderCafe = "shaders/shaderCafe.vert";


float angulo = 0.0f;

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-1.0f, -1.0f,0.0f,	//0
		1.0f,-1.0f,0.0f,	//1
		0.0f,1.0f, -0.5f,	//2
		0.0f,-1.0f,-1.0f,	//3

		/*
		//ORIGINAL
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3
		*/

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
	
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	//ÍNDICE 0
	GLfloat vertices_letras[] = {	
		//X			Y			Z			R		G		B

		//letra "C"		   //Nodos con respecto al mapa de la letra
		-0.9f,	0.9f,		0.0f,			0.45098f,	0.76862f,	0.764705f,//A
		-0.37f, 0.9f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //B
		-0.9f, 0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //C

		-0.37f, 0.9f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //B
		-0.9f, 0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //C
		-0.37f, 0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //P

		-0.9f, 0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //C
		-0.8f, 0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //D
		-0.9f, -0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //H

		-0.8f, 0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //D
		-0.9f, -0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //H
		-0.8f, -0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //J

		-0.9f, -0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //H
		-0.9f, -0.9f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //I
		-0.37f, -0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //N

		-0.9f, -0.9f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //I
		-0.37f, -0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //N
		-0.37f, -0.9f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //O

		-0.47f, 0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //E
		-0.47f, 0.35f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //F
		-0.37f, 0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //P

		-0.37f, 0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //P
		-0.37f, 0.35f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //G
		-0.47f, 0.35f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //F

		-0.47f, -0.35f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //K
		-0.47f, -0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //L
		-0.37f, -0.35f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //M

		-0.37f, -0.35f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //M
		-0.37f, -0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //N
		-0.47f, -0.55f,		0.0f,			0.45098f,	0.76862f,	0.764705f, //L

		//letra "Y"
		-0.27f, 0.8f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //A
		-0.1625f, 0.9f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //B
		-0.055f, 0.2f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //D

		-0.1625f, 0.9f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //B
		-0.005f, 0.5f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //C
		-0.055f, 0.2f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //D

		-0.005f, 0.5f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //C
		0.1525f, 0.9f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //F
		0.045f, 0.2f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //E

		0.1525f, 0.9f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //F
		0.26f, 0.8f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //G
		0.045f, 0.2f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //E

		-0.005f, 0.5f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //C
		-0.055f, 0.2f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //D
		0.045f, 0.2f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //E

		-0.055f, 0.2f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //D
		-0.055f, -0.9f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //H
		0.045f, 0.2f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //E

		0.045f, 0.2f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //E
		0.045f, -0.9f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //I
		-0.055f, -0.9f,		0.0f,			0.32549f,	0.568627f,	0.874098f, //H

		//letra "V"
		0.37f, 0.8f,		0.0f,			0.286274f,	0.282352f,	0.482352f, //A
		0.635f, -0.5f,		0.0f,			0.286274f,	0.282352f,	0.482352f, //D
		0.585f, -0.9f,		0.0f,			0.286274f,	0.282352f,	0.482352f, //C

		0.37f, 0.8f,		0.0f,			0.286274f,	0.282352f,	0.482352f, //A
		0.4775f, 0.9f,		0.0f,			0.286274f,	0.282352f,	0.482352f, //B
		0.635f, -0.5f,		0.0f,			0.286274f,	0.282352f,	0.482352f, //D

		0.635f, -0.5f,		0.0f,			0.286274f,	0.282352f,	0.482352f, //D
		0.7925f, 0.9f,		0.0f,			0.286274f,	0.282352f,	0.482352f, //F
		0.9f, 0.8f,			0.0f,			0.286274f,	0.282352f,	0.482352f, //G

		0.635f, -0.5f,		0.0f,			0.286274f,	0.282352f,	0.482352f, //D
		0.9f, 0.8f,			0.0f,			0.286274f,	0.282352f,	0.482352f, //G
		0.685f, -0.9f,		0.0f,			0.286274f,	0.282352f,	0.482352f, //E

		0.635f, -0.5f,		0.0f,			0.286274f,	0.282352f,	0.482352f, //D
		0.585f, -0.9f,		0.0f,			0.286274f,	0.282352f,	0.482352f, //C
		0.685f, -0.9f,		0.0f,			0.286274f,	0.282352f,	0.482352f //E
	
	};

	MeshColor *letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras,396);
	meshColorList.push_back(letras);

	//ÍNDICE 1
	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		
	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);

	//ÍNDICE 2
	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);

	//ÍNDICE 3
	GLfloat vertices_trianguloAzul[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,

	};

	MeshColor* trianguloAzul = new MeshColor();
	trianguloAzul->CreateMeshColor(vertices_trianguloAzul, 18);
	meshColorList.push_back(trianguloAzul);

	//ÍNDICE 4
	GLfloat vertices_trianguloVerde[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.5f,	0.0f,

	};

	MeshColor* trianguloVerde = new MeshColor();
	trianguloVerde->CreateMeshColor(vertices_trianguloVerde, 18);
	meshColorList.push_back(trianguloVerde);

	//ÍNDICE 5
	GLfloat vertices_cuadradoRojo[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* cuadradoRojo = new MeshColor();
	cuadradoRojo->CreateMeshColor(vertices_cuadradoRojo, 36);
	meshColorList.push_back(cuadradoRojo);

	//ÍNDICE 6
	GLfloat vertices_cuadradoVerde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoVerde = new MeshColor();
	cuadradoVerde->CreateMeshColor(vertices_cuadradoVerde, 36);
	meshColorList.push_back(cuadradoVerde);

	//ÍNDICE 7
	GLfloat vertices_cuadradoCafe[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,

	};

	MeshColor* cuadradoCafe = new MeshColor();
	cuadradoCafe->CreateMeshColor(vertices_cuadradoCafe, 36);
	meshColorList.push_back(cuadradoCafe);
}


void CreateShaders()
{
	Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	//Color Verde, INDICE 2
	Shader* shader3 = new Shader();
	shader3->CreateFromFiles(vShaderVerde, fShader);
	shaderList.push_back(*shader3);

	//Color Azul, INDICE 3
	Shader* shader4 = new Shader();
	shader4->CreateFromFiles(vShaderAzul, fShader);
	shaderList.push_back(*shader4);

	//Color VerdeOscuro, INDICE 4
	Shader* shader5 = new Shader();
	shader5->CreateFromFiles(vShaderVerdeOscuro, fShader);
	shaderList.push_back(*shader5);

	//Color Rojo, INDICE 5
	Shader* shader6 = new Shader();
	shader6->CreateFromFiles(vShaderRojo, fShader);
	shaderList.push_back(*shader6);

	//Color Cafe, INDICE 6
	Shader* shader7 = new Shader();
	shader7->CreateFromFiles(vShaderCafe, fShader);
	shaderList.push_back(*shader7);

}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
		//PRACTICA 02, ACTIVIDAD 1
		/*
		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		//Letras
		model = glm::mat4(1.0);
		//Lo recorre derecha, izquierda, arriba o abajo
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();
		*/

		//PRACTICA 02, ACTIVIDAD 2
		//Piramide Azul
		shaderList[3].useShader(); 
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, -3.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.3f, 0.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Cubo Rojo
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.3f, -4.0f));
		model = glm::scale(model, glm::vec3(0.85f, 1.2f, 0.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Cubo Verde X1
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.2f, 0.0f, -3.5));
		model = glm::scale(model, glm::vec3(0.25f, 0.35f, 0.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Cubo Verde X2
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.2f, 0.0f, -3.5f));
		model = glm::scale(model, glm::vec3(0.25f, 0.35f, 0.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Cubo Verde X3
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.724f, -3.5f));
		model = glm::scale(model, glm::vec3(0.25f, 0.35f, 0.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Cubo Cafe X1
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.7f, -0.785f, -3.5f));
		model = glm::scale(model, glm::vec3(0.18f, 0.23f, 0.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Cubo Cafe X2
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.7f, -0.785f, -3.5f));
		model = glm::scale(model, glm::vec3(0.18f, 0.23f, 0.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Piramide Verde Oscuro X1
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.7f, -0.4f, -3.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.28f, 0.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Piramide Verde Oscuro X2
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.7f, -0.4f, -3.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.28f, 0.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/