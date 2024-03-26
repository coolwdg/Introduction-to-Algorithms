#include<iostream>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include "math.h"
#include<vector>

using namespace std;
int n;
vector<vector<int>> matrixMultiplication(vector<vector<int>>& mat1, vector<vector<int>>& mat2, int n) {
	vector<vector<int>> result(n, vector<int>(n, 0));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				result[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}

	return result;
}
void Doolittle(vector<vector<int>> &a, vector<vector<int>> &L, vector<vector<int>> &U)
{
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (j == i) L[i][i] = 1;
			else
			{
				L[i][j] = a[i][j];
				for (int k = 0; k < j; k++)
				{
					L[i][j] -= L[i][k] * U[k][j];
				}
				L[i][j] /= U[j][j];
			}
		}

		for (int j = i; j < n; j++)
		{
			U[i][j] = a[i][j];
			for (int k = 0; k < i; k++)
			{
				U[i][j] -= L[i][k] * U[k][j];
			}
		}
	}
}
vector<std::vector<int>> matrixInverse(std::vector<std::vector<int>> matrix) {
	int n = matrix.size();
	std::vector<std::vector<int>> inverse(n, std::vector<int>(n, 0));

	// 构造单位矩阵
	for (int i = 0; i < n; ++i) {
		inverse[i][i] = 1;
	}

	for (int i = 0; i < n; ++i) {
		// 将第i列第i个元素设为1
		int factor = matrix[i][i];
		for (int j = 0; j < n; ++j) {
			matrix[i][j] /= factor;
			inverse[i][j] /= factor;
		}

		// 将第i列其他元素设为0
		for (int k = 0; k < n; ++k) {
			if (k == i) continue;
			factor = matrix[k][i];
			for (int j = 0; j < n; ++j) {
				matrix[k][j] -= factor * matrix[i][j];
				inverse[k][j] -= factor * inverse[i][j];
			}
		}
	}

	return inverse;
}
vector<int> forwardSubstitution(const std::vector<std::vector<int>>& L, const std::vector<int>& b) {
	int n = L.size();
	std::vector<int> y(n, 0);

	for (int i = 0; i < n; ++i) {
		y[i] = b[i];
		for (int j = 0; j < i; ++j) {
			y[i] -= L[i][j] * y[j];
		}
		y[i] /= L[i][i];
	}

	return y;
}
vector<int> backwardSubstitution(const std::vector<std::vector<int>>& U, const std::vector<int>& y) {
	int n = U.size();
	std::vector<int> x(n, 0);

	for (int i = n - 1; i >= 0; --i) {
		x[i] = y[i];
		for (int j = n - 1; j > i; --j) {
			x[i] -= U[i][j] * x[j];
		}
		x[i] /= U[i][i];
	}

	return x;
}
int main()
{
	cout << "输入矩阵的规模" << endl;
	cin >> n;
	cout << "输入系数矩阵" << endl;
	vector<vector<int>> L(n, vector<int>(n,0));
	vector<vector<int>> U(n, vector<int>(n,0));
	vector<vector<int>> a(n, vector<int>(n,0));
	vector<int> b(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> a[i][j];
		}
	}
	cout << "输入增广列" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> b[i];
	}

	Doolittle(a,L,U);
	cout << "LU分解" <<endl;
	cout << "U = " << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << U[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "L = " << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << L[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	vector<vector<int>> L1(matrixInverse(L));
	vector<vector<int>> U1(matrixInverse(U));
	vector<vector<int>> b3(n, vector<int>(n, 0));
	vector<int> y = forwardSubstitution(L, b);

	vector<int> solution = backwardSubstitution(U, y);
	cout << "Solution:" << std::endl;
	for (double val : solution) {
		std::cout << val << " ";
	}
	cout << endl << endl << endl;

	return 0;
}

