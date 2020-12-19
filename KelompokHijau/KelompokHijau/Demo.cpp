#include "Demo.h"

Demo::Demo() {

}

Demo::~Demo() {
}

void Demo::Init() {

	shaderProgram = BuildShader("vertexShader.vert", "fragmentShader.frag", nullptr);

	BuildColoredTempatTidur();

	BuildColoredKasur();

	BuildColoredSandaran();

	BuildColoredPlane();

	BuildColoredTembok();

	BuildColoredLemari();

	BuildColoredLemariKanan();

	BuildColoredLemariKiri();

	BuildColoredLaci();

	BuildColoredPintuLaci();

	BuildColoredPlafon();

	InitCamera();
}

void Demo::DeInit() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Demo::ProcessInput(GLFWwindow* window) {
	// Fungsi Keluar Program 
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// Fungsi Zoom Kamera
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 40) {
			fovy -= 0.0001f;
		}
	}

	// Input kamera untuk bergerak ke depan, belakang, kanan, kiri 
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}
	// Input kamera untuk ke atas dan bawah
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		posCamY += 0.005f;
		viewCamY += 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		posCamY -= 0.005f;
		viewCamY -= 0.005f;
	}

	// Untuk Update Rotasi kamera
	double mouseX, mouseY;
	double midX = screenWidth / 2;
	double midY = screenHeight / 2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Untuk mendapatkan posisi kursor
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set posisi kursor
	glfwSetCursorPos(window, midX, midY);

	// Untuk mendapatkan arah cursor mouse
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// Percepatan kamera
	viewCamY += angleZ * 2;

	// Untuk membatasi rotasi 
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);

}

void Demo::Update(double deltaTime) {

}

void Demo::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(this->shaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// LookAt kamera 
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	GLint viewLoc = glGetUniformLocation(this->shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// Lighting
	GLint lightPosLoc = glGetUniformLocation(this->shaderProgram, "lightPos");
	glUniform3f(lightPosLoc, 0, 25, 0);
	GLint viewPosLoc = glGetUniformLocation(this->shaderProgram, "viewPos");
	glUniform3f(viewPosLoc, 0, 12, 0);
	GLint lightColorLoc = glGetUniformLocation(this->shaderProgram, "lightColor");
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

	DrawColoredTempatTidur();

	DrawColoredKasur();

	DrawColoredSandaran();

	DrawColoredPlane();

	DrawColoredTembok();

	DrawColoredLemari();

	DrawColoredLemariKanan();

	DrawColoredLemariKiri();

	DrawColoredLaci();

	DrawColoredPintuLaci();

	DrawColoredPlafon();

	glDisable(GL_DEPTH_TEST);

}

// Objek Langit-Langit

void Demo::DrawColoredPlafon()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, texturePF);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 4);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, stexturePF);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 5);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 1.0f);

	glBindVertexArray(VAOPF); 

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredPlafon() {
	
	glGenTextures(1, &texturePF);
	glBindTexture(GL_TEXTURE_2D, texturePF);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("plafon.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexturePF);
	glBindTexture(GL_TEXTURE_2D, stexturePF);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("plafon.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {

		// upper
		15.0f, 25.0f,  15.0f,	0.0f, 0.0f,  0.0f,  1.0f,  0.0f,  // 16
		-15.0f, 25.0f,  15.0f, 1.0f, 0.0f,   0.0f,  1.0f,  0.0f,// 17
		-15.0f, 25.0f, -15.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,// 18
		15.0f, 25.0f, -15.0f,	0.0f, 1.0f,  0.0f,  1.0f,  0.0f,  // 19

	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,	 // top
	};

	glGenVertexArrays(1, &VAOPF);
	glGenBuffers(1, &VBOPF);
	glGenBuffers(1, &EBOPF);
	glBindVertexArray(VAOPF);

	glBindBuffer(GL_ARRAY_BUFFER, VBOPF);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOPF);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	 //define lighting pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/// TEMBOK

void Demo::DrawColoredTembok()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 1.0f);


	glBindVertexArray(VAO3); 

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredTembok() {
	
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("wallRed.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {

		//back
		-15.0f, -0.5f, -15.0f,		0.0f, 0.0f,    0.0f, 1.0f,  0.0f,
		 15.0f, -0.5f, -15.0f,		1.0f, 0.0f,    0.0f, 1.0f,  0.0f,
		 15.0f,  25.0f, -15.0f,     1.0f, 1.0f,	   0.0f, 1.0f,  0.0f,
		-15.0f,  25.0f, -15.0f,     0.0f, 1.0f,	   0.0f, 1.0f,  0.0f,

		// front
		-15.0f, -0.5f, 15.0f,		0.0f, 0.0f,    0.0f, 1.0f,  0.0f,
		15.0f, -0.5f, 15.0f,		1.0f, 0.0f,    0.0f, 1.0f,  0.0f,
		15.0f,  25.0f, 15.0f,		1.0f, 1.0f,    0.0f, 1.0f,  0.0f,
		-15.0f,  25.0f, 15.0f,		0.0f, 1.0f,    0.0f, 1.0f,  0.0f,

		// right
		15.0f,  25.0f,  15.0f,		0.0f, 0.0f,    0.0f, 1.0f,  0.0f,
		15.0f,  25.0f, -15.0f,		1.0f, 0.0f,    0.0f, 1.0f,  0.0f,
		15.0f, -0.5f, -15.0f,		1.0f, 1.0f,    0.0f, 1.0f,  0.0f,
		15.0f, -0.5f,  15.0f,		0.0f, 1.0f,    0.0f, 1.0f,  0.0f,

		// left
		-15.0f, -0.5f, -15.0f,		0.0f, 0.0f,    0.0f, 1.0f,  0.0f,
		-15.0f, -0.5f,  15.0f,		1.0f, 0.0f,    0.0f, 1.0f,  0.0f,
		-15.0f,  25.0f,  15.0f,     1.0f, 1.0f,	   0.0f, 1.0f,  0.0f,
		-15.0f,  25.0f, -15.0f,     0.0f, 1.0f,	   0.0f, 1.0f,  0.0f,


	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,	 // back
		4,  5,  6,  4,  6,  7,   // front
		8,  9,  10,  8,  10,  11,   // right
		12, 14, 13, 12, 15, 14,  // left
	};

	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glGenBuffers(1, &EBO3);
	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define nromal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// TEMPAT TIDUR

void Demo::BuildColoredTempatTidur() {

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("kayu.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("kayu.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {

		// front
		 -8.0f, -0.499f, 13.0f, 0.0f, 0.0f,	 0.0f,  1.0f,  0.0f, 	 // 0
		 -1.0f, -0.499f, 13.0f, 1.0f, 0.0f,	0.0f,  1.0f,  0.0f, 	 // 1
		 -1.0f,  0.5f, 13.0f, 1.0f, 1.0f,	0.0f,  1.0f,  0.0f, 	// 2
		 -8.0f, 0.5f, 13.0f,  0.0f, 1.0f,	0.0f,  1.0f,  0.0f, 	// 3
		
		 // right
		 -1.0f, 0.5f, 13.0f,  0.0f, 0.0f,	 0.0f,  -1.0f,  0.0f,	// 4
		 -1.0f, 0.5f, 4.0f,  1.0f, 0.0f,	 0.0f,  -1.0f,  0.0f,	// 5
		 -1.0f, -0.499f, 4.0f, 1.0f, 1.0f,	 0.0f,  -1.0f,  0.0f,	  // 6
		 -1.0f, -0.5f, 13.0f, 0.0f, 1.0f,	 0.0f,  -1.0f,  0.0f,	// 7
		
		 // back
		 -8.0f,  0.5f,  4.0f, 0.0f, 0.0f,	0.0f,  -1.0f,  0.0f,	// 8
		 -1.0f,  0.5f,  4.0f, 1.0f, 0.0f,	0.0f,  -1.0f,  0.0f,	 // 9
		 -1.0f, -0.499f,  4.0f, 1.0f, 1.0f,	0.0f,  -1.0f,  0.0f,		 // 10
		 -8.0f, -0.499f,  4.0f, 0.0f, 1.0f,	0.0f,  -1.0f,  0.0f,		// 11
		
		 // left
		 -8.0f, 0.5f, 13.0f,  0.0f, 0.0f,	0.0f,  -1.0f,  0.0f,	// 12
		 -8.0f, 0.5f, 4.0f,  1.0f, 0.0f,	0.0f,  -1.0f,  0.0f,	// 13
		 -8.0f, -0.499f, 4.0f, 1.0f, 1.0f,	0.0f,  -1.0f,  0.0f,		// 14
		 -8.0f, -0.499f, 13.0f, 0.0f, 1.0f,	0.0f,  -1.0f,  0.0f,		// 15
		
		 // upper
		 -1.0f, 0.5f,  13.0f, 0.0f, 0.0f,	0.0f,  -1.0f,  0.0f,	 // 16
		 -8.0f, 0.5f,  13.0f, 1.0f, 0.0f,	0.0f,  -1.0f,  0.0f,	// 17
		 -8.0f, 0.5f, 4.0f,  1.0f, 1.0f,	0.0f,  -1.0f,  0.0f,	// 18
		 -1.0f, 0.5f, 4.0f,  0.0f, 1.0f,	0.0f,  -1.0f,  0.0f,	 // 19

		  // bottom
		  -8.0f, -0.499f,  4.0f, 0.0f, 0.0f,	0.0f,  -1.0f,  0.0f,		 // 20
		  -1.0f, -0.499f,  4.0f, 1.0f, 0.0f,	0.0f,  -1.0f,  0.0f,		 // 21
		  -1.0f, -0.499f,  13.0f, 1.0f, 1.0f,	0.0f,  -1.0f,  0.0f,		 // 22
		  -8.0f, -0.499f,  13.0f, 0.0f, 1.0f,	0.0f,  -1.0f,  0.0f,		// 23

	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define texcoord pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredTempatTidur()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 1.0f);

	glBindVertexArray(VAO);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 108, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	
}

void Demo::BuildColoredKasur() { 
	glGenTextures(1, &texture6);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("kasur.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texture6);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("kasur.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {

		// front
		-8.0f, 0.51f, 13.0f,	0.0f, 0.0f, 0.0f,  1.0f,  0.0f,   // 0
		-1.0f, 0.51f, 13.0f,	1.0f, 0.0f, 0.0f,  1.0f,  0.0f,   // 1
		-1.0f, 1.5f,  13.0f,	1.0f, 1.0f, 0.0f,  1.0f,  0.0f,   // 2
		-8.0f, 1.5f,  13.0f,	0.0f, 1.0f, 0.0f,  1.0f,  0.0f,  // 3

		// right
		-1.0f, 1.5f,  13.0f,	0.0f, 0.0f,  0.0f,  -1.0f,  0.0f, // 4
		-1.0f, 1.5f,  4.0f,		1.0f, 0.0f,  0.0f,  -1.0f,  0.0f,  // 5
		-1.0f, 0.51f, 4.0f,		1.0f, 1.0f,  0.0f,  -1.0f,  0.0f,  // 6
		-1.0f, 0.51f, 13.0f,	0.0f, 1.0f,  0.0f,  -1.0f,  0.0f, // 7

		// back
		-8.0f,  1.5f,   4.0f,	0.0f, 0.0f, 0.0f,  -1.0f,  0.0f, // 8
		-1.0f,  1.5f,   4.0f,	1.0f, 0.0f, 0.0f,  -1.0f,  0.0f,  // 9
		-1.0f,  0.51f,  4.0f,	1.0f, 1.0f, 0.0f,  -1.0f,  0.0f,  // 10
		-8.0f,  0.51f,  4.0f,	0.0f, 1.0f, 0.0f,  -1.0f,  0.0f, // 11

		// left
		-8.0f, 1.5f,	13.0f,	0.0f, 0.0f, 0.0f,  -1.0f,  0.0f, // 12
		-8.0f, 1.5f,	4.0f,	1.0f, 0.0f, 0.0f,  -1.0f,  0.0f,  // 13
		-8.0f, 0.51f,	4.0f,	1.0f, 1.0f, 0.0f,  -1.0f,  0.0f,  // 14
		-8.0f, 0.51f,	13.0f,	0.0f, 1.0f, 0.0f,  -1.0f,  0.0f, // 15

		// upper
		-1.0f, 1.5f,	13.0f,	0.0f, 0.0f, 0.0f,  -1.0f,  0.0f,   // 16
		-8.0f, 1.5f,	13.0f,	1.0f, 0.0f, 0.0f,  -1.0f,  0.0f,  // 17
		-8.0f, 1.5f,	4.0f,	1.0f, 1.0f, 0.0f,  -1.0f,  0.0f,  // 18
		-1.0f, 1.5f,	4.0f,	0.0f, 1.0f, 0.0f,  -1.0f,  0.0f,   // 19

		// bottom
		-8.0f, 0.51f,  4.0f,	0.0f, 0.0f, 0.0f,  -1.0f,  0.0f,// 20
		-1.0f, 0.51f,  4.0f,	1.0f, 0.0f, 0.0f,  -1.0f,  0.0f, // 21
		-1.0f, 0.51f,  13.0f,	1.0f, 1.0f, 0.0f,  -1.0f,  0.0f, // 22
		-8.0f, 0.51f,  13.0f,	0.0f, 1.0f, 0.0f,  -1.0f,  0.0f,// 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO6);
	glGenBuffers(1, &VBO6);
	glGenBuffers(1, &EBO6);
	glBindVertexArray(VAO6);

	glBindBuffer(GL_ARRAY_BUFFER, VBO6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO6);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define texcoord pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawColoredKasur()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 1.0f);

	glBindVertexArray(VAO6); 

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	
	glDrawElements(GL_TRIANGLES, 108, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredSandaran() {
	
	glGenTextures(1, &texture7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("kayu.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texture7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("kayu.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	
	float vertices[] = {

		// front
		-8.0f, -0.499f, 14.99f,		0.0f, 0.0f, 0.0f,  -1.0f,  0.0f, // 0
		-1.0f, -0.499f, 14.99f,		1.0f, 0.0f, 0.0f,  -1.0f,  0.0f,  // 1
		-1.0f,  4.0f,	14.99f,		1.0f, 1.0f, 0.0f,  -1.0f,  0.0f,  // 2
		-8.0f,	4.0f,	14.99f,		0.0f, 1.0f, 0.0f,  -1.0f,  0.0f, // 3

		// right
		-1.0f, 4.0f,	13.01f,		0.0f, 0.0f, -1.0f,  -1.0f,  0.0f, // 4
		-1.0f, 4.0f,	14.99f,		1.0f, 0.0f, -1.0f,  -1.0f,  0.0f,  // 5
		-1.0f, -0.499f, 14.99f,		1.0f, 1.0f, -1.0f,  -1.0f,  0.0f,  // 6
		-1.0f, -0.499f, 13.01f,		0.0f, 1.0f, -1.0f,  -1.0f,  0.0f, // 7

		// back
		-8.0f,  4.0f,    13.01f,	0.0f, 0.0f, 1.0f,  0.0f,  0.0f, // 8
		-1.0f,  4.0f,	 13.01f,	1.0f, 0.0f, 1.0f,  0.0f,  0.0f,  // 9
		-1.0f, -0.499f,  13.01f,	1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  // 10
		-8.0f, -0.499f,  13.01f,	0.0f, 1.0f, 1.0f,  0.0f,  0.0f, // 11

		// left
		-8.0f, 4.0f,	13.01f,		0.0f, 0.0f, 0.0f,  -1.0f,  0.0f, // 12
		-8.0f, 4.0f,	14.99f,		1.0f, 0.0f, 0.0f,  -1.0f,  0.0f,  // 13
		-8.0f, -0.499f,	14.99f,		1.0f, 1.0f, 0.0f,  -1.0f,  0.0f,  // 14
		-8.0f, -0.499f,	13.01f,		0.0f, 1.0f, 0.0f,  -1.0f,  0.0f, // 15

		// upper
		-1.0f, 4.0f,	13.01f,		0.0f, 0.0f, 1.0f,  -1.0f,  0.0f,  // 16
		-8.0f, 4.0f,	13.01f,		1.0f, 0.0f, 1.0f,  -1.0f,  0.0f, // 17
		-8.0f, 4.0f,	14.99f,		1.0f, 1.0f, 1.0f,  -2.0f,  0.0f, // 18
		-1.0f, 4.0f,	14.99f,		0.0f, 1.0f, -1.0f,  -2.0f,  0.0f,  // 19

		// bottom
		-8.0f, -0.499f,  14.99f,	0.0f, 0.0f, 0.0f,  -1.0f,  0.0f, // 20
		-1.0f, -0.499f,  14.99f,	1.0f, 0.0f, 0.0f,  -1.0f,  0.0f,  // 21
		-1.0f, -0.499f,  13.01f,	1.0f, 1.0f, 0.0f,  -1.0f,  0.0f,  // 22
		-8.0f, -0.499f,  13.01f,	0.0f, 1.0f, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO7);
	glGenBuffers(1, &VBO7);
	glGenBuffers(1, &EBO7);
	glBindVertexArray(VAO7);

	glBindBuffer(GL_ARRAY_BUFFER, VBO7);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO7);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define texcoord pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawColoredSandaran()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 4.0f);

	glBindVertexArray(VAO7); 

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	
	glDrawElements(GL_TRIANGLES, 108, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// LEMARI

void Demo::BuildColoredLemari() {
	
	glGenTextures(1, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("lemari2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("grayscaleLemari2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {

		// front
		-14.99f, -0.499f,	14.99f,		0.0f, 0.0f,	0.0f,  1.0f,  0.0f, 			// 0
		-12.01f, -0.499f,	14.99f,		1.0f, 0.0f,	0.0f,  1.0f,  0.0f, 			 // 1
		-12.01f,  8.0f,		14.99f,		1.0f, 1.0f,	0.0f,  1.0f,  0.0f, 			 // 2
		-14.99f,  8.0f,		14.99f,		0.0f, 1.0f,	0.0f,  1.0f,  0.0f, 			// 3

		// right
		-12.01f, 8.0f,		14.99f,		0.0f, 0.0f,	 0.0f,  1.0f,  0.0f,				// 4
		-12.01f, 8.0f,		4.0f,		1.0f, 0.0f,	 0.0f,  1.0f,  0.0f,				 // 5
		-12.01f, -0.499f,	4.0f,		1.0f, 1.0f,	 0.0f,  1.0f,  0.0f,				 // 6
		-12.01f, -0.499f,   14.99f,		0.0f, 1.0f,	 0.0f,  1.0f,  0.0f,				// 7

		// back
		-14.99f,  8.0f,	   4.0f,	0.0f, 0.0f,		0.0f,  1.0f,  0.0f,				 // 8
		-12.01f,  8.0f,	   4.0f,	1.0f, 0.0f,		0.0f,  1.0f,  0.0f,				  // 9
		-12.01f, -0.499f,  4.0f,	1.0f, 1.0f,		0.0f,  1.0f,  0.0f,				  // 10
		-14.99f, -0.499f,  4.0f,	0.0f, 1.0f,		0.0f,  1.0f,  0.0f,				 // 11

		// left
		-14.99f, 8.0f,		14.99f,	0.0f, 0.0f,		0.0f,  1.0f,  0.0f,				// 12
		-14.99f, 8.0f,		4.0f,	1.0f, 0.0f,		0.0f,  1.0f,  0.0f,				 // 13
		-14.99f, -0.499f,	4.0f,	1.0f, 1.0f,		0.0f,  1.0f,  0.0f,				 // 14
		-14.99f, -0.499f,	14.99f,	0.0f, 1.0f,		0.0f,  1.0f,  0.0f,				// 15

		// upper
		-12.0f,	8.0f,		14.99f,	0.0f, 0.0f,		0.0f, 1.0f,  0.0f, 				  // 16
		-14.99f, 8.0f,		14.99f,	1.0f, 0.0f,		0.0f, 1.0f,  0.0f, 				 // 17
		-14.99f, 8.0f,		4.0f,	1.0f, 1.0f,		0.0f, 1.0f,  0.0f, 				 // 18
		-12.0f,	8.0f,		4.0f,	0.0f, 1.0f,		0.0f, 1.0f,  0.0f, 				  // 19

		// bottom
		-14.99f, -0.499f,  4.0f,	0.0f, 0.0f,		0.0f,  1.0f,  0.0f,					// 20
		-12.0f, -0.499f,  4.0f,	1.0f, 0.0f,			0.0f,  1.0f,  0.0f,					// 21
		-12.0f, -0.499f,  14.99f,	1.0f, 1.0f,		0.0f,  1.0f,  0.0f,					 // 22
		-14.99f, -0.499f,  14.99f, 0.0f, 1.0f,		0.0f,  1.0f,  0.0f,					// 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom

	};

	glGenVertexArrays(1, &VAO4);
	glGenBuffers(1, &VBO4);
	glGenBuffers(1, &EBO4);
	glBindVertexArray(VAO4);

	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define texcoord pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawColoredLemari() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 1);

	glBindVertexArray(VAO4); 

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 108, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredLemariKiri() {
	
	glGenTextures(1, &texturell);
	glBindTexture(GL_TEXTURE_2D, texturell);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("laci.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {

		// LEMARI

		-12.0f,  7.8f, 14.94f,		0.0f, 0.0f,   0.0f, -1.0f, 0.0f,                     // front top left 0
		-11.75f, 7.8f, 14.94f,		1.0f, 0.0f,   0.0f, -1.0f, 0.0f,                     // front top right 1
		-11.75f, 7.8f, 9.69f,		1.0f, 1.0f,   0.0f, -1.0f, 0.0f,                     // back top right 2
		-12.0f,  7.8f, 9.69f,		0.0f, 1.0f,   0.0f, -1.0f, 0.0f,                         // back top left 3 

		-12.0f, -0.3f, 14.94f,		0.0f, 0.0f,    0.0f,  -1.0f,  0.0f,					// front bottom left 4
		-11.75f, -0.3f, 14.94f,		1.0f, 0.0f,    0.0f,  -1.0f,  0.0f,                  // front bottom right 5
		-11.75f, -0.3f, 9.69f,		1.0f, 1.0f,    0.0f,  -1.0f,  0.0f,                  // back bottom right 6
		-12.0f, -0.3f, 9.69f,		0.0f, 1.0f,    0.0f,  -1.0f,  0.0f,                  // back bottom left 7 
												
	};

	unsigned int indices[] = {


		0, 1, 2,  // Top Face
		0, 2, 3,  // --------

		4, 5, 6,   // Bottom Face
		4, 6, 7,   // -----------

		4, 5, 1,   // Front Face
		4, 1, 0,   // ----------

		7, 6, 2,   // Back Face
		7, 2, 3,   // ---------

		5, 2, 6,   // Right Face
		5, 1, 2,   // ----------

		4, 7, 3,   // Left Face
		4, 3, 0    // ----------

	};

	glGenVertexArrays(1, &VAOll);
	glGenBuffers(1, &VBOll);
	glGenBuffers(1, &EBOll);
	glBindVertexArray(VAOll);

	glBindBuffer(GL_ARRAY_BUFFER, VBOll);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOll);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define texcoord pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawColoredLemariKiri() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturell);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAOll); 

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredLemariKanan() {

	glGenTextures(1, &texturelr);
	glBindTexture(GL_TEXTURE_2D, texturelr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("laci.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {

		// LEMARI

		-12.0f,  7.8f, 9.29f,	0.0f, 0.0f,   0.0f, -1.0f, 0.0f,               // front top left 0
		-11.75f, 7.8f, 9.29f,	1.0f, 0.0f,   0.0f, -1.0f, 0.0f,                // front top right 1
		-11.75f, 7.8f, 4.04f,	1.0f, 1.0f,   0.0f, -1.0f, 0.0f,                // back top right 2
		-12.0f,  7.8f, 4.04f,	0.0f, 1.0f,   0.0f, -1.0f, 0.0f,              // back top left 3 

		-12.0f, -0.3f, 9.29f,	0.0f, 0.0f,    0.0f,  -1.0f,  0.0f,          // front bottom left 4
		-11.75f, -0.3f, 9.29f,  1.0f, 0.0f,    0.0f,  -1.0f,  0.0f,           // front bottom right 5
		-11.75f, -0.3f, 4.04f,	1.0f, 1.0f,    0.0f,  -1.0f,  0.0f,           // back bottom right 6
		-12.0f, -0.3f, 4.04f,	0.0f, 1.0f,    0.0f,  -1.0f,  0.0f,           // back bottom left 7 

	};

	unsigned int indices[] = {

		0, 1, 2,  // Top Face
		0, 2, 3,  // --------

		4, 5, 6,   // Bottom Face
		4, 6, 7,   // -----------

		4, 5, 1,   // Front Face
		4, 1, 0,   // ----------

		7, 6, 2,   // Back Face
		7, 2, 3,   // ---------

		5, 2, 6,   // Right Face
		5, 1, 2,   // ----------

		4, 7, 3,   // Left Face
		4, 3, 0    // ----------

	};

	glGenVertexArrays(1, &VAOlr);
	glGenBuffers(1, &VBOlr);
	glGenBuffers(1, &EBOlr);
	glBindVertexArray(VAOlr);

	glBindBuffer(GL_ARRAY_BUFFER, VBOlr);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOlr);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define texcoord pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawColoredLemariKanan() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturelr);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAOlr); 

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// Laci

void Demo::BuildColoredLaci() {

	glGenTextures(1, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("lemari2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("lemari2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {

		//front
		-0.5f,	-0.499f, 13.0f,		0.0f, 0.0f,	0.0f,  1.0f,  0.0f,	 // 0
		2.5f,	-0.499f, 13.0f,		1.0f, 0.0f,	0.0f,  1.0f,  0.0f,	// 1
		2.5f,	2.5f,	 13.0f,		1.0f, 1.0f,	0.0f,  1.0f,  0.0f,	 // 2
		-0.5f,  2.5f,	 13.0f,		0.0f, 1.0f,	0.0f,  1.0f,  0.0f,	// 3

		// right
		2.5f,  2.5f,	14.99f,		0.0f, 0.0f,	0.0f,  1.0f,  0.0f,		 // 4
		2.5f,  2.5f,	13.0f,		1.0f, 0.0f,	0.0f,  1.0f,  0.0f,		 // 5
		2.5f, -0.499f,	13.0f,		1.0f, 1.0f,	0.0f,  1.0f,  0.0f,		 // 6
		2.5f, -0.499f,  14.99f,		0.0f, 1.0f,	0.0f,  1.0f,  0.0f,		 // 7

		// back
		-0.5f, -0.499f, 14.9f,		0.0f, 0.0f,	0.0f,  1.0f,  0.0f, 		// 8 
		2.5f,  -0.499f, 14.9f,		1.0f, 0.0f,	0.0f,  1.0f,  0.0f, 		// 9
		2.5f,   2.5f,	14.9f,		1.0f, 1.0f,	0.0f,  1.0f,  0.0f, 		// 10
		-0.5f,  2.5f,	14.9f,		0.0f, 1.0f,	0.0f,  1.0f,  0.0f, 		// 11

		// left
		-0.5f, -0.499f, 13.0f,		0.0f, 0.0f,	0.0f,  1.0f,  0.0f,		// 12
		-0.5f, -0.499f,	14.99f,		1.0f, 0.0f,	0.0f,  1.0f,  0.0f,		// 13
		-0.5f,  2.5f,	14.99f,		1.0f, 1.0f,	0.0f,  1.0f,  0.0f,		// 14
		-0.5f,  2.5f,	13.0f,		0.0f, 1.0f,	0.0f,  1.0f,  0.0f,		// 15

		// upper
		2.5f,  2.5f,	13.0f,		0.0f, 0.0f,	0.0f,  1.0f,  0.0f,		  // 16
		-0.5f, 2.5f,	13.0f,		1.0f, 0.0f,	0.0f,  1.0f,  0.0f,		 // 17
		-0.5f, 2.5f,	14.99f,		1.0f, 1.0f,	0.0f,  1.0f,  0.0f,		 // 18
		2.5f,  2.5f,	14.99f,		0.0f, 1.0f,	0.0f,  1.0f,  0.0f,		  // 19

		// bottom
		- 0.5, -0.499f,	14.99f,		0.0f, 0.0f,	0.0f,  1.0f,  0.0f,		// 20
		2.5,  -0.499f,	14.99f,		1.0f, 0.0f,	0.0f,  1.0f,  0.0f,		 // 21
		2.5,  -0.499f,	13.0f,		1.0f, 1.0f,	0.0f,  1.0f,  0.0f,		 // 22
		-0.5, -0.499f,  13.0f,		0.0f, 1.0f,	0.0f,  1.0f,  0.0f,		// 23

	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom

	};

	glGenVertexArrays(1, &VAO5);
	glGenBuffers(1, &VBO5);
	glGenBuffers(1, &EBO5);
	glBindVertexArray(VAO5);

	glBindBuffer(GL_ARRAY_BUFFER, VBO5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define texcoord pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawColoredLaci() {
	glUseProgram(shaderProgram);

	glBindTexture(GL_TEXTURE_2D, texture5);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 4.0f);

	glBindVertexArray(VAO5); 

	glDrawElements(GL_TRIANGLES, 108, GL_UNSIGNED_INT, 0);
	
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredPintuLaci() {
	
	glGenTextures(1, &texturePL);
	glBindTexture(GL_TEXTURE_2D, texturePL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("laci.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texturePL);
	glBindTexture(GL_TEXTURE_2D, texturePL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("laci.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
	
		//front
		-0.3f,	-0.3f,	12.99f,	0.0f, 0.0f,	0.0f,  1.0f,  0.0f,	 // 0
		2.3f,	-0.3f,	12.99f,	1.0f, 0.0f,	0.0f,  1.0f,  0.0f,	  // 1
		2.3f,	0.9f,	12.99f,	1.0f, 1.0f,	0.0f,  1.0f,  0.0f,	 // 2
		-0.3f,	0.9f,	12.99f,	0.0f, 1.0f,	0.0f,  1.0f,  0.0f,	 // 3


		// back
		-0.3f,	1.1f, 12.99f,	0.0f, 0.0f,	0.0f,  1.0f,  0.0f,	// 8 
		2.3f,	1.1f, 12.99f,	1.0f, 0.0f,	0.0f,  1.0f,  0.0f,	// 9
		2.3f,   2.3f, 12.99f,	1.0f, 1.0f,	0.0f,  1.0f,  0.0f,	// 10
		-0.3f,  2.3f, 12.99f,	0.0f, 1.0f,	0.0f,  1.0f,  0.0f,	// 11

	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom


	};

	glGenVertexArrays(1, &VAOPL);
	glGenBuffers(1, &VBOPL);
	glGenBuffers(1, &EBOPL);
	glBindVertexArray(VAOPL);

	glBindBuffer(GL_ARRAY_BUFFER, VBOPL);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOPL);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define texcoord pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawColoredPintuLaci() {
	glUseProgram(shaderProgram);

	glBindTexture(GL_TEXTURE_2D, texturePL);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texturePL);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 1.0f);

	glBindVertexArray(VAOPL); 

	glDrawElements(GL_TRIANGLES, 108, GL_UNSIGNED_INT, 0);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// LANTAI

void Demo::BuildColoredPlane()
{
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("glantai2.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture2);
	glBindTexture(GL_TEXTURE_2D, stexture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("lantai2.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLfloat vertices[] = {
		// bottom
		-15.0f, -0.5f, -15.0f,	5.0f, 5.0f, 0.0f, 1.0f,  0.0f,
		 15.0f, -0.5f, -15.0f,  0.0f, 0.0f, 0.0f, 1.0f,  0.0f,
		 15.0f, -0.5f,  15.0f,	5.0f, 0.0f, 0.0f, 1.0f,  0.0f,
		-15.0f, -0.5f,  15.0f,  0.0f, 5.0f, 0.0f, 1.0f,  0.0f,

	};

	GLuint indices[] = {
		0,  2,  1,  0,  3,  2
	};

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// TexCoord attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Demo::DrawColoredPlane()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, stexture2);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 3);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 1.0f);

	glBindVertexArray(VAO2); 

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::InitCamera()
{
	posCamX = 0.0f;
	posCamY = 3.0f;
	posCamZ = 8.0f;
	viewCamX = 0.0f;
	viewCamY = 3.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.001f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Demo::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}

void Demo::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}

void Demo::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}

int main(int argc, char** argv) {
	RenderEngine& app = Demo();
	app.Start("Proyek Akhir GRAFKOM TIF-A || Control : A = Kiri, S = Mundur, D = Kanan, W = Maju, Q = Naik, E = Turun, LMB = Zoom In, RMB = Zoom Out ", 1280, 720, false, false);
}