#include <string>
#include <windows.h>  
#include <cstdarg>
#include <iostream>
#include <algorithm>
#include <utility>
#include <chrono>
#include <errno.h>
#include "Logger.h"
#include <fstream>

using namespace std::chrono;
std::string Logger::fileName = "";


std::string Logger::LogTypeToString(const MessageType t) {
	switch (t) {
	case MessageType::TYPE_NONE:
		return "NONE";
	case MessageType::TYPE_FATAL_ERROR :
		return "FATAL_ERROR";
	case MessageType::TYPE_ERROR :
		return "ERROR";
	case MessageType::TYPE_WARNING:
		return "WARNING";
	case MessageType::TYPE_INFO:
		return "INFO";
	default:
		return "You forgot to add this function.";
	}
}


void Logger::Log(const MessageType mt, const std::string& message, const std::string& filename, const std::string& function,
                 const uint_least32_t& line)
{
	std::ofstream out;

	out.open(fileName, std::ios::out | std::ios::app);

#ifdef _DEBUG
	std::cout << filename << " : " << function << " : " << line << " : " << LogTypeToString(mt) << ": " << message;
	std::cout << "\n";
#endif
	out << filename << " : " << function << " : " << line << " : " << LogTypeToString(mt) << ": " << message;
	out << "\n";
	out.flush();
	out.close();

}

std::string Logger::GetTime() {
	char str[26]; /// get the time and date
	system_clock::time_point p = system_clock::now();
	const std::time_t result = system_clock::to_time_t(p);
	std::tm tm{};
	localtime_s(&tm, &result);
	char mbstr[100];
	std::strftime(mbstr, 100, "%D %T", (&tm));
	std::string dateAjoutSysteme(mbstr);

	std::stringstream buffer;


	return dateAjoutSysteme;

}
std::string SplitC(const std::string& str)
{
	std::string w = "";
	for (const auto x : str)
	{
		if (x == '\\')
		{
			//std::cout << w << std::endl;
			w = "";
		}
		else {
			w = w + x;
		}
	}
	//std::cout << w << std::endl;
	return w;
}

void Logger::InitLogger(const std::string& fileName_)
{
	fileName = fileName_;
	std::ofstream out;
	out.open(fileName, std::ios::out);

	char str[26]; /// get the time and date
	system_clock::time_point p = system_clock::now();
	std::time_t result = system_clock::to_time_t(p);
	ctime_s(str, sizeof str, &result); /// Since C11
	out << str;

	out.close();
}

void Logger::Info(const std::string& info, const std::source_location location) {

	Log(MessageType::TYPE_INFO, info, SplitC(location.file_name()), location.function_name(), location.line());
}
void Logger::Error(const std::string& info, const std::source_location location) {



	Log(MessageType::TYPE_ERROR, info, SplitC(location.file_name()), location.function_name(), location.line());

}

void Logger::FatalError(const std::string& info, const std::source_location location)
{
	Log(MessageType::TYPE_FATAL_ERROR, info, SplitC(location.file_name()), location.function_name(), location.line());
}

void Logger::Warning(const std::string& info, const std::source_location location)
{
	Log(MessageType::TYPE_WARNING, info, SplitC(location.file_name()), location.function_name(), location.line());
}

void Logger::None(const std::string& info, const std::source_location location)
{
	Log(MessageType::TYPE_NONE, info, SplitC(location.file_name()), location.function_name(), location.line());
}

