// vector_spaces.h

#pragma once
#include <cassert>
#include <iostream>
#include <vector>

/*
Overloaded functions to handle many operations
for vector spaces in most orders, e.g., 
commutative multiplication with scalar and vector/matrix.
*/
namespace vector_spaces
{
	//Self operations
	double inner_product(std::vector<double> v1, std::vector<double> v2); //v1 dot v2
	double vector_sum(std::vector<double> v); //sum of vector elements
	double vector_avg(std::vector<double> v); //arithmetic mean of vector elements

	std::vector<std::vector<double>> transpose(std::vector<std::vector<double>> A); //matrix transpose (real-valued)

	/* Group Operations:

	A group G is a collection of objects with an operation @ such that
	1) There is an identity element e such that x @ e = x for all x in G.
	2) Closure: x @ y in G for all x,y in G.
	3) Associativity: x @ (y @ z) = (x @ y ) @ z for all x,y,z in G.
	4) Inverse: For all x in G, there exists a y in G such that x @ y = e.

	An abelian group has an additional property
	5) Commutativity: x @ y = y @ x for all x,y in G
	*/

	//Addition
	std::vector<double> addition(std::vector<double> v1, std::vector<double> v2); //point-wise vector addition
	std::vector<std::vector<double>> addition(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B); //point-wise matrix addition	
	std::vector<double> subtraction(std::vector<double> v1, std::vector<double> v2); //point-wise vector subtraction
	std::vector<std::vector<double>> subtraction(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B); //point-wise matrix subtraction

	//Scale
	std::vector<double> scalar_multiplication(std::vector<double> v, double a); //point-wise vector scaling
	std::vector<double> scalar_multiplication(double a, std::vector<double> v); //point-wise vector scaling
	std::vector<std::vector<double>> scalar_multiplication(std::vector<std::vector<double>> A, double a); //point-wise matrix scaling
	std::vector<std::vector<double>> scalar_multiplication(double a, std::vector<std::vector<double>> A); //point-wise matrix scaling

	//Multiply
	std::vector<double> multiplication(std::vector<double> v, std::vector<std::vector<double>> A);
	std::vector<double> multiplication(std::vector<std::vector<double>> A, std::vector<double> v);
	std::vector<std::vector<double>> multiplication(const std::vector<std::vector<double>> A, std::vector<std::vector<double>> B); //matrix multiplication

	// Inverse
	std::vector<std::vector<double>> matrix_invert_2x2(std::vector<std::vector<double>> A);
}
