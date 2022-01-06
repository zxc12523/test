#include "bits/stdc++.h"
using namespace std;

#define eb emplace_back
#define fi first
#define se second
#define pii pair<int, int>
#define MOD 1000000007
#define FastIO                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define int long long
#define maxn 1000000007

/*--------------------------------------------------------------------*/
//resource: https://omeletwithoutegg.github.io/2019/12/06/Fast-IO/
inline char readchar()
{
    const int S = 1 << 20; // buffer size
    static char buf[S], *p = buf, *q = buf;
    if (p == q && (q = (p = buf) + fread(buf, 1, S, stdin)) == buf)
        return EOF;
    return *p++;
}

inline int nextint()
{
    int x = 0, c = readchar(), neg = false;
    while (('0' > c || c > '9') && c != '-' && c != EOF)
        c = readchar();
    if (c == '-')
        neg = true, c = readchar();
    while ('0' <= c && c <= '9')
        x = x * 10 + (c ^ '0'), c = readchar();
    if (neg)
        x = -x;
    return x; // returns 0 if EOF
}
/*--------------------------------------------------------------------*/

inline int sum(vector<int> &date, int x)
{
    int n, ret = 0;
    while (x)
    {
        ret += date[x];
        x -= (x & -x);
    }
    return ret;
}

inline void update(vector<int> &date, int x, int n)
{
    while (x < date.size() + 1)
    {
        date[x] += n;
        x += (x & -x);
    }
}

signed main()
{
    FastIO;
    int n, a, b, c, p, z, ans = 0;
    n = nextint();
    a = nextint();
    b = nextint();
    c = nextint();

    unordered_map<int, int> m;
    vector<pii> vec;
    vector<int> height;

    for (int i = 0; i < n; i++)
    {
        p = nextint();
        z = nextint();
        height.push_back(z);
        vec.push_back({p, z});
    }

    sort(vec.begin(), vec.end());
    sort(height.begin(), height.end());

    int ind = 1, ma = height.back(), total = n;

    m[height[0]] = ind++;
    for (int i = 1; i < height.size(); i++)
        if (height[i] != height[i - 1])
            m[height[i]] = ind++;

    vector<int> date(2 * m.size() + 1, 0);

    for (auto i : vec)
        update(date, m[i.second], 1);

    for (int i = 0, j = 0; i < n && j < n;)
    {

        if (a * vec[j].fi <= b * vec[i].fi + c)
        {
            update(date, m[vec[j++].se], -1);
            total--;
        }
        else
        {
            ans += total - sum(date, m[vec[i++].se]);
        }
    }

    printf("%lld\n", ans);
}