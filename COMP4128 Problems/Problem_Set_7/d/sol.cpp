#include <bits/stdc++.h>
using namespace std;

const long long N = 1e7;
bool marked[N + 1];
int firstPrime[N + 1];
long long allPrime[N + 1];
void solve()
{
    // ax + by = gcd(a,b)
    // (d1 + d2)*x + by = gcd(d1 + d2, by) = 1
    // d1 = b*i
    // d2 = b*j
    // (b*j + b*i)*x + by = 1
    // b*(j+i)*x + by = 1
    // let p = j +1
    // b*p*x + b*y = 1
    // b *(p + x + y)
    // b*a  where a can be a fraction
    // has to be a prime since if there its not prime, ez proof
    // Has to both add up to prime (maybe not)
    // could you goldbach conjecture (no this is stupid)
    // Use sieve to compute prime
    // suppose 24
    // 2*2*3*3
    // issue adding two primes might add to another prime, so you can't simply add two prime
    // 2*2*3*3*5*7
    // a*b*c*d
    // a + b = c, not possible.
    // gcd
    // d1 + d2, d1, d2 is composed of one of the prime factors of b
    // (a + b)*y + a*b*c*d*x = 1
    // but the issue is, we might have that a+b will equal c, how can we prevent this hmmmm...
    // (a + b*c*d)*y + a*b*c*d*x = 1.
    // but what about (a + b*c*d)*y + a*b*c*d*x = 1
    // this works since a < b < c < d
    // a < b*c*d
    // clearly (a+b*c*d) doesn't divide long longo a*b*c*d*x
    // but time complexity too sloow
    // so consider what if we want (a + b^2*c^2*d^2)*x + a*b^2*c^2*d*x
    // since a and b^2*c^2*d^2 are coprime, there are no shared factors between
    // a and b^2*c^2*d^2 are coprime, so there is no way of factorising them
    fill(allPrime, allPrime + N + 1, 1);
    for (int i = 2; i <= N; i++)
    {
        if (!marked[i])
        {
            for (int j = 2 * i; j <= N; j += i)
            {
                marked[j] = true;
                int tmp = j;
                if (tmp % i == 0)
                {
                    firstPrime[j] = i;
                    allPrime[j] *= i;
                }
            }
        }
    }

    long long n;
    cin >> n;
    long long result1[n];
    long long result2[n];
    for (long long i = 0; i < n; i++)
    {
        long long a;
        cin >> a;
        if (firstPrime[a] == allPrime[a] || firstPrime[a] == 0)
        {
            result1[i] = -1;
            result2[i] = -1;
            continue;
        }

        long long d1 = firstPrime[a];
        long long d2 = allPrime[a] / d1;
        result1[i] = d1;
        result2[i] = d2;
    }

    for (long long i = 0; i < n; i++)
    {
        cout << result1[i] << " ";
    }

    cout << "\n";

    for (long long i = 0; i < n; i++)
    {
        cout << result2[i] << " ";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
