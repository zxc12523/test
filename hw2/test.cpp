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
        int g[n][m];
        int dp[n][m][k + 1][2];
        int p[n][m][2];

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                string s;
                cin >> s;
                g[i][j] = s == "X" ? LONG_LONG_MIN : str_to_int(s);
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (i == 0 && j == 0)
                {
                    p[i][j][0] = 0;
                    p[i][j][1] = 0;
                }
                else
                {
                    int a = 0, b = 0, tmp = LONG_LONG_MIN;

                    a = i;
                    b = j ? dp[i][max(0LL, j - k)][min(j, k)][1] : 0;
                    tmp = j ? dp[i][max(0LL, j - k)][min(j, k)][0] : LONG_LONG_MIN;

                    for (int r = i - 1, c = k - 1; r >= max(0LL, i - k); r--, c--)
                    {
                        if (dp[r][max(0LL, j - c)][min(j + 1, c + 1)][0] > tmp)
                        {
                            tmp = dp[r][max(0LL, j - c)][min(j + 1, c + 1)][0];
                            a = r, b = dp[r][max(0LL, j - c)][min(j + 1, c + 1)][1];
                        }
                    }

                    if (g[i][j] == LONG_LONG_MIN || tmp == LONG_LONG_MIN)
                        g[i][j] = LONG_LONG_MIN;
                    else
                    {
                        g[i][j] += tmp;
                        p[i][j][0] = a;
                        p[i][j][1] = b;
                    }
                }

                dp[i][j][1][0] = g[i][j];
                dp[i][j][1][1] = j;

                for (int l = 2; j >= 1 && l <= min(j + 1, k); l++)
                {
                    if (dp[i][j - l + 1][l - 1][0] > dp[i][j - l + 2][l - 1][0])
                    {
                        dp[i][j - l + 1][l][0] = dp[i][j - l + 1][l - 1][0];
                        dp[i][j - l + 1][l][1] = dp[i][j - l + 1][l - 1][1];
                    }
                    else
                    {
                        dp[i][j - l + 1][l][0] = dp[i][j - l + 2][l - 1][0];
                        dp[i][j - l + 1][l][1] = dp[i][j - l + 2][l - 1][1];
                    }
                }
            }
        }

        // for (int i = 0; i < n; i++)
        // {
        //     for (int j = 0; j < m; j++)
        //     {
        //         if (g[i][j] == LONG_LONG_MIN)
        //         {
        //             cout << "X ";
        //         }
        //         else
        //         {
        //             cout << g[i][j] << ' ';
        //         }
        //     }
        //     cout << '\n';
        // }

        // for (int i = 0; i < n; i++)
        // {
        //     for (int j = 0; j < m; j++)
        //     {
        //         cout<<"("<<p[i][j].first<<", "<<p[i][j].second<<") ";
        //     }
        //     cout << '\n';
        // }

        if (g[n - 1][m - 1] == LONG_LONG_MIN)
        {
            cout << "Impassable" << '\n';
        }
        else
        {
            cout << "Passable" << '\n';
            cout << g[n - 1][m - 1] << '\n';

            pii cur = {n - 1, m - 1};
            vector<pii> vec = {cur};
            while (cur.first != 0 || cur.second != 0)
            {
                cur = {p[cur.first][cur.second][0], p[cur.first][cur.second][1]};
                vec.push_back(cur);
            }
            cout << vec.size() << '\n';
            for (int i = vec.size() - 1; i >= 0; i--)
            {
                cout << vec[i].first + 1 << ' ' << vec[i].second + 1 << '\n';
            }
        }
    }
}