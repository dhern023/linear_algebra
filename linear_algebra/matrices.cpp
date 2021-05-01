#include "matrices.h"

void matrices::lu_decomposition(std::vector<std::vector<double>> A, std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U, std::vector<double>& p)
{
	/*
	Performs the LU decomposition of a matrix with pivoting, to create
	LU = PA, where P is the permutation matrix.

	L, U are passed in as reference variables.

	(C) Plamen Koev of SJSU
	*/

	/*
	If all matrices are square, then by translation,
	confirming equality on all pairs of one side
	implies all matrices are the same size.
	*/

	//check all the matrices are square
	assert(A.size() == A[1].size());
	assert(L.size() == L[1].size());
	assert(U.size() == U[1].size());
	//check all matrices are the same size
	assert(A.size() == L.size() && A.size() == U.size());

	// the permutation vector is a cyclic group of order A.size().
	// reassigns just to be safe
	for (size_t i = 0; i < A.size(); i++) { p[i] = i; }

	double max = 0.0;
	double candidate = 0.0;
	size_t index = 0;
	std::vector<double> temp_row_vector;
	double temp_value = 0.0;

	for (size_t j = 0; j < A.size(); j++)
	{
		//find the largest entry below A[j][j]
		max = std::fabs(A[j][j]);
		index = j;
		for (size_t i = j + 1; i < A.size(); i++)
		{
			candidate = std::fabs(A[i][j]);
			if (candidate > max)
			{
				max = candidate;
				index = i;
			}
		}

		//swap row index and row j
		temp_row_vector = A[index];
		A[index] = A[j];
		A[j] = temp_row_vector;
		U[j] = temp_row_vector;

		//swap indices in the premutation cycle
		temp_value = p[index];
		p[index] = p[j];
		p[j] = temp_value;

		//Gaussian Elimination
		for (size_t i = j + 1; i < A.size(); i++)
		{
			A[i][j] = A[i][j] / A[j][j];
			L[i][j] = A[i][j]; //Store values in L
			for (size_t k = j+1; k < A.size(); k++)
			{
				A[i][k] = A[i][k] - A[i][j] * A[j][k];
			}
		}
		L[j][j] = 1; //Assign 1 along diagonal
		//U is upper triangular
		for (size_t i = 0; i < j; i++) { U[j][i] = 0; }
	}
}

double matrices::determinant(std::vector<std::vector<double>> A)
{
	/*
	Decomposes A = LU
	Since determinant is linear wrt products,
	det(upper or lower triangular M) = prod(diag(M)),
	diag(L) = 1, then
	det(A) = det(L)*det(U) = det(U) = prod(diag(U)).
	*/

	//Factor PA = LU
	std::vector<std::vector<double>> L(A.size(), std::vector<double>(A.size()));
	std::vector<std::vector<double>> U(A.size(), std::vector<double>(A.size()));
	std::vector<double> p(A.size());
	matrices::lu_decomposition(A, L, U, p);

	//Calculate det(U) = prod(diag(U))
	double result = 1.0;
	for (size_t i = 0; i < U.size(); i++)
	{
		result *= U[i][i];
	}

	return result;
}

void matrices::lower_triangular_solver(std::vector<std::vector<double>> L, std::vector<double> b, std::vector<double> &y)
{
	/*
	Solves the linear system Ly = b via forward elimination,
	in which L is lower-triangular.
	*/
	assert(L.size() == L[1].size());
	assert(L.size() == y.size());
	assert(b.size() == y.size());

	double sum;
	for (size_t i = 0; i < L.size(); i++)
	{
		sum = 0;
		for (size_t j = 0; j < i; j++)
		{
			sum += L[i][j] * y[j];
		}
		y[i] = (b[i] - sum) / L[i][i];
	}
}

void matrices::upper_triangular_solver(std::vector<std::vector<double>> U, std::vector<double> b, std::vector<double> &x)
{
	/*
	Solves the linear system Ux = b via backward substitution,
	in which U is upper-triangular.
	*/
	assert(U.size() == U[1].size());
	assert(U.size() == x.size());
	assert(b.size() == x.size());

	double sum;
	for (size_t i = U.size(); i-- > 0 ; )
	{
		sum = 0;
		for (size_t j = i + 1; j < U.size(); j++)
		{
			sum += U[i][j] * x[j];
		}
		x[i] = (b[i] - sum)/ U[i][i];
	}
}

void matrices::linear_system_solver(std::vector<std::vector<double>> A, std::vector<double> b, std::vector<double>& x)
{
	/*
	Solves linear system Ax = b by performing PA = LU via Pivoting Gaussian Elimination
	to solve linear systems 
		Ly = Pb via forwards substitution 
		Ux = y via backwards substitution.
	*/
	assert(A.size() == A[1].size());
	assert(A.size() == x.size());
	assert(b.size() == x.size());

	//Factor A = LU
	std::vector<std::vector<double>> L(A.size(), std::vector<double>(A[0].size()));
	std::vector<std::vector<double>> U(A.size(), std::vector<double>(A[0].size()));
	std::vector<double> p(A.size());
	matrices::lu_decomposition(A, L, U, p);

	std::vector<double> permuted_b;
	std::transform(p.begin(), p.end(), std::back_inserter(permuted_b), [&](size_t i) { return b[i]; });

	//Solve Ly = Pb for y
	std::vector<double> y(L.size());
	matrices::lower_triangular_solver(L, permuted_b, y);

	//Solve Ux = y
	matrices::upper_triangular_solver(U, y, x);
}
