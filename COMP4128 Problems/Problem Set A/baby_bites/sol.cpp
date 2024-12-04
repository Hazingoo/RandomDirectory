#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        string word;
        cin >> word;
        if (word != "mumble")
        {
            int number = stoi(word);
            if (number != i)
            {
                cout << "something is fishy" << endl;
                return;
            }
        }
    }

    cout << "makes sense" << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}