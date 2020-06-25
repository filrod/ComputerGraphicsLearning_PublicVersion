#include <iostream>
#include <string>
#include "FileHandler.h"

const int nx = 200;
const int ny = 100;

int main()
{
	ClearFile("image.ppm");
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	std::string line = "P3\n" + std::to_string(nx) + " " + std::to_string(ny) + "\n255\n";
	WriteLine("image.ppm", line);
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2;

			int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);

			std::cout << ir << " " << ig << " " << ib << "\n";
			line = "" + std::to_string(ir) + " " + std::to_string(ig) + " " + std::to_string(ib);
			WriteLine("image.ppm", line);
		}
	}
}