#include <bits/stdc++.h>
using namespace std;

using vi = vector<long long>;

void solve()
{
    long long n;
    cin >> n;
    vi marks(n);
    vi min_marks(n);
    for (long long i = 0; i < n; ++i)
    {
        cin >> marks[i];
        marks[i] = marks[i] + 1;
        // cout << "marks: " << marks[i] << endl;
    }

    min_marks[0] = 0;
    for (long long i = 1; i < n; ++i)
    {
        min_marks[i] = max(min_marks[i - 1], marks[i]);
        // cout << "min_marks: " << min_marks[i] << endl;
    }
    long long sum = 0;
    // cout << n << endl;
    for (long long i = n - 1; i > 0; i--)
    {
        if (min_marks[i] - min_marks[i - 1] > 1)
        {
            min_marks[i - 1] = min_marks[i] - 1;
        }
        sum += min_marks[i] - marks[i];
    }
    // cout << min_marks[0] << marks[0] << endl;
    // sum += min_marks[0] - marks[0] - 1;
    cout << sum << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}