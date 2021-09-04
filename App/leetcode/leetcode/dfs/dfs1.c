#include <stdio.h>
#define maxn 12
int n,r;
int ans=0;         //符合要求的排列总数 
int ret[maxn];     //保存产生的排列 
int vis[maxn];     //记录1~n是否已使用 1-是 0-否 
void dfs(int cur)  //从{1,2,...,n}中取r个数构成的排列
{
	int i;
	if(cur==r)     //r个数已经选完，输出选择方案 
	{
		for(i=0;i<cur-1;i++)
			printf("%d ",ret[i]);
		printf("%d\n",ret[cur-1]);
		ans++; 
		return;
	}
	//试探1~n n个数 
	for(i=1;i<=n;i++)
	{
		if(!vis[i])     //i未被使用 
		{
			vis[i]=1;   //置已使用标记 
			ret[cur]=i; //将i填入ret[cur] 
			dfs(cur+1); //继续搜索 
			vis[i]=0;   //回溯：清除标记 
		}
	}
} 
int main()
{
	///scanf("%d %d",&n,&r);
    n = 3;
	r = 3;
	dfs(0);
	printf("count=%d\n",ans);
	return 0;
}