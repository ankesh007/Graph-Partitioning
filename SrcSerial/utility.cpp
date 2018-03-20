#include "global_header.h"

void print_pair(pair<int,int> p)
{
	cout<<p.x<<" "<<p.y<<endl;
}

void printOutput()
{
	cout<<vertices<<" "<<edges<<endl;
	for(int i=1;i<=vertices;i++)
	{
		int lim=graph[i].size();
		for(int j=0;j<lim;j++)
			cout<<" "<<graph[i][j];
		cout<<endl;
	}
}

int getMoreThreads(int requested)
{
	int sendThreads=0;
	#pragma omp critical
	{
		sendThreads=min(availableThreads,requested);
		availableThreads-=sendThreads;
	}
	return sendThreads;
}

void freeThreads(int number)
{
	#pragma omp critical
	{
		availableThreads+=number;
	}
}

void parseInput()
{
	cin>>vertices>>edges;
	graph.resize(vertices+1);
	cin.getline(temp,sizeof(temp));

	for(int i=1;i<=vertices;i++){
		cin.getline(temp,sizeof(temp));
		std::stringstream stream(temp);
		int neighbour;
		while(stream>>neighbour) {
			graph[i].pb(neighbour);
		}
	}
}
