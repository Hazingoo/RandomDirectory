#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

void solve()
{
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    if (a + b + c + d == 0)
    {
        cout << "0" << endl;
        return;
    }
    // n^2-n-2*a
    double a1 = (1 + sqrt(1 + 4 * 1 * 2 * a)) / 2;
    long long a_num = a1;
    if (a == 0)
    {
        if (b || c)
        {
            a_num = 1;
        }
        else
        {
            a_num = 0;
        }
    }
    else if (a1 - a_num > 0)
    {
        cout << "impossible" << endl;
        return;
    }
    double d1 = (1 + sqrt(1 + 4 * 1 * 2 * d)) / 2;
    long long d_num = d1;
    if (d == 0)
    {
        if (b || c)
        {
            d_num = 1;
        }
        else
        {
            d_num = 0;
        }
    }
    else if (d1 - d_num > 0)
    {
        cout << "impossible" << endl;
        return;
    }

    if (a_num * d_num != b + c)
    {
        cout << "impossible" << endl;
        return;
    }
    string res = string(a_num, '0');
    long long n = res.size();
    while (b || d_num)
    {
        if (n > b)
        {
            n--;
        }
        else if (!b)
        {
            res = '1' + res;
            d_num--;
        }
        else
        {
            b -= n;
            res = res.substr(0, n) + '1' + res.substr(n, res.size());
            d_num--;
        }
    }

    cout << res << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}