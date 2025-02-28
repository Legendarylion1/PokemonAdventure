#pragma once
#include <iostream>
#include <unordered_map>
#include "../../ExternalData/saveData.h"
#include "../../Menu/menuData.h"
#include "InputData.h"
#include <GLFW/glfw3.h>
#include <vector>

//TODO: Add a screen to ask if they would like to remove a key bind
//TODO: Also add an error screen to explain why we didnt replace the key bind

static DetectedJoyStick detectedJoystick;

class Input
{
public:
	Input(){};
	Input(InputVariables* inputs) {
		m_inputs = inputs;
		m_state = new GLFWgamepadstate{};
	};

	void setup(GLFWwindow* window, PauseSettingsData* pauseData);

	void onUpdate();

	void load(InputSave save);

	void setCanHoldInput(bool value) { m_canHoldInput = value; };
	bool anyButtonPressed();

	void updateKeyBinds(PauseSettingsData* data);
	bool changingInput(ControlType type, KeyPriority priority, InputRequest request);

	InputVariables* getInputVaraibles() { return m_inputs; }

	operator InputSave const() { return getInputSave(); }

private:

	bool canBePressed(InputRequest request);

	bool getKeyboardInput(InputKey key);
	bool getControllerStickInput(InputKey key);
	bool getControllerButtonInput(InputKey key);

	void updateKeyEvents();
	void updateInputValues();
	void updateHeldInputValues();

	std::string getNewKeyboardPress();
	std::string getNewControllerPress();

private:

	RequestType getRequestFromInput(std::string input, ControlType desiredType);

	void removeInput(std::string input);
	void addInput(std::string input, RequestType type);

	InputSave getInputSave();

	void resetInputs();
	void detectController();

private:
	InputVariables* m_inputs = nullptr;
	InputVariables m_heldInputsOld;
	GLFWwindow* m_window = nullptr;

	PauseControlData* m_keyboardData = nullptr;
	PauseControlData* m_controllerData = nullptr;

	bool m_canHoldInput = true;

	int m_joystickID = -1;

	GLFWgamepadstate* m_state = nullptr;

private:

	// Let me be the first to say that this does not scale well
	// I plan to refactor it but I would like to finish the rest of the game first.
	// But yea. This is a lot

	std::vector<InputKey> m_allKeys
	{
		InputKey{GLFW_KEY_SPACE, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_0, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_1, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_2, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_3, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_4, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_5, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_6, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_7, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_8, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_9, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_A, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_B, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_C, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_D, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_E, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_F, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_G, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_H, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_I, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_J, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_K, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_L, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_M, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_N, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_O, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_P, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_Q, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_R, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_S, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_T, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_U, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_V, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_W, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_X, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_Y, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_Z, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_LEFT_SHIFT, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_LEFT_CONTROL, ControlType::KEYBOARD},
		InputKey{GLFW_KEY_LEFT_ALT, ControlType::KEYBOARD},

		InputKey{GLFW_GAMEPAD_BUTTON_A, ControlType::CONTROLLER_BUTTON},
		InputKey{GLFW_GAMEPAD_BUTTON_B, ControlType::CONTROLLER_BUTTON},
		InputKey{GLFW_GAMEPAD_BUTTON_X, ControlType::CONTROLLER_BUTTON},
		InputKey{GLFW_GAMEPAD_BUTTON_Y, ControlType::CONTROLLER_BUTTON},
		InputKey{GLFW_GAMEPAD_BUTTON_LEFT_BUMPER, ControlType::CONTROLLER_BUTTON},
		InputKey{GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER, ControlType::CONTROLLER_BUTTON},
		InputKey{GLFW_GAMEPAD_BUTTON_BACK, ControlType::CONTROLLER_BUTTON},
		InputKey{GLFW_GAMEPAD_BUTTON_START, ControlType::CONTROLLER_BUTTON},
		InputKey{GLFW_GAMEPAD_BUTTON_GUIDE, ControlType::CONTROLLER_BUTTON},
		InputKey{GLFW_GAMEPAD_BUTTON_LEFT_THUMB, ControlType::CONTROLLER_BUTTON},
		InputKey{GLFW_GAMEPAD_BUTTON_RIGHT_THUMB, ControlType::CONTROLLER_BUTTON},
		InputKey{GLFW_GAMEPAD_BUTTON_DPAD_UP, ControlType::CONTROLLER_BUTTON},
		InputKey{GLFW_GAMEPAD_BUTTON_DPAD_RIGHT, ControlType::CONTROLLER_BUTTON},
		InputKey{GLFW_GAMEPAD_BUTTON_DPAD_DOWN, ControlType::CONTROLLER_BUTTON},
		InputKey{GLFW_GAMEPAD_BUTTON_DPAD_LEFT, ControlType::CONTROLLER_BUTTON},

		InputKey{GLFW_GAMEPAD_AXIS_LEFT_X, ControlType::CONTROLLER_STICK, StickDirection::stickLeft},
		InputKey{GLFW_GAMEPAD_AXIS_LEFT_X, ControlType::CONTROLLER_STICK, StickDirection::stickRight},
		InputKey{GLFW_GAMEPAD_AXIS_LEFT_Y, ControlType::CONTROLLER_STICK, StickDirection::stickUp},
		InputKey{GLFW_GAMEPAD_AXIS_LEFT_Y, ControlType::CONTROLLER_STICK, StickDirection::stickDown},

		InputKey{GLFW_GAMEPAD_AXIS_RIGHT_X, ControlType::CONTROLLER_STICK,  StickDirection::stickLeft},
		InputKey{GLFW_GAMEPAD_AXIS_RIGHT_X, ControlType::CONTROLLER_STICK,  StickDirection::stickRight},
		InputKey{GLFW_GAMEPAD_AXIS_RIGHT_Y, ControlType::CONTROLLER_STICK,  StickDirection::stickUp},
		InputKey{GLFW_GAMEPAD_AXIS_RIGHT_Y, ControlType::CONTROLLER_STICK,  StickDirection::stickDown},

		InputKey{GLFW_GAMEPAD_AXIS_LEFT_TRIGGER, ControlType::CONTROLLER_STICK, StickDirection::stickDown},
		InputKey{GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER, ControlType::CONTROLLER_STICK, StickDirection::stickDown},
	};

	std::unordered_map<RequestType, std::string, RequestTypeHashFunction> m_activeRequests
	{
		{{KeyPriority::MAIN, InputRequest::UP, ControlType::KEYBOARD	},	keyBinds::w},
		{{KeyPriority::MAIN, InputRequest::DOWN, ControlType::KEYBOARD	},	keyBinds::s},
		{{KeyPriority::MAIN, InputRequest::LEFT, ControlType::KEYBOARD	},	keyBinds::a},
		{{KeyPriority::MAIN, InputRequest::RIGHT, ControlType::KEYBOARD	},	keyBinds::d},
		{{KeyPriority::MAIN, InputRequest::BACK, ControlType::KEYBOARD	},	keyBinds::q},
		{{KeyPriority::MAIN, InputRequest::PAUSE, ControlType::KEYBOARD	},	keyBinds::p},
		{{KeyPriority::MAIN, InputRequest::SELECT, ControlType::KEYBOARD},	keyBinds::e},
		{{KeyPriority::MAIN, InputRequest::SPRINT, ControlType::KEYBOARD},	keyBinds::left_shift},
		{{KeyPriority::ALT, InputRequest::UP, ControlType::KEYBOARD		},	keyBinds::i},
		{{KeyPriority::ALT, InputRequest::DOWN, ControlType::KEYBOARD	},	keyBinds::k},
		{{KeyPriority::ALT, InputRequest::LEFT, ControlType::KEYBOARD	},	keyBinds::j},
		{{KeyPriority::ALT, InputRequest::RIGHT, ControlType::KEYBOARD	},	keyBinds::l},
		{{KeyPriority::ALT, InputRequest::BACK, ControlType::KEYBOARD	},	""},
		{{KeyPriority::ALT, InputRequest::PAUSE, ControlType::KEYBOARD	},	""},
		{{KeyPriority::ALT, InputRequest::SELECT, ControlType::KEYBOARD	},	""},
		{{KeyPriority::ALT, InputRequest::SPRINT, ControlType::KEYBOARD	},	""},


		{{KeyPriority::MAIN, InputRequest::UP, ControlType::CONTROLLER_BUTTON		},		keyBinds::gamepad_dpad_up},
		{{KeyPriority::MAIN, InputRequest::DOWN, ControlType::CONTROLLER_BUTTON		},		keyBinds::gamepad_dpad_down},
		{{KeyPriority::MAIN, InputRequest::LEFT, ControlType::CONTROLLER_BUTTON		},		keyBinds::gamepad_dpad_left},
		{{KeyPriority::MAIN, InputRequest::RIGHT, ControlType::CONTROLLER_BUTTON	},		keyBinds::gamepad_dpad_right},
		{{KeyPriority::MAIN, InputRequest::BACK, ControlType::CONTROLLER_BUTTON		},		keyBinds::gamepad_b},
		{{KeyPriority::MAIN, InputRequest::PAUSE, ControlType::CONTROLLER_BUTTON	},		keyBinds::gamepad_start},
		{{KeyPriority::MAIN, InputRequest::SELECT, ControlType::CONTROLLER_BUTTON	},		keyBinds::gamepad_a},
		{{KeyPriority::MAIN, InputRequest::SPRINT, ControlType::CONTROLLER_BUTTON	},		keyBinds::gamepad_y},
		{{KeyPriority::ALT, InputRequest::UP, ControlType::CONTROLLER_BUTTON		},		""},
		{{KeyPriority::ALT, InputRequest::DOWN, ControlType::CONTROLLER_BUTTON		},		""},
		{{KeyPriority::ALT, InputRequest::LEFT, ControlType::CONTROLLER_BUTTON		},		""},
		{{KeyPriority::ALT, InputRequest::RIGHT, ControlType::CONTROLLER_BUTTON		},		""},
		{{KeyPriority::ALT, InputRequest::BACK, ControlType::CONTROLLER_BUTTON		},		""},
		{{KeyPriority::ALT, InputRequest::PAUSE, ControlType::CONTROLLER_BUTTON		},		""},
		{{KeyPriority::ALT, InputRequest::SELECT, ControlType::CONTROLLER_BUTTON	},		""},
		{{KeyPriority::ALT, InputRequest::SPRINT, ControlType::CONTROLLER_BUTTON	},		""},
	};

	std::unordered_map<InputKey, InputRequest, InputKeyHashFunction> m_keyEvents
	{
		{InputKey{GLFW_KEY_SPACE, ControlType::KEYBOARD},	InputRequest::EMPTY},
		{InputKey{GLFW_KEY_0, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_1, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_2, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_3, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_4, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_5, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_6, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_7, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_8, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_9, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_A, ControlType::KEYBOARD},		InputRequest::LEFT},
		{InputKey{GLFW_KEY_B, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_C, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_D, ControlType::KEYBOARD},		InputRequest::RIGHT},
		{InputKey{GLFW_KEY_E, ControlType::KEYBOARD},		InputRequest::SELECT},
		{InputKey{GLFW_KEY_F, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_G, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_H, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_I, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_J, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_K, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_L, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_M, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_N, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_O, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_P, ControlType::KEYBOARD},		InputRequest::PAUSE},
		{InputKey{GLFW_KEY_Q, ControlType::KEYBOARD},		InputRequest::BACK},
		{InputKey{GLFW_KEY_R, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_S, ControlType::KEYBOARD},		InputRequest::DOWN},
		{InputKey{GLFW_KEY_T, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_U, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_V, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_W, ControlType::KEYBOARD},		InputRequest::UP},
		{InputKey{GLFW_KEY_X, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_Y, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_Z, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_LEFT_SHIFT, ControlType::KEYBOARD},		InputRequest::SPRINT},
		{InputKey{GLFW_KEY_LEFT_CONTROL, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_KEY_LEFT_ALT, ControlType::KEYBOARD},		InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_BUTTON_A, ControlType::CONTROLLER_BUTTON}, InputRequest::SELECT},
		{InputKey{GLFW_GAMEPAD_BUTTON_B, ControlType::CONTROLLER_BUTTON}, InputRequest::BACK},
		{InputKey{GLFW_GAMEPAD_BUTTON_X, ControlType::CONTROLLER_BUTTON}, InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_BUTTON_Y, ControlType::CONTROLLER_BUTTON}, InputRequest::SPRINT},
		{InputKey{GLFW_GAMEPAD_BUTTON_LEFT_BUMPER, ControlType::CONTROLLER_BUTTON}, InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER, ControlType::CONTROLLER_BUTTON}, InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_BUTTON_BACK, ControlType::CONTROLLER_BUTTON}, InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_BUTTON_START, ControlType::CONTROLLER_BUTTON}, InputRequest::PAUSE},
		{InputKey{GLFW_GAMEPAD_BUTTON_GUIDE, ControlType::CONTROLLER_BUTTON}, InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_BUTTON_LEFT_THUMB, ControlType::CONTROLLER_BUTTON}, InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_BUTTON_RIGHT_THUMB, ControlType::CONTROLLER_BUTTON}, InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_BUTTON_DPAD_UP, ControlType::CONTROLLER_BUTTON}, InputRequest::UP},
		{InputKey{GLFW_GAMEPAD_BUTTON_DPAD_RIGHT, ControlType::CONTROLLER_BUTTON}, InputRequest::RIGHT},
		{InputKey{GLFW_GAMEPAD_BUTTON_DPAD_DOWN, ControlType::CONTROLLER_BUTTON}, InputRequest::DOWN},
		{InputKey{GLFW_GAMEPAD_BUTTON_DPAD_LEFT, ControlType::CONTROLLER_BUTTON}, InputRequest::LEFT},
		{InputKey{GLFW_GAMEPAD_AXIS_LEFT_X, ControlType::CONTROLLER_STICK, StickDirection::stickLeft}, InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_AXIS_LEFT_X, ControlType::CONTROLLER_STICK, StickDirection::stickRight}, InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_AXIS_LEFT_Y, ControlType::CONTROLLER_STICK, StickDirection::stickUp}, InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_AXIS_LEFT_Y, ControlType::CONTROLLER_STICK, StickDirection::stickDown}, InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_AXIS_RIGHT_X, ControlType::CONTROLLER_STICK,  StickDirection::stickLeft}, InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_AXIS_RIGHT_X, ControlType::CONTROLLER_STICK,  StickDirection::stickRight}, InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_AXIS_RIGHT_Y, ControlType::CONTROLLER_STICK,  StickDirection::stickUp}, InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_AXIS_RIGHT_Y, ControlType::CONTROLLER_STICK,  StickDirection::stickDown}, InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_AXIS_LEFT_TRIGGER, ControlType::CONTROLLER_STICK, StickDirection::stickDown}, InputRequest::EMPTY},
		{InputKey{GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER, ControlType::CONTROLLER_STICK, StickDirection::stickDown}, InputRequest::EMPTY},
	};

	std::unordered_map<InputRequest, InputKeyState> m_requestStatus
	{
		{InputRequest::UP, {false, false, false}},
		{InputRequest::DOWN, {false, false, false}},
		{InputRequest::LEFT, {false, false, false}},
		{InputRequest::RIGHT, {false, false, false}},
		{InputRequest::BACK, {false, false, false}},
		{InputRequest::PAUSE, {false, false, false}},
		{InputRequest::SELECT, {false, false, false}},
		{InputRequest::SPRINT, {false, false, false}}
	};

	std::unordered_map<InputKey, std::string, InputKeyHashFunction> m_inputDisplay
	{
		{InputKey{GLFW_KEY_SPACE, ControlType::KEYBOARD},	keyBinds::space	},
		{InputKey{GLFW_KEY_ESCAPE, ControlType::KEYBOARD},	keyBinds::escape},
		{InputKey{GLFW_KEY_UP, ControlType::KEYBOARD},		keyBinds::arrow_up},
		{InputKey{GLFW_KEY_DOWN, ControlType::KEYBOARD},	keyBinds::arrow_down},
		{InputKey{GLFW_KEY_LEFT, ControlType::KEYBOARD},	keyBinds::arrow_left},
		{InputKey{GLFW_KEY_RIGHT, ControlType::KEYBOARD},	keyBinds::arrow_right},
		{InputKey{GLFW_KEY_0, ControlType::KEYBOARD},		keyBinds::zero},
		{InputKey{GLFW_KEY_1, ControlType::KEYBOARD},		keyBinds::one},
		{InputKey{GLFW_KEY_2, ControlType::KEYBOARD},		keyBinds::two},
		{InputKey{GLFW_KEY_3, ControlType::KEYBOARD},		keyBinds::three},
		{InputKey{GLFW_KEY_4, ControlType::KEYBOARD},		keyBinds::four},
		{InputKey{GLFW_KEY_5, ControlType::KEYBOARD},		keyBinds::five},
		{InputKey{GLFW_KEY_6, ControlType::KEYBOARD},		keyBinds::six},
		{InputKey{GLFW_KEY_7, ControlType::KEYBOARD},		keyBinds::seven},
		{InputKey{GLFW_KEY_8, ControlType::KEYBOARD},		keyBinds::eight},
		{InputKey{GLFW_KEY_9, ControlType::KEYBOARD},		keyBinds::nine},
		{InputKey{GLFW_KEY_A, ControlType::KEYBOARD},		keyBinds::a},
		{InputKey{GLFW_KEY_B, ControlType::KEYBOARD},		keyBinds::b},
		{InputKey{GLFW_KEY_C, ControlType::KEYBOARD},		keyBinds::c},
		{InputKey{GLFW_KEY_D, ControlType::KEYBOARD},		keyBinds::d},
		{InputKey{GLFW_KEY_E, ControlType::KEYBOARD},		keyBinds::e},
		{InputKey{GLFW_KEY_F, ControlType::KEYBOARD},		keyBinds::f},
		{InputKey{GLFW_KEY_G, ControlType::KEYBOARD},		keyBinds::g},
		{InputKey{GLFW_KEY_H, ControlType::KEYBOARD},		keyBinds::h},
		{InputKey{GLFW_KEY_I, ControlType::KEYBOARD},		keyBinds::i},
		{InputKey{GLFW_KEY_J, ControlType::KEYBOARD},		keyBinds::j},
		{InputKey{GLFW_KEY_K, ControlType::KEYBOARD},		keyBinds::k},
		{InputKey{GLFW_KEY_L, ControlType::KEYBOARD},		keyBinds::l},
		{InputKey{GLFW_KEY_M, ControlType::KEYBOARD},		keyBinds::m},
		{InputKey{GLFW_KEY_N, ControlType::KEYBOARD},		keyBinds::n},
		{InputKey{GLFW_KEY_O, ControlType::KEYBOARD},		keyBinds::o},
		{InputKey{GLFW_KEY_P, ControlType::KEYBOARD},		keyBinds::p},
		{InputKey{GLFW_KEY_Q, ControlType::KEYBOARD},		keyBinds::q},
		{InputKey{GLFW_KEY_R, ControlType::KEYBOARD},		keyBinds::r},
		{InputKey{GLFW_KEY_S, ControlType::KEYBOARD},		keyBinds::s},
		{InputKey{GLFW_KEY_T, ControlType::KEYBOARD},		keyBinds::t},
		{InputKey{GLFW_KEY_U, ControlType::KEYBOARD},		keyBinds::u},
		{InputKey{GLFW_KEY_V, ControlType::KEYBOARD},		keyBinds::v},
		{InputKey{GLFW_KEY_W, ControlType::KEYBOARD},		keyBinds::w},
		{InputKey{GLFW_KEY_X, ControlType::KEYBOARD},		keyBinds::x},
		{InputKey{GLFW_KEY_Y, ControlType::KEYBOARD},		keyBinds::y},
		{InputKey{GLFW_KEY_Z, ControlType::KEYBOARD},		keyBinds::z},
		{InputKey{GLFW_KEY_LEFT_SHIFT, ControlType::KEYBOARD},		keyBinds::left_shift},
		{InputKey{GLFW_KEY_LEFT_CONTROL, ControlType::KEYBOARD},		keyBinds::left_control},
		{InputKey{GLFW_KEY_LEFT_ALT, ControlType::KEYBOARD},		keyBinds::left_alt},
		{InputKey{GLFW_GAMEPAD_BUTTON_A, ControlType::CONTROLLER_BUTTON},				keyBinds::gamepad_a},
		{InputKey{GLFW_GAMEPAD_BUTTON_B, ControlType::CONTROLLER_BUTTON},				keyBinds::gamepad_b},
		{InputKey{GLFW_GAMEPAD_BUTTON_X, ControlType::CONTROLLER_BUTTON},				keyBinds::gamepad_x},
		{InputKey{GLFW_GAMEPAD_BUTTON_Y, ControlType::CONTROLLER_BUTTON},				keyBinds::gamepad_y},
		{InputKey{GLFW_GAMEPAD_BUTTON_LEFT_BUMPER, ControlType::CONTROLLER_BUTTON},		keyBinds::gamepad_left_bumper},
		{InputKey{GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER, ControlType::CONTROLLER_BUTTON},	keyBinds::gamepad_right_bumper},
		{InputKey{GLFW_GAMEPAD_BUTTON_BACK, ControlType::CONTROLLER_BUTTON},			keyBinds::gamepad_back},
		{InputKey{GLFW_GAMEPAD_BUTTON_START, ControlType::CONTROLLER_BUTTON},			keyBinds::gamepad_start},
		{InputKey{GLFW_GAMEPAD_BUTTON_GUIDE, ControlType::CONTROLLER_BUTTON},			keyBinds::gamepad_guide},
		{InputKey{GLFW_GAMEPAD_BUTTON_LEFT_THUMB, ControlType::CONTROLLER_BUTTON},		keyBinds::gamepad_left_thumb},
		{InputKey{GLFW_GAMEPAD_BUTTON_RIGHT_THUMB, ControlType::CONTROLLER_BUTTON},		keyBinds::gamepad_right_thumb},
		{InputKey{GLFW_GAMEPAD_BUTTON_DPAD_UP, ControlType::CONTROLLER_BUTTON},			keyBinds::gamepad_dpad_up},
		{InputKey{GLFW_GAMEPAD_BUTTON_DPAD_RIGHT, ControlType::CONTROLLER_BUTTON},		keyBinds::gamepad_dpad_right},
		{InputKey{GLFW_GAMEPAD_BUTTON_DPAD_DOWN, ControlType::CONTROLLER_BUTTON},		keyBinds::gamepad_dpad_down},
		{InputKey{GLFW_GAMEPAD_BUTTON_DPAD_LEFT, ControlType::CONTROLLER_BUTTON},		keyBinds::gamepad_dpad_left},
		{InputKey{GLFW_GAMEPAD_AXIS_LEFT_X, ControlType::CONTROLLER_STICK, StickDirection::stickLeft},		 keyBinds::gamepad_left_stick_left},
		{InputKey{GLFW_GAMEPAD_AXIS_LEFT_X, ControlType::CONTROLLER_STICK, StickDirection::stickRight},		 keyBinds::gamepad_left_stick_right},
		{InputKey{GLFW_GAMEPAD_AXIS_LEFT_Y, ControlType::CONTROLLER_STICK, StickDirection::stickUp},		 keyBinds::gamepad_left_stick_up},
		{InputKey{GLFW_GAMEPAD_AXIS_LEFT_Y, ControlType::CONTROLLER_STICK, StickDirection::stickDown},		 keyBinds::gamepad_left_stick_down},
		{InputKey{GLFW_GAMEPAD_AXIS_RIGHT_X, ControlType::CONTROLLER_STICK,  StickDirection::stickLeft},	 keyBinds::gamepad_right_stick_left},
		{InputKey{GLFW_GAMEPAD_AXIS_RIGHT_X, ControlType::CONTROLLER_STICK,  StickDirection::stickRight},	 keyBinds::gamepad_right_stick_right},
		{InputKey{GLFW_GAMEPAD_AXIS_RIGHT_Y, ControlType::CONTROLLER_STICK,  StickDirection::stickUp},		 keyBinds::gamepad_right_stick_up},
		{InputKey{GLFW_GAMEPAD_AXIS_RIGHT_Y, ControlType::CONTROLLER_STICK,  StickDirection::stickDown},	 keyBinds::gamepad_right_stick_down},
		{InputKey{GLFW_GAMEPAD_AXIS_LEFT_TRIGGER, ControlType::CONTROLLER_STICK, StickDirection::stickDown}, keyBinds::gamepad_left_trigger},
		{InputKey{GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER, ControlType::CONTROLLER_STICK, StickDirection::stickDown},keyBinds::gamepad_right_trigger}
	};

	std::unordered_map<std::string, InputKey> m_displayInput
	{
		{keyBinds::space, InputKey{GLFW_KEY_SPACE, ControlType::KEYBOARD}},
		{keyBinds::escape, InputKey{GLFW_KEY_ESCAPE, ControlType::KEYBOARD}},
		{keyBinds::arrow_up, InputKey{GLFW_KEY_UP, ControlType::KEYBOARD}},
		{keyBinds::arrow_down, InputKey{GLFW_KEY_DOWN, ControlType::KEYBOARD}},
		{keyBinds::arrow_left, InputKey{GLFW_KEY_LEFT, ControlType::KEYBOARD}},
		{keyBinds::arrow_right, InputKey{GLFW_KEY_RIGHT, ControlType::KEYBOARD}},
		{keyBinds::zero, InputKey{GLFW_KEY_0, ControlType::KEYBOARD}},
		{keyBinds::one, InputKey{GLFW_KEY_1, ControlType::KEYBOARD}},
		{keyBinds::two, InputKey{GLFW_KEY_2, ControlType::KEYBOARD}},
		{keyBinds::three, InputKey{GLFW_KEY_3, ControlType::KEYBOARD}},
		{keyBinds::four, InputKey{GLFW_KEY_4, ControlType::KEYBOARD}},
		{keyBinds::five, InputKey{GLFW_KEY_5, ControlType::KEYBOARD}},
		{keyBinds::six, InputKey{GLFW_KEY_6, ControlType::KEYBOARD}},
		{keyBinds::seven, InputKey{GLFW_KEY_7, ControlType::KEYBOARD}},
		{keyBinds::eight, InputKey{GLFW_KEY_8, ControlType::KEYBOARD}},
		{keyBinds::nine, InputKey{GLFW_KEY_9, ControlType::KEYBOARD}},
		{keyBinds::a, InputKey{GLFW_KEY_A, ControlType::KEYBOARD}},
		{keyBinds::b, InputKey{GLFW_KEY_B, ControlType::KEYBOARD}},
		{keyBinds::c, InputKey{GLFW_KEY_C, ControlType::KEYBOARD}},
		{keyBinds::d, InputKey{GLFW_KEY_D, ControlType::KEYBOARD}},
		{keyBinds::e, InputKey{GLFW_KEY_E, ControlType::KEYBOARD}},
		{keyBinds::f, InputKey{GLFW_KEY_F, ControlType::KEYBOARD}},
		{keyBinds::g, InputKey{GLFW_KEY_G, ControlType::KEYBOARD}},
		{keyBinds::h, InputKey{GLFW_KEY_H, ControlType::KEYBOARD}},
		{keyBinds::i, InputKey{GLFW_KEY_I, ControlType::KEYBOARD}},
		{keyBinds::j, InputKey{GLFW_KEY_J, ControlType::KEYBOARD}},
		{keyBinds::k, InputKey{GLFW_KEY_K, ControlType::KEYBOARD}},
		{keyBinds::l, InputKey{GLFW_KEY_L, ControlType::KEYBOARD}},
		{keyBinds::m, InputKey{GLFW_KEY_M, ControlType::KEYBOARD}},
		{keyBinds::n, InputKey{GLFW_KEY_N, ControlType::KEYBOARD}},
		{keyBinds::o, InputKey{GLFW_KEY_O, ControlType::KEYBOARD}},
		{keyBinds::p, InputKey{GLFW_KEY_P, ControlType::KEYBOARD}},
		{keyBinds::q, InputKey{GLFW_KEY_Q, ControlType::KEYBOARD}},
		{keyBinds::r, InputKey{GLFW_KEY_R, ControlType::KEYBOARD}},
		{keyBinds::s, InputKey{GLFW_KEY_S, ControlType::KEYBOARD}},
		{keyBinds::t, InputKey{GLFW_KEY_T, ControlType::KEYBOARD}},
		{keyBinds::u, InputKey{GLFW_KEY_U, ControlType::KEYBOARD}},
		{keyBinds::v, InputKey{GLFW_KEY_V, ControlType::KEYBOARD}},
		{keyBinds::w, InputKey{GLFW_KEY_W, ControlType::KEYBOARD}},
		{keyBinds::x, InputKey{GLFW_KEY_X, ControlType::KEYBOARD}},
		{keyBinds::y, InputKey{GLFW_KEY_Y, ControlType::KEYBOARD}},
		{keyBinds::z, InputKey{GLFW_KEY_Z, ControlType::KEYBOARD}},
		{keyBinds::left_shift, InputKey{GLFW_KEY_LEFT_SHIFT, ControlType::KEYBOARD}},
		{keyBinds::left_control, InputKey{GLFW_KEY_LEFT_CONTROL, ControlType::KEYBOARD}},
		{keyBinds::left_alt, InputKey{GLFW_KEY_LEFT_ALT, ControlType::KEYBOARD}},
		{keyBinds::gamepad_a, InputKey{GLFW_GAMEPAD_BUTTON_A, ControlType::CONTROLLER_BUTTON}},
		{keyBinds::gamepad_b, InputKey{GLFW_GAMEPAD_BUTTON_B, ControlType::CONTROLLER_BUTTON}},
		{keyBinds::gamepad_x, InputKey{GLFW_GAMEPAD_BUTTON_X, ControlType::CONTROLLER_BUTTON}},
		{keyBinds::gamepad_y, InputKey{GLFW_GAMEPAD_BUTTON_Y, ControlType::CONTROLLER_BUTTON}},
		{keyBinds::gamepad_left_bumper , InputKey{GLFW_GAMEPAD_BUTTON_LEFT_BUMPER, ControlType::CONTROLLER_BUTTON}},
		{keyBinds::gamepad_right_bumper, InputKey{GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER, ControlType::CONTROLLER_BUTTON}},
		{keyBinds::gamepad_back, InputKey{GLFW_GAMEPAD_BUTTON_BACK, ControlType::CONTROLLER_BUTTON}},
		{keyBinds::gamepad_start, InputKey{GLFW_GAMEPAD_BUTTON_START, ControlType::CONTROLLER_BUTTON}},
		{keyBinds::gamepad_guide, InputKey{GLFW_GAMEPAD_BUTTON_GUIDE, ControlType::CONTROLLER_BUTTON}},
		{keyBinds::gamepad_left_thumb, InputKey{GLFW_GAMEPAD_BUTTON_LEFT_THUMB, ControlType::CONTROLLER_BUTTON}},
		{keyBinds::gamepad_right_thumb, InputKey{GLFW_GAMEPAD_BUTTON_RIGHT_THUMB, ControlType::CONTROLLER_BUTTON}},
		{keyBinds::gamepad_dpad_up, InputKey{GLFW_GAMEPAD_BUTTON_DPAD_UP, ControlType::CONTROLLER_BUTTON}},
		{keyBinds::gamepad_dpad_right, InputKey{GLFW_GAMEPAD_BUTTON_DPAD_RIGHT, ControlType::CONTROLLER_BUTTON}},
		{keyBinds::gamepad_dpad_down, InputKey{GLFW_GAMEPAD_BUTTON_DPAD_DOWN, ControlType::CONTROLLER_BUTTON}},
		{keyBinds::gamepad_dpad_left, InputKey{GLFW_GAMEPAD_BUTTON_DPAD_LEFT, ControlType::CONTROLLER_BUTTON}},
		{keyBinds::gamepad_left_stick_left,InputKey{GLFW_GAMEPAD_AXIS_LEFT_X, ControlType::CONTROLLER_STICK, StickDirection::stickLeft}},
		{keyBinds::gamepad_left_stick_right,InputKey{GLFW_GAMEPAD_AXIS_LEFT_X, ControlType::CONTROLLER_STICK, StickDirection::stickRight}},
		{keyBinds::gamepad_left_stick_up, InputKey{GLFW_GAMEPAD_AXIS_LEFT_Y, ControlType::CONTROLLER_STICK, StickDirection::stickUp}},
		{keyBinds::gamepad_left_stick_down, InputKey{GLFW_GAMEPAD_AXIS_LEFT_Y, ControlType::CONTROLLER_STICK, StickDirection::stickDown}},
		{keyBinds::gamepad_right_stick_left,InputKey{GLFW_GAMEPAD_AXIS_RIGHT_X, ControlType::CONTROLLER_STICK,  StickDirection::stickLeft}},
		{keyBinds::gamepad_right_stick_right,	InputKey{GLFW_GAMEPAD_AXIS_RIGHT_X, ControlType::CONTROLLER_STICK,  StickDirection::stickRight}},
		{keyBinds::gamepad_right_stick_up,InputKey{GLFW_GAMEPAD_AXIS_RIGHT_Y, ControlType::CONTROLLER_STICK,  StickDirection::stickUp}},
		{keyBinds::gamepad_right_stick_down,InputKey{GLFW_GAMEPAD_AXIS_RIGHT_Y, ControlType::CONTROLLER_STICK,  StickDirection::stickDown}},
		{keyBinds::gamepad_left_trigger,	InputKey{GLFW_GAMEPAD_AXIS_LEFT_TRIGGER, ControlType::CONTROLLER_STICK, StickDirection::stickDown}},
		{keyBinds::gamepad_right_trigger, InputKey{GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER, ControlType::CONTROLLER_STICK, StickDirection::stickDown}}
	};
};