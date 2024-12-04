#include <bits/stdc++.h>
using namespace std;

void solve()
{
    long long n;
    cin >> n;

    vector<long long> r(n);
    for (long long i = 0; i < n; i++)
    {
        cin >> r[i];
    }

    sort(r.begin(), r.end(), greater<long long>());

    long long max_el = r[0];
    vector<long long> result;
    result.push_back(max_el);

    long long count = max_el - 1;
    long long i = 1;
    while (count > 0 && i < n)
    {
        result.push_back(r[i]);
        if (r[i] < count)
        {
            count = r[i];
        }
        i++;
        count--;
    }

    cout << result.size() << "\n";

    for (long long i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
