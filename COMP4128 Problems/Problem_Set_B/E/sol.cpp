#include <bits/stdc++.h>
using namespace std;

using vi = vector<long long>;

struct Command
{
    char operation;
    long long x;
    long long y;
    long long z;
    pair<long long, long long> join;
};

multiset<long long> multisetNumbers;

long long root(long long x, vector<long long> &parent)
{
    return parent[x] == x ? x : parent[x] = root(parent[x], parent);
}

void join(long long x, long long y, vector<long long> &subtree_size, vector<long long> &parent, vector<long long> &population)
{
    x = root(x, parent);
    y = root(y, parent);

    if (x == y)
        return;

    auto it_x = multisetNumbers.find(population[x]);
    if (it_x != multisetNumbers.end())
        multisetNumbers.erase(it_x);
    auto it_y = multisetNumbers.find(population[y]);
    if (it_y != multisetNumbers.end())
        multisetNumbers.erase(it_y);

    if (subtree_size[x] < subtree_size[y])
    {
        parent[x] = y;
        population[y] += population[x];
        population[x] = 0;
        multisetNumbers.insert(population[y]);
        subtree_size[y] += subtree_size[x];
    }
    else
    {
        parent[y] = x;
        population[x] += population[y];
        population[y] = 0;
        multisetNumbers.insert(population[x]);
        subtree_size[x] += subtree_size[y];
    }
}

void solve()
{
    long long N, M, Q;
    cin >> N >> M >> Q;
    vector<long long> population(N);
    vector<long long> parent(N);
    vector<long long> subtree_size(N, 1);
    vector<tuple<long long, long long, int>> roads;
    vector<Command> commands;

    for (long long i = 0; i < N; i++)
    {
        cin >> population[i];
        parent[i] = i;
    }

    for (long long i = 0; i < M; i++)
    {
        long long x, y;
        cin >> x >> y;
        roads.emplace_back(x - 1, y - 1, 1);
    }

    for (long long i = 0; i < Q; i++)
    {
        char operation;
        cin >> operation;
        Command command1;
        if (operation == 'P')
        {
            long long x, y;
            cin >> x >> y;
            command1.operation = 'P';
            command1.x = x - 1;
            command1.y = y;
            command1.z = population[command1.x];
            population[command1.x] = y;
            commands.push_back(command1);
        }
        else if (operation == 'D')
        {
            long long x;
            cin >> x;
            command1.operation = 'D';
            command1.x = x - 1;
            get<2>(roads[command1.x]) = 0;
            command1.join = make_pair(get<0>(roads[command1.x]), get<1>(roads[command1.x]));
            commands.push_back(command1);
        }
    }

    for (long long i = 0; i < N; i++)
    {
        // cout << population[i] << endl;
        multisetNumbers.insert(population[i]);
    }

    for (auto &road : roads)
    {
        // cout << "hello world" << endl;
        if (get<2>(road))
        {
            // cout << "dan dan" << endl;
            // cout << "i joined with: " << get<0>(road) << " :" << get<1>(road) << endl;
            join(get<0>(road), get<1>(road), subtree_size, parent, population);
        }
    }

    vector<long long> res;
    // std::copy(multisetNumbers.begin(), multisetNumbers.end(),
    //           std::ostream_iterator<long long>(std::cout, "\n"));
    for (long long i = Q - 1; i >= 0; i--)
    {
        if (!multisetNumbers.empty())
        {
            // cout << "result: " << result << endl;
            res.push_back(*multisetNumbers.rbegin());
        }

        if (commands[i].operation == 'P')
        {

            long long root_x = root(commands[i].x, parent);
            auto it = multisetNumbers.find(population[root_x]);
            if (it != multisetNumbers.end())
            {
                multisetNumbers.erase(it);
            }
            population[root_x] -= commands[i].y;
            population[root_x] += commands[i].z;
            multisetNumbers.insert(population[root_x]);
        }
        else if (commands[i].operation == 'D')
        {
            long long u = commands[i].join.first;
            long long v = commands[i].join.second;
            join(u, v, subtree_size, parent, population);
        }
    }

    for (long long i = res.size() - 1; i >= 0; i--)
    {
        cout << res[i] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
