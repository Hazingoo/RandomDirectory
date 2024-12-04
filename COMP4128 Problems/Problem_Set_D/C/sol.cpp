#include <bits/stdc++.h>
using namespace std;
const int N = 101000;

int preorder[N]; // order of pushing to the DFS stack
                 // initialise to -1
int T = 0;       // counter for preorder sequence
int reach[N];    // reach[u] is the smallest preorder index
                 // of any vertex reachable from u
vector<pair<int, int>> bridges;

vector<int> edges[N];

vector<pair<int, int>> result;

void dfs(int u, int from = -1)
{
    preorder[u] = T++;
    reach[u] = preorder[u];
    for (int v : edges[u])
    {
        if (v != from)
        {
            if (preorder[v] == -1)
            { // u--v is a tree edge
                result.push_back(make_pair(u, v));
                // v hasn't been seen before, so recurse
                dfs(v, u);
                // if v can't reach anything earlier than itself
                // then u--v is a bridge
                if (reach[v] == preorder[v])
                    bridges.emplace_back(u, v);
            }
            // back edges
            else if (preorder[v] < preorder[u])
            {
                result.push_back(make_pair(u, v));
            }
            // anything reachable from v is reachable from u
            reach[u] = min(reach[u], reach[v]);
        }
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;

    memset(preorder, -1, sizeof(preorder));

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    dfs(0);

    if (bridges.size() > 0)
    {
        cout << 0 << "\n";
        return;
    }

    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i].first + 1 << " " << result[i].second + 1 << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}