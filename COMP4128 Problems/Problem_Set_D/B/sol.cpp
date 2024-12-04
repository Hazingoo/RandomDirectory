#include <bits/stdc++.h>
using namespace std;
const int N = 101000;

bool visited[N];
vector<int> Ididntthinkthisthroguh;

void dfs(int root, vector<vector<int>> &adj, int center)
{
    visited[root] = true;
    if (adj[root].size() == 1 && center != root)
    {
        Ididntthinkthisthroguh.push_back(root + 1);
        return;
    }

    for (int node : adj[root])
    {
        if (!visited[node])
        {
            dfs(node, adj, center);
        }
    }
}

// observation
// 1-*
// 2-*
// *-3
// 3-4
// 3-5
// doesn't work if each node has more than 2
void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n, vector<int>());

    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    int count = 0;
    int center = 0;
    for (int i = 0; i < n; i++)
    {
        if (adj[i].size() > 2)
        {
            count++;
            center = i;
        }
    }

    if (count > 1)
    {
        cout << "No\n";
        return;
    }
    else
    {
        cout << "Yes\n";
    }

    dfs(center, adj, center);

    cout << Ididntthinkthisthroguh.size() << "\n";
    for (int pr : Ididntthinkthisthroguh)
    {
        cout << center + 1 << " " << pr << "\n";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}