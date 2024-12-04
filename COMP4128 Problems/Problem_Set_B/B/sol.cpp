#include <bits/stdc++.h>
using namespace std;

using vi = vector<long long>;

void solve()
{
    string s;
    cin >> s;
    stack<char> t;
    string u = "";
    long long n = s.length();
    vector<char> string_val(n);
    string_val[n - 1] = s[n - 1];
    // "cdeaffb"
    // "aaaabbb"
    for (long long i = n - 2; i >= 0; i--)
    {
        if (s[i] > string_val[i + 1])
        {
            string_val[i] = string_val[i + 1];
        }
        else
        {
            string_val[i] = s[i];
        }
    }
    long long i = 0;
    while (i < n)
    {
        if (!t.empty())
        {
            if (t.top() <= string_val[i])
            {
                u += t.top();
                t.pop();
                continue;
            }
        }

        if (s[i] == string_val[i])
        {
            u += s[i];
        }
        else
        {
            t.push(s[i]);
        }
        i++;
    }
    while (!t.empty())
    {
        u += t.top();
        t.pop();
    }
    cout << u << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}
