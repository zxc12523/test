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

signed main()
{
    deque<int> q;
    q.push_back(1);
    q.push_back(1);
    q.push_back(2);
    q.push_back(3);
    q.push_back(3);
    cout << lower_bound(q.begin(), q.end(), 3) - q.begin();
}