#include <bits/stdc++.h>
using namespace std;

long long MOD = 1e9 + 7;
/*
 * matrix mult
 */

// Implementation for square matrices.
struct Matrix
{
    int n;
    vector<vector<long long>> v;

    Matrix(int _n) : n(_n)
    {
        v.resize(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                v[i].push_back(0);
    }

    Matrix operator*(const Matrix &o) const
    {
        Matrix res(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                {
                    res.v[i][j] += v[i][k] * o.v[k][j] % MOD;
                    res.v[i][j] = res.v[i][j] % MOD;
                }
        return res;
    }

    static Matrix getIdentity(int n)
    {
        Matrix res(n);
        for (int i = 0; i < n; i++)
            res.v[i][i] = 1;
        return res;
    }

    Matrix operator^(long long k) const
    {
        Matrix res = Matrix::getIdentity(n);
        Matrix a = *this;
        while (k)
        { // building up in powers of two
            if (k & 1)
                res = res * a;
            a = a * a;
            k /= 2;
        }
        return res;
    }
};

void solve()
{
    long long n, m;

    cin >> n >> m;
    // dp(n) = dp(n-1) + dp(n-m)
    // two ways
    // either we split or don't split

    // dp(n) = 1.0...0.1
    // dp(n-1) = 1.....0
    // dp(n-2) = 0.1.....0

    Matrix mat(101);

    mat.v[0][0] = 1;
    mat.v[0][m - 1] = 1;

    for (int i = 1; i < 101; i++)
    {
        mat.v[i][i - 1] = 1;
    }

    mat = mat ^ n;
    cout << mat.v[0][0] % MOD << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
