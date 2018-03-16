#ifndef GLOBAL_HEADER_H
#define GLOBAL_HEADER_H

#include <bits/stdc++.h>
#include <omp.h>

using namespace std;
typedef long double ld ;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;

#define long long long int
#define mp make_pair
#define pb push_back
#define x first
#define y second
#define endl "\n"

const int Maxn=6e6;
extern int vertices,edges,partitions;
extern vector<vi> graph;

void print_pair(pair<int,int> p);
void printOutput();
#endif