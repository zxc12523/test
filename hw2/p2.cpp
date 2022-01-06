#include "bits/stdc++.h"
using namespace std;

#define eb emplace_back
#define fi first
#define se second
#define pii pair<int, int>
#define pipii pair<int, pii>
#define mod 998244353
#define FastIO                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define int long long
#define maxn 1000000007

signed main()
{
    int t, f;
    for (cin >> t >> f; t > 0; t--)
    {
        int n, sum = 0, sum1;
        cin >> n;
        unordered_set<int> s, s1;
        unordered_map<int, pii> m, m1;
        vector<int> vec, ans(n + 1, 0);
        priority_queue<pipii, vector<pipii>, greater<pipii>> odd, eve;
        for (int i = 0; i < n; i++)
        {
            int tmp;
            cin >> tmp;
            if (vec.empty() || vec.back() * tmp < 0)
            {
                sum += tmp;
                vec.push_back(tmp);
            }
            else if (vec.back() < tmp)
            {
                sum -= vec.back() - tmp;
                vec.pop_back();
                vec.push_back(tmp);
            }
        }

        sum1 = sum;
        vector<int> vec1 = vec;

        if (vec1.front() < vec1.back())
        {
            sum1 -= vec1[0];
            vec1.erase(vec1.begin());
        }
        else
        {
            sum1 -= vec1.back();
            vec1.pop_back();
        }

        if (vec.size() & 2 == 1)
        {
            swap(vec, vec1);
            swap(sum, sum1);
        }

        for (int i = 0; i < vec.size(); i++)
        {
            int p = i == 0 ? vec.size() - 1 : i - 1;
            int n = i == vec.size() - 1 ? 0 : i + 1;

            m[i] = {p, n};
            eve.push({vec[i] + vec[n], {i, n}});
        }

        for (int i = 0; i < vec1.size(); i++)
        {
            int p = i == 0 ? vec1.size() - 1 : i - 1;
            int n = i == vec1.size() - 1 ? 0 : i + 1;

            m1[i] = {p, n};
            odd.push({vec1[i] + vec1[n], {i, n}});
        }

        int len = vec.size();

        while (len > 0)
        {
            while (!eve.empty() && (s.count(eve.top().se.fi) || s.count(eve.top().se.se)))
                eve.pop();

            ans[len] = sum;
            len -= 2;

            if (eve.empty())
                break;

            pair<int, pii> p = eve.top();

            eve.pop();
            sum -= p.fi;
            s.insert(p.se.fi);
            s.insert(p.se.se);
            int l = m[p.se.fi].fi;
            int r = m[p.se.se].se;
            eve.push({vec[l] + vec[r], {l, r}});
            m[l].se = r;
            m[r].fi = l;
        }

        len = vec1.size();
        while (len > 0)
        {
            while (!odd.empty() && (s1.count(odd.top().se.fi) || s1.count(odd.top().se.se)))
                odd.pop();

            ans[len] = sum1;
            len -= 2;

            if (odd.empty())
                break;

            pair<int, pii> p = odd.top();

            odd.pop();
            sum1 -= p.fi;
            s1.insert(p.se.fi);
            s1.insert(p.se.se);
            int l = m1[p.se.fi].fi;
            int r = m1[p.se.se].se;
            odd.push({vec1[l] + vec1[r], {l, r}});
            m1[l].se = r;
            m1[r].fi = l;
        }

        for (int i = 1; i <= n; i++)
            cout << ans[i] << ' ';
        cout << '\n';
    }
}