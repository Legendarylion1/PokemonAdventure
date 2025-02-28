#pragma once

struct InputVariables
{
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool interact = false;
	bool pause = false;
	bool back = false;
	bool sprint = false;
};

enum class KeyPriority
{
	MAIN = 1,
	ALT = 2
};

enum class InputRequest
{
	UP = 4,
	DOWN = 8,
	LEFT = 16,
	RIGHT = 32,
	SELECT = 64,
	PAUSE = 128,
	BACK = 256,
	EMPTY = 512,
	SPRINT = 1024
};

enum class ControlType
{
	KEYBOARD = 2048,
	CONTROLLER_BUTTON = 4096,
	CONTROLLER_STICK = 8192
};

struct DetectedJoyStick
{
	int id = -1;
	int event = -1;
};

namespace StickDirection
{
	static float sensitivity = .75f;
	static float none = -1;
	static float stickUp = -(sensitivity);
	static float stickDown = sensitivity;
	static float stickLeft = -(sensitivity);
	static float stickRight = sensitivity;
}

struct InputKey
{
	int key;
	ControlType type;
	float stickDirection = StickDirection::none;

	bool operator==(const InputKey other) const
	{
		if ((this->key + (int)this->type) * this->stickDirection ==
			(other.key + (int)other.type) * other.stickDirection)
			return true;
		else
			return false;
	}
};

struct InputKeyState
{
	bool status = false;
	bool held = false;
	bool pressed = false;
};

struct RequestType
{
	KeyPriority priority;
	InputRequest inputRequest;
	ControlType controlType;
	bool operator==(const RequestType other) const
	{
		return (int)this->priority + (int)this->inputRequest + (int)this->controlType ==
			(int)other.priority + (int)other.inputRequest + (int)other.controlType;
	}
};

class InputKeyHashFunction
{
public:
	size_t operator()(const InputKey& key) const
	{
		return (size_t)((key.key + (int)key.type) * key.stickDirection);
	}
};


class RequestTypeHashFunction
{
public:
	size_t operator()(const RequestType& requestType) const
	{
		return (size_t)((int)requestType.priority + (int)requestType.inputRequest + (int)requestType.controlType);
	}
};

namespace keyBinds
{
	static std::string a = "A";
	static std::string b = "B";
	static std::string c = "C";
	static std::string d = "D";
	static std::string e = "E";
	static std::string f = "F";
	static std::string g = "G";
	static std::string h = "H";
	static std::string i = "I";
	static std::string j = "J";
	static std::string k = "K";
	static std::string l = "L";
	static std::string m = "M";
	static std::string n = "N";
	static std::string o = "O";
	static std::string p = "P";
	static std::string q = "Q";
	static std::string r = "R";
	static std::string s = "S";
	static std::string t = "T";
	static std::string u = "U";
	static std::string v = "V";
	static std::string w = "W";
	static std::string x = "X";
	static std::string y = "Y";
	static std::string z = "Z";

	static std::string zero		= "0";
	static std::string one		= "1";
	static std::string two		= "2";
	static std::string three	= "3";
	static std::string four		= "4";
	static std::string five		= "5";
	static std::string six		= "6";
	static std::string seven	= "7";
	static std::string eight	= "8";
	static std::string nine		= "9";

	static std::string space		= "SPC";
	static std::string escape		= "ESC";
	static std::string arrow_up		= "UP";
	static std::string arrow_down	= "DWN";
	static std::string arrow_left	= "LFT";
	static std::string arrow_right	= "RGT";

	static std::string left_shift	= "LSH";
	static std::string left_control	= "CTL";
	static std::string left_alt		= "ALT";


	static std::string gamepad_a	= "GA";
	static std::string gamepad_b	= "GB";
	static std::string gamepad_x	= "GX";
	static std::string gamepad_y	= "GY";

	static std::string gamepad_left_bumper	= "LB";
	static std::string gamepad_right_bumper	= "RB";

	static std::string gamepad_back		= "MNU";
	static std::string gamepad_guide	= "GDE";
	static std::string gamepad_start	= "SRT";

	static std::string gamepad_left_thumb	= "L";
	static std::string gamepad_right_thumb	= "R";

	static std::string gamepad_dpad_up		= "DU";
	static std::string gamepad_dpad_down	= "DD";
	static std::string gamepad_dpad_left	= "DL";
	static std::string gamepad_dpad_right	= "DR";

	static std::string gamepad_left_stick_up	= "LU";
	static std::string gamepad_left_stick_down	= "LD";
	static std::string gamepad_left_stick_left	= "LL";
	static std::string gamepad_left_stick_right	= "LR";

	static std::string gamepad_right_stick_up	= "RU";
	static std::string gamepad_right_stick_down = "RD";
	static std::string gamepad_right_stick_left = "RL";
	static std::string gamepad_right_stick_right = "RR";

	static std::string gamepad_left_trigger = "LT";
	static std::string gamepad_right_trigger = "RT";
}