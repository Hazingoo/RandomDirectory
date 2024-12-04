#include <bits/stdc++.h>
using namespace std;

using vi = vector<long long>;

void solve()
{
    long long n, k;
    string s, t;
    cin >> n >> k >> s >> t;
    long long x = 1;
    long long y = 1;
    long long res = 0;

    for (long long i = 0; i < n; i++)
    {
        if (s[i] == 'a')
        {
            x = 2 * x - 1;
        }
        else
        {
            x = 2 * x;
        }

        if (t[i] == 'a')
        {
            y = 2 * y - 1;
        }
        else
        {
            y = 2 * y;
        }
        long long temp = y - x + 1;
        if (temp >= k)
        {
            res += k * (n - i);
            cout << res << endl;
            return;
        }
        else
        {
            res += y - x + 1;
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