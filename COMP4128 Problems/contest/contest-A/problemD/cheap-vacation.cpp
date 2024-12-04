#include <bits/stdc++.h>
using namespace std;

using vi = vector<long long>;

void solve()
{
    long long n, k;
    cin >> n >> k;

    long long low = 0, high = n;
    while (low <= high)
    {
        long long i = (low + high) / 2;
        long long res = (n - i) * ((n - i) + 1) / 2 - i;

        if (res == k)
        {
            cout << i << "\n";
            return;
        }
        else if (res > k)
        {
            low = i + 1;
        }
        else
        {
            high = i - 1;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}
