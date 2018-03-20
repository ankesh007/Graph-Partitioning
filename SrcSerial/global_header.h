#ifndef GLOBAL_HEADER_H
#define GLOBAL_HEADER_H

#include <bits/stdc++.h>
#include <omp.h>

using namespace std;
typedef long double ld ;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;
typedef vector<vi> vvi;
typedef vector<vpi> vvpi;

#define long long long int
#define mp make_pair
#define pb push_back
#define x first
#define y second
#define THREAD_LIM 64

const int Maxn=1e7;
extern int vertices,edges,partitions;
extern vector<vi> graph;
extern int availableThreads;
extern char temp[Maxn];

void printOutput();
void coarsen(vvpi &old_graph,vvi &old_vector_set,vi &old_vertex_weight,vvpi &new_graph,vvi &new_vector_set,vi &new_vertex_weight);
void gggp(int x,vvpi  &graph,vvi  &vector_set,vi &vertex_weight,vi &partition1,vi &partition2);
void decoarsen(vvi &old_vector_set,vvpi &new_graph,vi &new_vertex_weight,vi &partition1,vi &partition2,vi &new_partition1,vi &new_partition2);
void printCoarsenedGraph(vector<vvi> vertexMapGraph,vector<vvpi> edgeMapGraph,vvi vertexWeight);



void print_pair(pair<int,int> p);
int getMoreThreads(int i);
void printOutput();
void freeThreads(int number);
void parseInput();



struct Comparator
{
	bool operator()(pii a,pii b)
	{
		if(a.x!=b.x)
			return a.x>b.x;
		return a.y>b.y;
	}
};
#endif