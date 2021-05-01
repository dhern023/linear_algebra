// matrices.h

#pragma once
#include <cmath>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

/*
Specific operations that have to do with arrays of size 2D or higher.
E.g., you can't decompose a vector...or can you?
*/

namespace matrices {
	void lu_decomposition(std::vector<std::vector<double>> A, std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U, std::vector<double>& p);
	double determinant(std::vector<std::vector<double>> A);
	void lower_triangular_solver(std::vector<std::vector<double>> L, std::vector<double> b, std::vector<double> &y);
	void upper_triangular_solver(std::vector<std::vector<double>> U, std::vector<double> b, std::vector<double> &x);
	void linear_system_solver(std::vector < std::vector<double>> A, std::vector<double> b, std::vector<double> &x);
}