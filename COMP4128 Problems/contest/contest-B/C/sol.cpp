#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

void solve()
{
    long long n;
    cin >> n;
    long long dp[n][n];

    memset(dp, 0, sizeof(dp));
    dp[0][0] = 0;
    dp[0][1] = 1;
    dp[0][2] = 3;
    for (long long i = 3; i <= n; i++)
    {

        for (long long j = i; j >= 0; j--)
        {
            long long result = 1;
            if (j - 1 >= 0)
            {
                if (dp[0][j - 1] == 0)
                {
                    result = 1;
                }
                else
                {
                    result *= dp[0][j - 1];
                }
            }

            if (i - j - 1 >= 0)
            {
                if (dp[0][i - j - 1] != 0)
                {
                    result = (result * dp[0][i - j - 1]);
                }
            }

            dp[0][i] += result;
        }
    }

    cout << dp[0][n] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}

// 0 1 3 2
// 0 3 1 2
//  0 1 2 4 3
//  0 1 2 4 3

// 0 1 4 2 3