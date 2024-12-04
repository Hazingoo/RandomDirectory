#include <bits/stdc++.h>
using namespace std;
struct Node
{
    long long sum, min_val, max_val;
    bool is_increasing, is_decreasing;
};
Node tree[1 << 18];

long long n, m;

// query the sum over [qL, qR) (0-based)
// i is the index in the tree, rooted at 1 so children are 2i and 2i+1
// instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
// the root node is responsible for [0, n)
Node query(long long qL, long long qR, long long i = 1, long long cL = 0, long long cR = n)
{
    // the query range exactly matches this node's range of responsibility
    if (cL == qL && cR == qR)
        return tree[i];
    // we might need to query one or both of the children
    long long mid = (cL + cR) / 2;
    Node ans;
    ans.max_val = -1;
    // query the part within the left child [cL, mid), if any
    if (qL < mid)
    {
        ans = query(qL, min(qR, mid), i * 2, cL, mid);
    }
    // query the part within the right child [mid, cR), if any
    if (qR > mid)
    {
        if (ans.max_val == -1)
        {
            ans = query(max(qL, mid), qR, i * 2 + 1, mid, cR);
        }
        else
        {
            Node right_node = query(max(qL, mid), qR, i * 2 + 1, mid, cR);
            Node result;
            result.sum = ans.sum + right_node.sum;
            result.max_val = max(ans.max_val, right_node.max_val);
            result.min_val = min(ans.min_val, right_node.min_val);
            result.is_increasing = ans.is_increasing && right_node.is_increasing && ans.max_val <= right_node.min_val;
            result.is_decreasing = ans.is_decreasing && right_node.is_decreasing && ans.min_val >= right_node.max_val;
            ans = result;
        }
    }
    return ans;
}

// p is the index in the array (0- based)
// v is the value that the p-th element will be updated to
// i is the index in the tree , rooted at 1 so children are 2i and 2i+1
// instead of explicitly storing each node 's range of responsibility [cL ,cR), we
// calculate it on the way down
// the root node is responsible for [0, n)
void update(long long p, long long v, long long i = 1, long long cL = 0, long long cR = n)
{
    if (cR - cL == 1)
    {
        Node node = {v, v, v, true, true};
        tree[i] = node;
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
    Node node;
    node.sum = tree[i * 2].sum + tree[i * 2 + 1].sum;
    node.max_val = max(tree[i * 2 + 1].max_val, tree[i * 2].max_val);
    node.min_val = min(tree[i * 2 + 1].min_val, tree[i * 2].min_val);
    node.is_increasing = tree[i * 2].is_increasing && tree[i * 2 + 1].is_increasing && tree[i * 2].max_val <= tree[i * 2 + 1].min_val;
    node.is_decreasing = tree[i * 2].is_decreasing && tree[i * 2 + 1].is_decreasing && tree[i * 2].min_val >= tree[i * 2 + 1].max_val;
    tree[i] = node;
}

void solve()
{
    cin >> n >> m;
    vector<long long> difficulties(n);
    for (int i = 0; i < n; i++)
    {
        cin >> difficulties[i];
        update(i, difficulties[i]);
    }

    for (int i = 0; i < m; i++)
    {
        char op;
        long long x, y;
        cin >> op >> x >> y;
        x--;
        if (op == 'U')
        {
            update(x, y);
        }
        else if (op == 'M')
        {
            // y--;
            Node node = query(x, y);
            cout << node.max_val << '\n';
        }
        else if (op == 'S')
        {
            // y--;
            Node node = query(x, y);
            cout << node.sum << '\n';
        }
        else if (op == 'I')
        {
            // y--;
            Node node = query(x, y);
            cout << (node.is_increasing ? 1 : 0) << '\n';
        }
        else
        {
            // y--;
            Node node = query(x, y);
            cout << (node.is_decreasing ? 1 : 0) << '\n';
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