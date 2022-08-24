#pragma once

#include <source_location>
#include <string>
enum class MessageType : unsigned short {
	TYPE_NONE = 0,
	TYPE_FATAL_ERROR,
	TYPE_ERROR,
	TYPE_WARNING,
	TYPE_TRACE,
	TYPE_INFO
};
class Logger
{

	static std::string GetTime();

	template<typename ... T>
	static void Log(const std::string& ms, T ...m);


	public:
		//template<typename ... T>
		//static void Info(T... m) {
		//	//va_list valist;
		//	//va_start(valist, m);
		//	Log(" INFO: ", m ...);

		//}

		static void Info(std::string info, const std::source_location location =
			std::source_location::current());
		static void Error(std::string info, const std::source_location location =
			std::source_location::current());
		static void FileWriter(const char* arr, std::string logFileName);


};

