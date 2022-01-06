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
#define maxn 200001

signed main()
{
    FastIO;
    int t, f;
    for (cin >> t >> f; t > 0; t--)
    {
        int n;
        cin >> n;
        vector<pii> vec, ans;
        for (int i = 0; i < n; i++)
        {
            int tmp;
            cin >> tmp;
            vec.push_back({tmp, i});
        }
        ans.push_back(vec[0]);
        int sum = vec[0].fi;
        for (int i = 1; i < n; i++)
        {
            if ((vec[i].fi <= 0 && ans.back().fi <= 0) ||
                (vec[i].fi > 0 && ans.back().fi > 0))
            {
                if (vec[i].fi > ans.back().fi)
                {
                    sum -= ans.back().fi;
                    sum += vec[i].fi;
                    ans.pop_back();
                    ans.push_back(vec[i]);
                }
            }
            else
            {
                if (sum < 0)
                {
                    sum = vec[i].fi;
                    ans.clear();
                    ans.push_back(vec[i]);
                }
                else if (vec[i].fi + ans.back().fi > 0)
                {
                    sum += vec[i].fi;
                    ans.push_back(vec[i]);
                }
            }
        }
        if (ans.size() > 1 && ans.front().fi < 0)
        {
            sum -= ans[0].fi;
            ans.erase(ans.begin());
        }
        if (ans.size() > 1 && ans.back().fi < 0)
        {
            sum -= ans.back().fi;
            ans.pop_back();
        }

        cout << sum << '\n';
        if (f == 1)
        {
            cout << ans.size() << ' ';
            for (auto i : ans)
                cout << i.se + 1 << ' ';
            cout << '\n';
        }
    }
}