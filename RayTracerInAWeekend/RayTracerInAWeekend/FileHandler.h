#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>

inline bool fileExists(const std::string& fName)
{
	struct stat buffer;
	return (stat (fName.c_str(), &buffer) == 0);
}

inline void WriteLine(const std::string& fName, std::string& line)
{
	
	std::fstream f(fName, std::ios::out | std::ios::app);
	f << line << std::endl;
	f.close();
}

inline void ClearFile(const std::string& fName)
{
	if (fileExists(fName))
	{
		std::fstream f(fName, std::ios::out);
		f << "";
		f.close();
	}
}