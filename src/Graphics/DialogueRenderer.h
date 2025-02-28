#pragma once
#include "../Menu/Menu.h"
#include "../Game/Timer.h"
#include "../Menu/MenuFunction/MenuFunction.h"
#include "../Menu/MenuFunction/MenuSetup.h"

class DialogueRenderer
{
public:

	DialogueRenderer() {};

	void setup(Menu* menu, Input* input, Timer* timer, Renderer* renderer)
	{ 
		m_menu = menu;
		m_input = input;
		m_timer = timer;
		m_renderer = renderer;

		MenuSetup::setupDialogueRenderer(m_menu, &m_dialogueText);

		m_dialogueText.topButtonRenderData.visible = &m_dialogueText.buttonActiveStatus;
		m_dialogueText.bottomButtonRenderData.visible = &m_dialogueText.buttonActiveStatus;

		float size = 0.15f;
		float width = size * 9.0f;
		float height = size * 16.0f;

		m_dialogueText.nextArrow = ImageRenderData{ 96.0f, 7.0f, width, height, g_overlayTextureLocations[MenuOverlay::DIALOGUE_DOWN_ARROW], nullptr, &m_dialogueText.nextArrowVisible, false };
	};

	void setSpeakerName(std::string name)
	{
		m_dialogueText.speakerName = name;

		if (name == "")
		{
			m_dialogueText.nameOutline.visible = false;
			return;
		}

		float fontSizePercentage = 5.0f;
		unsigned int fontSize = (unsigned int)(m_renderer->getResolution().x * (fontSizePercentage / 100.0f));

		MenuFunction::adjustSpeakerNameContainer(name, fontSizePercentage, m_renderer->getTextLength(name, fontSize), &m_dialogueText.nameOutline, m_renderer->getResolution().x, 5.0f, m_boxYPercent + 0.15f);
	}

	void setDialogue(std::string topLine, std::string bottomLine, bool awaitClick, bool battleDialogue = false, int* requestedData = nullptr, std::string topOption = "", std::string bottomOption = "")
	{
		//TODO: Take in Dialogue Object
		m_topLine = topLine;
		m_bottomLine = bottomLine;
		m_awaitClick = awaitClick;
		m_battleDialogue = battleDialogue;
		m_dialogueText.topLine = "";
		m_dialogueText.bottomLine = "";
		m_menu->setOverlay(MenuOverlay::DIALOGUE);
		m_menu->setCanLeave(false);
		m_timer->resetTimer();
		m_count = 0;

		if (m_battleDialogue)
			m_menu->setOverlayBackground(MenuOverlay::DIALOGUE, new ImageRenderData{ 50.0f, m_boxYPercent, 50.0f,  m_boxHeightPercent, g_overlayTextureLocations[MenuOverlay::BATTLE_CHAT] });
		else
			m_menu->setOverlayBackground(MenuOverlay::DIALOGUE, new ImageRenderData{ 50.0f, m_boxYPercent, 50.0f, m_boxHeightPercent, g_overlayTextureLocations[MenuOverlay::DIALOGUE] });

		if (requestedData == nullptr)
			return;

		m_requestedData = requestedData;
		m_dialogueText.topButtonOption = topOption;
		m_dialogueText.bottomButtonOption = bottomOption;
		*m_requestedData = NONE;
		m_menu->setRequestedData(requestedData);
		m_input->setCanHoldInput(false);
	}

	bool rendereringDialogue()
	{

		if (m_topLine.size() == m_dialogueText.topLine.size() && m_bottomLine.size() == m_dialogueText.bottomLine.size())
		{

			if (m_requestedData != nullptr && m_dialogueText.buttonActiveStatus == true && *m_requestedData != NONE)
			{
				resetDialogueRenderer();
				return false;
			}
			else if (m_requestedData == nullptr && m_awaitClick && m_input->anyButtonPressed())	//TODO: Visualize await click
			{
				resetDialogueRenderer();
				return false;
			}
			else if (m_requestedData == nullptr && !m_awaitClick)
			{
				resetDialogueRenderer();
				return false;
			}

			if (m_requestedData != nullptr && !m_dialogueText.buttonActiveStatus)
				displayOptions();

			if (m_requestedData != nullptr)//TODO: Add delay before accepting inputs
			{
				m_input->onUpdate();
				m_menu->handleInputs();
			}
		}

		

		return true;
	}

	void resetDialogueRenderer()
	{
		setSpeakerName("");

		m_dialogueText.nextArrowVisible = false;
		m_requestedData = nullptr;
		m_dialogueText.buttonActiveStatus = false;
		m_input->setCanHoldInput(true);
		m_menu->clearRequestedData();
		m_menu->setOverlay(MenuOverlay::NONE);
		m_menu->setCanLeave(true);
	}

	void renderDownArrow()
	{
		if (m_topLine.size() != m_dialogueText.topLine.size() || m_bottomLine.size() != m_dialogueText.bottomLine.size())
			return;

		m_dialogueText.nextArrowVisible = true;

		//TODO: Animate with slight vertical bob
	}

	void renderDialogue()
	{
		m_menu->renderMenu();
		
		if (m_topLine.size() != m_dialogueText.topLine.size())
			addCharacter(m_topLine, true);
		else
			addCharacter(m_bottomLine, false);

		renderDownArrow();
	};

	void displayOptions()
	{
		// Height will always be consitent
		// Width will change with the text

		float fontSize = 40.0f;

		float widthSize = 100.0f;

		float wdith = (widthSize / 1000.0f) * 100.0f;
		float height = (50.0f / 563.0f) * 100.0f;

		float xPos = ((950.0f - (widthSize / 2.0f)) / 1000.0f) * 100.0f;
		float yPos = (150.0f / 563.0f) * 100.0f;

		float heightGap = height;

		m_dialogueText.topButtonRenderData.percentageX = xPos;
		m_dialogueText.topButtonRenderData.percentageY = yPos + heightGap;
		m_dialogueText.topButtonRenderData.widthPercent = wdith;
		m_dialogueText.topButtonRenderData.heightPercent = height;
		m_dialogueText.topButtonRenderData.fontSize = fontSize;
		m_dialogueText.topButtonRenderData.color = Color::WHITE;

		m_dialogueText.bottomButtonRenderData.percentageX = xPos;
		m_dialogueText.bottomButtonRenderData.percentageY = yPos;
		m_dialogueText.bottomButtonRenderData.widthPercent = wdith;
		m_dialogueText.bottomButtonRenderData.heightPercent = height;
		m_dialogueText.bottomButtonRenderData.fontSize = fontSize;
		m_dialogueText.bottomButtonRenderData.color = Color::WHITE;



		m_dialogueText.buttonActiveStatus = true;
	}

	bool getFasterText() { return m_fasterText; }
	void setFasterText(bool fasterText) { 

		if (fasterText != m_fasterText)
			toggleFasterText();
	}

	void toggleFasterText()
	{
		if (m_fasterText)
		{
			m_fasterText = false;
			m_textSpeed -= m_textSpeedIncrease;
		}
		else
		{
			m_fasterText = true;
			m_textSpeed += m_textSpeedIncrease;
		}
	}

	void adjustPauseDisplay(std::string* fasterText)
	{
		if (m_fasterText)
			*fasterText = "ON";
		else
			*fasterText = "OFF";
	}

private:

	void addCharacter(std::string line, bool top)
	{
		if (m_dialogueText.topLine == m_topLine && m_dialogueText.bottomLine == m_bottomLine)
			return;

		if (m_count >= 100)
		{
			if (top)
				m_dialogueText.topLine += line.at(m_dialogueText.topLine.size());
			else
				m_dialogueText.bottomLine += line.at(m_dialogueText.bottomLine.size());

			m_count = 0;
			return;
		}

		m_count += (int)(200 * m_timer->getDelta() * m_textSpeed);
	};

private:
	DialogueRendererData m_dialogueText;

	Renderer* m_renderer = nullptr;
	Menu* m_menu = nullptr;
	Input* m_input = nullptr;
	Timer* m_timer = nullptr;

	int m_count = 0;

	float m_textSpeed = 10;
	float m_textSpeedIncrease = 10;

	bool m_fasterText = false;

	std::string m_topLine;
	std::string m_bottomLine;
	bool m_awaitClick = false;
	bool m_battleDialogue = false;

	int* m_requestedData = nullptr;
private:

	const float m_boxYPercent = 12.5f;
	const float m_boxHeightPercent = 10.0f;
};