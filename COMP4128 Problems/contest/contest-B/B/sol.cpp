#include <bits/stdc++.h>
using namespace std;

const long long N = 1000100; // Adjusted for max grid size of 1000x1000
long long tree_min[1 << 21]; // Increased size to accommodate larger N
long long tree_max[1 << 21];
const long long INF = 1e9 + 1;
long long n; // actual length of underlying array

// Query the min over [qL, qR)
long long query_min(long long qL, long long qR, long long i = 1, long long cL = 0, long long cR = n)
{
    if (cL == qL && cR == qR)
        return tree_min[i];
    long long mid = (cL + cR) / 2;
    long long ans = INF;
    if (qL < mid)
        ans = min(ans, query_min(qL, min(qR, mid), i * 2, cL, mid));
    if (qR > mid)
        ans = min(ans, query_min(max(qL, mid), qR, i * 2 + 1, mid, cR));
    return ans;
}

// Query the max over [qL, qR)
long long query_max(long long qL, long long qR, long long i = 1, long long cL = 0, long long cR = n)
{
    if (cL == qL && cR == qR)
        return tree_max[i];
    long long mid = (cL + cR) / 2;
    long long ans = -INF;
    if (qL < mid)
        ans = max(ans, query_max(qL, min(qR, mid), i * 2, cL, mid));
    if (qR > mid)
        ans = max(ans, query_max(max(qL, mid), qR, i * 2 + 1, mid, cR));
    return ans;
}

void update(long long p, long long v, long long i = 1, long long cL = 0, long long cR = n)
{
    if (cR - cL == 1)
    {
        tree_min[i] = tree_max[i] = v;
        return;
    }
    long long mid = (cL + cR) / 2;
    if (p < mid)
    {
        update(p, v, i * 2, cL, mid);
    }
    else
    {
        update(p, v, i * 2 + 1, mid, cR);
    }
    tree_min[i] = min(tree_min[i * 2], tree_min[i * 2 + 1]);
    tree_max[i] = max(tree_max[i * 2], tree_max[i * 2 + 1]);
}

bool isTragiSquare(long long r, long long c, long long k)
{
    long long min_inside = INF, max_inside = -INF;
    for (long long i = r; i < r + k; ++i)
    {
        long long range_min = query_min(i * c + r, i * c + r + k);
        long long range_max = query_max(i * c + r, i * c + r + k);
        min_inside = min(min_inside, range_min);
        max_inside = max(max_inside, range_max);
    }

    // Check left and right
    for (long long i = r; i < r + k; ++i)
    {
        if (r > 0 && query_max(i * c, i * c + r) >= min_inside)
            return false;
        if (r + k < c && query_min(i * c + r + k, (i + 1) * c) <= max_inside)
            return false;
    }

    // Check top and bottom
    for (long long j = 0; j < c; ++j)
    {
        if (r > 0 && query_max(j, (r - 1) * c + j + 1) >= min_inside)
            return false;
        if (r + k < c && query_min((r + k) * c + j, n) <= max_inside)
            return false;
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long r, c, k;
    cin >> r >> c >> k;

    n = r * c;
    for (long long i = 0; i < r; ++i)
    {
        for (long long j = 0; j < c; ++j)
        {
            long long x;
            cin >> x;
            update(i * c + j, x);
        }
    }

    for (long long i = 0; i <= r - k; ++i)
    {
        for (long long j = 0; j <= c - k; ++j)
        {
            if (isTragiSquare(i, j, k))
            {
                cout << "YES\n"
                     << i + 1 << " " << j + 1 << "\n";
                return 0;
            }
        }
    }

    cout << "NO\n";
    return 0;
}