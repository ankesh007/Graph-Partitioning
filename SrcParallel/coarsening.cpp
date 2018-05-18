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

void coarsen(vvpi &old_graph,int starting,int ending,vpi &pairList)
{
	cout<<"Hey from Coarsening"<<endl;
	int s=ending-starting;
	int map_counter=0;
	vi randomArray(s,0);
	vi revrandomArray(s,0);
	int randomGenerator=s;
	for(int i=0;i<s;i++)
	{
		randomArray[i]=i+starting;
		revrandomArray[i]=i;//rev random array of i+starting
	}

	cout<<"Entering While"<<endl;

	while(randomGenerator>0)
	{
		int rr=rand()%randomGenerator;
		int x=randomArray[rr];

		int max_weight=0;
		int max_id;
		int y=old_graph[x].size();
		// cout<<x<<" "<<"Enter"<<endl;
		for(int i=0;i<y;i++)
		{
			if(revrandomArray[old_graph[x][i].x-starting]<randomGenerator && old_graph[x][i].second>max_weight && old_graph[x][i].x>=starting && old_graph[x][i].x<ending){
				max_id=old_graph[x][i].first;
				max_weight=old_graph[x][i].second;
			}
		}
		randomGenerator--;
		// cout<<"Before Swap"<<endl;
		swap(revrandomArray[x-starting],revrandomArray[randomArray[randomGenerator]-starting]);
		swap(randomArray[rr],randomArray[randomGenerator]);
		// cout<<x<<" "<<"1swap"<<endl;
		// revrandomArray[randomArray[rr]]=rr;
		// revrandomArray[x]=randomGenerator;

		if(max_weight==0){
			pairList.pb({x,-1});
			continue;
		}

		randomGenerator--;
		// cout<<"Mostly"<<endl;
		int pos=revrandomArray[max_id-starting];
		swap(revrandomArray[max_id-starting],revrandomArray[randomArray[randomGenerator]-starting]);
		swap(randomArray[pos],randomArray[randomGenerator]);
		pairList.pb({x,max_id});
	}
	cout<<"Return Coarsening"<<endl;
}
