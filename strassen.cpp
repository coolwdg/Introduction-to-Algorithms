#include<iostream>
#include<vector>
using namespace std;
vector<vector<int>> add(const vector<vector<int>>& A, const vector<vector<int>>& B)
{
	int n = A.size();
	vector<vector<int>> C(n, vector<int>(n, 0));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
	return C;
}
vector<vector<int>> reduce(const vector<vector<int>>& A, const vector<vector<int>>& B)
{
	int n = A.size();
	vector<vector<int>> C(n, vector<int>(n, 0));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			C[i][j] = A[i][j] - B[i][j];
		}
	}
	return C;
}
vector<vector<int>> solve(const vector<vector<int>>& A, const vector<vector<int>>& B)
{
	int n = A.size();
	if (n == 1)
	{
		return { {A[0][0] * B[0][0]}};
	}
	int half = n / 2;
	vector<vector<int>> A11(half, vector<int>(half));
	vector<vector<int>> A12(half, vector<int>(half));
	vector<vector<int>> A21(half, vector<int>(half));
	vector<vector<int>> A22(half, vector<int>(half));
	vector<vector<int>> B11(half, vector<int>(half));
	vector<vector<int>> B12(half, vector<int>(half));
	vector<vector<int>> B21(half, vector<int>(half));
	vector<vector<int>> B22(half, vector<int>(half));
	for (int i = 0; i < half; ++i)
	{
		for (int j = 0; j < half; ++j)
		{
			A11[i][j] = A[i][j];
			A12[i][j] = A[i][j + half];
			A21[i][j] = A[i + half][j];
			A22[i][j] = A[i + half][j + half];
			B11[i][j] = B[i][j];
			B12[i][j] = B[i][j + half];
			B21[i][j] = B[i + half][j];
			B22[i][j] = B[i + half][j + half];
		}
	}
	vector<vector<int>> P1 = solve(A11, reduce(B12, B22));
	vector<vector<int>> P2 = solve(add(A11,A12), B22);
	vector<vector<int>> P3 = solve(add(A21, A22),B11);
	vector<vector<int>> P4 = solve(A22, reduce(B21, B11));
	vector<vector<int>> P5 = solve(add(A11,A22),add(B11, B22));
	vector<vector<int>> P6 = solve(reduce(A12,A22), add(B21, B22));
	vector<vector<int>> P7 = solve(reduce(A11,A21), add(B11, B12));

	vector<vector<int>> C11 = reduce(add(add(P5, P4), P6), P2);
	vector<vector<int>> C12 = add(P1, P2);
	vector<vector<int>> C21 = add(P3, P4);
	vector<vector<int>> C22 = reduce(add(P5, P1), add(P3, P7));
	vector<vector<int>> result(n, vector<int>(n, 0));
	for (int i = 0; i < half; ++i)
	{
		for (int j = 0; j < half; ++j)
		{
			result[i][j] = C11[i][j];
			result[i][j + half] = C12[i][j];
			result[i + half][j] = C21[i][j];
			result[i + half][j + half] = C22[i][j];
			
		}
	}
	return result;
	

}
int main()
{
	int n;
	cout << "输入矩阵规模n" << endl;
	cin >> n;
	vector<vector<int>> A(n, vector<int>(n, 0));
	vector<vector<int>> B(n, vector<int>(n, 0));
	vector<vector<int>> C(n, vector<int>(n, 0));
	
	cout << "输入A" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> A[i][j];
		}
	}
	cout << "输入B" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> B[i][j];
		}
	}
	C = solve(A, B);
	cout << "A*B的结果是：" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout<<C[i][j]<<" ";
		}
		cout << endl;
	}

	return 0;
}