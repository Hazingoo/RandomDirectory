#include <bits/stdc++.h>
using namespace std;

// Compile using g++ -std=c++11 -O2 -Wall sol.cpp -o sol
const int N = 10000;
int parent[N];
int subtree_size[N];

void init(int n)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        subtree_size[i] = 1;
    }
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
        parent[x] = y;
        subtree_size[y] += subtree_size[x];
    }
    else
    {
        parent[y] = x;
        subtree_size[x] += subtree_size[y];
    }
}

int root(int x)
{
    // only roots are their own parents
    // otherwise apply path compression
    return parent[x] == x ? x : parent[x] = root(parent[x]);
}

void solve()
{
    int n;
    cin >> n;
    init(n);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
