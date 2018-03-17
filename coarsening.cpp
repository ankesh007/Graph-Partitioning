#include "global_header.h"

void coarsen(vvpi &old_graph,vvi &old_vector_set,vvpi &new_graph,vvi &new_vector_set)
{
	cout<<"Hey from Coarsening"<<endl;
	int s=old_graph.size();
	vector<int>  matching(s,0);
	vector<int> mapping(s,0);
	int map_counter=0;

	for(int x=0;x<s;x++)
	{
		if(matching[x]==1)
			continue;

		int max_weight=0;
		int max_id;
		int y=old_graph[x].size();
		for(int i=0;i<y;i++)
		{
			if(matching[old_graph[x][i].first]==0 && old_graph[x][i].second>max_weight){
				max_id=old_graph[x][i].first;
				max_weight=old_graph[x][i].second;
			}
		}

		matching[x]=1;
		if(max_weight==0){
			vector<int> a;
			a.pb(x);
			new_vector_set.pb(a),
			mapping[x]=map_counter++;
			continue;
		}

		vector<int> a;
		matching[max_id]=1;
		a.pb(x);
		a.pb(max_id);
		new_vector_set.pb(a);
		mapping[x]=map_counter;
		mapping[max_id]=map_counter++;																																													
	}

	new_graph.resize(new_vector_set.size());

	map<pair<int,int>,int> m;
	for(int i=0;i<s;i++)
	{
		for(auto itr:old_graph[i])
		{
			if(mapping[i]==mapping[itr.x])
				continue;
			m[{mapping[i],mapping[itr.x]}]+=itr.y;
		}
	}

	for(auto itr:m)
	{
		new_graph[itr.x.x].pb({itr.x.y,itr.y});
	}
}