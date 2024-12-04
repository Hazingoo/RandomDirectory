#include <bits/stdc++.h>
using namespace std;

using vi = vector<long long>;

void solve()
{
    long long n;
    cin >> n;
    vector<long long> row1(n);
    vector<long long> row2(n);
    long long dp[n][3];

    for (long long i = 0; i < n; i++)
    {
        cin >> row1[i];
    }

    for (long long i = 0; i < n; i++)
    {
        cin >> row2[i];
    }

    dp[0][0] = row1[0];
    dp[0][1] = row2[0];
    dp[0][2] = 0;

    for (long long i = 1; i < n; i++)
    {
        dp[i][0] = max(dp[i - 1][1], dp[i - 1][2]) + row1[i];
        dp[i][1] = max(dp[i - 1][0], dp[i - 1][2]) + row2[i];
        dp[i][2] = max(dp[i - 1][0], max(dp[i - 1][1], dp[i - 1][2]));
    }

    cout << max(dp[n - 1][0], max(dp[n - 1][1], dp[n - 1][2])) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}