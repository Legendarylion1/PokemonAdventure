#pragma once


enum ErrorCodes
{
	UNHANDLED_SIM_DATA,
	UNHANDLED_MOVE_CHOICE,
	UNHANDLED_ENUM,
	UNIDENTIFIED_ITEM,
	FAILED_PP_REDUCTION,
	OUTSIDE_SCOPE,
	INVALID_ELEMENT
};

enum class LogLevel
{
	DEBUG,
	INFO,
	ERROR,
	CRITICAL
};

class Logger	//TODO: Implement proper logger lol
{
public:
	Logger() {};

	void log(LogLevel logLevel, std::string message, std::string functionName = "", std::string className = "")
	{
		//if (m_dataLog.size() == m_maxLogSize)
		//	m_dataLog.erase(m_dataLog.begin());
		//
		//std::string data;
		//
		//switch (logLevel)
		//{
		//case LogLevel::DEBUG:
		//	data += "[DEBUG] ";
		//	break;
		//case LogLevel::INFO:
		//	data += "[INFO] ";
		//	break;
		//case LogLevel::ERROR:
		//	data += "[ERROR] ";
		//	break;
		//case LogLevel::CRITICAL:
		//	data += "[CRITICAL] ";
		//	break;
		//default:
		//	data += "[CRITICAL] ";
		//	break;
		//}
		//
		//if (className.size() > 0)
		//	data += "[" + className + "] ";
		//if (functionName.size() > 0)
		//	data += "[" + functionName + "] ";
		//
		//data += message;
		//m_dataLog.push_back(data);
	}


	void reportCriticalError(ErrorCodes errorCode)
	{
		//std::string fullCommand = m_scriptLocation + " \"";
		//
		//for (size_t i = 0; i < m_dataLog.size(); i++)
		//	fullCommand += m_dataLog.at(i) + "\\n";
		//
		//fullCommand += "\"";
		//
		//system(fullCommand.c_str());

		exit(errorCode);
	}

private:

	//int m_maxLogSize = 50;
	//std::vector<std::string> m_dataLog;
	//std::string m_scriptLocation = "python emailScript.py";
};

static Logger* logger = new Logger();