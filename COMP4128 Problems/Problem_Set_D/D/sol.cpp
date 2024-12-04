#include <bits/stdc++.h>
using namespace std;
const int N = 5010;

vector<int> edges[N];

int colourEdges[N][N];
int visited[N];
int max_colour;

void dfs(int v)
{
    if (visited[v] == 1 || visited[v] == 2)
    {
        return;
    }

    visited[v] = 1;
    for (int u : edges[v])
    {
        if (visited[u] == 1)
        {
            // back edge
            max_colour = 2;
            colourEdges[v][u] = 2;
        }

        if (visited[u] == 0)
        {
            // forward edge
            dfs(u);
        }
        else if (visited[u] == 2)
        {
            // cross edge
        }
    }
    visited[v] = 2;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    max_colour = 1;
    vector<pair<int, int>> edgePair;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            colourEdges[i][j] = 1;
        }
    }

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        edges[x].push_back(y);
        edgePair.push_back(make_pair(x, y));
    }
    for (int i = 0; i < n; i++)
    {
        dfs(i);
    }

    cout << max_colour << "\n";

    for (pair<int, int> &e : edgePair)
    {
        cout << colourEdges[e.first][e.second] << " ";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}