#include <bits/stdc++.h>
#define MAXN 1345

using namespace std;

typedef pair<int, int> pr;
long long dp[15][MAXN];
int mer[MAXN][MAXN];
int vis[15], vist[15];

void initMer()
{
    int n = 9;
    int lim = 1 << (n + 1);
    memset(mer, -1, sizeof(mer));
    for (int i = 0; i < lim; ++i)
    {
        for (int j = 0; j < lim; ++j)0
        {
            memset(vis, 0, sizeof(vis));
            for (int k = 0; k <= n; ++k)
            {
                if (j & (1 << k)) vis[k]++;
                if (i & (1 << k)) vis[k]++;
            }
            int flag = 1;
            int tmp = 0;
            for (int k = 0; k <= n; ++k)
            {
                if (vis[k] >= 2)
                {
                    flag = 0;
                    break;
                }
                if (vis[k] == 0) continue;
                if (vis[k] == 1 && k == n)
                {
                    flag = 0;
                    break;
                }
                if (vis[k + 1] == 0)
                {
                    flag = 0;
                    break;
                }
                vis[k]--;
                vis[k + 1]--;
                tmp |= (1 << k);
            }
            if (flag) mer[i][j] = tmp;
        }
    }
}

int main()
{
    freopen("immetric.in", "r", stdin);
    freopen("immetric.out", "w", stdout);
    initMer();
    int ca = 0;
    for (;;)
    {
        ++ca;
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i < (1 << (n + 1)); ++i)
            if (mer[i][0] > 0)
                dp[n][mer[i][0]] = 1;
        for (int i = n - 1; i >= 0; --i)
            for (int j = 0; j < (1 << (i + 1)); ++j)
                for (int k = 0; k < (1 << (i + 1)); ++k)
                {
                    int tmp = mer[j][k];
                    if (tmp > 0)
                        dp[i][tmp] += dp[i + 1][j];
                }
        cout << "Case #" << ca << ": " << dp[1][1] << endl;
    }
    return 0;
}