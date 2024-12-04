#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
bool visited[N];
static bool sortByThird(const tuple<int, int, int> &a,
                        const tuple<int, int, int> &b)
{
    return (get<2>(a) < get<2>(b));
}

void solve()
{
    long long n;
    cin >> n;

    vector<long long> employees(n);
    for (long long i = 0; i < n; i++)
    {
        cin >> employees[i];
    }

    memset(visited, false, sizeof(visited));

    vector<tuple<long long, long long, long long>> applications;

    long long m;
    cin >> m;

    for (long long i = 0; i < m; i++)
    {
        long long x, y, cost;
        cin >> x >> y >> cost;
        x--;
        y--;
        tuple<long long, long long, long long> app = make_tuple(x, y, cost);
        applications.push_back(app);
    }

    sort(applications.begin(), applications.end(), sortByThird);

    long long connections = 0;
    long long total = 0;
    for (long long i = 0; i < m && connections != n - 1; i++)
    {
        tuple<long long, long long, long long> app = applications[i];
        if (!visited[get<1>(app)])
        {
            visited[get<1>(app)] = true;
            total += get<2>(app);
            connections++;
        }
    }

    if (connections != n - 1)
    {
        cout << -1 << "\n";
        return;
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