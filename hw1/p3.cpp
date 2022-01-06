#include "bits/stdc++.h"
using namespace std;

#define eb emplace_back
#define pii pair<int, int>
#define MOD 1000000007
#define FastIO                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define int long long
#define maxn 1000000007

int times = 0, ans = 0;

int cmp(pii a, pii b)
{
    return a.second < b.second;
}

signed main()
{
    FastIO;
    int n, x, y;
    cin >> n;

    vector<pii> vec;
    stack<pair<pii, int>> s;
    stack<pair<vector<pii>, int>> s1;

    for (int i = 0; i < n; i++)
    {
        cin >> x >> y;
        vec.push_back({x, y});
    }
    sort(vec.begin(), vec.end(), cmp);

    s.push({{0, n - 1}, 0});
    while (s.size())
    {
        pair<pii, int> tmp = s.top();
        s.pop();

        if (tmp.first.first == -1)
        {
            deque<pii> u1_stack, d1_stack, u2_stack, d2_stack;

            vector<pii> b = s1.top().first;
            s1.pop();
            vector<pii> a = s1.top().first;
            s1.pop();

            for (int i = 0, j = 0; j < b.size();)
            {
                if (i < a.size() && a[i].first < b[j].first)
                {
                    while (d1_stack.size() && (d1_stack.back().second < a[i].second))
                        d1_stack.pop_back();

                    d1_stack.push_back(a[i++]);
                }
                else
                {
                    while (u1_stack.size() && (u1_stack.back().second > b[j].second))
                        u1_stack.pop_back();

                    if (u1_stack.empty())
                        ans += d1_stack.size();
                    else
                        ans += d1_stack.end() - lower_bound(d1_stack.begin(), d1_stack.end(), u1_stack.back());

                    u1_stack.push_back(b[j++]);
                }
            }

            for (int i = a.size() - 1, j = b.size() - 1; j >= 0;)
            {
                if (i >= 0 && a[i].first > b[j].first)
                {
                    while (d2_stack.size() && (d2_stack.front().second < a[i].second))
                        d2_stack.pop_front();

                    d2_stack.push_front(a[i--]);
                }
                else
                {
                    while (u2_stack.size() && (u2_stack.front().second > b[j].second))
                        u2_stack.pop_front();

                    if (u2_stack.empty())
                        ans += d2_stack.size();
                    else
                        ans += lower_bound(d2_stack.begin(), d2_stack.end(), u2_stack.front()) - d2_stack.begin();

                    u2_stack.push_front(b[j--]);
                }
            }

            vector<pii> ret;

            for (int i = 0, j = 0; i < a.size() || j < b.size();)
            {
                if (i == a.size())
                    ret.push_back(b[j++]);
                else if (j == b.size())
                    ret.push_back(a[i++]);
                else if (a[i].first < b[j].first)
                    ret.push_back(a[i++]);
                else
                    ret.push_back(b[j++]);
            }

            s1.push({ret, tmp.second});
        }
        else if (tmp.first.first != tmp.first.second)
        {
            s.push({{-1, -1}, tmp.second});
            int mid = (tmp.first.first + tmp.first.second) >> 1;
            s.push({{mid + 1, tmp.first.second}, 1});
            s.push({{tmp.first.first, mid}, 0});
        }
        else
        {
            s1.push({vector<pii>(1, vec[tmp.first.first]), tmp.second});
        }
    }

    cout << ans << '\n';
}