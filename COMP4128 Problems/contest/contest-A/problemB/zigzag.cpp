#include <bits/stdc++.h>
using namespace std;

using vi = vector<long long>;

void solve()
{
    long long r;
    cin >> r;
    string s;
    cin >> s;

    char grid[r][s.length()];

    long long row = 0, col = 0;
    long long down = 0;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < s.length(); j++)
        {
            grid[i][j] = ' ';
        }
    }
    for (int i = 0; i < s.length(); i++)
    {
        if (row == 0)
        {
            down = 1;
        }
        else if (row == r - 1)
        {
            down = 0;
        }

        if (down == 1)
        {
            grid[row++][col++] = '.';
        }
        else
        {
            grid[row--][col++] = '.';
        }
    }

    long long counter = 0;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < s.length(); j++)
        {
            if (grid[i][j] == '.')
            {
                grid[i][j] = s[counter++];
            }
        }
    }

    // for (int i = 0; i < r; i++)
    // {
    //     for (int j = 0; j < s.length(); j++)
    //     {
    //         cout << grid[i][j];
    //     }
    //     cout << "\n";
    // }

    string res = "";
    row = 0;
    col = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (row == 0)
        {
            down = 1;
        }
        else if (row == r - 1)
        {
            down = 0;
        }

        if (down == 1)
        {
            res += grid[row++][col++];
        }
        else
        {
            res += grid[row--][col++];
        }
    }
    cout << res << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}