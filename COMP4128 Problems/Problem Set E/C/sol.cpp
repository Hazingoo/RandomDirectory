#include <bits/stdc++.h>
using namespace std;

struct edge
{
    long long y;
    long long cost;
    int isTrain;
};

const int N = 501;
long long dist[N][N];
vector<long long> removedVertex;
bool active[N];
int n;

const long long INF = 200000;

void solve()
{
    fill(active, active + N, false);
    cin >> n;

    for (long long i = 0; i < n; i++)
    {
        for (long long j = 0; j < n; j++)
        {
            dist[i][j] = INF;
        }
    }

    for (long long i = 0; i < n; i++)
    {
        for (long long j = 0; j < n; j++)
        {
            cin >> dist[i][j];
        }
    }

    for (long long i = 0; i < n; i++)
    {
        long long vertex;
        cin >> vertex;
        vertex--;
        removedVertex.push_back(vertex);
    }

    // for (long long i = 0; i < n; i++)
    // {
    //     cout << removedVertex[i] << endl;
    // }

    vector<long long> result;

    for (long long i = n - 1; i >= 0; i--)
    {
        long long sum = 0;
        active[removedVertex[i]] = true;
        for (long long j = 0; j < n; j++)
        {
            for (long long k = 0; k < n; k++)
            {
                dist[j][k] = min(dist[j][k], dist[j][removedVertex[i]] + dist[removedVertex[i]][k]);
                if (active[j] && active[k])
                {
                    sum += dist[j][k];
                }
            }
        }
        result.push_back(sum);
    }

    for (long long i = n - 1; i >= 0; i--)
    {
        cout << result[i] << " ";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}