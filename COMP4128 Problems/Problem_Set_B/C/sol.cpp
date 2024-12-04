#include <bits/stdc++.h>
using namespace std;

using vi = vector<long long>;

bool sortbysec(const pair<pair<long long, long long>, long long> &a,
               const pair<pair<long long, long long>, long long> &b)
{
    return (a.first.second < b.first.second);
}

bool sortbyFirst(const pair<pair<long long, long long>, long long> &a,
                 const pair<pair<long long, long long>, long long> &b)
{

    return a.first.first > b.first.first;
}

bool sortByFirstBugs(pair<long long, long long> &a, pair<long long, long long> &b)
{
    return a.first > b.first;
}
vector<long long> valid(long long days, vector<pair<long long, long long>> bugs, vector<pair<pair<long long, long long>, long long>> students, long long s)
{
    // cout << "new\n"
    //      << endl;
    vector<long long> res(bugs.size());
    long long count = 0;
    long long total_s = 0;
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;
    if (students.size() * days < bugs.size())
    {
        return {};
    }
    long long student_idx = 0;
    while (count != bugs.size())
    {
        while (students[student_idx].first.first >= bugs[count].first && student_idx < students.size())
        {
            pair<long long, long long> temp;
            temp.first = students[student_idx].first.second;
            temp.second = students[student_idx].second;
            pq.push(temp);
            student_idx++;
        }

        if (pq.empty())
        {
            return {};
        }
        pair<long long, long long> first_student = pq.top();
        pq.pop();
        total_s += first_student.first;
        if (total_s > s)
        {
            return {};
        }
        long long end = count + days;
        while (count < end && count < bugs.size())
        {
            res[bugs[count].second] = first_student.second;
            count++;
        }
    }

    return res;
}
void solve()
{
    long long n, m, s;
    cin >> n >> m >> s;
    vector<pair<long long, long long>> bugs;
    vector<pair<pair<long long, long long>, long long>> students(n);
    for (long long i = 0; i < m; i++)
    {
        long long x;
        cin >> x;

        bugs.push_back(make_pair(x, i));
    }
    for (long long i = 0; i < n; i++)
    {
        cin >> students[i].first.first;
        students[i].second = i + 1;
    }
    for (long long i = 0; i < n; i++)
    {
        cin >> students[i].first.second;
    }

    sort(students.begin(), students.end(), sortbysec);
    sort(students.begin(), students.end(), sortbyFirst);
    sort(bugs.begin(), bugs.end(), sortByFirstBugs);

    long long low = 0;
    long long high = m;
    // for (long long i = 0; i < students.size(); i++)
    // {
    //     cout << students[i].first.first << " " << students[i].first.second << " " << students[i].second << "\n";
    // }

    // for (long long i = 0; i < bugs.size(); i++)
    // {
    //     cout << bugs[i].first << " " << bugs[i].second << "\n";
    // }
    vector<long long> ans;

    while (low <= high)
    {
        long long mid = (low + high) / 2;
        // cout << mid << endl;
        vector<long long> res = valid(mid, bugs, students, s);
        if (!res.size())
        {
            low = mid + 1;
        }
        else
        {
            ans = res;
            high = mid - 1;
        }
    }

    if (ans.size())
    {
        cout << "YES" << "\n";
        for (long long i = 0; i < ans.size(); i++)
        {
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    else
    {
        cout << "NO" << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}
