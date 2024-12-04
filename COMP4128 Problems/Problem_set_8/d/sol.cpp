#include <bits/stdc++.h>
using namespace std;

typedef pair<double, double> pt;
#define x first
#define y second

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
bool ccw(pt a, pt b, pt c)
{
    return cross(b - a, c - a) > 0; // Bruh, need to change this since its strictly
}

double sq(double t) { return t * t; }

double dist(pt p, pt q) { return sqrt(sq(p.x - q.x) + sq(p.y - q.y)); }

bool collinear(pt a, pt b, pt c, pt d)
{
    return zero(cross(b - a, c - a)) &&
           zero(cross(b - a, d - a));
}

/*
 * convex hull
 */

vector<pt> half_hull(vector<pt> pts)
{
    vector<pt> res;
    for (int i = 0; i < pts.size(); i++)
    {
        // ccw means we have a left turn; we don't want that
        while (res.size() >= 2 &&
               ccw(pts[i], res[res.size() - 1], res[res.size() - 2]))
        {
            res.pop_back();
        }
        res.push_back(pts[i]);
    }
    return res;
}

vector<pt> convex_hull(vector<pt> pts)
{
    sort(pts.begin(), pts.end());
    vector<pt> top = half_hull(pts);

    reverse(pts.begin(), pts.end());
    vector<pt> bottom = half_hull(pts);

    top.pop_back();
    bottom.pop_back();
    vector<pt> res(top.begin(), top.end());
    res.insert(res.end(), bottom.begin(), bottom.end());
    return res;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> reds(n);
    int triangles[n][n];
    vector<int> blacks(m);
    for (int i = 0; i < n; i++)
    {
        cin >> reds[i];
    }

    for (int i = 0; i < m; i++)
    {
        cin >> blacks[i];
    }

    sort(reds.begin(), reds.end());
    sort(blacks.begin(), blacks.end());
    pt origin = pt(0, 0);
    /// Calculate the illuminatis
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = 0; k < m; k++)
            {
                if (ccw(reds[i], reds[j], blacks[k]) ) 
            }
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
