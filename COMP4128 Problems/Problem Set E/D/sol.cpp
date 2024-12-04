#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int from, to;
    long long weight;
    int id;
};

const int N = 1000;
vector<Edge> adjMat[N];
vector<Edge> edgesList;
long long dist[N];
bool visited[N];
int prevArray[N];
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> heapQueue;
long long n, m, L, start, target;

void dijkstra(int source)
{
    fill(dist, dist + n, LLONG_MAX);
    fill(visited, visited + n, false);
    fill(prevArray, prevArray + n, -1);
    heapQueue.push({0, source});
    dist[source] = 0;
    while (!heapQueue.empty())
    {
        auto [currentDist, node] = heapQueue.top();
        heapQueue.pop();

        if (visited[node])
            continue;
        visited[node] = true;

        for (const Edge &edge : adjMat[node])
        {
            if (!visited[edge.to] && dist[node] + edge.weight < dist[edge.to])
            {
                dist[edge.to] = dist[node] + edge.weight;
                prevArray[edge.to] = node;
                heapQueue.push({dist[edge.to], edge.to});
            }
        }
    }
}

void solve()
{
    cin >> n >> m >> L >> start >> target;

    vector<int> goneEdges;
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        long long cost;
        cin >> u >> v >> cost;

        if (cost == 0)
        {
            adjMat[u].push_back({u, v, 1, i});
            adjMat[v].push_back({v, u, 1, i});
            goneEdges.push_back(i);
        }
        else
        {
            adjMat[u].push_back({u, v, cost, -1});
            adjMat[v].push_back({v, u, cost, -1});
        }

        edgesList.push_back({u, v, cost, i});
    }
    dijkstra(start);

    if (dist[target] > L)
    {
        cout << "NO\n";
        return;
    }

    if (dist[target] == L)
    {
        cout << "YES\n";
        for (const Edge &edge : edgesList)
        {
            if (edge.weight == 0)
            {
                cout << edge.from << " " << edge.to << " " << 1 << "\n";
            }
            else
            {
                cout << edge.from << " " << edge.to << " " << edge.weight << "\n";
            }
        }
        return;
    }

    while (dist[target] < L)
    {
        vector<int> pathEdges;
        int node = target;

        while (node != start)
        {
            int prevArrayNode = prevArray[node];
            for (const Edge &edge : adjMat[prevArrayNode])
            {
                if (edge.to == node)
                {
                    pathEdges.push_back(edge.id);
                    break;
                }
            }
            node = prevArrayNode;
        }

        bool updated = false;
        for (int edgeId : pathEdges)
        {
            if (edgeId == -1)
                continue;

            for (Edge &edge : edgesList)
            {
                if (edge.id == edgeId && edge.weight == 0)
                {
                    long long difference = L - dist[target];
                    for (Edge &e : adjMat[edge.from])
                    {
                        if (e.to == edge.to && e.id == edgeId)
                        {
                            // cout << e.weight << "\n";
                            e.weight += difference;
                        }
                    }
                    // checks id and does stuff
                    for (Edge &e : adjMat[edge.to])
                    {
                        if (e.to == edge.from && e.id == edgeId)
                        {
                            e.weight += difference;
                        }
                    }
                    updated = true;
                    break;
                }
            }
            if (updated)
                break;
        }

        if (!updated)
        {
            cout << "NO\n";
            return;
        }

        dijkstra(start);
    }

    cout << "YES\n";
    for (const Edge &edge : edgesList)
    {
        if (edge.weight == 0)
        {
            for (const Edge &e : adjMat[edge.from])
            {
                if (e.to == edge.to && e.id == edge.id)
                {
                    cout << edge.from << " " << edge.to << " " << e.weight << "\n";
                    break;
                }
            }
        }
        else
        {
            cout << edge.from << " " << edge.to << " " << edge.weight << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
