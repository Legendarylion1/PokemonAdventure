#include "Renderer.h"
#include <GLFW/glfw3.h>

Renderer::~Renderer()
{
	m_textureCache.clearTextureCache();
	m_shader.Delete();
	glfwTerminate();
}

void Renderer::init(Coordinate* playerCoord, Timer* timer)
{
	//PRINT("Renderer Init");
	m_playerCoord = playerCoord;
	m_timer = timer;

	//PRINT("GLFW INIT");
	if (!glfwInit())
		exit(404);

	//PRINT("CREATE WINDOW");
	//m_window = glfwCreateWindow(m_resolution.x, m_resolution.y, "Hello World", glfwGetPrimaryMonitor(), NULL);	//TODO: Start off in smaller window to pick a save. Then go full screen for the rest of the game based on the imported settings
	m_window = glfwCreateWindow((int)m_resolution.x, (int)m_resolution.y, "Pokemon Adventure", NULL, NULL);

	//PRINT("Add Hint");
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	//PRINT("Shared Window");
	m_shared = glfwCreateWindow((int)m_resolution.x, (int)m_resolution.y, "Pokemon Adventure", NULL, m_window);

	//PRINT("Hide Shared");
	glfwHideWindow(m_shared);
	
	//PRINT("Pre Terminate");
	if (!m_window)
	{
		//PRINT("Terminating");
		glfwTerminate();
		return;
	}

	//PRINT("Setting Context");
	/* Make the window's context current */
	glfwMakeContextCurrent(m_window);

	//if (glewInit() != GLEW_OK)
	//	exit(3);

	//PRINT("Get Return Code");
	GLenum returnCode = glewInit();

	if (returnCode != GLEW_OK)
	{
		std::cout << "[Renderer] Return Code Error: " << returnCode << std::endl;
		exit(returnCode);
	}

	//PRINT("Setting Shader");
	m_shader = Shader("src/Graphics/Shader/default.vert", "src/Graphics/Shader/default.frag");

	//PRINT("Setting Blend");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//PRINT("Setting Smooth");
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	//PRINT("Activating Shader");
	m_shader.Activate();

	//PRINT("Init Player Textures");
	//m_mapData = { 36 * , 69 * m_tileSize, Texture(g_MapTextureLocations[SectionID::HOME_VILLAGE_ROUTE_1].c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE) };	//TODO: Fix
	m_characterTextures[CharacterID::PLAYER_MALE_TRAINER] = Texture(g_CharacterTextureLocations[CharacterID::PLAYER_MALE_TRAINER].c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_characterTextures[CharacterID::PLAYER_FEMALE_TRAINER] = Texture(g_CharacterTextureLocations[CharacterID::PLAYER_FEMALE_TRAINER].c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	m_characterTextures[CharacterID::FIRST_TRAINER] = Texture(g_CharacterTextureLocations[CharacterID::FIRST_TRAINER].c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);	//TODO: Fix

	//PRINT("Init Text Renderer");
	m_textRenderer = new TextRenderer(&m_shader, m_resolution.x, m_resolution.y);
	
}

void Renderer::onUpdate()
{
	m_timer->onUpdate();
	showFps();
	pollUpdates();
	clearBuffer();
}

void Renderer::load(RendererSave save)
{
	m_showFps = save.showFPS;
	setResolution((RendererResolutiion)save.resolution);

	if (save.fullscreen)
		toggleFullScreen();
}

void Renderer::loadNewGame()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	if (mode->width <= 1280)
		setResolution(RendererResolutiion::_1280x720);
	else if (mode->width <= 1920)
		setResolution(RendererResolutiion::_1920x1080);
	else
		setResolution(RendererResolutiion::_2560x1440);

	toggleFullScreen();
}

bool Renderer::shouldClose()
{
	return glfwWindowShouldClose(m_window);
}

void Renderer::clearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT);
	m_shader.Activate();
}

void Renderer::pollUpdates()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void Renderer::clearCache()
{
	m_textureCache.clearTextureCache();
}

void Renderer::setResolution(RendererResolutiion resolution)
{

	switch (resolution)
	{
	case RendererResolutiion::_1280x720:
		m_viewScale = 0.5f;
		m_resolution = Resolution{ 1280.0f, 720.0f };
		break;
	case RendererResolutiion::_1920x1080:
		m_viewScale = 0.75f;
		m_resolution = Resolution{ 1920.0f, 1080.0f };
		break;
	case RendererResolutiion::_2560x1440:
		m_viewScale = 1.0f;
		m_resolution = Resolution{ 2560.0f, 1440.0f };
		break;
	default:
		break;
	}

	m_tileSize = 200.0f * m_viewScale;

	m_textRenderer->setScreenSize(m_resolution.x, m_resolution.y);
	glViewport(0, 0, (GLsizei)m_resolution.x, (GLsizei)m_resolution.y);
	glfwSetWindowSize(m_window, (int)m_resolution.x, (int)m_resolution.y);

	if (!m_fullscreen)
		glfwSetWindowPos(m_window, 0, 30);	//30 is the title bar size

	//TODO: Min and Max
}

void Renderer::renderCharacter(Position position, CharacterID trainerID)
{
	float xPos = (position.coords.xTile * m_tileSize) + position.coords.screenX;
	float yPos = (position.coords.yTile * m_tileSize) + position.coords.screenY;

	GLfloat fightUI[]
	{
		//TOP Environment
		xPos, yPos, 0.0f,								0.0f, 0.0f, 0.0f, 0.0f,		(position.spriteState * 0.333f), (position.direction * 0.25f),
		xPos, yPos + m_tileSize, 0.0f,					0.0f, 0.0f, 0.0f, 0.0f,		(position.spriteState * 0.333f), (position.direction * 0.25f) + 0.25f,
		xPos + m_tileSize, yPos + m_tileSize, 0.0f,		0.0f, 0.0f, 0.0f, 0.0f,		(position.spriteState * 0.333f) + 0.333f, (position.direction * 0.25f) + 0.25f,
		xPos + m_tileSize, yPos, 0.0f,					0.0f, 0.0f,	0.0f, 0.0f,		(position.spriteState * 0.333f) + 0.333f, (position.direction * 0.25f),

	};

	GLuint indices1[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(fightUI, sizeof(fightUI));
	EBO EBO1(indices1, sizeof(indices1));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	m_characterTextures[trainerID].Bind();
	VAO1.Bind();

	positionCamera(glm::vec3(0, 0, 0));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO1.Unbind();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	m_characterTextures[trainerID].Unbind();
}

void Renderer::renderButton(ButtonRenderData data, std::string text, bool highlight)
{
	float buttonX = m_resolution.x * (data.percentageX / 100.0f);
	float buttonY = m_resolution.y * (data.percentageY / 100.0f);

	float borderWidth = m_resolution.x *  (data.widthPercent  / 100.0f);
	float borderHeight = m_resolution.y * (data.heightPercent / 100.0f);

	borderWidth = borderWidth / 2.0f;
	borderHeight = borderHeight / 2.0f;

	float borderSizePixels = 5.0f;

	float buttonWidth = borderWidth - borderSizePixels;	
	float buttonHeight = borderHeight - borderSizePixels;


	Color borderColor = Color::BLACK;
	

	Color buttonColor = data.color;
	if (highlight && data.highlight)
		buttonColor = Color::GOLD;

	GLfloat fightUI[]
	{

		buttonX - borderWidth, buttonY - borderHeight, 0.0f,			colorMap[borderColor].r, colorMap[borderColor].g, colorMap[borderColor].b, 0.0f,
		buttonX - borderWidth, buttonY + borderHeight, 0.0f,			colorMap[borderColor].r, colorMap[borderColor].g, colorMap[borderColor].b, 0.0f,
		buttonX + borderWidth, buttonY + borderHeight, 0.0f,			colorMap[borderColor].r, colorMap[borderColor].g, colorMap[borderColor].b, 0.0f,
		buttonX + borderWidth, buttonY - borderHeight, 0.0f,			colorMap[borderColor].r, colorMap[borderColor].g, colorMap[borderColor].b, 0.0f,
		
		buttonX - buttonWidth, buttonY - buttonHeight, 0.0f,			colorMap[buttonColor].r, colorMap[buttonColor].g, colorMap[buttonColor].b, 0.0f,
		buttonX - buttonWidth, buttonY + buttonHeight, 0.0f,			colorMap[buttonColor].r, colorMap[buttonColor].g, colorMap[buttonColor].b, 0.0f,
		buttonX + buttonWidth, buttonY + buttonHeight, 0.0f,			colorMap[buttonColor].r, colorMap[buttonColor].g, colorMap[buttonColor].b, 0.0f,
		buttonX + buttonWidth, buttonY - buttonHeight, 0.0f,			colorMap[buttonColor].r, colorMap[buttonColor].g, colorMap[buttonColor].b, 0.0f,
	};
	
	GLuint indices1[] =
	{
		0, 2, 1,
		0, 3, 2,

		4, 6, 5,
		4, 7, 6,
	};
	
	VAO VAO1;
	VAO1.Bind();
	
	VBO VBO1(fightUI, sizeof(fightUI));
	EBO EBO1(indices1, sizeof(indices1));
	
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	
	VAO1.Bind();
	
	positionCamera(glm::vec3((m_playerCoord->xTile * m_tileSize) - (m_resolution.x / 2) + (m_tileSize / 2.0f) + m_playerCoord->screenX, (m_playerCoord->yTile * m_tileSize) - (m_resolution.y / 2) + (m_tileSize / 2.0f) + m_playerCoord->screenY, 0.0f));
	
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	VAO1.Unbind();
	
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	
	if (text.size() == 0)
		return;
	
	unsigned int fontSize = (unsigned int)(borderHeight / 3.0f);

	if (data.fontSize == renderOptions::autoSizeText)
	{
		float fontSize = m_textRenderer->getFontSize(text, data.widthPercent, data.heightPercent);
		renderText(text, buttonX, buttonY - (fontSize / 2.0f), (unsigned int)fontSize, Alignment::CENTER_ALIGN, Color::BLACK);
	}
	else
		renderText(text, buttonX, buttonY - (data.fontSize / 2.0f), data.fontSize, Alignment::CENTER_ALIGN, Color::BLACK);
}

void Renderer::renderTextBox(TextBoxRenderData data, std::string text)
{
	float xPos = m_resolution.x * (data.percentageX / 100.0f);
	float yPos = m_resolution.y * (data.percentageY / 100.0f);

	unsigned int fontSize = (unsigned int)(m_resolution.x * (data.fontSizePercentage / 100.0f));

	if (data.textWrapPercent == -1.0f)
	{
		renderText(text, xPos, yPos, fontSize, data.alignment, data.color);
		return;
	}

	int wrapPixelCount = (int)(m_resolution.x * (data.textWrapPercent / 100.0f));
	float wrapOffset = (int)(m_resolution.x * (data.textWrapOffsetPercent / 100.0f));

	renderText(text, xPos, yPos, fontSize, data.alignment, data.color, wrapPixelCount, wrapOffset);
}

void Renderer::renderImage(ImageRenderData data)
{
	std::string imagePath = data.staticImage;
	if (data.dynamicImage != nullptr)
		imagePath = *data.dynamicImage;

	if (imagePath.size() == 0)
		return;

	float imageX = m_resolution.x * (data.percentageX / 100.0f);
	float imageY = m_resolution.y * (data.percentageY / 100.0f);

	float imageWidth = m_resolution.x * (data.widthPercent / 100.0f);
	float imageHeight = m_resolution.y * (data.heightPercent / 100.0f);

	Texture* image = m_textureCache.getTexture(imagePath);

	GLfloat fightUI[]
	{
		//TOP Environment
		imageX - imageWidth, imageY - imageHeight, 0.0f,		0.0f, 0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		imageX - imageWidth, imageY + imageHeight, 0.0f,		0.0f, 0.0f, 0.0f, 0.0f,		0.0f, 1.0f,
		imageX + imageWidth, imageY + imageHeight, 0.0f,		0.0f, 0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		imageX + imageWidth, imageY - imageHeight, 0.0f,		0.0f, 0.0f,	0.0f, 0.0f,		1.0f, 0.0f,
	};

	GLuint indices1[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(fightUI, sizeof(fightUI));
	EBO EBO1(indices1, sizeof(indices1));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	image->Bind();
	VAO1.Bind();

	positionCamera(glm::vec3((m_playerCoord->xTile * m_tileSize) - (m_resolution.x / 2) + (m_tileSize / 2.0f) + m_playerCoord->screenX, (m_playerCoord->yTile * m_tileSize) - (m_resolution.y / 2) + (m_tileSize / 2.0f) + m_playerCoord->screenY, 0.0f));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO1.Unbind();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	image->Unbind();
	//image.Delete();
}

void Renderer::renderDynamicImage(DynamicImageRenderData data)
{
	std::string imagePath = data.dynamicImage;

	if (imagePath.size() == 0)
		return;

	float imageX = m_resolution.x * (data.percentageX / 100.0f);
	float imageY = m_resolution.y * (data.percentageY / 100.0f);

	float imageWidth = m_resolution.x * (data.widthPercent / 100.0f);
	float imageHeight = m_resolution.y * (data.heightPercent / 100.0f);

	Texture* image = m_textureCache.getTexture(imagePath);

	GLfloat fightUI[]
	{
		//TOP Environment
		imageX - imageWidth, imageY - imageHeight, data.alpha,		data.color.r, data.color.g, data.color.b, data.color.a,		data.imageTextureCoords.bottomLeftX, data.imageTextureCoords.bottomLeftY,
		imageX - imageWidth, imageY + imageHeight, data.alpha,		data.color.r, data.color.g, data.color.b, data.color.a,		data.imageTextureCoords.topLeftX, data.imageTextureCoords.topLeftY,
		imageX + imageWidth, imageY + imageHeight, data.alpha,		data.color.r, data.color.g, data.color.b, data.color.a,		data.imageTextureCoords.topRightX, data.imageTextureCoords.topRightY,
		imageX + imageWidth, imageY - imageHeight, data.alpha,		data.color.r, data.color.g, data.color.b, data.color.a,		data.imageTextureCoords.bottomRightX, data.imageTextureCoords.bottomRightY,
	};

	GLuint indices1[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(fightUI, sizeof(fightUI));
	EBO EBO1(indices1, sizeof(indices1));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	image->Bind();
	VAO1.Bind();

	positionCamera(glm::vec3((m_playerCoord->xTile * m_tileSize) - (m_resolution.x / 2) + (m_tileSize / 2.0f) + m_playerCoord->screenX, (m_playerCoord->yTile * m_tileSize) - (m_resolution.y / 2) + (m_tileSize / 2.0f) + m_playerCoord->screenY, 0.0f));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO1.Unbind();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	image->Unbind();
	//image.Delete();
}

void Renderer::renderMap()
{
	//m_mapData.yTileSize * m_tileSize * m_viewScale
	//m_mapData.xTileSize * m_tileSize * m_viewScale
	
	GLfloat fightUI[]
	{
		//TOP Environment
		0.0f, 0.0f, 0.0f,																0.0f, 0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		0.0f, m_mapData.yTileSize * m_tileSize, 0.0f,									0.0f, 0.0f, 0.0f, 0.0f,		0.0f, 1.0f,
		m_mapData.xTileSize * m_tileSize, m_mapData.yTileSize * m_tileSize, 0.0f,		0.0f, 0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		m_mapData.xTileSize * m_tileSize, 0.0f, 0.0f,									0.0f, 0.0f,	0.0f, 0.0f,		1.0f, 0.0f,

	};

	GLuint indices1[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(fightUI, sizeof(fightUI));
	EBO EBO1(indices1, sizeof(indices1));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	m_mapData.texture.Bind();
	VAO1.Bind();

	positionCamera(glm::vec3(0, 0, 0));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO1.Unbind();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	m_mapData.texture.Unbind();
}

void Renderer::renderBackground()
{
	GLfloat fightUI[]
	{
		//TOP Environment
		0.0f, 0.0f, 0.0f,							0.0f, 0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		0.0f, m_resolution.y, 0.0f,					0.0f, 0.0f, 0.0f, 0.0f,		0.0f, 1.0f,
		m_resolution.x, m_resolution.y, 0.0f,		0.0f, 0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		m_resolution.x, 0.0f, 0.0f,					0.0f, 0.0f,	0.0f, 0.0f,		1.0f, 0.0f,
	};

	GLuint indices1[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(fightUI, sizeof(fightUI));
	EBO EBO1(indices1, sizeof(indices1));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	m_sceneBackground.Bind();
	VAO1.Bind();

	positionCamera(glm::vec3((m_playerCoord->xTile * m_tileSize) - (m_resolution.x / 2) + (m_tileSize / 2.0f) + m_playerCoord->screenX, (m_playerCoord->yTile * m_tileSize) - (m_resolution.y / 2) + (m_tileSize / 2.0f) + m_playerCoord->screenY, 0.0f));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO1.Unbind();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	m_sceneBackground.Unbind();
}

void Renderer::renderText(std::string text, float x, float y,unsigned int fontSize, Alignment alignment, Color fontColor, int textWrapPixels, float textWrapOffset)
{
	m_textRenderer->renderText(text, x, y, fontSize, alignment, fontColor, textWrapPixels, textWrapOffset);
}

void Renderer::renderRectangle(RectangleRenderData data)
{
	float x = m_resolution.x * (data.bottomLeftXPercentage / 100.0f);
	float y = m_resolution.y * (data.bottomLeftYPercentage / 100.0f);

	float width = m_resolution.x * (*data.widthPercent / 100.0f);
	float height = m_resolution.y * (data.heightPercent / 100.0f);

	GLfloat fightUI[]
	{
		//TOP Environment
		x, y, 0.0f,							colorMap[data.color].r, colorMap[data.color].g, colorMap[data.color].b, 0.0f,
		x, y + height, 0.0f,				colorMap[data.color].r, colorMap[data.color].g, colorMap[data.color].b, 0.0f,
		x + width, y + height, 0.0f,		colorMap[data.color].r, colorMap[data.color].g, colorMap[data.color].b, 0.0f,
		x + width, y, 0.0f,					colorMap[data.color].r, colorMap[data.color].g, colorMap[data.color].b, 0.0f,

	};

	GLuint indices1[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(fightUI, sizeof(fightUI));
	EBO EBO1(indices1, sizeof(indices1));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	VAO1.Bind();

	positionCamera(glm::vec3((m_playerCoord->xTile * m_tileSize) - (m_resolution.x / 2) + (m_tileSize / 2.0f) + m_playerCoord->screenX, (m_playerCoord->yTile * m_tileSize) - (m_resolution.y / 2) + (m_tileSize / 2.0f) + m_playerCoord->screenY, 0.0f));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO1.Unbind();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
}

void Renderer::renderTexture(Texture* texture)
{
	if (texture == nullptr)
	{
		std::cout << "[RENDERER] Recieved null Texture" << std::endl;
		return;
	}

	texture->texUnit(m_shader, "tex0", 0);

	GLfloat fightUI[]
	{
		//TOP Environment
		0.0f, 0.0f, 0.0f,							0.0f, 0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		0.0f, m_resolution.y, 0.0f,					0.0f, 0.0f, 0.0f, 0.0f,		0.0f, 1.0f,
		m_resolution.x, m_resolution.y, 0.0f,		0.0f, 0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		m_resolution.x, 0.0f, 0.0f,					0.0f, 0.0f,	0.0f, 0.0f,		1.0f, 0.0f,

	};

	GLuint indices1[] =
	{
		//BOTTOM Display Bar
		0, 2, 1,
		0, 3, 2
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(fightUI, sizeof(fightUI));
	EBO EBO1(indices1, sizeof(indices1));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	texture->Bind();
	VAO1.Bind();

	positionCamera(glm::vec3((m_playerCoord->xTile * m_tileSize) - (m_resolution.x / 2) + (m_tileSize / 2.0f) + m_playerCoord->screenX, (m_playerCoord->yTile * m_tileSize) - (m_resolution.y / 2) + (m_tileSize / 2.0f) + m_playerCoord->screenY, 0.0f));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	VAO1.Unbind();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	texture->Unbind();
}

void Renderer::renderPolygon(PolygonData data)
{
	if (!data.visible)
		return;

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(data.verticeData, sizeof(data.verticeData));
	EBO EBO1(data.indiceData, sizeof(data.indiceData));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	VAO1.Bind();

	positionCamera(glm::vec3((m_playerCoord->xTile * m_tileSize) - (m_resolution.x / 2) + (m_tileSize / 2.0f) + m_playerCoord->screenX, (m_playerCoord->yTile * m_tileSize) - (m_resolution.y / 2) + (m_tileSize / 2.0f) + m_playerCoord->screenY, 0.0f));

	glDrawElements(GL_TRIANGLES, data.indicesToDraw, GL_UNSIGNED_INT, 0);
	VAO1.Unbind();

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
}

void Renderer::loadCharacterTextures(std::vector<CharacterID> ids)
{
	for (CharacterID id : ids)
	{
		if (m_characterTextures.find(id) == m_characterTextures.end())
			m_characterTextures[id] = Texture(g_CharacterTextureLocations[id].c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	}
}

void Renderer::loadMap(SectionID id, int width, int height)
{
	if (m_mapData.textureLoaded)
		m_mapData.texture.Delete();
	m_mapData = { (float)width, (float)height, Texture(g_MapTextureLocations[id].c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE), true };
}

void Renderer::loadBackground(std::string path)
{
	m_sceneBackground = Texture(path.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
}

void Renderer::unloadCharacters()
{
	//TODO: Unload Characters in the game
	for (auto it = m_characterTextures.begin(); it != m_characterTextures.end(); it++)
		it->second.Delete();

	m_characterTextures.clear();
}

void Renderer::positionCamera(glm::vec3 translate)
{
	glm::vec3 camPosition = glm::vec3((m_playerCoord->xTile * m_tileSize) - (m_resolution.x / 2) + (m_tileSize / 2.0f) + m_playerCoord->screenX , (m_playerCoord->yTile * m_tileSize) - (m_resolution.y / 2) + (m_tileSize / 2.0f) + m_playerCoord->screenY, 0.0f);

	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), translate);

	view = glm::lookAt(camPosition, camPosition + Orientation, Up);
	proj = glm::ortho(0.0f, m_resolution.x, 0.0f, m_resolution.y, -1.0f, 1.0f);

	glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "mvp"), 1, GL_FALSE, glm::value_ptr(proj * view * model));
}

void Renderer::adjustRenderSettings(PauseSettingsData* data)
{
	if (m_showFps)
		data->showFps = "ON";
	else
		data->showFps = "OFF";

	if (m_fullscreen)
		data->fullscreen = "ON";
	else
		data->fullscreen = "OFF";

	data->resolution = std::to_string((int)m_resolution.x) + "x" + std::to_string((int)m_resolution.y);
}

void Renderer::toggleShowFPS()
{
	if (m_showFps)
		m_showFps = false;
	else
		m_showFps = true;
}

void Renderer::toggleFullScreen()
{
	if (m_fullscreen)
	{
		glfwSetWindowMonitor(m_window, NULL, 0, 0, (int)m_resolution.x, (int)m_resolution.y, GLFW_DONT_CARE);
		m_fullscreen = false;
	}
	else
	{
		glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, (int)m_resolution.x, (int)m_resolution.y, GLFW_DONT_CARE);
		m_fullscreen = true;
	}

	if (!m_fullscreen)
		glfwSetWindowPos(m_window, 0, 30);
}

void Renderer::showFps()
{
	if (!m_showFps)
		return;

	float xPos = m_resolution.x * (100.0f / 100.0f);
	float yPos = m_resolution.y * (97.0f / 100.0f);

	if (!m_fullscreen)
		yPos -= m_resolution.y * (2.0f / 100.0f);

	unsigned int fontSize = (unsigned int)(m_resolution.x * (2.0f / 100.0f));

	m_textRenderer->renderText(std::to_string((int)(1.0f / m_timer->getDelta())) + " FPS", xPos, yPos, fontSize, Alignment::RIGHT_ALIGN, Color::BLACK);
}
