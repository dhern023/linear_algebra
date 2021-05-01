// vector_spaces.cpp
// post-build command: lib vector_spaces.obj

#include "vector_spaces.h"

// Inplace operations
double vector_spaces::inner_product(std::vector<double> v1, std::vector<double> v2)
{
	assert(v1.size() == v2.size());
	double result = v1[0] * v2[0];
	for (size_t i = 1; i < v1.size(); i++)
	{
		result += v1[i] * v2[i];
	}
	return result;
}

double vector_spaces::vector_sum(std::vector<double> v)
{
	double result = v[0];
	for (size_t i = 1; i < v.size(); i++)
	{
		result += v[i];
	}
	return result;
}

double vector_spaces::vector_avg(std::vector<double> v)
{
	assert(v.size() > 0);
	double sum = vector_sum(v);
	return sum / v.size();
}

std::vector<std::vector<double>> vector_spaces::transpose(std::vector<std::vector<double>> A)
{
	std::vector<std::vector<double>> A_T(A[0].size(), std::vector<double>(A.size()));
	for (size_t i = 0; i < A.size(); i++)
	{
		for (size_t j = 0; j < A[0].size(); j++)
		{
			A_T[i][j] = A[j][i];
		}
	}
	return A_T;
}

// Group Operations =======================================================================================

std::vector<double> vector_spaces::addition(std::vector<double> v1, std::vector<double> v2)
{
	assert(v1.size() == v2.size());
	std::vector<double> v(v1.size());

	for (size_t i = 0; i < v1.size(); i++)
	{
		v[i] = v1[i] + v2[i];
	}
	return v;
}

std::vector<std::vector<double>> vector_spaces::addition(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B)
{
	assert(A.size() == B.size());
	assert(A[0].size() == B[0].size());

	std::vector<std::vector<double>> C(A.size());

	for (size_t i = 0; i < A.size(); i++)
	{
		C[i] = vector_spaces::addition(A[i], B[i]);
	}
	return C;
}

std::vector<double> vector_spaces::subtraction(std::vector<double> v1, std::vector<double> v2)
{
	assert(v1.size() == v2.size());
	std::vector<double> v(v1.size());

	for (size_t i = 0; i < v1.size(); i++)
	{
		v[i] = v1[i] - v2[i];
	}
	return v;
}

std::vector<std::vector<double>> vector_spaces::subtraction(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B)
{
	// Initial subtractions do not reduce floating point accuracy.

	assert(A.size() == B.size());
	assert(A[0].size() == B[0].size());

	std::vector<std::vector<double>> C(A.size());

	for (size_t i = 0; i < A.size(); i++)
	{
		for (size_t j = 0; j < A[i].size(); j++)
		{
			C[i].push_back(A[i][j] - B[i][j]);
		}
	}
	return C;
}

std::vector<double> vector_spaces::scalar_multiplication(std::vector<double> v, double a)
{
	if (a == 0)
	{
		std::vector<double> result(v.size(), 0.0);
		return result;
	}
	else
	{
		std::vector<double> result;
		for (size_t i = 0; i < v.size(); i++)
		{
			result.push_back(v[i] * a);
		}
		return result;
	}
}

std::vector<double> vector_spaces::scalar_multiplication(double a, std::vector<double> v)
{
	if (a == 0)
	{
		std::vector<double> result(v.size(), 0.0);
		return result;
	}
	else
	{
		std::vector<double> result;
		for (size_t i = 0; i < v.size(); i++)
		{
			result.push_back(v[i] * a);
		}
		return result;
	}
}

std::vector<std::vector<double>> vector_spaces::scalar_multiplication(std::vector<std::vector<double>> A, double a)
{
	std::vector<std::vector<double>> B;
	for (size_t i = 0; i < A.size(); i++)
	{
		B.push_back(vector_spaces::scalar_multiplication(A[i], a));
	}
	return B;
}

std::vector<std::vector<double>> vector_spaces::scalar_multiplication(double a, std::vector<std::vector<double>> A)
{
	std::vector<std::vector<double>> B;
	for (size_t i = 0; i < A.size(); i++)
	{
		B.push_back(vector_spaces::scalar_multiplication(A[i], a));
	}
	return B;
}

std::vector<double> vector_spaces::multiplication(std::vector<double> v, std::vector<std::vector<double>> A)
{
	//v*A in which v is a row vector, results in a row vector.
	assert(v.size() == A[0].size());

	std::vector<double> result;
	for (size_t i = 0; i < A.size(); i++)
	{
		result.push_back(vector_spaces::inner_product(v, A[i]));
	}
	return result;
}

std::vector<double> vector_spaces::multiplication(std::vector<std::vector<double>> A, std::vector<double> v)
{
	//A*v in which v is a column vector, should result in a column vector. Sigh...
	assert(A[0].size() == v.size());

	std::vector<double> result;
	for (size_t i = 0; i < A.size(); i++)
	{
		result.push_back(vector_spaces::inner_product(v, A[i]));
	}
	return result;
}

std::vector<std::vector<double>> vector_spaces::multiplication(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B)
{
	assert(A[0].size() == B.size());

	std::vector<std::vector<double>> B_T = vector_spaces::transpose(B);

	std::vector<std::vector<double>> C(A.size(), std::vector<double>(B[0].size()));
	for (size_t i = 0; i < A.size(); i++)
	{
		for (size_t j = 0; j < B_T.size(); j++)
		{
			C[i][j] = vector_spaces::inner_product(A[i], B_T[j]);
		}
	}
	return C;
}

//Inverses
std::vector<std::vector<double>> vector_spaces::matrix_invert_2x2(std::vector<std::vector<double>> A)
{
	assert(A.size() == 2 && A[0].size() == 2); //must be 2x2
	double denominator = A[0][0] * A[1][1] - A[0][1] * A[1][0];
	assert(denominator != 0); //avoid indefinite

	std::vector<std::vector<double>> inverse = A;
	inverse[0][0] = A[1][1];
	inverse[0][1] = -A[0][1];
	inverse[1][1] = A[0][0];
	inverse[1][0] = -A[1][0];
	return vector_spaces::scalar_multiplication(inverse, 1 / denominator);
}