#include <bits/stdc++.h>
using namespace std;

struct edge
{
    long long y;
    long long cost;
    int isTrain;
};

const int N = 100100;
vector<edge> edges[N];
int n, m, k;
int trainsKept = 0;

int seen[N];
long long dist[N];

struct myComp
{
    constexpr bool operator()(
        edge const &a,
        edge const &b)
        const noexcept
    {
        if (a.cost != b.cost)
        {
            return a.cost > b.cost;
        }
        return a.isTrain > b.isTrain;
    }
};

void dij()
{
    priority_queue<edge, vector<edge>, myComp> pq;
    fill(dist, dist + N, LLONG_MAX);
    dist[0] = 0;
    // seen[0] = 1;

    // for (edge e : edges[0])
    // {
    //     pq.push(e);
    // }

    pq.push({0, 0, false});

    while (!pq.empty())
    {
        edge cur = pq.top();
        // cout << cur.y << "\n";
        pq.pop();

        if (seen[cur.y])
            continue;

        if (cur.isTrain)
        {
            trainsKept++;
        }

        dist[cur.y] = cur.cost;
        seen[cur.y] = true;

        // relax all edges from v
        for (edge nxt : edges[cur.y])
        {
            long long u = nxt.y, weight = nxt.cost;
            if (!seen[u])
                pq.push({u, cur.cost + weight, nxt.isTrain});
        }
    }
}
void solve()
{
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++)
    {
        long long x, y, cost;
        cin >> x >> y >> cost;
        x--;
        y--;
        edges[x].push_back({y, cost, 0});
        edges[y].push_back({x, cost, 0});
    }

    for (int i = 0; i < k; i++)
    {
        long long y, cost;
        cin >> y >> cost;
        y--;
        edges[0].push_back({y, cost, 1});
        edges[y].push_back({0, cost, 1});
    }

    dij();
    cout << k - trainsKept << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}