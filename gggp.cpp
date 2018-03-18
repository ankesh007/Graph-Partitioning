#include "global_header.h"

void gggp(vvpi  &graph,vvi  &vector_set,vi &vertex_weight,vi &partition1,vi &partition2)
{
	// cout<<"Enter GGGP"<<endl;
	set<pii,Comparator> dijkstra; 
	int partition_weight=0;
	int s=graph.size();
	vector<int>  matching(s,0);
	vector<int> gain(s,0);
	int x=rand()%(s);
	partition1.pb(x);
	matching[x]=1;
	partition_weight+=vertex_weight[x];
	int total_lim=0;
	for(auto itr:vertex_weight)
		total_lim+=itr;
	for(int i=0;i<s;i++)
	{
		if(i==x)
			continue;
		for(auto itr:graph[i])
		{
			if(matching[itr.x]==matching[i])
				gain[i]-=itr.y;
			else
				gain[i]+=itr.y;
		}
		dijkstra.insert({gain[i],i});
	}

	int lim=(total_lim>>1);
	while(partition_weight<lim)
	{
		auto itr=*(dijkstra.begin());
		dijkstra.erase(itr);
		partition1.pb(itr.y);
		matching[itr.y]=1;
		partition_weight+=vertex_weight[itr.y];

		for(auto itr2:graph[itr.y])
		{
			if(matching[itr2.x]==1)
				continue;
			dijkstra.erase({gain[itr2.x],itr2.x});
			if(matching[itr.y]==matching[itr2.x])
			{
				gain[itr2.x]-=2*itr2.y;				
			}
			else
			{
				gain[itr2.x]+=2*itr2.y;
			}
			dijkstra.insert({gain[itr2.x],itr2.x});
		}
	}
	for(int i=0;i<s;i++)
	{
		if(matching[i]==0)
		{
			partition2.pb(i);
		}
	}
	// cout<<"Exit GGGP"<<endl;	
}