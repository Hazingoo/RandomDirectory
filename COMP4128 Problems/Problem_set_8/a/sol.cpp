#include <bits/stdc++.h>
using namespace std;

struct pt
{
    double x, y, dist;
    long long idx;
    pt(double x_ = 0, double y_ = 0) : x(x_), y(y_), dist(0), idx(0) {}
};

const double EPS = 1e-8;

pt operator-(pt a, pt b)
{
    return pt(a.x - b.x, a.y - b.y);
}

bool zero(double x)
{
    return fabs(x) <= EPS;
}

double cross(pt a, pt b)
{
    return a.x * b.y - a.y * b.x;
}
double sq(double t) { return t * t; }

double dist(pt p, pt q) { return sqrt(sq(p.x - q.x) + sq(p.y - q.y)); }

bool collinear(pt a, pt b, pt c, pt d)
{
    return zero(cross(b - a, c - a)) &&
           zero(cross(b - a, d - a));
}

bool compare(pt a, pt b)
{
    return a.dist < b.dist;
}

void solve()
{
    int n;
    cin >> n;
    pt array[n];
    cin >> array[0].x >> array[0].y;
    array[0].idx = 1;
    for (int i = 1; i < n; i++)
    {
        cin >> array[i].x >> array[i].y;
        array[i].idx = i + 1;
        array[i].dist = dist(array[i], array[0]);
    }

    sort(array, array + n, compare);
    cout << "1" << " " << array[1].idx << " ";
    for (int i = 2; i < n; i++)
    {
        if (!collinear(array[0], array[1], array[i], array[0]))
        {
            cout << array[i].idx << "\n";
            return;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
