#include <bits/stdc++.h>
using namespace std;

int main()
{
    string c = "hello world";
    c = c.substr(0, 2) + '1' + c.substr(2, c.size());
    cout << c << endl;
}