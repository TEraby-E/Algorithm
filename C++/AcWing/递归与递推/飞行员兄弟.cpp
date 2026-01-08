#include <bits/stdc++.h>

using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using u128 = unsigned __int128;

using a2 = array<int, 2>;
using a3 = array<int, 3>;
using a4 = array<int, 4>;

#define x first
#define y second
typedef pair<int, int> PII;

const int N = 5;
const int MAXN = 1e6 + 10;
const int inf = 1e9;
// const int mod = 1e9 + 7;
const int mod = 998244353;

char g[N][N], backup[N][N];

int get(int x, int y)
{
    return 4 * x + y;
}

void turn_one(int x, int y)
{
    if (g[x][y] == '+')
        g[x][y] = '-';
    else
        g[x][y] = '+';
}

void turn_all(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        turn_one(x, i);
        turn_one(i, y);
    }
    turn_one(x, y);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), std::cout.tie(0);

    vector<PII> res;
    for (int i = 0; i < 4; i++)
        cin >> g[i];
    for (int op = 0; op < 1 << 16; op++)
    {
        vector<PII> temp;
        memcpy(backup, g, sizeof g); // 备份

        // 进行操作
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (op >> get(i, j) & 1)
                {
                    temp.push_back({i, j});
                    turn_all(i, j);
                }

        // 判断灯泡是否全亮
        bool has_closed = false;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (g[i][j] == '+')
                    has_closed = true;

        if (has_closed == false)
        {
            if (res.empty() || res.size() > temp.size())
                res = temp;
        }
        memcpy(g, backup, sizeof g);
    }
    cout << res.size() << endl;
    for (auto op : res)
        cout << op.x + 1 << ' ' << op.y + 1 << endl;

    return 0;
}