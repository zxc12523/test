#include "bits/stdc++.h"
using namespace std;

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

int str_to_int(string s)
{
    int ans = 0, tmp = 1;
    if (s[0] == '-')
    {
        for (int i = s.size() - 1; i >= 1; i--)
        {
            ans += (s[i] - '0') * tmp;
            tmp *= 10;
        }
        return -ans;
    }
    else
    {
        for (int i = s.size() - 1; i >= 0; i--)
        {
            ans += (s[i] - '0') * tmp;
            tmp *= 10;
        }
        return ans;
    }
}

signed main()
{
    FastIO;
    int t, n, m, k;
    for (cin >> t; t > 0; t--)
    {
        cin >> n >> m >> k;

        int tmp = 1;
        vector<int> len = {1, 1};
        while ((tmp = ceil((float)(len.back() * 3) / 2.0)) <= k)
            len.push_back(tmp);

        int g[n][m];
        pii p[n][m];
        pair<int, pii> dp[n][m][len.size()];

        int max_l = len.back();

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                string s;
                cin >> s;
                g[i][j] = s == "X" ? LONG_LONG_MIN : str_to_int(s);
            }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                pair<int, pii> point;
                int c = max(0LL, j - k + max_l - 1);
                int r = max(0LL, i - k + max_l - 1);
                if (!((i == 0 && j == 0) || g[i][j] == LONG_LONG_MIN))
                {
                    if (i == 0)
                        point = max(dp[i][c][len.size() - 1], dp[i][j - 1][len.size() - 1]);

                    else if (j == 0)
                        point = max(dp[r][j][len.size() - 1], dp[i - 1][j][len.size() - 1]);

                    else
                        point = max({dp[i][c][len.size() - 1], dp[r][j][len.size() - 1], dp[i][j - 1][len.size() - 1], dp[i - 1][j][len.size() - 1]});

                    if (point.fi == LONG_LONG_MIN)
                        g[i][j] = point.fi;
                    else
                    {
                        g[i][j] += point.fi;
                        p[i][j] = point.se;
                    }
                }

                dp[i][j][1] = {g[i][j], {i, j}};
                for (int ind = 2; ind < len.size() && len[ind] <= k; ind++)
                {
                    int off = ceil((float)len[ind - 1] / 2.0);
                    dp[i][j][ind] = max({dp[i][j][ind - 1], dp[i][max(0LL, j - off)][ind - 1], dp[max(0LL, i - off)][j][ind - 1]});
                }
            }
        }

        if (g[n - 1][m - 1] == LONG_LONG_MIN)
            cout << "Impassable" << '\n';
        else
        {
            cout << "Passable" << '\n';
            cout << g[n - 1][m - 1] << '\n';

            pii cur = {n - 1, m - 1};
            vector<pii> vec = {cur};
            while (cur.first != 0 || cur.second != 0)
            {
                cur = p[cur.first][cur.second];
                vec.push_back(cur);
            }
            cout << vec.size() << '\n';
            for (int i = vec.size() - 1; i >= 0; i--)
                cout << vec[i].first + 1 << ' ' << vec[i].second + 1 << '\n';
        }
    }
}