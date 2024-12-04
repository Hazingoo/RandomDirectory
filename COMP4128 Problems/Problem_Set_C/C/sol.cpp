#include <bits/stdc++.h>
using namespace std;
const int N = 105;
const long long INF = 1e18;

int n, m, k;
int colors[N];
int paint[N][N];
long long dp[N][N][N];

void solve()
{
    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++)
    {
        cin >> colors[i];
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> paint[i][j];
        }
    }

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            for (int p = 0; p <= k; p++)
            {
                dp[i][j][p] = INF;
            }
        }
    }

    if (colors[1] != 0)
    {
        dp[1][colors[1]][1] = 0;
    }
    else
    {
        for (int j = 1; j <= m; j++)
        {
            dp[1][j][1] = paint[1][j];
        }
    }

    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int q = 1; q <= k; q++)
            {
                if (dp[i - 1][j][q] == INF)
                    continue;
                long long cost = dp[i - 1][j][q];

                if (colors[i] != 0)
                {
                    int newTotal = q;
                    if (j != colors[i])
                    {
                        newTotal++;
                    }
                    if (newTotal <= k)
                    {
                        dp[i][colors[i]][newTotal] = min(dp[i][colors[i]][newTotal], cost);
                    }
                }
                else
                {
                    for (int p = 1; p <= m; p++)
                    {
                        int newTotal = q;
                        if (j != p)
                        {
                            newTotal++;
                        }
                        if (newTotal <= k)
                        {
                            dp[i][p][newTotal] = min(dp[i][p][newTotal], cost + paint[i][p]);
                        }
                    }
                }
            }
        }
    }

    long long result = INF;
    for (int i = 1; i <= m; i++)
    {
        result = min(result, dp[n][i][k]);
    }

    if (result == INF)
    {
        cout << -1 << "\n";
    }
    else
    {
        cout << result << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
