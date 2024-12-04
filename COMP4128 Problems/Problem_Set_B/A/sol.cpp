#include <bits/stdc++.h>
using namespace std;

using vi = vector<long long>;

// Reference https://www.geeksforgeeks.org/sort-vector-of-pairs-in-ascending-order-in-c/
bool sortBySec(pair<long long, long long> &a, pair<long long, long long> &b)
{
    return (a.second < b.second);
}

void solve()
{
    long long n, k;
    cin >> n >> k;
    vector<pair<long long, long long>> activities(n);
    multiset<long long> classroom;
    for (long long i = 0; i < n; i++)
    {
        cin >> activities[i].first >> activities[i].second;
    }

    for (long long i = 0; i < k; i++)
    {
        classroom.insert(-1);
    }
    sort(activities.begin(), activities.end(), sortBySec);
    long long count = 0;
    for (long long i = 0; i < n; i++)
    {
        auto el = classroom.upper_bound(activities[i].first);
        if (el != classroom.begin())
        {
            auto prevEl = prev(el);
            classroom.erase(prevEl);
            classroom.insert(activities[i].second + 1);
            count++;
        }
    }
    cout << count << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}