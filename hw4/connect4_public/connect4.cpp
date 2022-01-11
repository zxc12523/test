#include "connect4.h"
#include <bits/stdc++.h>

#define eb emplace_back
#define fi first
#define se second
#define pii pair<long long, long long>
#define mod 998244353
#define FastIO                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define maxn 1000000007

using namespace std;

long long op = 0;

long long height[7];
set<long long> valid;

long long grid[6][7];

// The columns are numbered from 0 to 6

void check_valid()
{
    valid.clear();
    for (long long j = 0; j < 7; j++)
        if (height[j] < 6)
            valid.insert(j);
}

void update_grid(long long p, long long col)
{
    grid[height[col]++][col] = p;
}

long long grade(map<long long, long long> &m, long long &score){
    if (m[1] && m[2]){
        score += 0;
    }
    else if (m[1] == 4)
    {
        return maxn;
    }
    else if (m[1] == 3 && m[0] == 1)
    {
        score += 10;
    }
    else if (m[1] == 2 && m[0] == 2)
    {
        score += 5;
    }
    else if (m[1] == 1 && m[0] == 3)
    {
        score += 2;
    }
    else if (m[2] == 4)
    {
        return -maxn;
    }
    return 0;
}

long long grade_hor(map<long long, long long> &m, long long &reward){
    for(long long i=0;i<6;i++) {
        for(long long j=0;j<4;j++){
            m[grid[i][j]]++;
        }

        long long tmp = grade(m, reward);
        if (tmp == maxn)
            return maxn;
        else if (tmp == -maxn)
            return -maxn;

        for(long long j=4;j<7;j++){
            m[grid[i][j]]++;
            m[grid[i][j-4]]--;

            long long tmp = grade(m, reward);
            if (tmp == maxn)
                return maxn;
            else if (tmp == -maxn)
                return -maxn;
        }
    }
    return 0;
}

long long grade_ver(map<long long, long long> &m, long long &reward){
    for(long long j=0;j<7;j++) {
        for(long long i=0;i<4;i++){
            m[grid[i][j]]++;
        }

        long long tmp = grade(m, reward);
        if (tmp == maxn)
            return maxn;
        else if (tmp == -maxn)
            return -maxn;

        for(long long i=4;i<6;i++){
            m[grid[i][j]]++;
            m[grid[i-4][j]]--;

            long long tmp = grade(m, reward);
            if (tmp == maxn)
                return maxn;
            else if (tmp == -maxn)
                return -maxn;
        }
    }
    return 0;
}

long long grade_dia_l(long long &reward){
    for(long long i=0;i<3;i++) {
        for(long long j=0;j<4;j++){
            map<long long, long long> m;
            for(long long k=0;k<4;k++){
                m[grid[i+k][j+k]]++;
            }

            long long tmp = grade(m, reward);
            if (tmp == maxn)
                return maxn;
            else if (tmp == -maxn)
                return -maxn;
        }
    }
    return 0;
}

long long grade_dia_r(long long &reward){
    for(long long i=0;i<3;i++) {
        for(long long j=3;j<7;j++){
            map<long long, long long> m;
            for(long long k=0;k<4;k++){
                m[grid[i+k][j-k]]++;
            }
            
            long long tmp = grade(m, reward);
            if (tmp == maxn)
                return maxn;
            else if (tmp == -maxn)
                return -maxn;
        }
    }
    return 0;
}

long long evaluate(){
    long long reward = 0, d;
    map<long long, long long> m;

    d = grade_hor(m, reward);
    if (d == maxn)
        return maxn;
    else if (d == -maxn)
        return -maxn;
    m.clear();

    d = grade_ver(m, reward);
    if (d == maxn)
        return maxn;
    else if (d == -maxn)
        return -maxn;

    d = grade_dia_l(reward);
    if (d == maxn)
        return maxn;
    else if (d == -maxn)
        return -maxn;

    d = grade_dia_r(reward);
    if (d == maxn)
        return maxn;
    else if (d == -maxn)
        return -maxn;

    return 0;
}

pii deter(long long forward_step, long long pre_min, long long pre_max, long long who){
    check_valid();
    long long e = evaluate();
    if (e == maxn){
        return {-1, e};
    }
    else if (e == -maxn){
        return {-1, e};
    }
    else if (valid.size() == 0){
        return {-2, 0LL};
    }
    else if (forward_step == 0){
        return {-2, e};
    }
    else if (who == 1){
        long long cur_ma = LONG_LONG_MIN, choose_col = -1;
        for(auto j:valid){
            grid[height[j]++][j] = 1;
            pii p = deter(forward_step-1, pre_min, pre_max, 0);
            grid[--height[j]][j] = 0;

            if(p.second > cur_ma){
                cur_ma = p.second, choose_col = j;
            }

            pre_max = max(pre_max, cur_ma);

            if (cur_ma > pre_min){
                break;
            }
        }
        return {choose_col, cur_ma};
    }
    else if (who == 0){
        long long cur_mi = LONG_LONG_MAX, choose_col = -1;
        for(auto j:valid){
            grid[height[j]++][j] = 2;
            pii p = deter(forward_step-1, pre_min, pre_max, 1);
            grid[--height[j]][j] = 0;

            if (p.second < cur_mi){
                cur_mi = p.second, choose_col = j;
            }

            pre_min = min(pre_min, cur_mi);

            if (pre_max > cur_mi){
                break;
            }
        }
        return {choose_col, cur_mi};
    }
}

int decide(int yp_move)
{
    if (yp_move == -1)
    {
        // A new game starts
        // TODO: Please remember to reset everything here (if needed)
        op = 0;

        for (long long i = 0; i < 6; i++)
            for (long long j = 0; j < 7; j++)
                grid[i][j] = 0;

        for (long long j = 0; j < 7; j++)
            height[j] = 0;
    }
    else
    {
        // YP placed his piece at column `yp_move`
        update_grid(2LL, yp_move);
    }

    if (op++ < 3)
    {
        update_grid(1, 3);
        return 3;
    }

    pii p = deter(5, LONG_LONG_MAX, LONG_LONG_MIN, 0);
    update_grid(1LL, p.first);

    return (int)p.first; // always place at the rightmost column
}
