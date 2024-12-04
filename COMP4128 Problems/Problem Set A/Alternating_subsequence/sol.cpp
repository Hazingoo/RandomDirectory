#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

void solve()
{
    int n;
    cin >> n;

    long long total_sum = 0;
    vi a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int cur_max = a[0];
    for (int i = 1; i < n; i++)
    {
        if ((a[i] > 0 && a[i - 1] > 0) || (a[i] < 0 && a[i - 1] < 0))
        {
            if (a[i] > cur_max)
            {
                cur_max = a[i];
            }
        }
        else
        {
            total_sum += cur_max;
            cur_max = a[i];
        }
    }
    total_sum += cur_max;
    cout << total_sum << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--)
        solve();
}