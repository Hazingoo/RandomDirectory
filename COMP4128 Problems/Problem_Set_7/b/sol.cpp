#include <bits/stdc++.h>
using namespace std;

// Returns prime factors in increasing order with right multiplicity.
vector<long long> primefactorize(long long x)
{
    vector<long long> factors;
    for (long long f = 2; f * f <= x; f++)
        while (x % f == 0)
        {
            factors.push_back(f);
            x /= f;
        }

    if (x != 1)
        factors.push_back(x);
    return factors;
}

void solve()
{
    long long val;
    cin >> val;

    if (val == 1)
    {
        cout << "1 0\n";
        return;
    }

    vector<long long> factors = primefactorize(val);
    unordered_map<long long, long long> factorCount;
    long long res = 1, maxVal = -1;
    bool flag = false;
    for (long long factor : factors)
    {
        if (factorCount.count(factor) > 0)
        {
            factorCount[factor]++;
        }
        else
        {
            factorCount[factor] = 1;
        }
    }

    for (auto &pair : factorCount)
    {
        res *= pair.first;
        if (maxVal != -1 && pair.second > maxVal)
        {
            maxVal = pair.second;
            flag = true;
        }
        else if (maxVal == -1)
        {
            maxVal = pair.second;
        }
        else if (maxVal > pair.second)
        {
            flag = true;
        }
    }

    long long count1 = ceil(log2(maxVal));
    long long count2 = floor(log2(maxVal));

    if (flag || (count1 != count2))
    {
        count1++;
    }
    cout << res << " " << count1 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
