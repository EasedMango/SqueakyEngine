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

template<typename ... T>
void Logger::Log(const std::string& ms, T ...m) {
	
	std::cout << ms;
	((std::cout << std::forward<T>(m) << " "), ...);
	//std::cout << m << std::endl;

	printf("\n");
}

std::string Logger::GetTime() {
	char str[26]; /// get the time and date
	system_clock::time_point p = system_clock::now();
	std::time_t result = system_clock::to_time_t(p);
	std::tm tm;
	localtime_s(&tm ,&result);
	char mbstr[100];
	std::strftime(mbstr, 100, "%D %T", (&tm));
	std::string dateAjoutSysteme(mbstr);

	std::stringstream buffer;


	return dateAjoutSysteme;

}
std::string split_c(std::string str)
{
	std::string w = "";
	for (auto x : str)
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

void Logger::Info(std::string info, const std::source_location location) {
	std::string loc = location.file_name();
	loc = split_c(loc);
	Log(GetTime(), " ", loc, ":", location.function_name(), ":", location.line(), ":", "\nINFO: ", info);
}
void Logger::Error(std::string info, const std::source_location location) {

	std::string loc = location.file_name();
	loc =split_c(loc);
	
	Log(GetTime()," ", loc, ":", location.function_name(), ":", location.line(), ":", "\nWARNING: ", info);
}

void Logger::FileWriter(const char* arr, std::string logFileName)
{
	std::ofstream out;
	std::string msg= logFileName;
	out.open(logFileName, std::ios::out | std::ios::app);

#ifdef _DEBUG
	std::cout << msg << std::endl;
#endif
	out << msg << std::endl;
	out.flush();
	out.close();
}




