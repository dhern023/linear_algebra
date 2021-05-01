// couts.cpp
// post-build command: lib couts.obj

#include "couts.h"

void couts::cout_vector(std::vector<double> v)
{
	std::cout << "{";
	for (size_t i = 0; i < v.size() - 1; i++)
	{
		std::cout << v[i] << ",";
	}
	std::cout << v[v.size() - 1] << "}" << std::endl;
}

void couts::cout_matrix(std::vector<std::vector<double>> A)
{
	std::cout << "{";
	for (size_t i = 0; i < A.size(); i++)
	{
		std::cout << "{";
		for (size_t j = 0; j < A[i].size() - 1; j++)
		{
			std::cout << A[i][j] << ",";
		}
		std::cout << A[i][A[i].size() - 1];

		if (i == A.size() - 1)
		{
			std::cout << "}}" << std::endl;
		}
		else
		{
			std::cout << "}," << std::endl;
		}
	}
}