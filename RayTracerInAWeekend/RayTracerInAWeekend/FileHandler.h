#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include "RayTracerInAWeekend.h"
#include "vec3.h"

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

inline std::string WriteColor(ColorRGB pixelColor, int samplesPerPixel)
{
    auto r = pixelColor.x();
    auto g = pixelColor.y();
    auto b = pixelColor.z();

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    auto scale = 1.0f / samplesPerPixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    int ir = static_cast<int>(255.99 * clamp(r, 0.0f, 0.999f));
    int ig = static_cast<int>(255.99 * clamp(g, 0.0f, 0.999f));
    int ib = static_cast<int>(255.99 * clamp(b, 0.0f, 0.999f));

    //std::cout << ir << " " << ig << " " << ib << "\n";
    return "" + std::to_string(ir) + " " + std::to_string(ig) + " " + std::to_string(ib);
}