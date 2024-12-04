#include <bits/stdc++.h>
using namespace std;
const int N = 100100;

int n, k;
string left_wall, right_wall;
vector<int> edges[2 * N];
int seen[2 * N];

void solve()
{
    cin >> n >> k >> left_wall >> right_wall;

    // left wall
    for (int i = 0; i < n; i++)
    {
        if (left_wall[i] != 'X')
        {
            if (left_wall[i + 1] != 'X')
            {
                edges[i].push_back(i + 1);
                edges[i + 1].push_back(i);
            }

            if (i + k < n && right_wall[i + k] != 'X')
            {
                edges[i].push_back(i + k + n);
            }
        }
    }

    // right wall
    for (int i = 0; i < n; i++)
    {
        if (right_wall[i] != 'X')
        {
            if (right_wall[i + 1] != 'X')
            {
                edges[i + n].push_back(i + n + 1);
                edges[i + n + 1].push_back(i + n);
            }

            if (i + k < n && left_wall[i + k] != 'X')
            {
                edges[i + n].push_back(i + k);
            }
        }
    }

    queue<pair<int, int>> q;
    q.push(make_pair(0, -1));
    seen[0] = 1;
    while (!q.empty())
    {
        pair<int, int> pos = q.front();
        q.pop();
        // cout << pos.first << " " << pos.second << "\n";
        if (pos.second >= pos.first % n)
            continue;

        for (int v : edges[pos.first])
        {

            if (!seen[v])
            {
                seen[v] = 1;
                q.push(make_pair(v, pos.second + 1));
            }

            if ((v >= n && (2 * n - v <= k)) || (v < n && (n - v <= k)))
            {
                // cout << v << "\n";
                cout << "YES" << "\n";
                return;
            }
        }
    }

    cout << "NO" << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}