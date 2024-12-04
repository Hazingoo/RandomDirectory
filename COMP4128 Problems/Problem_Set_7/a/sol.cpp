#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

long long modPow(long long x, long long n)
{
    if (n == 0)
        return 1;
    long long a = modPow(x, n / 2);
    a = a * a % MOD;
    if (n % 2 == 1)
        a = a * x % MOD;
    return a;
}
void solve()
{
    long long n;
    cin >> n;
    for (long long i = 0; i < n; i++)
    {
        long long length;
        cin >> length;
        long long arr[length];

        long long result = 0;

        for (long long j = 0; j < length; j++)
        {
            cin >> arr[j];
        }

        sort(arr, arr + length);

        for (long long j = 0; j < length; j++)
        {
            for (long long k = 0; k < j; k++)
            {
                long long temp = (modPow(2, j - k - 1) % MOD * (arr[j] - arr[k])) % MOD;
                result = temp + result % MOD;
            }
        }
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
