#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
 * range tree query
 */

const int N = 200100;
// the number of additional nodes created can be as high as the next power of two up from N (2^17 = 131,072)
long long tree[1 << 19];

int n, k; // actual length of underlying array

// query the sum over [qL, qR) (0-based)
// i is the index in the tree, rooted at 1 so children are 2i and 2i+1
// instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
// the root node is responsible for [0, n)
long long query(int qL, int qR, int i = 1, int cL = 0, int cR = n)
{
    // the query range exactly matches this node's range of responsibility
    if (cL == qL && cR == qR)
        return tree[i];
    // we might need to query one or both of the children
    int mid = (cL + cR) / 2;
    long long ans = -1;
    // query the part within the left child [cL, mid), if any
    if (qL < mid)
        ans = query(qL, min(qR, mid), i * 2, cL, mid);
    // query the part within the right child [mid, cR), if any
    if (qR > mid)
    {
        long long result = query(max(qL, mid), qR, i * 2 + 1, mid, cR);
        if (ans != -1)
        {
            ans = min(result, ans);
        }
        else
        {
            ans = result;
        }
    }
    return ans;
}

/*
 * range tree update
 */

// p is the index in the array (0-based)
// v is the value that the p-th element will be updated to
// i is the index in the tree, rooted at 1 so children are 2i and 2i+1
// instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
// the root node is responsible for [0, n)
void update(int p, long long v, int i = 1, int cL = 0, int cR = n)
{
    if (cR - cL == 1)
    {
        // this node is a leaf, so apply the update
        tree[i] = v;
        // cout << tree[i] << "\n";
        return;
    }
    // figure out which child is responsible for the index (p) being updated
    int mid = (cL + cR) / 2;
    if (p < mid)
        update(p, v, i * 2, cL, mid);
    else
        update(p, v, i * 2 + 1, mid, cR);
    // once we have updated the correct child, recalculate our stored value.
    tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
}

// print the entire tree to stderr
// instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
// the root node is responsible for [0, n)
void debug(int i = 1, int cL = 0, int cR = n)
{
    // print current node's range of responsibility and value
    cerr << "tree[" << cL << "," << cR << ") = " << tree[i];

    if (cR - cL > 1)
    { // not a leaf
        // recurse within each child
        int mid = (cL + cR) / 2;
        debug(i * 2, cL, mid);
        debug(i * 2 + 1, mid, cR);
    }
}

typedef long long ll;
const ll INF = 1e18;
long long dp[N];
vector<pair<int, int>> segments[N];

// referenced from the segment cover lecture
void solve()
{
    string s;
    cin >> n >> k >> s;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '1')
        {
            int bottom = max(1, i + 1 - k);
            int top = min(n, i + k + 1);
            segments[top].emplace_back(bottom, i + 1);
        }
        else
        {
            segments[i + 1].emplace_back(i + 1, i + 1);
        }
    }

    for (int i = 0; i <= n; i++)
    {
        update(i, INF);
    }

    for (int i = 0; i <= n; i++)
    {
        dp[i] = INF;
        for (auto seg : segments[i])
        {
            ll prevcost = seg.first == 1 ? 0 : query(seg.first - 1, i);
            dp[i] = min(dp[i], prevcost + seg.second);
        }
        update(i, dp[i]);
    }
    // debug();
    cout << dp[n] << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}