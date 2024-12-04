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
    // level[v] stores dist from s to v
    // uptochild[v] stores first non-useless child.
    vector<int> level, uptochild;

    FlowNetwork(int _n) : n(_n)
    {
        // adjacency matrix is zero-initialised
        adjMat.resize(n);
        for (int i = 0; i < n; i++)
            adjMat[i].resize(n);
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
    }

    void add_edge(int u, int v, ll c)
    {
        // add to any existing edge without overwriting
        adjMat[u][v] += c;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        // cout << u << "->" << v << ": " << c << "\n";
    }

    void flow_edge(int u, int v, ll c)
    {
        // cout << u << "->" << v << ": " << c << "\n";
        // if (v == 10)
        // {
        //     cout << u - 3 << "\n";
        // }
        adjMat[u][v] -= c;
        adjMat[v][u] += c;
    }

    /*
     * dinic 2
     */

    // constructs the level graph and returns whether the sink is still reachable
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
            uptochild[u] = 0; // reset uptochild
            for (int v : adjList[u])
                if (adjMat[u][v] > 0)
                {
                    if (level[v] != -1) // already seen
                        continue;
                    level[v] = level[u] + 1;
                    q.push(v);
                }
        }
        return level[t] != -1;
    }

    /*
     * dinic 3
     */

    // finds an augmenting path with up to f flow.
    ll augment(int u, int t, ll f)
    {
        if (u == t)
            return f; // base case.
        // note the reference here! we increment uptochild[u], i.e. walk through u's neighbours
        // until we find a child that we can flow through
        for (int &i = uptochild[u]; i < adjList[u].size(); i++)
        {
            int v = adjList[u][i];
            if (adjMat[u][v] > 0)
            {
                // ignore edges not in the BFS tree.
                if (level[v] != level[u] + 1)
                    continue;
                // revised flow is constrained also by this edge
                ll rf = augment(v, t, min(f, adjMat[u][v]));
                // found a child we can flow through!
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

    /*
     * dinic 4
     */

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
    int n, m, k;

    cin >> n >> m >> k;

    FlowNetwork flowNetwork(m + n + 3);
    int source = m + n + 1, sink = m + n + 2;
    flowNetwork.add_edge(source, 0, k);

    // 0th is the extra node, 1th -> nth are hero nodes nth-> n+mth nodes are monster nodes
    for (int i = 1; i <= m; i++)
    {
        flowNetwork.add_edge(n + i, sink, 1);
    }

    for (int i = 1; i <= n; i++)
    {
        flowNetwork.add_edge(source, i, 1);
        flowNetwork.add_edge(0, i, 1);
    }

    for (int i = 1; i <= n; i++)
    {
        int t;
        cin >> t;
        // cout << t << "\n";
        for (int j = 1; j <= t; j++)
        {
            int monsterIdx;
            cin >> monsterIdx;
            flowNetwork.add_edge(i, n + monsterIdx, 1);
        }
    }

    int result = flowNetwork.dinic(source, sink);
    cout << result << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
