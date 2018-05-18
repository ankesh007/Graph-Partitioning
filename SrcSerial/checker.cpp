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

const int Maxn=1e7;
   
void print_pair(pair<int,int> p)
{
	cout<<p.x<<" "<<p.y<<endl;
}

vector<vector<pii > >  graph;
int vertices,edges;
int partitions;
char temp[Maxn];
vector<int> partition_numb;
vector<int> myPartition;
vector<int> partitionCount;
float threshold=0.05;

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

int main(int argc,char **argv)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	freopen(argv[1],"r",stdin);
	parseInput();
	partitions=atoi(argv[3]);	

	fflush(stdin);
	ifstream open_out(argv[2]);
	string line;

	while(getline(open_out,line,'\n'))
	{
		istringstream stream(line);

		int part;
		while(stream>>part) {
			partition_numb.pb(part);
		}
	}

	if(partition_numb.size()!=vertices)
	{
		cout<<"Printed Vertex != "<<vertices<<endl;
		cout<<"Vertices Found "<<partition_numb.size()<<endl;
		return 0;
	}
	myPartition.resize(vertices+1);
	partitionCount.resize(partitions);
	int maxInPartition=0,minInPartition=1e9;

	for(int i=0;i<vertices;i++)
	{
		if(partition_numb[i]<0 || partition_numb[i]>=partitions)
		{
			cout<<"Wrong Partition No"<<endl;
			cout<<"Vertex "<<(i+1)<<" Number Given "<<partition_numb[i]<<endl;
			return 0;
		}
		myPartition[i+1]=partition_numb[i];
		partitionCount[partition_numb[i]]++;
	}

	for(int i=0;i<partitions;i++)
	{	
		maxInPartition=max(maxInPartition,partitionCount[i]);
		minInPartition=min(minInPartition,partitionCount[i]);
	}

	float diff=maxInPartition-minInPartition;
	diff=diff/vertices;

	if(diff>threshold)
	{
		cout<<"Threshold Limit breached"<<endl;
		cout<<"Your threshold = "<<diff<<endl;
		return 0;
	}

	int cost=0;

	for(int i=1;i<=vertices;i++)
	{
		for(auto itr:graph[i])
		{
			if(myPartition[itr.x]!=myPartition[i])
				cost++;
		}
	}

	cout<<"Correctness Verified"<<endl;
	cout<<"Edge Cut Cost "<<(cost/2)<<endl;
}