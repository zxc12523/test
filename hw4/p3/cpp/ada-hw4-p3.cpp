#include "ada-hw4-p3.h"
#include <bits/stdc++.h>

// feel free to use global variables
using namespace std;

vector<int> contest;
vector<int> conceal;
stack<int> s;
map<int, int> m;

vector<int> init(int N)
{
    contest.resize(N);
    conceal.resize(N);
    for (int i = 0; i < N; ++i)
        contest[i] = i, conceal[i] = 0;

    for (int i = 0; i < N;)
    {
        if (s.empty())
        {
            if (i == N - 1)
            {
                s.push(i);
            }
            else
            {
                if (compare(i, i + 1))
                {
                    s.push(i), s.push(i + 1);
                }
                else
                {
                    m[contest[i]] = contest[i + 1];
                    m[contest[i + 1]] = contest[i];
                    conceal[i] = conceal[i + 1] = 1;
                }
            }

            i += 2;
        }
        else
        {
            if (compare(s.top(), i))
            {
                s.push(i);
            }
            else
            {
                m[s.top()] = contest[i];
                m[contest[i]] = s.top();
                conceal[s.top()] = conceal[i] = 1;
                s.pop();
            }
            i += 1;
        }
    }

    vector<int> ans;
    for (int i = 0; i < N; i++)
        if (conceal[i] == 1)
            ans.push_back(i);

    return ans;
}

vector<int> insert(int p, int id)
{
    contest.insert(contest.begin() + p, id);
    conceal.insert(conceal.begin() + p, 0);

    int l = -1, r = -1;

    for (int i = p + 1; i < contest.size(); i++)
    {
        if (conceal[i] == 0)
        {
            r = i;
            break;
        }
    }

    for (int i = p - 1; i >= 0; i--)
    {
        if (conceal[i] == 0)
        {
            l = i;
            break;
        }
    }

    if (l != -1 && !compare(contest[l], contest[p]))
    {
        m[contest[l]] = contest[p];
        m[contest[p]] = contest[l];
        conceal[l] = conceal[p] = 1;
    }
    else if (r != -1 && !compare(contest[p], contest[r]))
    {
        m[contest[r]] = contest[p];
        m[contest[p]] = contest[r];
        conceal[r] = conceal[p] = 1;
    }

    // for (int i = 0; i < contest.size(); i++)
    //     cout << contest[i] << ' ';
    // cout << '\n';
    // for (int i = 0; i < conceal.size(); i++)
    //     cout << conceal[i] << ' ';
    // cout << '\n';

    vector<int> ans;
    for (int i = 0; i < contest.size(); i++)
        if (conceal[i] == 1)
            ans.push_back(contest[i]);

    return ans;
}

vector<int> remove(int p)
{
    if (conceal[p])
    {
        int v = m[contest[p]];

        for (int i = 0; i < contest.size(); i++)
        {
            if (contest[i] == v)
            {
                v = i;
                break;
            }
        }

        int l = -1, r = -1;

        for (int i = v + 1; i < contest.size(); i++)
        {
            if (conceal[i] == 0)
            {
                r = i;
                break;
            }
        }

        for (int i = v - 1; i >= 0; i--)
        {
            if (conceal[i] == 0)
            {
                l = i;
                break;
            }
        }

        if (l != -1 && !compare(contest[l], contest[v]))
        {
            m[contest[l]] = contest[v];
            m[contest[v]] = contest[l];
            conceal[l] = conceal[v] = 1;
        }
        else if (r != -1 && !compare(contest[v], contest[r]))
        {
            m[contest[r]] = contest[v];
            m[contest[v]] = contest[r];
            conceal[r] = conceal[v] = 1;
        }
        else
        {
            conceal[v] = 0;
        }
    }
    contest.erase(contest.begin() + p);
    conceal.erase(conceal.begin() + p);

    // for (int i = 0; i < contest.size(); i++)
    //     cout << contest[i] << ' ';
    // cout << '\n';
    // for (int i = 0; i < conceal.size(); i++)
    //     cout << conceal[i] << ' ';
    // cout << '\n';

    vector<int> ans;
    for (int i = 0; i < contest.size(); i++)
        if (conceal[i] == 1)
            ans.push_back(contest[i]);

    return ans;
}
