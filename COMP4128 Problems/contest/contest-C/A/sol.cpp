#include <bits/stdc++.h>
using namespace std;

const long long MAX_VERTICES = 200010;

long long n;
vector<long long> edges[MAX_VERTICES];

/*
 * tarjan 1
 */

// we will number the vertices in the order we see them in the DFS
long long dfs_index[MAX_VERTICES];
// for each vertex, store the smallest number of any vertex we see
// in its DFS firstbtree
long long lowlink[MAX_VERTICES];

// explicit stack
stack<long long> s; // #include <stack>
bool in_stack[MAX_VERTICES];

// arbitrarily number the SCCs and remember which one things are in
long long scc_counter;
long long which_scc[MAX_VERTICES];

void connect(long long v)
{
    // a static variable doesn't get reset between function calls
    static long long i = 1;
    // set the number for this vertex
    // the smallest numbered thing it can see so far is itself
    lowlink[v] = dfs_index[v] = i++;
    s.push(v);
    in_stack[v] = true;

    // continued

    /*
     * tarjan 2
     */

    for (auto w : edges[v])
    { // for each edge v -> w
        if (!dfs_index[w])
        { // w hasn't been visited yet
            connect(w);
            // if w can see something, v can too
            lowlink[v] = min(lowlink[v], lowlink[w]);
        }
        else if (in_stack[w])
        {
            // w is already in the stack, but we can see it
            // this means v and w are in the same SCC
            lowlink[v] = min(lowlink[v], dfs_index[w]);
        }
    }
    // v is the root of an SCC
    if (lowlink[v] == dfs_index[v])
    {
        long long w;
        do
        {
            w = s.top();
            s.pop();
            in_stack[w] = false;
            which_scc[w] = scc_counter;
        } while (w != v);
        ++scc_counter;
    }
}

void solve()
{
    cin >> n;
    for (long long i = 1; i <= n; i++)
    {
        long long a, b;
        cin >> a >> b;
        edges[i].push_back(a);
        edges[i].push_back(b);
    }
    for (long long i = 1; i <= n; i++)
    {
        if (!dfs_index[i])
        {
            connect(i);
        }
    }

    vector<long long> condensation[MAX_VERTICES];
    bool outgoing[MAX_VERTICES] = {false};
    for (long long i = 1; i <= n; i++)
    {
        for (long long v : edges[i])
        {
            long long parent = which_scc[i];
            long long child = which_scc[v];
            if (parent != child)
            {
                condensation[parent].push_back(child);
                outgoing[parent] = true;
            }
        }
    }

    long long count = 0;
    for (long long i = 0; i < scc_counter; ++i)
    {
        if (!outgoing[i])
        {
            ++count;
        }
    }

    if (count > 1)
    {
        cout << "No\n";
        return;
    }

    bool checkVisit[MAX_VERTICES] = {false};
    stack<long long> checkStack;

    long long start = which_scc[1];
    checkStack.push(start);
    checkVisit[start] = true;

    while (!checkStack.empty())
    {
        long long first = checkStack.top();
        checkStack.pop();
        for (auto second : condensation[first])
        {
            if (!checkVisit[second])
            {
                checkVisit[second] = true;
                checkStack.push(second);
            }
        }
    }

    for (long long i = 0; i < scc_counter; i++)
    {
        if (!checkVisit[i])
        {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
