#include <bits/stdc++.h>
using namespace std;

const long long N = 3010;
int m;
int used[N][N];
#define ll long long
/*
 * kruskal
 */

struct edge
{
    int u, v;
    long long w;
};
bool operator<(const edge &a, const edge &b)
{
    return a.w < b.w;
}

edge edges[N];
int p[N];
/*
 * union find slow
 */

int parent[N];

void init(int n)
{
    for (int i = 1; i <= n; i++)
        parent[i] = i;
}

int root(int x)
{
    // only roots are their own parents
    return parent[x] == x ? x : root(parent[x]);
}

void join(int x, int y)
{
    // join roots
    x = root(x);
    y = root(y);
    // test whether already connected
    if (x == y)
        return;
    parent[y] = x;
}

int mst()
{
    auto comp = [](edge a, edge b)
    {
        return a.w < b.w;
    };

    sort(edges, edges + m, comp); // sort by increasing weight
    int total_weight = 0;
    for (int i = 0; i < m; i++)
    {
        edge &e = edges[i];
        // cout << e.u << " " << e.v << " " << e.w << "\n";
        // if the endpoints are in different trees, join them
        if (root(e.u) != root(e.v))
        {
            used[e.u][e.v] = 1;
            total_weight += e.w;
            join(e.u, e.v);
        }
    }
    return total_weight;
}
void solve()
{
    int n;
    cin >> n >> m;
    init(n);

    int source, sink;
    long long weight;
    cin >> source >> sink >> weight;

    for (int i = 0; i < m - 1; i++)
    {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        edges[i] = {a, b, c};
    }

    edges[m - 1] = {source, sink, weight};

    mst();
    if (used[source][sink])
    {
        cout << "0\n";
    }
    else
    {
        cout << "1\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
