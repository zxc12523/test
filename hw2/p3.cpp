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
#define maxn 1000000007
#define int long long

int cmp(pair<pii, pii> a, pair<pii, pii> b)
{
    return a.se.se > b.se.se;
}

int solve(vector<pair<pii, pii>> vec)
{
    int n = vec.size();
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    sort(vec.begin(), vec.end()); // sort by s e

    int i = 0, ans = 0, time = vec[0].fi.fi;

    while (i < n || pq.size())
    {
        while (i < n && vec[i].fi.fi == time)
        {
            pq.push({vec[i].fi.se, vec[i].se.fi});
            i++;
        }

        // cout<<time<<' '<<pq.size()<<'\n';
        // cout<<pq.top().fi<<' '<<pq.top().se<<'\n';

        int w = min(pq.top().se, pq.top().fi - time + 1);

        if (i == n || time + w <= vec[i].fi.fi)
        {
            time += w;
            ans += w;
            pq.pop();
        }
        else
        {
            pii tmp = pq.top();
            pq.pop();
            tmp.second -= vec[i].fi.fi - time;
            ans += vec[i].fi.fi - time;
            pq.push(tmp);

            time = vec[i].fi.fi;
        }

        if (i < n && pq.size() == 0)
        {
            time = vec[i].fi.fi;
        }
    }

    return ans;
}

signed main()
{
    int n, a, b, c, d;
    cin >> n;

    vector<pair<pii, pii>> vec;
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    for (int i = 0; i < n; i++)
    {
        cin >> a >> b >> c >> d;
        vec.push_back({{a, b}, {c, d}}); // s e x p
    }

    sort(vec.begin(), vec.end(), cmp);

    // for(auto i:vec) {
    //     cout<<i.se.se<<' ';
    // }
    // cout<<'\n';

    int ans = 0, tmp = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        ans += solve(vec) * (vec[i].se.se - tmp);

        // cout<<'\n'<<ans<<' '<<tmp<<'\n';

        tmp = vec[i].se.se;
        vec.pop_back();
    }

    cout << ans << '\n';
}