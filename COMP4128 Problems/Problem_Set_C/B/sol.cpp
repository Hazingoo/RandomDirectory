#include <bits/stdc++.h>
using namespace std;

const long long N = 20;
const long long INF = 1e9;
long long n, m, k;
long long satisfaction[N];
long long rules[N][N];
long long dp[1 << N][N];

void solve()
{
    cin >> n >> m >> k;
    for (long long i = 0; i < n; i++)
    {
        cin >> satisfaction[i];
    }
    memset(rules, 0, sizeof(rules));
    for (long long i = 0; i < k; i++)
    {
        long long x, y, c;
        cin >> x >> y >> c;
        rules[x - 1][y - 1] = c;
    }

    for (long long mask = 0; mask < (1 << n); mask++)
    {
        for (long long last = 0; last < n; last++)
        {
            dp[mask][last] = -INF;
        }
    }

    for (long long i = 0; i < n; i++)
    {
        dp[1 << i][i] = satisfaction[i];
    }

    for (long long mask = 1; mask < (1 << n); mask++)
    {
        long long count_eaten = __builtin_popcount(mask);
        if (count_eaten > m)
            continue;

        for (long long last = 0; last < n; last++)
        {
            if (!(mask & (1 << last)))
                continue;

            long long prev_mask = mask ^ (1 << last);

            // cout << last << endl;

            for (long long prev = 0; prev < n; prev++)
            {
                // cout << prev_mask << endl;
                if (prev_mask & (1 << prev))
                {
                    dp[mask][last] = max(dp[mask][last],
                                         dp[prev_mask][prev] + satisfaction[last] + rules[prev][last]);
                }
            }
        }
    }

    long long result = -INF;
    for (long long mask = 0; mask < (1 << n); mask++)
    {
        // cout << mask << endl;
        if (__builtin_popcount(mask) == m)
        {
            for (long long i = 0; i < n; i++)
            {
                if (mask & (1 << i))
                {
                    result = max(result, dp[mask][i]);
                }
            }
        }
    }
    cout << result << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}