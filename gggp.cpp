#include "global_header.h"
void gggp(vvpi  &graph,vvi  &vector_set,vi &vertex_weight,vi &partition1,vi &partition2)
{
	int partition_weight=0;
	int s=graph.size();
	vector<int>  matching(s,0);
	int x=rand()%(s);
	partition1.pb(x);
	// graph.erase(graph.begin()+x);
	matching[x]=1;
	partition_weight+=vertex_weight[x];
	// min_edgecut=0
	// // first=True;
	// min_index=-1;
	while(partition_weight<vertices/2)
	{
		int min_edgecut=0;
		// first=True;
		int min_index=-1;
		for(int i=0;i<s;i++)
		{
			int edge_cut=0;
			if(matching[i]==0)
			{
				for(int j=0;j<graph[i].size();j++)
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