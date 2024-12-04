#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    // Store segments as pairs of start and end points
    vector<pair<int, int>> segments(n);
    set<int> coords;

    // Read input and store unique coordinates
    for (int i = 0; i < n; i++)
    {
        int a, b, h;
        cin >> a >> b >> h;
        segments[i] = {a, b};
        coords.insert(a);
        coords.insert(b);
    }

    // Convert coordinates to vector and create index mapping
    vector<int> x_coords(coords.begin(), coords.end());
    map<int, int> coord_to_idx;
    for (int i = 0; i < x_coords.size(); i++)
    {
        coord_to_idx[x_coords[i]] = i;
    }

    // Create adjacency list:
    // Edge between coordinates i and j exists if any segment spans them
    vector<vector<int>> adj(coords.size());

    for (auto [start, end] : segments)
    {
        int start_idx = coord_to_idx[start];
        int end_idx = coord_to_idx[end];

        // Add edges between all pairs of coordinates this segment spans
        for (int i = start_idx; i < end_idx; i++)
        {
            for (int j = i + 1; j <= end_idx; j++)
            {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    // Find maximum degree in the graph
    int max_degree = 0;
    for (const auto &neighbors : adj)
    {
        max_degree = max(max_degree, (int)neighbors.size());
    }

    // The answer is the maximum vertex degree divided by 2
    // (because each edge was added twice in undirected graph)
    cout << (max_degree + 1) / 2 << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}