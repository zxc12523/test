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

int ans = -1;

int dp[501][501];
int gd[501][501];

signed main()
{
    FastIO;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> dp[i][i];

    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            gd[i][j] = __gcd(dp[i][i], dp[j][j]);

    for (int l = 1; l <= n; l++)
    {
        for (int i = 1; i + l <= n; i++)
        {
            int g1 = gd[i][i + l], tmp = LONG_LONG_MIN, t = i + l;

            // ... ...
            for (int j = i + 1; j < t - 1; j++)
                if (dp[i][j] != 1 && dp[j + 1][t] != 1)
                    tmp = max(tmp, dp[i][j] + dp[j + 1][t]);

            if (g1 != 1)
            {
                // 0 ... 0
                if (i + 1 != t - 1 && dp[i + 1][t - 1] != 1)
                    tmp = max(tmp, g1 + dp[i + 1][t - 1]);

                // 0 ... 0 ... 0
                for (int m = i + 1; m < t; m++)
                {
                    int g2 = gd[i][m], g3 = gd[m][t];
                    if (!(g2 == 1 || g3 == 1 || dp[i + 1][m - 1] == 1 || dp[m + 1][t - 1] == 1) && (i + 1 != m - 1) && (m + 1 != t - 1))
                    {
                        tmp = max(tmp, g2 + g3 + dp[i + 1][m - 1] + dp[m + 1][t - 1]);
                    }
                }
            }

            dp[i][t] = tmp == LONG_LONG_MIN ? 1 : tmp;
        }
    }

    dp[1][n] == 1 ? cout << -1 << '\n' : cout << dp[1][n] << '\n';
}