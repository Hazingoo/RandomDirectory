#include <bits/stdc++.h>
using namespace std;
const int N = 5000 + 10;
const int MOD = 998244353;

typedef long long ll;

ll madd(ll a, ll b)
{
    return ((a + b) % MOD + MOD) % MOD;
}

ll mmult(ll a, ll b)
{
    return (a * b) % MOD;
}

ll modpow(ll x, ll n, int m)
{
    if (n == 0)
        return 1;
    ll a = modpow(x, n / 2, m);
    a = a * a % m;
    if (n % 2 == 1)
        a = a * x % m;
    return a;
}

ll modinv(ll x)
{
    return modpow(x, MOD - 2, MOD);
}

long long modinverses[N];
long long dp[N][N];
long long totalCards[N];

void calcModInverses()
{
    for (int i = 1; i < N; i++)
    {
        modinverses[i] = modinv(i);
    }
}

void solve()
{
    int n;
    cin >> n;
    vector<int> array;
    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        array.push_back(num);
        totalCards[num]++;
    }

    calcModInverses();
    // i = number of elements selected j = last been selected
    // if count(j) > 0
    // dp[i][j] += count(j)-1/(n-i) case we win
    // dp[i][j] += count(k)/(n-i) *sum(n, k = j + 1) dp[i][k] case we win in the future
    // have to compute in decreasing order of k
    // final solution just dp[0][0]
    // change: Time limit error, guess i have to do precomputation
    for (int i = n - 1; i >= 0; i--)
    {
        int prefixSum[n];
        fill(prefixSum, prefixSum + n, 0);

        for (int j = n; j >= 0; j--)
        {
            prefixSum[j] = mmult(totalCards[j], dp[i + 1][j]);
            if (j < n)
            {
                prefixSum[j] = madd(prefixSum[j + 1], prefixSum[j]);
            }
        }
        // stuff we select
        for (int j = n; j >= 0; j--)
        {
            // we have the chance to win
            if (totalCards[j] > 1)
            {
                int temp = mmult(totalCards[j] - 1, modinverses[n - i]);
                dp[i][j] = madd(temp, dp[i][j]);
            }

            if (j < n)
            {
                int temp = mmult(prefixSum[j + 1], modinverses[n - i]);
                dp[i][j] = madd(temp, dp[i][j]);
            }
        }
    }

    cout << dp[0][0] << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
