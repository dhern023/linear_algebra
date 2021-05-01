// norms.cpp
// post-build command: lib norms.obj

#include "norms.h"

//Euclidean metric
double norms::two_norm(std::vector<double> v)
{
	double sum = 0;
	for (size_t i = 0; i < v.size(); i++)
	{
		sum += v[i] * v[i];
	}
	return std::sqrt(sum);
}

double norms::two_norm(std::vector<double> v1, std::vector<double> v2)
{
	assert(v1.size() == v2.size());
	double sum = 0;
	double temp_difference;
	for (size_t i = 0; i < v1.size(); i++)
	{
		temp_difference = v1[i] - v2[i];
		sum += temp_difference * temp_difference;
	}
	return std::sqrt(sum);
}


double norms::p_norm(std::vector<double> v, int p)
{
	assert(p != 0);
	double sum = 0;
	for (size_t i = 0; i < v.size(); i++)
	{
		double abs_result = std::abs(v[i]);
		sum += std::pow(abs_result, p);
	}
	return std::pow(sum, 1.0 / p);
}

double norms::p_norm(std::vector<double> v1, std::vector<double> v2, int p)
{
	assert(p != 0);
	assert(v1.size() == v2.size());
	double sum = 0;
	double temp_difference;
	for (size_t i = 0; i < v1.size(); i++)
	{
		temp_difference = v1[i] - v2[i];
		double abs_result = std::abs(temp_difference);
		sum += std::pow(abs_result, p);
	}
	return std::pow(sum, 1.0 / p);
}