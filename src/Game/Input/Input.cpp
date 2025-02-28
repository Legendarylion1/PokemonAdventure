#include "Input.h"

void Input::setup(GLFWwindow* window, PauseSettingsData* pauseData)
{
	m_window = window;
	m_keyboardData = &pauseData->keyboardData;
	m_controllerData = &pauseData->controllerData;

	glfwSetJoystickCallback([](int joystickID, int event)
	{
		std::cout << "Joystick Event Detected" << std::endl;

		if (glfwJoystickIsGamepad(joystickID) && event == GLFW_CONNECTED)
		{
			std::cout << "Joystick is a gamepad" << std::endl;
			detectedJoystick.id = joystickID;
			detectedJoystick.event = event;
		}
		else if (detectedJoystick.id == joystickID && event != GLFW_CONNECTED)
		{
			detectedJoystick.id = joystickID;
			detectedJoystick.event = GLFW_DISCONNECTED;
		}

	});
}

void Input::onUpdate()
{
	resetInputs();
	detectController();

	if (m_joystickID != -1)
		glfwGetGamepadState(m_joystickID, m_state);

	
	for (auto key = m_activeRequests.begin(); key != m_activeRequests.end(); key++)
	{
		if (key->second == "")
			continue;

		switch (m_displayInput[key->second].type)
		{
		case ControlType::KEYBOARD:
			getKeyboardInput(m_displayInput[key->second]);
			break;
		case ControlType::CONTROLLER_BUTTON:
			getControllerButtonInput(m_displayInput[key->second]);
			break;
		case ControlType::CONTROLLER_STICK:
			getControllerStickInput(m_displayInput[key->second]);
			break;
		default:
			break;
		}
	}
	
	updateInputValues();
	updateHeldInputValues();
}

void Input::load(InputSave save)
{
	m_activeRequests[{KeyPriority::MAIN, InputRequest::UP, ControlType::KEYBOARD }]					= save.keyboardUp.main;
	m_activeRequests[{KeyPriority::MAIN, InputRequest::DOWN, ControlType::KEYBOARD }]				= save.keyboardDown.main;
	m_activeRequests[{KeyPriority::MAIN, InputRequest::LEFT, ControlType::KEYBOARD }]				= save.keyboardLeft.main;
	m_activeRequests[{KeyPriority::MAIN, InputRequest::RIGHT, ControlType::KEYBOARD }]				= save.keyboardRight.main;
	m_activeRequests[{KeyPriority::MAIN, InputRequest::SELECT, ControlType::KEYBOARD }]				= save.keyboardSelect.main;
	m_activeRequests[{KeyPriority::MAIN, InputRequest::BACK, ControlType::KEYBOARD }]				= save.keyboardBack.main;
	m_activeRequests[{KeyPriority::MAIN, InputRequest::PAUSE, ControlType::KEYBOARD }]				= save.keyboardPause.main;
	m_activeRequests[{KeyPriority::MAIN, InputRequest::SPRINT, ControlType::KEYBOARD }]				= save.keyboardSprint.main;
	m_activeRequests[{KeyPriority::ALT, InputRequest::UP, ControlType::KEYBOARD }]					= save.keyboardUp.alt;
	m_activeRequests[{KeyPriority::ALT, InputRequest::DOWN, ControlType::KEYBOARD }]				= save.keyboardDown.alt;
	m_activeRequests[{KeyPriority::ALT, InputRequest::LEFT, ControlType::KEYBOARD }]				= save.keyboardLeft.alt;
	m_activeRequests[{KeyPriority::ALT, InputRequest::RIGHT, ControlType::KEYBOARD }]				= save.keyboardRight.alt;
	m_activeRequests[{KeyPriority::ALT, InputRequest::SELECT, ControlType::KEYBOARD }]				= save.keyboardSelect.alt;
	m_activeRequests[{KeyPriority::ALT, InputRequest::BACK, ControlType::KEYBOARD }]				= save.keyboardBack.alt;
	m_activeRequests[{KeyPriority::ALT, InputRequest::PAUSE, ControlType::KEYBOARD }]				= save.keyboardPause.alt;
	m_activeRequests[{KeyPriority::ALT, InputRequest::SPRINT, ControlType::KEYBOARD }]				= save.keyboardSprint.alt;
	m_activeRequests[{KeyPriority::MAIN, InputRequest::UP, ControlType::CONTROLLER_BUTTON }]		= save.controllerUp.main;
	m_activeRequests[{KeyPriority::MAIN, InputRequest::DOWN, ControlType::CONTROLLER_BUTTON }]		= save.controllerDown.main;
	m_activeRequests[{KeyPriority::MAIN, InputRequest::LEFT, ControlType::CONTROLLER_BUTTON }]		= save.controllerLeft.main;
	m_activeRequests[{KeyPriority::MAIN, InputRequest::RIGHT, ControlType::CONTROLLER_BUTTON }]		= save.controllerRight.main;
	m_activeRequests[{KeyPriority::MAIN, InputRequest::SELECT, ControlType::CONTROLLER_BUTTON }]	= save.controllerSelect.main;
	m_activeRequests[{KeyPriority::MAIN, InputRequest::BACK, ControlType::CONTROLLER_BUTTON }]		= save.controllerBack.main;
	m_activeRequests[{KeyPriority::MAIN, InputRequest::PAUSE, ControlType::CONTROLLER_BUTTON }]		= save.controllerPause.main;
	m_activeRequests[{KeyPriority::MAIN, InputRequest::SPRINT, ControlType::CONTROLLER_BUTTON }]	= save.controllerSprint.main;
	m_activeRequests[{KeyPriority::ALT, InputRequest::UP, ControlType::CONTROLLER_BUTTON }]			= save.controllerUp.alt;
	m_activeRequests[{KeyPriority::ALT, InputRequest::DOWN, ControlType::CONTROLLER_BUTTON }]		= save.controllerDown.alt;
	m_activeRequests[{KeyPriority::ALT, InputRequest::LEFT, ControlType::CONTROLLER_BUTTON }]		= save.controllerLeft.alt;
	m_activeRequests[{KeyPriority::ALT, InputRequest::RIGHT, ControlType::CONTROLLER_BUTTON }]		= save.controllerRight.alt;
	m_activeRequests[{KeyPriority::ALT, InputRequest::SELECT, ControlType::CONTROLLER_BUTTON }]		= save.controllerSelect.alt;
	m_activeRequests[{KeyPriority::ALT, InputRequest::BACK, ControlType::CONTROLLER_BUTTON }]		= save.controllerBack.alt;
	m_activeRequests[{KeyPriority::ALT, InputRequest::PAUSE, ControlType::CONTROLLER_BUTTON }]		= save.controllerPause.alt;
	m_activeRequests[{KeyPriority::ALT, InputRequest::SPRINT, ControlType::CONTROLLER_BUTTON }]		= save.controllerSprint.alt;

	updateKeyEvents();
	resetInputs();
}

bool Input::anyButtonPressed()
{
	
	for (InputKey key : m_allKeys)
	{
		switch (key.type)
		{
		case ControlType::KEYBOARD:
			if (getKeyboardInput(key))
				return true;
			break;
		case ControlType::CONTROLLER_BUTTON:
			if (getControllerButtonInput(key))
				return true;
			break;
		case ControlType::CONTROLLER_STICK:
			if (getControllerStickInput(key))
				return true;
			break;
		default:
			break;
		}
	}

	return false;
}

bool Input::canBePressed(InputRequest request)
{
	if (m_canHoldInput)
		return true;

	if (m_requestStatus[request].held == true)
		return false;

	return true;
}

void Input::updateKeyBinds(PauseSettingsData* data)
{
	data->keyboardData.UpMain		= m_activeRequests[{KeyPriority::MAIN, InputRequest::UP, ControlType::KEYBOARD }];
	data->keyboardData.DownMain		= m_activeRequests[{KeyPriority::MAIN, InputRequest::DOWN, ControlType::KEYBOARD }];
	data->keyboardData.LeftMain		= m_activeRequests[{KeyPriority::MAIN, InputRequest::LEFT, ControlType::KEYBOARD }];
	data->keyboardData.RightMain	= m_activeRequests[{KeyPriority::MAIN, InputRequest::RIGHT, ControlType::KEYBOARD }];
	data->keyboardData.BackMain		= m_activeRequests[{KeyPriority::MAIN, InputRequest::BACK, ControlType::KEYBOARD }];
	data->keyboardData.PauseMain	= m_activeRequests[{KeyPriority::MAIN, InputRequest::PAUSE, ControlType::KEYBOARD }];
	data->keyboardData.SelectMain	= m_activeRequests[{KeyPriority::MAIN, InputRequest::SELECT, ControlType::KEYBOARD }];
	data->keyboardData.SprintMain	= m_activeRequests[{KeyPriority::MAIN, InputRequest::SPRINT, ControlType::KEYBOARD }];
	data->keyboardData.UpAlt		= m_activeRequests[{KeyPriority::ALT, InputRequest::UP, ControlType::KEYBOARD }];
	data->keyboardData.DownAlt		= m_activeRequests[{KeyPriority::ALT, InputRequest::DOWN, ControlType::KEYBOARD }];
	data->keyboardData.LeftAlt		= m_activeRequests[{KeyPriority::ALT, InputRequest::LEFT, ControlType::KEYBOARD }];
	data->keyboardData.RightAlt		= m_activeRequests[{KeyPriority::ALT, InputRequest::RIGHT, ControlType::KEYBOARD }];
	data->keyboardData.BackAlt		= m_activeRequests[{KeyPriority::ALT, InputRequest::BACK, ControlType::KEYBOARD }];
	data->keyboardData.PauseAlt		= m_activeRequests[{KeyPriority::ALT, InputRequest::PAUSE, ControlType::KEYBOARD }];
	data->keyboardData.SelectAlt	= m_activeRequests[{KeyPriority::ALT, InputRequest::SELECT, ControlType::KEYBOARD }];
	data->keyboardData.SprintAlt	= m_activeRequests[{KeyPriority::ALT, InputRequest::SPRINT, ControlType::KEYBOARD }];
	data->controllerData.UpMain		= m_activeRequests[{KeyPriority::MAIN, InputRequest::UP, ControlType::CONTROLLER_BUTTON }];
	data->controllerData.DownMain	= m_activeRequests[{KeyPriority::MAIN, InputRequest::DOWN, ControlType::CONTROLLER_BUTTON }];
	data->controllerData.LeftMain	= m_activeRequests[{KeyPriority::MAIN, InputRequest::LEFT, ControlType::CONTROLLER_BUTTON }];
	data->controllerData.RightMain	= m_activeRequests[{KeyPriority::MAIN, InputRequest::RIGHT, ControlType::CONTROLLER_BUTTON }];
	data->controllerData.BackMain	= m_activeRequests[{KeyPriority::MAIN, InputRequest::BACK, ControlType::CONTROLLER_BUTTON }];
	data->controllerData.PauseMain	= m_activeRequests[{KeyPriority::MAIN, InputRequest::PAUSE, ControlType::CONTROLLER_BUTTON }];
	data->controllerData.SelectMain	= m_activeRequests[{KeyPriority::MAIN, InputRequest::SELECT, ControlType::CONTROLLER_BUTTON }];
	data->controllerData.SprintMain	= m_activeRequests[{KeyPriority::MAIN, InputRequest::SPRINT, ControlType::CONTROLLER_BUTTON }];
	data->controllerData.UpAlt		= m_activeRequests[{KeyPriority::ALT, InputRequest::UP, ControlType::CONTROLLER_BUTTON }];
	data->controllerData.DownAlt	= m_activeRequests[{KeyPriority::ALT, InputRequest::DOWN, ControlType::CONTROLLER_BUTTON }];
	data->controllerData.LeftAlt	= m_activeRequests[{KeyPriority::ALT, InputRequest::LEFT, ControlType::CONTROLLER_BUTTON }];
	data->controllerData.RightAlt	= m_activeRequests[{KeyPriority::ALT, InputRequest::RIGHT, ControlType::CONTROLLER_BUTTON }];
	data->controllerData.BackAlt	= m_activeRequests[{KeyPriority::ALT, InputRequest::BACK, ControlType::CONTROLLER_BUTTON }];
	data->controllerData.PauseAlt	= m_activeRequests[{KeyPriority::ALT, InputRequest::PAUSE, ControlType::CONTROLLER_BUTTON }];
	data->controllerData.SelectAlt	= m_activeRequests[{KeyPriority::ALT, InputRequest::SELECT, ControlType::CONTROLLER_BUTTON }];
	data->controllerData.SprintAlt	= m_activeRequests[{KeyPriority::ALT, InputRequest::SPRINT, ControlType::CONTROLLER_BUTTON }];
}

bool Input::changingInput(ControlType type, KeyPriority priority, InputRequest request)
{
	// (Case 1) If binding the new key would leave no selection options deny the bind and return
	// (Case 2) If Key was never bound add the key
	// (Case 3) If new key was previously bound and is replacing another key then swap the keys

	if (type == ControlType::CONTROLLER_BUTTON && m_joystickID == -1)
		return false;

	if (type == ControlType::CONTROLLER_BUTTON)
		glfwGetGamepadState(m_joystickID, m_state);


	// Old input is what exists in the slot we want to put our new input
	std::string newInput;
	std::string oldInput;

	RequestType newRequest{ priority, request, type };
	RequestType oldRequest{};



	// Get New Key Press
	if (type == ControlType::KEYBOARD)
		newInput = getNewKeyboardPress();
	else
		newInput = getNewControllerPress();

	if (newInput == "")
		return true;


	// Find if our input was previously bound
	oldRequest = getRequestFromInput(newInput, type);

	if (oldRequest.controlType != ControlType::CONTROLLER_STICK)
		oldInput = m_activeRequests[newRequest];

	

	if (oldInput != "")	
	{
		addInput(oldInput, oldRequest);
	}
	else
	{
		// This means that nothing will be replacing the input
		// If we would leave the input empty dont allow

		for (auto request = m_activeRequests.begin(); request != m_activeRequests.end(); request++)
		{
			if (request->second == newInput && newRequest.inputRequest != request->first.inputRequest)
			{
				// Check the main and alt of the request
				// If there is a value other than new input then we can continue. Otherwise we return false as an error
				KeyPriority testPriority = KeyPriority::MAIN;

				if (request->first.priority == KeyPriority::MAIN)
					testPriority = KeyPriority::ALT;

				if (m_activeRequests[{testPriority, request->first.inputRequest, request->first.controlType}] == "")
				{
					std::cout << "Cannot swap. It would leave no suitable input";
					return false;
				}
			}
		}
	}

	removeInput(newInput);
	addInput(newInput, newRequest);

	updateKeyEvents();

	return false;
}

bool Input::getKeyboardInput(InputKey key)
{
	if (glfwGetKey(m_window, key.key) == GLFW_PRESS)
	{
		if (canBePressed(m_keyEvents[key]))
		{
			//std::cout << "Pressed: " << m_inputDisplay[key] << std::endl;
			m_requestStatus[m_keyEvents[key]].status = true;
			m_requestStatus[m_keyEvents[key]].held = true;
		}
		else
		{
			m_requestStatus[m_keyEvents[key]].pressed = true;
		}
		return true;
	}

	return false;
}

bool Input::getControllerStickInput(InputKey key)
{
	if (key.stickDirection > 0 && m_state->axes[key.key] > key.stickDirection)
	{
		if (canBePressed(m_keyEvents[key]))
		{
			//std::cout << "Pressed: " << m_inputDisplay[key] << std::endl;
			m_requestStatus[m_keyEvents[key]].status = true;
			m_requestStatus[m_keyEvents[key]].held = true;
		}
		else
		{
			m_requestStatus[m_keyEvents[key]].pressed = true;
		}

		return true;
	}
	else if (key.stickDirection < 0 && m_state->axes[key.key] < key.stickDirection)
	{
		if (canBePressed(m_keyEvents[key]))
		{
			//std::cout << "Pressed: " << m_inputDisplay[key] << std::endl;
			m_requestStatus[m_keyEvents[key]].status = true;
			m_requestStatus[m_keyEvents[key]].held = true;
		}
		else
		{
			m_requestStatus[m_keyEvents[key]].pressed = true;
		}

		return true;
	}

	return false;
}

bool Input::getControllerButtonInput(InputKey key)
{
	if (m_state->buttons[key.key] == GLFW_PRESS)
	{
		if (canBePressed(m_keyEvents[key]))
		{
			//std::cout << "Pressed: " << m_inputDisplay[key] << std::endl;
			m_requestStatus[m_keyEvents[key]].status = true;
			m_requestStatus[m_keyEvents[key]].held = true;
		}
		else
		{
			m_requestStatus[m_keyEvents[key]].pressed = true;
		}

		return true;
	}

	return false;
}

void Input::updateKeyEvents()
{
	for (auto request = m_keyEvents.begin(); request != m_keyEvents.end(); request++)
		request->second = InputRequest::EMPTY;

	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::MAIN, InputRequest::UP, ControlType::KEYBOARD }]]] = InputRequest::UP;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::MAIN, InputRequest::DOWN, ControlType::KEYBOARD }]]] = InputRequest::DOWN;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::MAIN, InputRequest::LEFT, ControlType::KEYBOARD }]]] = InputRequest::LEFT;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::MAIN, InputRequest::RIGHT, ControlType::KEYBOARD }]]] = InputRequest::RIGHT;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::MAIN, InputRequest::SELECT, ControlType::KEYBOARD }]]] = InputRequest::SELECT;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::MAIN, InputRequest::BACK, ControlType::KEYBOARD }]]] = InputRequest::BACK;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::MAIN, InputRequest::PAUSE, ControlType::KEYBOARD }]]] = InputRequest::PAUSE;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::MAIN, InputRequest::SPRINT, ControlType::KEYBOARD }]]] = InputRequest::SPRINT;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::ALT, InputRequest::UP, ControlType::KEYBOARD }]]] = InputRequest::UP;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::ALT, InputRequest::DOWN, ControlType::KEYBOARD }]]] = InputRequest::DOWN;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::ALT, InputRequest::LEFT, ControlType::KEYBOARD }]]] = InputRequest::LEFT;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::ALT, InputRequest::RIGHT, ControlType::KEYBOARD }]]] = InputRequest::RIGHT;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::ALT, InputRequest::SELECT, ControlType::KEYBOARD }]]] = InputRequest::SELECT;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::ALT, InputRequest::BACK, ControlType::KEYBOARD }]]] = InputRequest::BACK;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::ALT, InputRequest::PAUSE, ControlType::KEYBOARD }]]] = InputRequest::PAUSE;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::ALT, InputRequest::SPRINT, ControlType::KEYBOARD }]]] = InputRequest::SPRINT;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::MAIN, InputRequest::UP, ControlType::CONTROLLER_BUTTON }]]] = InputRequest::UP;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::MAIN, InputRequest::DOWN, ControlType::CONTROLLER_BUTTON }]]] = InputRequest::DOWN;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::MAIN, InputRequest::LEFT, ControlType::CONTROLLER_BUTTON }]]] = InputRequest::LEFT;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::MAIN, InputRequest::RIGHT, ControlType::CONTROLLER_BUTTON }]]] = InputRequest::RIGHT;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::MAIN, InputRequest::SELECT, ControlType::CONTROLLER_BUTTON }]]] = InputRequest::SELECT;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::MAIN, InputRequest::BACK, ControlType::CONTROLLER_BUTTON }]]] = InputRequest::BACK;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::MAIN, InputRequest::PAUSE, ControlType::CONTROLLER_BUTTON }]]] = InputRequest::PAUSE;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::MAIN, InputRequest::SPRINT, ControlType::CONTROLLER_BUTTON }]]] = InputRequest::SPRINT;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::ALT, InputRequest::UP, ControlType::CONTROLLER_BUTTON }]]] = InputRequest::UP;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::ALT, InputRequest::DOWN, ControlType::CONTROLLER_BUTTON }]]] = InputRequest::DOWN;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::ALT, InputRequest::LEFT, ControlType::CONTROLLER_BUTTON }]]] = InputRequest::LEFT;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::ALT, InputRequest::RIGHT, ControlType::CONTROLLER_BUTTON }]]] = InputRequest::RIGHT;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::ALT, InputRequest::SELECT, ControlType::CONTROLLER_BUTTON }]]] = InputRequest::SELECT;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::ALT, InputRequest::BACK, ControlType::CONTROLLER_BUTTON }]]] = InputRequest::BACK;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::ALT, InputRequest::PAUSE, ControlType::CONTROLLER_BUTTON }]]] = InputRequest::PAUSE;
	m_keyEvents[m_displayInput[m_activeRequests[{KeyPriority::ALT, InputRequest::SPRINT, ControlType::CONTROLLER_BUTTON }]]] = InputRequest::SPRINT;
}

void Input::updateInputValues()
{
	m_inputs->up = m_requestStatus[InputRequest::UP].status;
	m_inputs->down = m_requestStatus[InputRequest::DOWN].status;
	m_inputs->left = m_requestStatus[InputRequest::LEFT].status;
	m_inputs->right = m_requestStatus[InputRequest::RIGHT].status;
	m_inputs->interact = m_requestStatus[InputRequest::SELECT].status;
	m_inputs->pause = m_requestStatus[InputRequest::PAUSE].status;
	m_inputs->back = m_requestStatus[InputRequest::BACK].status;
	m_inputs->sprint = m_requestStatus[InputRequest::SPRINT].status;
}

void Input::updateHeldInputValues()
{
	if (!m_requestStatus[InputRequest::UP].pressed && !m_requestStatus[InputRequest::UP].status)
		m_requestStatus[InputRequest::UP].held = false;
	if (!m_requestStatus[InputRequest::DOWN].pressed && !m_requestStatus[InputRequest::DOWN].status)
		m_requestStatus[InputRequest::DOWN].held = false;
	if (!m_requestStatus[InputRequest::LEFT].pressed && !m_requestStatus[InputRequest::LEFT].status)
		m_requestStatus[InputRequest::LEFT].held = false;
	if (!m_requestStatus[InputRequest::RIGHT].pressed && !m_requestStatus[InputRequest::RIGHT].status)
		m_requestStatus[InputRequest::RIGHT].held = false;
	if (!m_requestStatus[InputRequest::BACK].pressed && !m_requestStatus[InputRequest::BACK].status)
		m_requestStatus[InputRequest::BACK].held = false;
	if (!m_requestStatus[InputRequest::SELECT].pressed && !m_requestStatus[InputRequest::SELECT].status)
		m_requestStatus[InputRequest::SELECT].held = false;
	if (!m_requestStatus[InputRequest::SPRINT].pressed && !m_requestStatus[InputRequest::SPRINT].status)
		m_requestStatus[InputRequest::SPRINT].held = false;
	if (!m_requestStatus[InputRequest::PAUSE].pressed && !m_requestStatus[InputRequest::PAUSE].status)
		m_requestStatus[InputRequest::PAUSE].held = false;
}

std::string Input::getNewKeyboardPress()
{
	for (InputKey key : m_allKeys)
	{
		if (key.type != ControlType::KEYBOARD)
			continue;

		if (glfwGetKey(m_window, key.key) == GLFW_PRESS)
			return m_inputDisplay[key];
	}

	return std::string();
}

std::string Input::getNewControllerPress()
{
	for (InputKey key : m_allKeys)
	{
		if (key.type == ControlType::KEYBOARD)
			continue;

		if (key.type == ControlType::CONTROLLER_BUTTON && m_state->buttons[key.key] == GLFW_PRESS)
		{
			return m_inputDisplay[key];
		}
		else if (key.type == ControlType::CONTROLLER_STICK)
		{
			if (key.stickDirection > 0 && m_state->axes[key.key] > key.stickDirection)
				return m_inputDisplay[key];
			else if (key.stickDirection < 0 && m_state->axes[key.key] < key.stickDirection)
				return m_inputDisplay[key];
		}
	}

	return std::string();
}

RequestType Input::getRequestFromInput(std::string input, ControlType desiredType)
{
	for (auto request = m_activeRequests.begin(); request != m_activeRequests.end(); request++)
	{
		if (request->first.controlType != desiredType)
			continue;

		if (request->second == input)
		{
			return request->first;
		}
	}

	return { KeyPriority::MAIN, InputRequest::UP, ControlType::CONTROLLER_STICK };
}

void Input::removeInput(std::string input)
{
	for (auto request = m_activeRequests.begin(); request != m_activeRequests.end(); request++)
	{
		if (request->second == input)
		{
			request->second = "";
			break;
		}
	}
}

void Input::addInput(std::string input, RequestType type)
{
	m_activeRequests[type] = input;
}

InputSave Input::getInputSave()
{
	InputSave data;

	data.keyboardUp.main			= m_activeRequests[{KeyPriority::MAIN, InputRequest::UP, ControlType::KEYBOARD}];
	data.keyboardDown.main			= m_activeRequests[{KeyPriority::MAIN, InputRequest::DOWN, ControlType::KEYBOARD}];
	data.keyboardLeft.main			= m_activeRequests[{KeyPriority::MAIN, InputRequest::LEFT, ControlType::KEYBOARD}];
	data.keyboardRight.main			= m_activeRequests[{KeyPriority::MAIN, InputRequest::RIGHT, ControlType::KEYBOARD}];
	data.keyboardSelect.main		= m_activeRequests[{KeyPriority::MAIN, InputRequest::SELECT, ControlType::KEYBOARD}];
	data.keyboardBack.main			= m_activeRequests[{KeyPriority::MAIN, InputRequest::BACK, ControlType::KEYBOARD}];
	data.keyboardPause.main			= m_activeRequests[{KeyPriority::MAIN, InputRequest::PAUSE, ControlType::KEYBOARD}];
	data.keyboardSprint.main		= m_activeRequests[{KeyPriority::MAIN, InputRequest::SPRINT, ControlType::KEYBOARD}];
	data.keyboardUp.alt				= m_activeRequests[{KeyPriority::ALT, InputRequest::UP, ControlType::KEYBOARD}];
	data.keyboardDown.alt			= m_activeRequests[{KeyPriority::ALT, InputRequest::DOWN, ControlType::KEYBOARD}];
	data.keyboardLeft.alt			= m_activeRequests[{KeyPriority::ALT, InputRequest::LEFT, ControlType::KEYBOARD}];
	data.keyboardRight.alt			= m_activeRequests[{KeyPriority::ALT, InputRequest::RIGHT, ControlType::KEYBOARD}];
	data.keyboardSelect.alt			= m_activeRequests[{KeyPriority::ALT, InputRequest::SELECT, ControlType::KEYBOARD}];
	data.keyboardBack.alt			= m_activeRequests[{KeyPriority::ALT, InputRequest::BACK, ControlType::KEYBOARD}];
	data.keyboardPause.alt			= m_activeRequests[{KeyPriority::ALT, InputRequest::PAUSE, ControlType::KEYBOARD}];
	data.keyboardSprint.alt			= m_activeRequests[{KeyPriority::ALT, InputRequest::SPRINT, ControlType::KEYBOARD}];
	data.controllerUp.main			= m_activeRequests[{KeyPriority::MAIN, InputRequest::UP, ControlType::CONTROLLER_BUTTON}];
	data.controllerDown.main		= m_activeRequests[{KeyPriority::MAIN, InputRequest::DOWN, ControlType::CONTROLLER_BUTTON}];
	data.controllerLeft.main		= m_activeRequests[{KeyPriority::MAIN, InputRequest::LEFT, ControlType::CONTROLLER_BUTTON}];
	data.controllerRight.main		= m_activeRequests[{KeyPriority::MAIN, InputRequest::RIGHT, ControlType::CONTROLLER_BUTTON}];
	data.controllerSelect.main		= m_activeRequests[{KeyPriority::MAIN, InputRequest::SELECT, ControlType::CONTROLLER_BUTTON}];
	data.controllerBack.main		= m_activeRequests[{KeyPriority::MAIN, InputRequest::BACK, ControlType::CONTROLLER_BUTTON}];
	data.controllerPause.main		= m_activeRequests[{KeyPriority::MAIN, InputRequest::PAUSE, ControlType::CONTROLLER_BUTTON}];
	data.controllerSprint.main		= m_activeRequests[{KeyPriority::MAIN, InputRequest::SPRINT, ControlType::CONTROLLER_BUTTON}];
	data.controllerUp.alt			= m_activeRequests[{KeyPriority::ALT, InputRequest::UP, ControlType::CONTROLLER_BUTTON}];
	data.controllerDown.alt			= m_activeRequests[{KeyPriority::ALT, InputRequest::DOWN, ControlType::CONTROLLER_BUTTON}];
	data.controllerLeft.alt			= m_activeRequests[{KeyPriority::ALT, InputRequest::LEFT, ControlType::CONTROLLER_BUTTON}];
	data.controllerRight.alt		= m_activeRequests[{KeyPriority::ALT, InputRequest::RIGHT, ControlType::CONTROLLER_BUTTON}];
	data.controllerSelect.alt		= m_activeRequests[{KeyPriority::ALT, InputRequest::SELECT, ControlType::CONTROLLER_BUTTON}];
	data.controllerBack.alt			= m_activeRequests[{KeyPriority::ALT, InputRequest::BACK, ControlType::CONTROLLER_BUTTON}];
	data.controllerPause.alt		= m_activeRequests[{KeyPriority::ALT, InputRequest::PAUSE, ControlType::CONTROLLER_BUTTON}];
	data.controllerSprint.alt		= m_activeRequests[{KeyPriority::ALT, InputRequest::SPRINT, ControlType::CONTROLLER_BUTTON}];

	return data;
}

void Input::resetInputs()
{
	m_inputs->up = false;
	m_inputs->down = false;
	m_inputs->left = false;
	m_inputs->right = false;
	m_inputs->interact = false;
	m_inputs->pause = false;
	m_inputs->back = false;
	m_inputs->sprint = false;

	m_requestStatus[InputRequest::UP].status = false;
	m_requestStatus[InputRequest::DOWN].status = false;
	m_requestStatus[InputRequest::LEFT].status = false;
	m_requestStatus[InputRequest::RIGHT].status = false;
	m_requestStatus[InputRequest::BACK].status = false;
	m_requestStatus[InputRequest::SELECT].status = false;
	m_requestStatus[InputRequest::SPRINT].status = false;
	m_requestStatus[InputRequest::PAUSE].status = false;

	m_requestStatus[InputRequest::UP].pressed = false;
	m_requestStatus[InputRequest::DOWN].pressed = false;
	m_requestStatus[InputRequest::LEFT].pressed = false;
	m_requestStatus[InputRequest::RIGHT].pressed = false;
	m_requestStatus[InputRequest::BACK].pressed = false;
	m_requestStatus[InputRequest::SELECT].pressed = false;
	m_requestStatus[InputRequest::SPRINT].pressed = false;
	m_requestStatus[InputRequest::PAUSE].pressed = false;
}

void Input::detectController()
{
	if (detectedJoystick.id == -1)
		return;

	if (detectedJoystick.event == GLFW_CONNECTED && m_joystickID == -1)
	{
		m_joystickID = detectedJoystick.id;
		std::cout << "Controller Detected id:" << m_joystickID << std::endl;
	}
	else if (detectedJoystick.event == GLFW_DISCONNECTED && detectedJoystick.id == m_joystickID)
	{
		std::cout << "Controller Disconnected id:" << m_joystickID << std::endl;
		m_joystickID = -1;
	}

	detectedJoystick.event = GLFW_DONT_CARE;
}
