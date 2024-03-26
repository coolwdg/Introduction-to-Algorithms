#include<iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
inline double Abs(const double& x) 
{
    return x < 0 ? -x : x;
}

inline int Comp(const double& x, const double& y) 
{
    if (Abs(x - y) < 1e-7)
    {
        return 0;
    }
        
    return Abs(x) > Abs(y) ? 1 : -1;
}
int n;
int m;



int main() 
{
    cout << "输入矩阵的行数和列数" << endl;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    vector<int> ans(m);
    cout << "输入矩阵" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> a[i][j];
        }
    }  
           
    for (int i = 0; i < n; i++) 
    {
        int pos = i;
        for (int j = i+1; j < n; j++)
            if (Comp(a[j][i], a[pos][i]) == 1)
                pos = j;
        
        if (Comp(a[pos][i], 0) == 0) 
        {
            puts("No Solution");
            return 0;
        }
        for (int j = 0; j < m; j++)
            swap(a[pos][j], a[i][j]);
       
        double tmp = a[i][i];
        for (int j = i; j < m; j++)
            a[i][j] /= tmp;
        
        for (int j = i + 1; j < n; j++) 
        {
            tmp = a[j][i];
            for (int k = i; k < m; k++)
                a[j][k] -= a[i][k] * tmp;
        }
        
    }
    for (int i = n-1; i >= 0; i--) 
    {
        ans[i] = a[i][n];
        for (int j = n-1; j >= i + 1; j--)
            ans[i] -= ans[j] * a[i][j];
    }
    for (int i = 0; i < n; i++)
    cout << ans[i] << " ";
    return 0;
}
