#include <bits/stdc++.h>
using namespace std;

struct pt
{
    double x, y, dist;
    long long idx;
    pt(double x_ = 0, double y_ = 0) : x(x_), y(y_), dist(0), idx(0) {}
};

const double EPS = 1e-8;
const int N = 1e5;
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

pt arrays[N];
int n;

bool check(int idx1, int idx2)
{
    pt point3 = pt(-1, -1);
    bool point3Flag = false;
    pt point4 = pt(-1, -1);
    bool point4Flag = false;
    for (int i = 0; i < n; i++)
    {
        // cout << "idx:" << i << "\n";
        if (i != idx2 && i != idx1)
        {
            if (collinear(arrays[idx1], arrays[idx2], arrays[idx1], arrays[i]))
            {
                // cout << "this:" << arrays[i].x << " " << arrays[i].y << "\n";
            }
            else
            {
                if (!point3Flag)
                {
                    point3Flag = true;
                    point3 = arrays[i];
                }
                else if (!point4Flag)
                {
                    point4Flag = true;
                    point4 = arrays[i];
                }
                else
                {
                    if (!collinear(point3, point4, point3, arrays[i]))
                    {
                        return false;
                    }
                }
            }
        }
    }
    // cout << arrays[idx1].x << " " << arrays[idx1].y << "\n";
    // cout << arrays[idx2].x << " " << arrays[idx2].y << "\n";
    // cout << point3.x << " " << point3.y << "\n";
    // cout << point4.x << " " << point4.y << "\n";
    return true;
}

void solve()
{

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> arrays[i].x >> arrays[i].y;
    }

    // check each line, we have that one of these lines must form the first line
    // otherwise its not possible
    if (check(0, 1) || check(0, 2) || check(1, 2))
    {

        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
