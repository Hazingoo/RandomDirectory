#include <bits/stdc++.h>
using namespace std;
const int N = 2 * 1e5 + 10;
const int M = 2 * 1e5 + 10;
int is_in_MST[M];
int parent[N][50];
struct edge
{
    int u, v, idx, w;
};
vector<edge> mstEdge[N];
int maxEdge[N][50];
/*
 * kruskal
 */

bool operator<(const edge &a, const edge &b)
{
    return a.w < b.w;
}

int unionParent[N];
int subtree_size[N];

void init(int n)
{
    for (int i = 1; i <= n; i++)
    {
        unionParent[i] = i;
        subtree_size[i] = 1;
    }
}

/*
 * union find path compression
 */

int root(int x)
{
    // only roots are their own unionParents
    // otherwise apply path compression
    return unionParent[x] == x ? x : unionParent[x] = root(unionParent[x]);
}

void join(int x, int y)
{
    // join roots
    x = root(x);
    y = root(y);
    // test whether already connected
    if (x == y)
        return;
    // size heuristic
    // hang smaller subtree under root of larger subtree
    if (subtree_size[x] < subtree_size[y])
    {
        unionParent[x] = y;
        subtree_size[y] += subtree_size[x];
    }
    else
    {
        unionParent[y] = x;
        subtree_size[x] += subtree_size[y];
    }
}
vector<int> adjMat[N];
edge edges[N];
edge inputEdges[N];
int p[N];
int root(int u);
void join(int u, int v);
long long m;

int mst()
{
    sort(edges, edges + m); // sort by increasing weight
    int total_weight = 0;
    for (int i = 0; i < m; i++)
    {
        // cout << "is it looping" << "\n";
        edge &e = edges[i];
        // cout << "try to joining: " << e.u << " " << e.v << "\n";
        // if the endpoints are in different trees, join them
        if (root(e.u) != root(e.v))
        {
            mstEdge[e.u].push_back(e);
            edge newEdge;
            newEdge.u = e.v;
            newEdge.v = e.u;
            newEdge.w = e.w;
            mstEdge[e.v].push_back(newEdge);
            is_in_MST[e.idx] = 1;
            total_weight += e.w;
            join(e.u, e.v);
            // cout << "joining: " << e.u << " " << e.v << "\n";
        }
    }
    return total_weight;
}

/*
 * lca 1
 */

// parent[u][k] is the 2^k-th parent of u
int log2s[N];
int depth[N];

int n;
void preprocess()
{
    log2s[0] = -1;
    log2s[1] = 0;
    for (int i = 2; i <= n; ++i)
    {
        log2s[i] = log2s[i / 2] + 1;
    }
    for (int i = 1; i <= n; i++)
    {
        // assume parent[i][0] (the parent of i) is already filled in
        for (int j = 1; (1 << j) < n; j++)
        {
            parent[i][j] = -1;
            maxEdge[i][j] = -1;
        }
    }

    // fill in the parent for each power of two up to n
    for (int j = 1; (1 << j) < n; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            if (parent[i][j - 1] != -1)
            {
                // the 2^j-th parent is the 2^(j-1)-th parent of the 2^(j-1)-th parent
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
                maxEdge[i][j] = max(maxEdge[i][j - 1], maxEdge[parent[i][j - 1]][j - 1]);
            }
        }
    }
}

/*
 * lca 2
 */

int lca(int u, int v)
{
    // make sure u is deeper than v
    int ans = 0;
    if (depth[u] < depth[v])
    {
        swap(u, v);
    }

    // log2s[i] holds the largest k such that 2^k <= i
    // precompute by DP: log2s[i] = log2s[i/2] + 1
    for (int i = log2s[depth[u]]; i >= 0; i--)
    {
        // repeatedly raise u by the largest possible power of two until it is the same depth as v
        if (depth[u] - (1 << i) >= depth[v])
        {
            ans = max(ans, maxEdge[u][i]);
            u = parent[u][i];
        }
    }

    if (u == v)
        return ans;

    for (int i = log2s[depth[u]]; i >= 0; i--)
        if (parent[u][i] != -1 && parent[u][i] != parent[v][i])
        {
            // raise u and v as much as possible without having them coincide
            // this is important because we're looking for the lowest common ancestor, not just any
            ans = max(ans, maxEdge[u][i]);
            ans = max(ans, maxEdge[v][i]);
            u = parent[u][i];
            v = parent[v][i];
        }

    ans = max(ans, maxEdge[u][0]);
    ans = max(ans, maxEdge[v][0]);
    return ans;
}

int getParent(int u, int v)
{
    // make sure u is deeper than v
    if (depth[u] < depth[v])
        swap(u, v);

    // log2s[i] holds the largest k such that 2^k <= i
    // precompute by DP: log2s[i] = log2s[i/2] + 1
    for (int i = log2s[depth[u]]; i >= 0; i--)
    {
        // repeatedly raise u by the largest possible power of two until it is the same depth as v
        if (depth[u] - (1 << i) >= depth[v])
            u = parent[u][i];
    }

    if (u == v)
        return u;

    for (int i = log2s[depth[u]]; i >= 0; i--)
        if (parent[u][i] != -1 && parent[u][i] != parent[v][i])
        {
            // raise u and v as much as possible without having them coincide
            // this is important because we're looking for the lowest common ancestor, not just any
            u = parent[u][i];
            v = parent[v][i];
        }

    // u and v are now distinct but have the same parent, and that parent is the LCA
    return parent[u][0];
}

int seen[N];

void dfs(int v = 1, int from = -1, int curDepth = 0, int weight = -1)
{
    seen[v] = 1;
    depth[v] = curDepth;
    parent[v][0] = from;
    maxEdge[v][0] = weight;
    // cout << "from: " << from << "to: " << v << "at depth: " << curDepth << "\n";
    for (edge u : mstEdge[v])
    {
        if (!seen[u.v])
        {
            dfs(u.v, v, curDepth + 1, u.w);
        }
    }
}

void solve()
{
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edge newEdge;
        newEdge.u = u;
        newEdge.v = v;
        newEdge.w = w;
        newEdge.idx = i;
        edges[i] = newEdge;
        inputEdges[i] = newEdge;
    }
    init(n);
    int cost = mst();
    dfs();

    preprocess();

    // cout << "parent: " << getParent(1, 2) << "\n";
    // cout << "value: " << lca(1, 2) << "\n";
    for (int i = 0; i < m; i++)
    {
        // cout << "looking at: " << inputEdges[i].u << ": " << inputEdges[i].v << "\n";
        if (is_in_MST[i])
        {
            // cout << "in MST" << "\n";
            cout << cost << endl;
        }
        else
        {
            // cout << "not in MST" << "\n";
            int heaviestCost = lca(inputEdges[i].u, inputEdges[i].v);
            // cout << "heaviestcost: " << heaviestCost << "\n";
            // cout << "parent: " << getParent(inputEdges[i].v, inputEdges[i].u) << "\n";
            cout << cost - heaviestCost + inputEdges[i].w << endl;
            // cout << "------" << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}