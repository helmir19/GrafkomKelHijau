#pragma once
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>

class Demo :
	public RenderEngine
{
public:
	Demo();
	~Demo();
private:
	GLuint shaderProgram, VBO, VAO, EBO, texture, VBO2, VAO2, EBO2, texture2, VBO3, VAO3, EBO3, texture3, VBO4, VAO4, EBO4, texture4,
		VBO5, VAO5, EBO5, texture5, VBO6, VAO6, EBO6, texture6, VBO7, VAO7, EBO7, texture7, VBOll, VAOll, EBOll, texturell,
		VBOlr, VAOlr, EBOlr, texturelr;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow* window);
	void BuildColoredTempatTidur();
	void BuildColoredKasur();
	void BuildColoredSandaran();
	void BuildColoredPlane();
	void BuildColoredTembok();
	void BuildColoredLemari();
	void BuildColoredLemariKanan();
	void BuildColoredLemariKiri();
	void BuildColoredLaci();
	void DrawColoredTembok();
	void DrawColoredTempatTidur();
	void DrawColoredLemari();
	void DrawColoredLemariKanan();
	void DrawColoredLemariKiri();
	void DrawColoredLaci();
	void DrawColoredPlane();
	void DrawColoredKasur();
	void DrawColoredSandaran();
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();
};

