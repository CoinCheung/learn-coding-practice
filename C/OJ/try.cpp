#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
 
int stamps[300];//保存所有邮票值
int now[5];//当前组合
int ans[5];//最终结果组合
int n,m,total,ansnum;//总邮票数目，顾客需求以及组合邮票的数目
bool tie,none;//是否是平局还是没有这种组合
bool vis[300];//为了计算多少种邮票的标志数组
 
void print();//输出格式

int cal(int tmp[], int num)//计算有多少种类邮票
{
	int res = 0;
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < num; i ++)
	{
		if (!vis[tmp[i]])
		{
			vis[tmp[i]] = true;
			res ++;
		}
	}
	return res;
}
 
int getMax(int tmp[], int num)//计算邮票中的最大值
{
	int res = 0;
	for (int i = 0; i < num; i ++)
	{
		if (res < stamps[tmp[i]])
		{
			res = stamps[tmp[i]];
		}
	}
	return res;
}
 
void comp()//更新邮票组合
{
	int know = cal(now, total);
	int kans = cal(ans, ansnum);
	int maxans = getMax(ans, ansnum);
	int maxnow = getMax(now, total);
 
	if (ansnum == -1 || know > kans || (know == kans && ansnum > total) || (kans == know && ansnum == total && maxnow > maxans))
	{
		tie = false;
		ansnum = total;
		for (int i = 0; i < total; i ++)
		{
			ans[i] = now[i];
		}
		return;
	}
	if (kans == know && ansnum == total && maxnow == maxans)
	{
		tie = true;
	}
 
}
 
void dfs(int nn, int ssum)//深搜，遍历每一种情况
{
	if (ssum > m)
	{
		return;
	}
	if (ssum == m)
	{
		none = false;
		comp();
	}
	if (total == 4)
	{
		return;
	}
	for (int i = nn; i < n; i ++)
	{
		now[total] = i;
		total ++;
		dfs(i, ssum + stamps[i]);
		total --;
	}
}
 
int main()//主函数
{
	int i,j;
	while (scanf("%d", &j) != EOF)
	{
		i = 0;
		stamps[i] = j;
		while (stamps[i])
		{
			i ++;
			scanf("%d", &stamps[i]);
		}
		n = i ;
		sort(stamps, stamps + n);
		while (scanf("%d" ,&m),m)
		{
			total = 0;
			ansnum = -1;
			tie = false;
			none = true;
			dfs(0, 0);
			if (!none)
			{
				sort(ans, ans + ansnum);
			}
			print();
		}
	}
	return 0;
}
 
 
void print()//输出格式
{
	if (none)
	{
		printf("%d ---- none\n", m);
		return;
	}
	printf("%d (%d):", m, cal(ans, ansnum));
	if (tie)
	{
		printf(" tie\n");
		return;
	}
	for (int i = 0; i < ansnum; i ++)
	{
		printf(" %d", stamps[ans[i]]);
	}
	printf("\n");
}
