#pragma once
#define STRINGIFY( name ) # name
#include <map>
#include <source_location>
#include <string>

class Logger
{
	enum class MessageType : unsigned short {
		TYPE_NONE = 0,
		TYPE_FATAL_ERROR,
		TYPE_ERROR,
		TYPE_WARNING,
		TYPE_INFO
	};



	static void Log(MessageType mt, const std::string& message, const std::string& filename, const std::string& function,
	         const uint_least32_t& line);
	static std::string GetTime();

	//static  std::ofstream out;


	/*static 	void Log( T ...m);
	static void Log(MessageType mt, const std::string& message, const std::string& filename, const std::string& function,
	                 const std::string& line);*/
	static std::string fileName;
	static std::string LogTypeToString(MessageType t);

public:
	Logger(const Logger&) = delete;
	Logger(Logger&&) = delete;
	Logger& operator=(const Logger&) = delete;
	Logger& operator=(Logger&&) = delete;
	Logger() = delete;

	static void InitLogger(const std::string& fileName_);

	static void Info(const std::string& info, const std::source_location location =
		std::source_location::current());
	static void Error(const std::string& info, const std::source_location location =
		std::source_location::current());
	static void FatalError(const std::string& info, const std::source_location location =
		std::source_location::current());
	static void Warning(const std::string& info, const std::source_location location =
		std::source_location::current());
	static void None(const std::string& info, const std::source_location location =
		std::source_location::current());



};

