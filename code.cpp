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

   
void print_pair(pair<int,int> p)
{
	cout<<p.x<<" "<<p.y<<endl;
}

vector<vector<pii > >  graph;

int main(int argc,char **argv)
{
	freopen(argv[1],"r",stdin);
	// freopen(argv[2],"w",stdout);
	
	int vertices,edges;
	
	scanf("%d %d",&vertices,&edges);
	graph.resize(vertices+1);
	printf("%d %d\n",vertices,edges);
	

	for(int i=1;i<=vertices;i++){
		char *s;
		fgets(s,vertices*6,stdin);
		std::stringstream stream(s);
		printf("%d\n",i);
		while(1) {
			int neighbour;
			stream >> neighbour;
			if(!stream)
				break;
			graph[i].pb({neighbour,1});
			// printf("%d \n",neighbour);
		}
		printf("\n");
	} 
}
