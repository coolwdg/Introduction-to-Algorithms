#include<iostream>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include "math.h"
#include<vector>
using namespace std;
int n;

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

void Matrix_inverse(vector<vector<int>>& arc,int n, vector<vector<int>>& ans)//计算矩阵的逆
{
	int i, j, k;//列
	double max, tempA, tempB, P;
	int max_num;
	vector<vector<int>> arcs=arc;

	for (i = 0; i < n; i++)
	{
		ans[i][i] = 1;
	}
	for (i = 0; i < n; i++)//第i列
	{
		max = fabs(arcs[i][i]);
		max_num = i;
		for (j = i + 1; j < n; j++)//选出主元
		{
			if (fabs(arcs[j][i]) > max)
			{
				max = fabs(arcs[j][i]);
				max_num = j;
			}
		}
		for (k = 0; k < n; k++)//交换行
		{
			tempA = arcs[i][k];
			arcs[i][k] = arcs[max_num][k];
			arcs[max_num][k] = tempA;
			tempB = ans[i][k];
			ans[i][k] = ans[max_num][k];
			ans[max_num][k] = tempB;
		}
		for (k = i + 1; k < n; k++)
		{
			P = arcs[k][i] / arcs[i][i];
			for (j = 0; j < n; j++)
			{
				arcs[k][j] = arcs[k][j] - arcs[i][j] * P;
				ans[k][j] = ans[k][j] - ans[i][j] * P;
			}
		}
	}
	for (i = 0; i < n; i++)//行
	{
		P = arcs[i][i];
		for (j = i; j < n; j++)
		{
			arcs[i][j] = arcs[i][j] / P;
		}
		for (j = 0; j < n; j++)
		{
			ans[i][j] = ans[i][j] / P;
		}
	}
	for (i = n - 1; i > 0; i--)
	{
		for (j = i - 1; j >= 0; j--)
		{
			for (k = 0; k < n; k++)
			{
				ans[j][k] = ans[j][k] - ans[i][k] * arcs[j][i];
			}
		}
	}
}

int main()
{
	cout << "输入矩阵的规模" << endl;
	cin >> n;
	cout << "输入系数矩阵" << endl;
	vector<vector<int>> L(n, vector<int>(n,0));
	vector<vector<int>> L1(n, vector<int>(n, 0));
	vector<vector<int>> U(n, vector<int>(n,0));
	vector<vector<int>> U1(n, vector<int>(n, 0));
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
	Matrix_inverse(U, 3, L1);
	Matrix_inverse(L, 3, U1);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << L1[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
