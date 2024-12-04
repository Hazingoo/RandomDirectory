#include <bits/stdc++.h>
using namespace std;

using vi = vector<long long>;

void solve()
{
    long long n;
    cin >> n;

    vector<pair<long long, long long>> m;
    for (long long i = 0; i < n; i++)
    {
        long long a, b;
        cin >> a >> b;
        pair<long long, long long> job;
        job.first = a;
        job.second = b;
        m.push_back(job);
    }

    sort(m.begin(), m.end());

    long long total = 0;
    long long cur = 0;
    for (long long i = 0; i < m.size(); i++)
    {
        // printf("first: %lld second: %lld total: %lld\n", m[i].first, m[i].second, total);
        cur += m[i].second - (m[i].first + total);
        total += m[i].first;
    }

    cout << cur << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}
