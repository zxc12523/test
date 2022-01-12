#include <bits/stdc++.h>
#include "ypglpk.hpp"

// g++ -std=c++17 -O2 -oexample main.cpp -I /usr/local/include -L /usr/local/lib -lglpk -Wall

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
#define num 80

using namespace std;

vector<bitset<num>> maximal;
vector<bitset<num>> adj(num, bitset<num>(0));

void find_clique(bitset<num> p, bitset<num> r, bitset<num> s)
{
    if (r == 0 && s == 0)
    {
        maximal.push_back(p);
        return;
    }

    int u;
    for (int i = 0; i < num; i++)
    {
        if ((r | s)[i] == 1)
        {
            u = i;
            break;
        }
    }

    for (int i = 0; i < num; i++)
    {
        if ((r & ~adj[u])[i] == 1)
        {
            bitset<num> tmp(0);
            tmp[i] = 1;
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
    FastIO;
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

        vector<vector<double>> A(n + maximal.size(), vector<double>(maximal.size(), 0));
        vector<double> B(n + maximal.size(), -1);
        vector<double> C(maximal.size(), -1);
        vector<bool> isint(maximal.size(), 1);

        for (int j = 0; j < maximal.size(); j++)
            for (int i = 0; i < n; i++)
                A[i][j] = (double)-maximal[j][i];

        for (int j = 0; j < maximal.size(); j++)
            A[n + j][j] = (double)-1, B[n + j] = 0;

        /*
        for (auto i : A)
        {
            for (auto j : i)
            {
                cout << j << ' ';
            }
            cout << '\n';
        }
        */

        pair<double, vector<double>> p = ypglpk::mixed_integer_linear_programming(A, B, C, isint);

        int cnt = 0;
        for (int i = 0; i < maximal.size(); i++)
        {
            if (p.second[i] == 1)
            {
                cnt++;
            }
        }

        cout << cnt << '\n';

        set<int> s;
        for (int i = 0; i < maximal.size(); i++)
        {
            if (p.second[i] == 1)
            {
                vector<int> tmp;

                for (int j = 0; j < n; j++)
                {
                    if (A[j][i] == -1 && s.count(j) == 0)
                    {
                        s.insert(j);
                        tmp.push_back(j);
                    }
                }
                cout << tmp.size() << ' ';
                for (auto j : tmp)
                    cout << j << ' ';
                cout << '\n';
            }
        }

        maximal.clear();
        adj.clear();
        adj.resize(num);
    }
}