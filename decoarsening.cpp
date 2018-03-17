#include "global_header.h"

void decoarsen(vvi &old_vector_set,vvpi &new_graph,vi &new_vertex_weight,vi &partition1,vi &partition2,vi &new_partition1,vi &new_partition2)
{
	int pw1=partition1.size();
	int pw2=partition2.size();
	int s=new_graph.size();
	vector<int> matching(s,0);
	for(int i=0;i<pw1;i++)
	{
		for(int j=0;j<old_vector_set[i];j++)
		{
			new_partition1.pb(old_vector_set[i][j]);
		}
	}
	for(int i=0;i<pw2;i++)
	{
		for(int j=0;j<old_vector_set[i];j++)
		{
			new_partition2.pb(old_vector_set[i][j]);
			matching[old_vector_set[i][j]]=1;
		}
	}
	int nwp1=new_partition1.size();
	int nwp2=new_partition2.size();
	vector<int> gain_part1(npw1,0);
	vector<int> gain_part2(npw2,0);
	vector<int> matching_part1(npw1,0);
	vector<int> matching_part2(npw2,0);
	vpi swap; 
	for(int i=0;i<nwp1;i++)
	{
		int i1=new_partition1[i];
		int ss=new_graph[i1].size();
		int gain=0;
		for(int j=0;j<ss;j++)
		{
			int r=new_graph[i1][ss].first;
			if(matching[r]==matching[i1])
			{
				gain-=graph[i1][r];
			}
			else
			{
				gain+=graph[i1][r];
			}
		}
		gain_part1[i]=gain;
	}
	for(int i=0;i<nwp2;i++)
	{
		int i1=new_partition2[i];
		int ss=new_graph[i1].size();
		int gain=0;
		for(int j=0;j<ss;j++)
		{
			int r=new_graph[i1][ss].first;
			if(matching[r]==matching[i1])
			{
				gain-=graph[i1][r];
			}
			else
			{
				gain+=graph[i1][r];
			}
		}
		gain_part2[i]=gain;
	}
	while(true)
	{
		int losing=0;
		int max_gain1=-1e9;
		int part1_id=0;
		for(int i=0;i<nwp1;i++)
		{
			if(matching_part1[i]==0)
			{
				if(gain_part1[i]>max_gain1)
				{
					max_gain1=gain_part1[i];
					part1_id=i;
				}
			}
		}
		if(max_gain1<0)
		{
			losing=losing+1;
		}
		else{
			losing=0;
		}
		matching_part1[i]==1;
		// partition2.pb(insert);
		// // partition1.erase(partition1.begin()+i);
		// for(int i=0;i<)
		int max_gain2=-1e9;
		int part2_id=0;
		for(int i=0;i<nwp2;i++)
		{
			if(matching_part2[i]==0)
			{
				if(gain_part2[i]>max_gain2)
				{
					max_gain2=gain_part2[i];
					part2_id=new_partition2[i];
				}
			}
		}
		if(max_gain2<0)
		{
			losing=losing+1;
		}
		else{
			losing=0;
		}

	}

}