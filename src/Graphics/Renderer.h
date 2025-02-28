#pragma once

#include "PositionalData.h"
#include "../Menu/menuData.h"
#include "../Game/Timer.h"
#include "../ExternalData/saveData.h"
#include "Texture/TextureLocations.h"
#include "TextRenderer.h"
#include "Buffers/VAO.h"
#include "Buffers/EBO.h"
#include "TextureCache.h"

struct MapDrawData
{
	float xTileSize;
	float yTileSize;
	Texture texture;
	bool textureLoaded = false;
};

enum RendererResolutiion	//TODO: Figure out how to name these. Its a number but what is proper convention
{
	_1280x720,
	_1920x1080,
	_2560x1440
};

struct Resolution
{
	float x = 1280.0f;
	float y = 720.0f;

	operator RendererResolutiion const()
	{
		if (x == 1280)
			return RendererResolutiion::_1280x720;
		else if (x == 1920)
			return RendererResolutiion::_1920x1080;
		else
			return RendererResolutiion::_2560x1440;
	}
};

class Renderer
{
public:
	Renderer() {};
	~Renderer();

	void init(Coordinate* playerCoord, Timer* timer);
	void onUpdate(); 
	GLFWwindow* getSharedWindow() { return m_shared; };	//NOTE: Took 4 Hours to figure out how to render textures on seperate thread


	void load(RendererSave save);
	void loadNewGame();

	bool shouldClose();
	void clearBuffer();
	void pollUpdates();

	void clearCache();

	void setResolution(RendererResolutiion resolution);

	GLFWwindow* getWindow() { return m_window; };
	Resolution getResolution() { return m_resolution; };
	float getTileSize() { return m_tileSize; };
	float getDeltaTime() { return m_timer->getDelta(); }

	void renderCharacter(Position position, CharacterID trainerID);
	void renderButton(ButtonRenderData data, std::string text, bool highlight);
	void renderTextBox(TextBoxRenderData data, std::string text);
	void renderImage(ImageRenderData data);
	void renderDynamicImage(DynamicImageRenderData data);
	void renderMap();
	void renderBackground();
	void renderText(std::string text, float x, float y, unsigned int fontSize, Alignment alignment, Color fontColor, int textWrapPixels = -1, float textWrapOffset = 0.0f);
	void renderRectangle(RectangleRenderData data);
	void renderTexture(Texture* texture);
	void renderPolygon(PolygonData data);

public:

	void loadCharacterTextures(std::vector<CharacterID> ids);	
	void loadMap(SectionID id, int width, int height);
	void loadBackground(std::string path);

	void unloadCharacters();

public:
	void adjustRenderSettings(PauseSettingsData* data);

	void toggleShowFPS();
	void toggleFullScreen();

	operator RendererSave const() { return { m_resolution, m_fullscreen, m_showFps }; };

	float getTextLength(std::string text, unsigned int fontSize) { return m_textRenderer->getTextLength(text, fontSize); }
private:

	void positionCamera(glm::vec3 translate);

	void showFps();

private:

	GLFWwindow* m_window = nullptr;	
	GLFWwindow* m_shared = nullptr;
	Shader m_shader;
	TextRenderer* m_textRenderer = nullptr;
	Timer* m_timer = nullptr;

	TextureCache m_textureCache;

	Resolution m_resolution;
	Coordinate* m_playerCoord = nullptr;

	std::unordered_map<CharacterID, Texture> m_characterTextures;
	std::unordered_map<PokemonID, Texture> m_pokemonTextures;
	MapDrawData m_mapData;

private:
	float m_viewScale = 1.0f;
	float m_tileSize = 200.0f;
	//float (m_tileSize / 2.0f) = m_tileSize / 2.0f;

private:
	bool m_fullscreen = false;
	bool m_showFps = false;

	Texture m_sceneBackground;
};