#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

const int M = 20;
const long long INF = LLONG_MAX;
long long dp[(1 << M)];
long long numOfSuch[M][M];

void solve()
{
    int n, m;
    string s;
    cin >> n >> m >> s;

    for (int i = 0; i < n - 1; i++)
    {
        numOfSuch[s[i] - 'a'][s[i + 1] - 'a']++;
        numOfSuch[s[i + 1] - 'a'][s[i] - 'a']++;
    }

    fill(dp, dp + (1 << m), INF);
    dp[0] = 0;

    for (int bit_mask = 1; bit_mask < (1 << m); bit_mask++)
    {
        int cnt = __builtin_popcount(bit_mask);
        for (int letter1 = 0; letter1 < m; letter1++)
        {
            if (!(bit_mask & (1 << letter1)))
                continue;
            int bye = bit_mask ^ (1 << letter1);
            long long cost = 0;

            for (int letter2 = 0; letter2 < m; letter2++)
            {
                if (letter1 == letter2)
                    continue;
                if (bye & (1 << letter2))
                {
                    cost += cnt * numOfSuch[letter1][letter2];
                }
                else
                {
                    cost -= cnt * numOfSuch[letter1][letter2];
                }
            }

            dp[bit_mask] = min(dp[bit_mask], dp[bye] + cost);
        }
    }

    cout << dp[(1 << m) - 1] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
