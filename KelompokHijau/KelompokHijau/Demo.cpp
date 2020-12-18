#include "Demo.h"



Demo::Demo() {

}


Demo::~Demo() {
}


void Demo::Init() {
	// build and compile our shader program
	// ------------------------------------
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

	InitCamera();
}

void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Demo::ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// zoom camera
	// -----------
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

	// update camera movement 
	// -------------
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

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		posCamY += 0.005f;
		viewCamY += 0.005f;
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		posCamY -= 0.005f;
		viewCamY -= 0.005f;
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth / 2;
	double midY = screenHeight / 2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(this->shaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	GLint viewLoc = glGetUniformLocation(this->shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

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

	glDisable(GL_DEPTH_TEST);
}

/// TEMBOK

void Demo::DrawColoredTembok()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO3); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredTembok() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("wallRed.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		//back
		-15.0, -0.5, -15.0, 0, 0, // 8 
		 15.0, -0.5, -15.0, 1, 0, // 9
		 15.0,  25.0, -15.0, 1, 1, // 10
		-15.0,  25.0, -15.0, 0, 1, // 11

		// front
		-15.0, -0.5, 15.0, 0, 0,  // 0
		15.0, -0.5, 15.0, 1, 0,   // 1
		15.0,  25.0, 15.0, 1, 1,   // 2
		-15.0,  25.0, 15.0, 0, 1,  // 3

		// right
		15.0,  25.0,  15.0, 0, 0,  // 4
		15.0,  25.0, -15.0, 1, 0,  // 5
		15.0, -0.5, -15.0, 1, 1,  // 6
		15.0, -0.5,  15.0, 0, 1,  // 7

		// left
		-15.0, -0.5, -15.0, 0, 0, // 12
		-15.0, -0.5,  15.0, 1, 0, // 13
		-15.0,  25.0,  15.0, 1, 1, // 14
		-15.0,  25.0, -15.0, 0, 1, // 15

		// upper
		15.0, 25.0,  15.0, 0, 0,   // 16
		-15.0, 25.0,  15.0, 1, 0,  // 17
		-15.0, 25.0, -15.0, 1, 1,  // 18
		15.0, 25.0, -15.0, 0, 1,   // 19

	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,	 // back
		4,  5,  6,  4,  6,  7,   // front
		8,  9,  10,  8,  10,  11,   // right
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18  // upper
	};

	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glGenBuffers(1, &EBO3);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

// TEMPAT TIDUR

void Demo::BuildColoredTempatTidur() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("kayu.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		//// format position, tex coords

		// front
		-8.0, -0.499, 13.0, 0, 0,  // 0
		-1.0, -0.499, 13.0, 1, 0,   // 1
		-1.0,  0.5, 13.0, 1, 1,   // 2
		-8.0, 0.5, 13.0, 0, 1,  // 3

		// right
		-1.0, 0.5, 13.0, 0, 0,  // 4
		-1.0, 0.5, 4.0, 1, 0,   // 5
		-1.0, -0.499, 4.0, 1, 1,   // 6
		-1.0, -0.5, 13.0, 0, 1,  // 7

		// back
		-8.0,  0.5,  4.0, 0, 0,  // 8
		-1.0,  0.5,  4.0, 1, 0,   // 9
		-1.0, -0.499,  4.0, 1, 1,   // 10
		-8.0, -0.499,  4.0, 0, 1,  // 11

		// left
		-8.0, 0.5, 13.0, 0, 0,  // 12
		-8.0, 0.5, 4.0, 1, 0,   // 13
		-8.0, -0.499, 4.0, 1, 1,   // 14
		-8.0, -0.499, 13.0, 0, 1,  // 15

		// upper
		-1.0, 0.5,  13.0, 0, 0,   // 16
		-8.0, 0.5,  13.0, 1, 0,  // 17
		-8.0, 0.5, 4.0, 1, 1,  // 18
		-1.0, 0.5, 4.0, 0, 1,   // 19

		// bottom
		-8.0, -0.499,  4.0, 0, 0, // 20
		-1.0, -0.499,  4.0, 1, 0,  // 21
		-1.0, -0.499,  13.0, 1, 1,  // 22
		-8.0, -0.499,  13.0, 0, 1, // 23

	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom

	/*	24, 25, 26, 24, 26, 27,
		28, 29, 30, 28, 30, 31,
		32, 33, 34, 32, 34, 35,
		36, 37, 38, 36, 38, 39,
		40, 41, 42, 40, 42, 43*/

	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredTempatTidur()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 144, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredKasur() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture6);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("kasur.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		//// format position, tex coords

		// front
		-8.0, 0.51, 13.0, 0, 0,  // 0
		-1.0, 0.51, 13.0, 1, 0,   // 1
		-1.0, 1.5, 13.0, 1, 1,   // 2
		-8.0, 1.5, 13.0, 0, 1,  // 3

		// right
		-1.0, 1.5, 13.0, 0, 0,  // 4
		-1.0, 1.5, 4.0, 1, 0,   // 5
		-1.0, 0.51, 4.0, 1, 1,   // 6
		-1.0, 0.51, 13.0, 0, 1,  // 7

		// back
		-8.0,  1.5,  4.0, 0, 0,  // 8
		-1.0,  1.5,  4.0, 1, 0,   // 9
		-1.0,  0.51,  4.0, 1, 1,   // 10
		-8.0,  0.51,  4.0, 0, 1,  // 11

		// left
		-8.0, 1.5, 13.0, 0, 0,  // 12
		-8.0, 1.5, 4.0, 1, 0,   // 13
		-8.0, 0.51, 4.0, 1, 1,   // 14
		-8.0, 0.51, 13.0, 0, 1,  // 15

		// upper
		-1.0, 1.5,  13.0, 0, 0,   // 16
		-8.0, 1.5,  13.0, 1, 0,  // 17
		-8.0, 1.5, 4.0, 1, 1,  // 18
		-1.0, 1.5, 4.0, 0, 1,   // 19

		// bottom
		-8.0, 0.51,  4.0, 0, 0, // 20
		-1.0, 0.51,  4.0, 1, 0,  // 21
		-1.0, 0.51,  13.0, 1, 1,  // 22
		-8.0, 0.51,  13.0, 0, 1, // 23

	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom

		////Badan
		//0, 1, 2,  // Top Face
		//0, 2, 3,  // --------

		//4, 5, 6,   // Bottom Face
		//4, 6, 7,   // -----------

		//4, 5, 1,   // Front Face
		//4, 1, 0,   // ----------

		//7, 6, 2,   // Back Face
		//7, 2, 3,   // ---------

		//5, 2, 6,   // Right Face
		//5, 1, 2,   // ----------

		//4, 7, 3,   // Left Face
		//4, 3, 0,    // ----------
		////Pintu Kiri
		//8, 9, 10,  // Top Face
		//8, 10, 11,  // --------

		//12, 13, 14,   // Bottom Face
		//12, 14, 15,   // -----------

		//12, 13, 9,   // Front Face
		//12, 9, 8,   // ----------

		//15, 14, 10,   // Back Face
		//15, 10, 11,   // ---------

		//13, 10, 14,   // Right Face
		//13, 9, 10,   // ----------

		//12, 15, 11,   // Left Face
		//12, 11, 8,    // ----------
		////Pintu Kanan
		//16, 17, 18,  // Top Face
		//16, 18, 19,  // --------

		//20, 21, 22,   // Bottom Face
		//20, 22, 23,   // -----------

		//20, 21, 17,   // Front Face
		//20, 17, 16,   // ----------

		//23, 22, 18,   // Back Face
		//23, 18, 19,   // ---------

		//21, 18, 22,   // Right Face
		//21, 17, 18,   // ----------

		//20, 23, 19,   // Left Face
		//20, 19, 16    // ----------

	};

	glGenVertexArrays(1, &VAO6);
	glGenBuffers(1, &VBO6);
	glGenBuffers(1, &EBO6);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO6);

	glBindBuffer(GL_ARRAY_BUFFER, VBO6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO6);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredKasur()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO6); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 108, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredSandaran() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("kayu.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		//// format position, tex coords

		// front
		-8.0, -0.499, 14.99, 0, 0,  // 0
		-1.0, -0.499, 14.99, 1, 0,   // 1
		-1.0,  4.0, 14.99, 1, 1,   // 2
		-8.0, 4.0, 14.99, 0, 1,  // 3

		// right
		-1.0, 4.0, 13.01, 0, 0,  // 4
		-1.0, 4.0, 14.99, 1, 0,   // 5
		-1.0, -0.499, 14.99, 1, 1,   // 6
		-1.0, -0.499, 13.01, 0, 1,  // 7

		// back
		-8.0,  4.0,  13.01, 0, 0,  // 8
		-1.0,  4.0,  13.01, 1, 0,   // 9
		-1.0, -0.499,  13.01, 1, 1,   // 10
		-8.0, -0.499,  13.01, 0, 1,  // 11

		// left
		-8.0, 4.0, 13.01, 0, 0,  // 12
		-8.0, 4.0, 14.99, 1, 0,   // 13
		-8.0, -0.499, 14.99, 1, 1,   // 14
		-8.0, -0.499, 13.01, 0, 1,  // 15

		// upper
		-1.0, 4.0,  13.01, 0, 0,   // 16
		-8.0, 4.0,  13.01, 1, 0,  // 17
		-8.0, 4.0, 14.99, 1, 1,  // 18
		-1.0, 4.0, 14.99, 0, 1,   // 19

		// bottom
		-8.0, -0.499,  14.99, 0, 0, // 20
		-1.0, -0.499,  14.99, 1, 0,  // 21
		-1.0, -0.499,  13.01, 1, 1,  // 22
		-8.0, -0.499,  13.01, 0, 1, // 23

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
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO7);

	glBindBuffer(GL_ARRAY_BUFFER, VBO7);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO7);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredSandaran()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO7); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 108, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// LEMARI

void Demo::BuildColoredLemari() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("lemari2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		//// format position, tex coords

		// front
		-14.99, -0.499, 14.99, 0, 0,  // 0
		-12.01, -0.499, 14.99, 1, 0,   // 1
		-12.01,  8.0, 14.99, 1, 1,   // 2
		-14.99, 8.0, 14.99, 0, 1,  // 3

		// right
		-12.01, 8.0, 14.99, 0, 0,  // 4
		-12.01, 8.0, 4.0, 1, 0,   // 5
		-12.01, -0.499, 4.0, 1, 1,   // 6
		-12.01, -0.499, 14.99, 0, 1,  // 7

		// back
		-14.99,  8.0,  4.0, 0, 0,  // 8
		-12.01,  8.0,  4.0, 1, 0,   // 9
		-12.01, -0.499,  4.0, 1, 1,   // 10
		-14.99, -0.499,  4.0, 0, 1,  // 11

		// left
		-14.99, 8.0, 14.99, 0, 0,  // 12
		-14.99, 8.0, 4.0, 1, 0,   // 13
		-14.99, -0.499, 4.0, 1, 1,   // 14
		-14.99, -0.499, 14.99, 0, 1,  // 15

		// upper
		-12.0, 8.0,  14.99, 0, 0,   // 16
		-14.99, 8.0,  14.99, 1, 0,  // 17
		-14.99, 8.0, 4.0, 1, 1,  // 18
		-12.0, 8.0, 4.0, 0, 1,   // 19

		// bottom
		-14.99, -0.499,  4.0, 0, 0, // 20
		-12.0, -0.499,  4.0, 1, 0,  // 21
		-12.0, -0.499,  14.99, 1, 1,  // 22
		-14.99, -0.499,  14.99, 0, 1 // 23


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
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO4);

	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredLemari() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO4); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 108, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredLemariKiri() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texturell);
	glBindTexture(GL_TEXTURE_2D, texturell);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("pintulemari.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		//// format position, tex coords

		// LEMARI

		-12.0,  7.8, 14.94, 0	,	0,   // front top left 0
		-11.75, 7.8, 14.94,  1	,	0,   // front top right 1
		-11.75, 7.8, 9.69, 1	,	1,   // back top right 2
		-12.0,  7.8, 9.69, 0,	1,       // back top left 3 

		-12.0, -0.3, 14.94, 0	,	0, // front bottom left 4
		-11.75, -0.3, 14.94,  1	,	0, // front bottom right 5
		-11.75, -0.3, 9.69, 1	,	1, // back bottom right 6
		-12.0, -0.3, 9.69, 0,	1, // back bottom left 7 

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
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOll);

	glBindBuffer(GL_ARRAY_BUFFER, VBOll);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOll);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredLemariKiri() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturell);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAOll); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredLemariKanan() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texturelr);
	glBindTexture(GL_TEXTURE_2D, texturelr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("pintuLemari.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		//// format position, tex coords

		// LEMARI

		-12.0,  7.8, 9.29, 0	,	0,  // front top left 0
		-11.75, 7.8, 9.29,  1	,	0,   // front top right 1
		-11.75, 7.8, 4.04, 1	,	1,   // back top right 2
		-12.0,  7.8, 4.04, 0,	1, // back top left 3 

		-12.0, -0.3, 9.29, 0	,	0, // front bottom left 4
		-11.75, -0.3, 9.29,  1	,	0, // front bottom right 5
		-11.75, -0.3, 4.04, 1	,	1, // back bottom right 6
		-12.0, -0.3, 4.04, 0,	1, // back bottom left 7 

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
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOlr);

	glBindBuffer(GL_ARRAY_BUFFER, VBOlr);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOlr);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredLemariKanan() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturelr);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAOlr); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// Laci

void Demo::BuildColoredLaci() {
	// load image into texture memory
		// ------------------------------
		// Load and create a texture 
	glGenTextures(1, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("lemari2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		//// format position, tex coords

		//front
		-0.5, -0.5, 13.0, 0, 0,  // 0
		2.5, -0.5, 13.0, 1, 0,   // 1
		2.5,  2.5, 13.0, 1, 1,   // 2
		-0.5,  2.5, 13.0, 0, 1,  // 3

		// right
		2.5,  2.5,  14.9, 0, 0,  // 4
		2.5,  2.5, 13.0, 1, 0,  // 5
		2.5, -0.5, 13.0, 1, 1,  // 6
		2.5, -0.5,  14.9, 0, 1,  // 7

		// back
		-0.5, -0.5, 14.9, 0, 0, // 8 
		2.5,  -0.5, 14.9, 1, 0, // 9
		2.5,   2.5, 14.9, 1, 1, // 10
		-0.5,  2.5, 14.9, 0, 1, // 11

		// left
		-0.5, -0.5, 13.0, 0, 0, // 12
		-0.5, -0.5,  14.9, 1, 0, // 13
		-0.5,  2.5,  14.9, 1, 1, // 14
		-0.5,  2.5, 13.0, 0, 1, // 15

		// upper
		2.5, 2.5,  13.0, 0, 0,   // 16
		-0.5, 2.5,  13.0, 1, 0,  // 17
		-0.5, 2.5, 14.9, 1, 1,  // 18
		2.5, 2.5, 14.9, 0, 1,   // 19

		// bottom
		-0.5, -0.5, 14.9, 0, 0, // 20
		2.5, -0.5, 14.9, 1, 0,  // 21
		2.5, -0.5,  13.0, 1, 1,  // 22
		-0.5, -0.5,  13.0, 0, 1, // 23

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
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO5);

	glBindBuffer(GL_ARRAY_BUFFER, VBO5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawColoredLaci() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO5); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 108, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}


void Demo::BuildColoredPintuLaci() {
	// load image into texture memory
		// ------------------------------
		// Load and create a texture 
	glGenTextures(1, &texturePL);
	glBindTexture(GL_TEXTURE_2D, texturePL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("wallRed.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		//// format position, tex coords

		//front
		-0.3, -0.3, 12.9, 0, 0,  // 0
		2.3, -0.3, 12.9, 1, 0,   // 1
		2.3,  0.9, 12.9, 1, 1,   // 2
		-0.3,  0.9, 12.9, 0, 1,  // 3


		// back
		-0.3, 1.1, 12.9, 0, 0, // 8 
		2.3,  1.1, 12.9, 1, 0, // 9
		2.3,   2.3, 12.9, 1, 1, // 10
		-0.3,  2.3, 12.9, 0, 1, // 11

		////front
		//-0.5, -0.5, 12.0, 0, 0,  // 0
		//2.5, -0.5, 12.0, 1, 0,   // 1
		//2.5,  2.5, 12.0, 1, 1,   // 2
		//-0.5,  2.5, 12.0, 0, 1,  // 3

		//// right
		//2.5,  2.5,  14.9, 0, 0,  // 4
		//2.5,  2.5, 13.0, 1, 0,  // 5
		//2.5, -0.5, 13.0, 1, 1,  // 6
		//2.5, -0.5,  14.9, 0, 1,  // 7

		//// back
		//-0.5, -0.5, 14.9, 0, 0, // 8 
		//2.5,  -0.5, 14.9, 1, 0, // 9
		//2.5,   2.5, 14.9, 1, 1, // 10
		//-0.5,  2.5, 14.9, 0, 1, // 11

		//// left
		//-0.5, -0.5, 13.0, 0, 0, // 12
		//-0.5, -0.5,  14.9, 1, 0, // 13
		//-0.5,  2.5,  14.9, 1, 1, // 14
		//-0.5,  2.5, 13.0, 0, 1, // 15

		//// upper
		//2.5, 2.5,  13.0, 0, 0,   // 16
		//-0.5, 2.5,  13.0, 1, 0,  // 17
		//-0.5, 2.5, 14.9, 1, 1,  // 18
		//2.5, 2.5, 14.9, 0, 1,   // 19

		//// bottom
		//-0.5, -0.5, 14.9, 0, 0, // 20
		//2.5, -0.5, 14.9, 1, 0,  // 21
		//2.5, -0.5,  13.0, 1, 1,  // 22
		//-0.5, -0.5,  13.0, 0, 1, // 23

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
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOPL);

	glBindBuffer(GL_ARRAY_BUFFER, VBOPL);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOPL);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawColoredPintuLaci() {
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturePL);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAOPL); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 108, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// LANTAI

void Demo::BuildColoredPlane()
{
	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("lantai2.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-15.0, -0.5, -15.0,  0,  0,
		 15.0, -0.5, -15.0, 5,  0,
		 15.0, -0.5,  15.0, 5, 5,
		-15.0, -0.5,  15.0,  0, 5,

		//back
		//-15.0, -0.5, -15.0, 0, 0, // 8 
		// 15.0, -0.5, -15.0, 5, 0, // 9
		// 15.0,  25.0, -15.0, 5, 5, // 10
		//-15.0,  25.0, -15.0, 0, 5, // 11


	};

	GLuint indices[] = {
		0,  2,  1,  0,  3,  2
		/*4,  5,  6,  4,  6,  7*/
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}

void Demo::DrawColoredPlane()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 1);

	glBindVertexArray(VAO2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

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
	// forward positive cameraspeed and backward negative -cameraspeed.
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

	// left positive cameraspeed and right negative -cameraspeed.
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
	app.Start("Camera: Free Camera Implementation", 800, 600, false, false);
}