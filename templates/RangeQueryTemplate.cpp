#include <bits/stdc++.h>
using namespace std;

/*
 * range tree query
 */

const int N = 100100;
int tree[1 << 18];

int n;

int query(int qL, int qR, int i = 1, int cL = 0, int cR = n)
{
    // the query range exactly matches this node's range of responsibility
    if (cL == qL && cR == qR)
        return tree[i];
    // we might need to query one or both of the children
    int mid = (cL + cR) / 2;
    int ans = 0;
    // query the part within the left child [cL, mid), if any
    if (qL < mid)
        ans += query(qL, min(qR, mid), i * 2, cL, mid);
    // query the part within the right child [mid, cR), if any
    if (qR > mid)
        ans += query(max(qL, mid), qR, i * 2 + 1, mid, cR);
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
void update(int p, int v, int i = 1, int cL = 0, int cR = n)
{
    if (cR - cL == 1)
    {
        // this node is a leaf, so apply the update
        tree[i] = v;
        return;
    }
    // figure out which child is responsible for the index (p) being updated
    int mid = (cL + cR) / 2;
    if (p < mid)
        update(p, v, i * 2, cL, mid);
    else
        update(p, v, i * 2 + 1, mid, cR);
    // once we have updated the correct child, recalculate our stored value.
    tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

/*
 * range tree debug
 */

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

void solve()
{
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
