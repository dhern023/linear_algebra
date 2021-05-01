// files.h

#pragma once
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

namespace files
{
	void vector_write(std::vector<double> v, std::string outname, bool append); //write a double vector
	void matrix_write(std::vector<std::vector<double>> A, std::string outname, bool append);
}