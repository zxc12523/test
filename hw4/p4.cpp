#include <bits/stdc++.h>

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

using namespace std;

int dp[1001][1001];
int one[1001][1001];
int dif[2001];
int xo[2001];

vector<int> ran;
vector<int> vec;

int solve(int n, int m, int p)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= min(i, m); j++)
        {
            if (i == j)
            {
                dp[i][j] = dp[i - 1][j - 1] + vec[i - 1 + p];
                one[i][j] = 1;
            }
            else if (j == 1)
            {
                dp[i][j] = dp[i - 1][j] + dif[i - 1 + p];

                if (i > 2)
                {
                    dp[i][j] += xo[i - 1 + p];
                }
            }
            else
            {
                // 口口口 口口 "口" 最後一個獨立
                dp[i][j] = dp[i - 1][j - 1] + vec[i - 1 + p];
                one[i][j] = 1;

                // 口 口口口 口口<-口 最後一個黏上去
                if (one[i - 1][j] == 1)
                { // 口 口口口 口<-口 尾段長度1
                    int tmp = dp[i - 1][j] + dif[i - 1 + p];
                    if (tmp < dp[i][j])
                    {
                        dp[i][j] = tmp;
                        one[i][j] = 0;
                    }
                }
                else
                {
                    int tmp = min(dp[i - 2][j - 1] + vec[i - 2 + p] + dif[i - 1 + p],
                                  dp[i - 1][j] + dif[i - 1 + p] + xo[i - 1 + p]);
                    if (tmp < dp[i][j])
                    {
                        dp[i][j] = tmp;
                        one[i][j] = 0;
                    }
                }
            }
        }
    }

    return dp[n][m];
}

signed main()
{
    FastIO;
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        vec.push_back(t);
    }

    for (int i = 0; i < n; i++)
    {
        vec.push_back(vec[i]);
        ran.push_back(i);
    }

    for (int i = 1; i < vec.size(); i++)
    {
        dif[i] = vec[i] - abs(vec[i] - vec[i - 1]);
    }
    for (int i = 2; i < vec.size(); i++)
    {
        xo[i] = vec[i - 1] * ((vec[i - 2] & vec[i - 1]) ^ (vec[i - 1] | vec[i]) ^ (vec[i] + vec[i - 2]));
    }

    int ans = LONG_LONG_MAX;

    srand(17);
    random_shuffle(ran.begin(), ran.end());

    for (int i = 0; i < min(n, (int)5000000 / (n * m)); i++)
    {
        ans = min(ans, solve(n, m, ran[i]));
    }

    cout << ans << '\n';
}