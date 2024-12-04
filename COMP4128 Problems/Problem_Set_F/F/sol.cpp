#include <bits/stdc++.h>
using namespace std;
#define ll long long
const long long INF = 1e15;

struct FlowNetwork
{
    int n;
    vector<vector<ll>> adjMat;
    vector<vector<int>> adjList;
    vector<int> level, uptochild;
    vector<int> seen;

    FlowNetwork(int _n) : n(_n)
    {
        adjMat.resize(n, vector<ll>(n, 0));
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
        seen.resize(n);
    }

    void add_edge(int u, int v, ll c)
    {
        adjMat[u][v] += c;
        adjMat[v][u] += c;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
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
                    adjMat[u][v] -= rf;
                    adjMat[v][u] += rf;
                    return rf;
                }
            }
        }
        return 0;
    }

    ll dinic(int s, int t)
    {
        ll res = 0;
        while (bfs(s, t))
        {
            fill(uptochild.begin(), uptochild.end(), 0);
            while (ll x = augment(s, t, INF))
            {
                res += x;
            }
        }
        return res;
    }

    void dfs1(int s)
    {
        seen[s] = 1;
        for (int v : adjList[s])
        {
            if (!seen[v] && adjMat[s][v] > 0)
            {
                dfs1(v);
            }
        }
    }

    void dfs2(int s)
    {
        seen[s] = 1;
        for (int v : adjList[s])
        {
            if (!seen[v] && adjMat[v][s] > 0)
            {
                dfs2(v);
            }
        }
    }

    bool check(int s, int t)
    {
        fill(seen.begin(), seen.end(), 0);
        dfs1(s);
        int total1 = accumulate(seen.begin(), seen.end(), 0);
        fill(seen.begin(), seen.end(), 0);
        dfs2(t);
        int total2 = accumulate(seen.begin(), seen.end(), 0);

        return total1 + total2 == n;
    }
};

void solve()
{
    freopen("attack.in", "r", stdin);
    freopen("attack.out", "w", stdout);
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    a--;
    b--;
    FlowNetwork flowNetwork(n);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--;
        v--;
        flowNetwork.add_edge(u, v, w);
    }

    flowNetwork.dinic(a, b);

    if (flowNetwork.check(a, b))
    {
        cout << "UNIQUE\n";
    }
    else
    {
        cout << "AMBIGUOUS\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
