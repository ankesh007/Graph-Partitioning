#include "global_header.h"

void gggp(vvpi  &graph,vvi  &vector_set,vi &vertex_weight,vi &partition1,vi &partition2)
{
	int partition_weight=0;
	int s=graph.size();
	vector<int>  matching(s,0);
	int x=rand()%(s);
	partition1.pb(x);
	matching[x]=1;
	partition_weight+=vertex_weight[x];
	int total_lim=0;
	for(auto itr:vertex_weight)
		total_lim+=itr;

	int lim=(total_lim>>1);
	while(partition_weight<lim)
	{
		int min_edgecut=0;
		int min_index=-1;
		for(int i=0;i<s;i++)
		{
			int edge_cut=0;
			if(matching[i]==0)
			{
				int len=graph[i].size();
				for(int j=0;j<len;j++)
				{
					if(matching[graph[i][j].first]==1)
					{
						edge_cut-=graph[i][j].second;
					}
					else
					{
						edge_cut+=graph[i][j].second;
					}
				}
				if(min_index==-1){
					min_index=i;
					min_edgecut=edge_cut;
				}
				else if(edge_cut<min_edgecut){
					min_index=i;
					min_edgecut=edge_cut;
				}
			}
		}
		partition1.pb(min_index);
		matching[min_index]=1;
		partition_weight+=vertex_weight[min_index];
	}
	for(int i=0;i<s;i++)
	{
		if(matching[i]==0)
		{
			partition2.pb(i);
		}
	}
}