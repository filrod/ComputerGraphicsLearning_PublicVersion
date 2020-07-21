#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include "RayTracerInAWeekend.h"

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

inline std::string WriteColor(ColorRGB pixelColor)
{
    int ir = static_cast<int>(255.99 * clamp(pixelColor.r(), 0.0f, 0.999f));
    int ig = static_cast<int>(255.99 * clamp(pixelColor.g(), 0.0f, 0.999f));
    int ib = static_cast<int>(255.99 * clamp(pixelColor.b(), 0.0f, 0.999f));

    //std::cout << ir << " " << ig << " " << ib << "\n";
    return "" + std::to_string(ir) + " " + std::to_string(ig) + " " + std::to_string(ib);
}