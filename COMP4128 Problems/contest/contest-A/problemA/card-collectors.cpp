#include <bits/stdc++.h>
using namespace std;

using vi = vector<long long>;

void solve()
{
    int n, m, val;
    cin >> n >> m;
    vi cards(m + 1);
    int s;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        for (int j = 0; j < s; j++)
        {
            cin >> val;
            cards[val]++;
        }
    }

    int min_value = cards[1];
    for (int i = 2; i < cards.size(); i++)
    {
        if (min_value > cards[i])
        {
            min_value = cards[i];
        }
    }

    cout << min_value << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}