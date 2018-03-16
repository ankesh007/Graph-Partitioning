#include <bits/stdc++.h>
#include <omp.h>

typedef long double ld ;
using namespace std;
typedef pair<int,int> pii;
#define long long long int
#define mp make_pair
#define pb push_back
#define x first
#define y second
#define endl "\n"

const int Maxn=6e6;
   
void print_pair(pair<int,int> p)
{
	cout<<p.x<<" "<<p.y<<endl;
}

vector<vector<pii > >  graph;
int vertices,edges;
int partitions;
char temp[Maxn];

void printOutput()
{
	cout<<vertices<<" "<<edges<<endl;
	for(int i=1;i<=vertices;i++)
	{
		int lim=graph[i].size();
		for(int j=0;j<lim;j++)
			cout<<" "<<graph[i][j].x;
		cout<<endl;
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
			graph[i].pb({neighbour,1});
		}
	}
}

void naiveSolution()
{
	int counter=0;
	for(int i=1;i<=vertices;i++)
	{
		cout<<counter<<" ";
		counter++;
		counter%=partitions;
	}
	cout<<endl;
}

int main(int argc,char **argv)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);
	partitions=atoi(argv[3]);	
	parseInput();
	naiveSolution();
	// printOutput();
}