#include "global_header.h"

void printCoarsenedGraph(vector<vvi> vertexMapGraph,vector<vvpi> edgeMapGraph,vvi vertexWeight)
{
	int kk=vertexWeight.size();
	for(int k=0;k<=kk;k++)
	{	
		for(int i=0;i<vertexMapGraph[k].size();i++)
		{
			cout<<i<<"Weight:"<<vertexWeight[k][i]<<": ";
			for(auto itr:vertexMapGraph[k][i])
				cout<<itr<<" ";
			cout<<endl;
		}
		for(int i=0;i<edgeMapGraph[k].size();i++)
		{
			for(auto itr:edgeMapGraph[k][i])
				cout<<i<<" "<<itr.x<<" "<<itr.y<<endl;
		}
	}
}

void coarsen(vvpi &old_graph,vvi &old_vector_set,vi &old_vertex_weight,vvpi &new_graph,vvi &new_vector_set,vi &new_vertex_weight)
{
	// cout<<"Hey from Coarsening"<<endl;
	int s=old_graph.size();
	vi mapping(s,0);
	int map_counter=0;
	vi randomArray(s,0);
	vi revrandomArray(s,0);
	int randomGenerator=s;
	for(int i=0;i<s;i++)
	{
		randomArray[i]=i;
		revrandomArray[i]=i;
	}

	while(randomGenerator>0)
	{
		int rr=rand()%randomGenerator;
		int x=randomArray[rr];

		int max_weight=0;
		int max_id;
		int y=old_graph[x].size();
		for(int i=0;i<y;i++)
		{
			if(revrandomArray[old_graph[x][i].x]<randomGenerator && old_graph[x][i].second>max_weight){
				max_id=old_graph[x][i].first;
				max_weight=old_graph[x][i].second;
			}
		}
		randomGenerator--;
		swap(revrandomArray[x],revrandomArray[randomArray[randomGenerator]]);
		swap(randomArray[rr],randomArray[randomGenerator]);
		// revrandomArray[randomArray[rr]]=rr;
		// revrandomArray[x]=randomGenerator;

		if(max_weight==0){
			vector<int> a;
			a.pb(x);
			new_vector_set.pb(a),
			mapping[x]=map_counter++;
			new_vertex_weight.pb(old_vertex_weight[x]);
			continue;
		}
		randomGenerator--;
		int pos=revrandomArray[max_id];
		swap(revrandomArray[max_id],revrandomArray[randomArray[randomGenerator]]);
		swap(randomArray[pos],randomArray[randomGenerator]);
		// revrandomArray[randomArray[pos]]=pos;
		// revrandomArray[max_id]=randomGenerator;

		vector<int> a;
		a.pb(x);
		a.pb(max_id);
		new_vector_set.pb(a);
		mapping[x]=map_counter;
		mapping[max_id]=map_counter++;
		new_vertex_weight.pb(old_vertex_weight[x]+old_vertex_weight[max_id]);																																													
	}
	// cout<<mapping.size()<<" "<<map_counter<<endl;

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
	// cout<<"Return Coarsening"<<endl;
}
