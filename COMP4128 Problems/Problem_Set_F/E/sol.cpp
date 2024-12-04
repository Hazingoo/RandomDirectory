#include <bits/stdc++.h>
using namespace std;
#define ll long long
const long long INF = 1e15;

/*
 * dinic 1
 */

struct FlowNetwork
{
    int n;
    vector<vector<ll>> adjMat, adjList;
    vector<int> level, uptochild;

    FlowNetwork(int _n) : n(_n)
    {
        adjMat.resize(n, vector<ll>(n, 0));
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
    }

    void add_edge(int u, int v, ll c)
    {
        adjMat[u][v] += c;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void flow_edge(int u, int v, ll c)
    {
        adjMat[u][v] -= c;
        adjMat[v][u] += c;
    }

    bool bfs(int s, int t)
    {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            uptochild[u] = 0;
            for (int v : adjList[u])
            {
                if (adjMat[u][v] > 0 && level[v] == -1)
                {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] != -1;
    }

    ll augment(int u, int t, ll f)
    {
        if (u == t)
            return f;
        for (int &i = uptochild[u]; i < adjList[u].size(); i++)
        {
            int v = adjList[u][i];
            if (adjMat[u][v] > 0 && level[v] == level[u] + 1)
            {
                ll rf = augment(v, t, min(f, adjMat[u][v]));
                if (rf > 0)
                {
                    flow_edge(u, v, rf);
                    return rf;
                }
            }
        }
        level[u] = -1;
        return 0;
    }

    ll dinic(int s, int t)
    {
        ll res = 0;
        while (bfs(s, t))
            for (ll x = augment(s, t, INF); x; x = augment(s, t, INF))
                res += x;
        return res;
    }
};

void solve()
{
    int n, t;
    cin >> n >> t;

    FlowNetwork network(2 * n * n + 3);
    vector<vector<char>> grid(n, vector<char>(n));
    vector<vector<int>> scientist_count(n, vector<int>(n, 0));
    vector<vector<int>> capsule_count(n, vector<int>(n, 0));
    pair<int, int> reactor;
    const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

    // Reading scientists and reactor data
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            char c;
            cin >> c;
            if (isdigit(c))
            {
                scientist_count[i][j] = c - '0';
                if (scientist_count[i][j] > 0)
                {
                    network.add_edge(0, i * n + j + 1, scientist_count[i][j]);
                }
            }
            else
            {
                grid[i][j] = c;
                if (c == 'Z')
                    reactor = {i, j};
            }
        }
    }

    // Reading rescue capsule data
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            char c;
            cin >> c;
            if (isdigit(c))
            {
                capsule_count[i][j] = c - '0';
                if (capsule_count[i][j] > 0)
                {
                    network.add_edge(i * n + j + n * n + 1, 2 * n * n + 2, capsule_count[i][j]);
                }
            }
        }
    }

    // BFS to determine when each cell becomes unsafe
    vector<vector<int>> unsafe_time(n, vector<int>(n, t + 1));
    queue<pair<int, int>> q;
    q.push(reactor);
    unsafe_time[reactor.first][reactor.second] = 0;
    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++)
        {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && ny >= 0 && nx < n && ny < n && grid[nx][ny] != 'Y' && unsafe_time[nx][ny] > unsafe_time[x][y] + 1)
            {
                unsafe_time[nx][ny] = unsafe_time[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    // Connect scientists to capsules if reachable
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (scientist_count[i][j] > 0)
            {
                queue<pair<int, int>> q;
                vector<vector<int>> dist(n, vector<int>(n, -1));
                q.push({i, j});
                dist[i][j] = 0;
                while (!q.empty())
                {
                    auto [x, y] = q.front();
                    q.pop();
                    if (dist[x][y] > t || dist[x][y] >= unsafe_time[x][y])
                        continue;
                    if (capsule_count[x][y] > 0)
                    {
                        network.add_edge(i * n + j + 1, x * n + y + n * n + 1, INF);
                    }
                    for (int d = 0; d < 4; d++)
                    {
                        int nx = x + dx[d], ny = y + dy[d];
                        if (nx >= 0 && ny >= 0 && nx < n && ny < n && grid[nx][ny] != 'Y' && dist[nx][ny] == -1)
                        {
                            dist[nx][ny] = dist[x][y] + 1;
                            q.push({nx, ny});
                        }
                    }
                }
            }
        }
    }

    cout << network.dinic(0, 2 * n * n + 2) << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
