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

const int Maxn=1e7;
extern int vertices,edges,partitions;
extern vector<vi> graph;

void print_pair(pair<int,int> p);
void printOutput();
void coarsen(vvpi &old_graph,vvi &old_vector_set,vi &old_vertex_weight,vvpi &new_graph,vvi &new_vector_set,vi &new_vertex_weight);
void gggp(vvpi  &graph,vvi  &vector_set,vi &vertex_weight,vi &partition1,vi &partition2);
void decoarsen(vvi &old_vector_set,vvpi &new_graph,vi &new_vertex_weight,vi &partition1,vi &partition2,vi &new_partition1,vi &new_partition2);
void printCoarsenedGraph(vector<vvi> vertexMapGraph,vector<vvpi> edgeMapGraph,vvi vertexWeight);
#endif