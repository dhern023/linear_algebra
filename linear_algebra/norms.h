// norms.h

#pragma once
#include <cassert>
#include <cmath>
#include <vector>

namespace norms
{
	double two_norm(std::vector<double> v); //Euclidean Metric (size)
	double two_norm(std::vector<double> v1, std::vector<double> v2); //Euclidean Metric (Distance) between two vectors
	double p_norm(std::vector<double> v, int p = 2); //p-norm (size)
	double p_norm(std::vector<double> v1, std::vector<double> v2, int p); //p-norm (Distance) between two vectors

}