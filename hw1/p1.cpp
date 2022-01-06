#include "bits/stdc++.h"
using namespace std;

#define eb emplace_back
#define fi first
#define se second
#define pii pair<int, int>
#define mod 998244353
#define FastIO                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define int long long
#define maxn 1000000007


vector<int> ans;
vector<queue<int>> q(3);

int fastpow(int base, int time)
{
    if (time == 0)
        return 1;
    int ret = 0, tmp = base, ind = 1;
    while (ind <= time)
    {
        if (ind & time)
        {
            ret += tmp;
            ret = (ret + mod) % mod;
        }
        tmp *= tmp;
        tmp = (tmp + mod) % mod;
        ind <<= 1;
    }
    return ret;
}

int find_pos(int n)
{
    for (int i = 0; i < 3; i++)
        if (q[i].size() && q[i].front() == n)
            return i;
    return 3;
}

int solve(int s, int d, int c, int n)
{
    if (n == 0)
        return 0;
    q[find_pos(n)].pop();
    if (!(s & c) && !(d & c))
        return -1;
    if (s & c)
    {
        //cout<<n-1<<'\n';
        ans.push_back(n - 1);
        return solve(s, (1 << 3) - 1 - s - d, 1 << find_pos(n - 1), n - 1);
    }
    else
    {
        return solve((1 << 3) - 1 - s - d, d, 1 << find_pos(n - 1), n - 1);
    }
}

signed main()
{
    FastIO;
    int n, tmp = 0;
    cin >> n;
    for (int i = 0; i < 3; i++)
    {
        int k, tmp;
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            cin >> tmp;
            q[i].push(tmp);
        }
    }
    if (solve(1 << 0, 1 << 2, 1 << find_pos(n), n) == -1)
        cout << -1 << '\n';
    else
    {
        for (auto i : ans)
        {
            tmp += pow_2[i];
            tmp = (tmp + mod) % mod;
        }
        cout << tmp << '\n';
    }
}