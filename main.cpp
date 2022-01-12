#include <bits/stdc++.h>
#include "ypglpk.hpp"

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
#define num 10

using namespace std;
using namespace ypglpk;

vector<bitset<num>> maximal;
vector<bitset<num>> adj(num, bitset<num>(0));

void find_clique(bitset<num> p, bitset<num> r, bitset<num> s)
{
    if (r == 0 && s == 0)
    {
        maximal.push_back(p);
        return;
    }

    bitset<num> tmp(1);
    for (int i = 0; i < num; i++)
    {
        if (r[i] == 1)
        {
            p[i] = 1;
            find_clique(p, r & adj[i], s & adj[i]);
            p[i] = 0;

            r &= ~tmp;
            s |= tmp;
        }
    }
}

signed main()
{
    int t;
    for (cin >> t; t > 0; t--)
    {
        int n, m, f, t;
        cin >> n >> m;
        for (int i = 0; i < m; i++)
        {
            cin >> f >> t;
            adj[f][t] = 1;
            adj[t][f] = 1;
        }
        bitset<num> potential(0), remain(0), skip(0);
        for (int i = 0; i < n; i++)
        {
            remain <<= 1;
            remain |= 1;
        }
        find_clique(potential, remain, skip);

        vector<vector<double>> A(num + maximal.size(), vector<double>(maximal.size(), 0));
        vector<double> B(num + maximal.size(), -1);
        vector<double> C(maximal.size(), -1);
        vector<bool> isint(maximal.size(), 1);

        for (int j = 0; j < maximal.size(); j++)
            for (int i = 0; i < num; i++)
                A[i][j] = (double)-maximal[j][i];

        for (int j = 0; j < maximal.size(); j++)
            A[num + j][j] = (double)-1, B[num + j] = 0;

        pair<double, vector<double>> p = ypglpk::mixed_integer_linear_programming(A, B, C, isint);

        for (auto i : p.second)
            cout << i << ' ';
        cout << '\n';
    }
}