#include "global_header.h"

float threshold=0.05;

void gggp(int x,vvpi  &graph,vvi  &vector_set,vi &vertex_weight,vi &partition1,vi &partition2)
{
	// cout<<"Enter GGGP"<<endl;
	set<pii,Comparator> dijkstra; 
	int partition_weight=0;
	int s=graph.size();
	vector<int>  matching(s,0);
	vector<int> gain(s,0);
	// int x=rand()%(s);
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
	while(partition_weight<lim && (!dijkstra.empty()))
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

void gggp2(int x,vi &vertex_set,vi &partition1,vi &partition2,int curNo,int depth)
{
	// cout<<"Enter GGGP"<<endl;
	set<pii,Comparator> dijkstra; 
	int partition_weight=0;
	int s=vertex_set.size();
	int thresh=threshold*s;
	// int x=rand()%(s);
	partition1.pb(x);
	matching[depth][x]=1;
	partition_weight=1;
	int total_lim=s;

	for(int j=0;j<s;j++)
	{
		int i=vertex_set[j];
		if(i==x)
			continue;
		for(auto itr:graph[i])
		{
			if(globalPartition[depth][itr]!=curNo)
				continue;
			if(matching[depth][i]==matching[depth][itr])
				gain[depth][i]-=1;
			else
				gain[depth][i]+=1;
		}
		dijkstra.insert({gain[depth][i],i});
	}

	int lim=(s>>1);
	while(true && (!dijkstra.empty()))
	{
		auto itr=*(dijkstra.begin());
		dijkstra.erase(itr);

		int diff=(s-partition_weight-partition_weight);
		if(itr.x<0 && diff<=thresh)
			break;
		if(diff<=-thresh)
			break;

		partition1.pb(itr.y);
		matching[depth][itr.y]=1;
		partition_weight+=1;

		for(auto itr2:graph[itr.y])
		{
			if(globalPartition[depth][itr2]!=curNo)
				continue;
			if(matching[depth][itr2]==1)
				continue;
			dijkstra.erase({gain[depth][itr2],itr2});
			gain[depth][itr2]+=2;
			dijkstra.insert({gain[depth][itr2],itr2});
		}
	}
	int newS=partition1.size();
	newS=s-newS;
	partition2.resize(newS);
	int j=0;
	for(int ii=0;ii<s;ii++)
	{
		int i=vertex_set[ii];
		if(matching[depth][i]==0)
		{
			partition2[j++]=i;
		}
	}
	// cout<<"Exit GGGP"<<endl;	
}