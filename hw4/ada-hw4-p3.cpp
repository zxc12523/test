#include <bits/stdc++.h>
#include "ada-hw4-p3.h"

// feel free to use global variables
std::vector<int> contest;
std::vector<int> conceal;
std::vector<int> prev;
std::unordered_map<int, int> board;

std::vector<int> init(int N)
{
    contest.resize(N);
    for (int i = 0; i < N; ++i)
        contest[i] = i;
    for (int i = 0; i < N; i++)
    {
        if (prev.size())
        { // prev有人
            int tmp = prev.back();
            if (!compare(tmp, i))
            {
                prev.pop_back();
                conceal.push_back(tmp);
                conceal.push_back(i);
                board[tmp] = 1;
                board[i] = 1;
            }
            else
            {
                prev.push_back(i);
            }
        }
        else
        {
            if (i != N - 1 && !compare(i, i + 1))
            {
                conceal.push_back(i);
                conceal.push_back(i + 1);
                board[i] = 1;
                board[i + 1] = 1;
                i++;
            }
            else if (i == N - 1)
            {
                prev.push_back(i);
            }
            else
            {
                prev.push_back(i);
                prev.push_back(i + 1);
                i++;
            }
        }
    }
    std::sort(conceal.begin(), conceal.end());
    return conceal;
}
void insertToConceal(int id)
{
    for (int i = 0; i < conceal.size(); i++)
    {
        if (id < conceal[i])
        {
            conceal.insert(conceal.begin() + i, id);
            return;
        }
    }
    conceal.push_back(id);
}
std::vector<int> insert(int p, int id)
{
    contest.insert(contest.begin() + p, id);
    for (int i = p - 1; i >= 0; i--)
    { // find left
        if (board[contest[i]] == 0)
        { // left
            if (!compare(contest[i], id))
            {
                board[contest[i]] = 1;
                board[id] = 1;
                insertToConceal(contest[i]);
                conceal.push_back(id);
                return conceal;
            }
            break;
        }
    }
    for (int i = p + 1; i < contest.size(); i++)
    {
        if (board[contest[i]] == 0)
        { // right
            if (!compare(id, contest[i]))
            {
                board[contest[i]] = 1;
                board[id] = 1;
                insertToConceal(contest[i]);
                conceal.push_back(id);
            }
            break;
        }
    }
    return conceal;
}
void eraseConceal(int id)
{
    for (int i = 0; i < conceal.size(); i++)
    {
        if (id == conceal[i])
        {
            board[id] = 0;
            conceal.erase(conceal.begin() + i);
        }
    }
}
std::vector<int> remove(int p)
{
    board[contest[p]] = -1;
    eraseConceal(contest[p]);
    contest.erase(contest.begin() + p);
    for (int i = p - 1; i >= 0; i--)
    {
        if (board[contest[i]] == 1)
        { // left conceal
            for (int j = i - 1; j >= 0; j--)
            {
                if (board[contest[j]] == 0)
                { // left remain
                    if (!compare(contest[j], contest[i]))
                    {
                        return conceal;
                    }
                    break;
                }
            }
            for (int j = i + 1; j < contest.size(); j++)
            {
                if (board[contest[j]] == 0)
                { // right remain
                    if (!compare(contest[i], contest[j]))
                    {
                        return conceal;
                    }
                    break;
                }
            }
            eraseConceal(contest[i]);
            return conceal;
        }
    }
    for (int i = p; i < contest.size(); i++)
    {
        if (board[contest[i]] == 1)
        { // right conceal
            for (int j = i - 1; j >= 0; j--)
            {
                if (board[contest[j]] == 0)
                { // left remain
                    if (!compare(contest[j], contest[i]))
                    {
                        return conceal;
                    }
                    break;
                }
            }
            for (int j = i + 1; j < contest.size(); j++)
            {
                if (board[contest[j]] == 0)
                { // right remain
                    if (!compare(contest[i], contest[j]))
                    {
                        return conceal;
                    }
                    break;
                }
            }
            eraseConceal(contest[i]);
            return conceal;
        }
    }
    return conceal;
}