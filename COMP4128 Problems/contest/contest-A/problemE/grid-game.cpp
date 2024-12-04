#include <bits/stdc++.h>
using namespace std;
using vi = vector<long long>;

bool checkInWordsUsed(unordered_set<string> &wordsUsed, const string &item)
{
    return wordsUsed.find(item) != wordsUsed.end();
}

bool dp(unordered_map<string, vector<string>> &map_str, unordered_set<string> &wordsUsed, vector<vector<string>> &groups, vector<string> &grid, string word)
{
    if (groups.size() == 4)
    {
        return true;
    }

    for (string word1 : map_str[word])
    {
        if (checkInWordsUsed(wordsUsed, word1))
        {
            continue;
        }

        for (string word2 : map_str[word1])
        {
            if (checkInWordsUsed(wordsUsed, word2))
            {
                continue;
            }

            for (string word3 : map_str[word2])
            {
                if (checkInWordsUsed(wordsUsed, word3))
                {
                    continue;
                }

                vector<string> wordsCheck = {word, word1, word2, word3};
                bool validGroup = true;

                for (int a = 0; a < 4 && validGroup; a++)
                {
                    for (int b = a + 1; b < 4; b++)
                    {
                        if (find(map_str[wordsCheck[a]].begin(), map_str[wordsCheck[a]].end(), wordsCheck[b]) == map_str[wordsCheck[a]].end())
                        {
                            validGroup = false;
                            break;
                        }
                    }
                }

                if (!validGroup)
                {
                    continue;
                }

                groups.push_back({word, word1, word2, word3});
                wordsUsed.insert(word);
                wordsUsed.insert(word1);
                wordsUsed.insert(word2);
                wordsUsed.insert(word3);
                string nextS;
                for (int i = 0; i < grid.size(); i++)
                {
                    if (!wordsUsed.count(grid[i]))
                    {
                        nextS = grid[i];
                    }
                }
                if (dp(map_str, wordsUsed, groups, grid, nextS))
                {
                    return true;
                }

                groups.pop_back();
                wordsUsed.erase(word);
                wordsUsed.erase(word1);
                wordsUsed.erase(word2);
                wordsUsed.erase(word3);
            }
        }
    }

    return false;
}

void solve()
{
    vector<string> grid(16);
    unordered_set<string> wordsUsed;
    vector<vector<string>> groups;
    long long n;

    for (long long i = 0; i < 16; i++)
    {
        cin >> grid[i];
    }

    cin >> n;

    unordered_map<string, vector<string>> map_str;

    for (long long i = 0; i < n; i++)
    {
        string a, b;
        cin >> a >> b;

        map_str[a].push_back(b);
        map_str[b].push_back(a);
    }

    // for (string s : map_str[grid[0]])
    // {
    //     cout << s << endl;
    // }

    wordsUsed.insert(grid[0]);

    if (dp(map_str, wordsUsed, groups, grid, grid[0]))
    {
        cout << "Possible" << "\n";
        for (const auto &group : groups)
        {
            for (const auto &word : group)
            {
                cout << word << " ";
            }
            cout << "\n";
        }
    }
    else
    {
        cout << "Impossible" << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin.sync_with_stdio(false);

    solve();
}
