#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const long long MOD = 1e9 + 7;
const long long N = 255;
ll f[N];
long long modpow(long long x, long long n)
{
    if (n == 0)
        return 1;
    long long a = modpow(x, n / 2);
    a = a * a % MOD;
    if (n % 2 == 1)
        a = a * x % MOD;
    return a;
}

ll inv(ll x)
{
    return modpow(x, MOD - 2); // Fermat's little theorem
}

ll combinatoric(int n, int k)
{
    ll res = (f[n] * inv(f[n - k])) % MOD;
    res = (res * inv(f[k])) % MOD;
    return res;
}

void solve()
{
    f[0] = 1;
    for (int i = 1; i < N; i++)
        f[i] = (i * f[i - 1]) % MOD;
    // this problem is basically, just number of ways to place a 1 in each row, don't care about columnn,
    // each row must has at least 1 1, so we can just care about each row
    // or column, also be careful of not double counting (could be inclusion and exclusion principle),
    // we can achieve this by limiting our selves to numbers > 2, but we might
    // need each cell to have 1 as well
    long long n, k;

    cin >> n >> k;
    long long total = 0;
    for (int i = 0; i <= n; i++)
    {
        ll expn = modpow(
                      modpow(k, n - i) * modpow(k - 1, i) % MOD - modpow(k - 1, n) + MOD,
                      n) %
                  MOD;
        // Apply inclusion-exclusion principle
        total += (modpow(-1, i) * combinatoric(n, i) % MOD * expn) % MOD;
        total = (total + MOD) % MOD; // Ensure non-negative modulo result
    }

    cout << total << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
