#include "global_header.h"
   
int ITERATIONS=100;
int VERTEX_SET_SIZE=1;

void print_pair(pair<int,int> p)
{
	cout<<p.x<<" "<<p.y<<endl;
}

char temp[Maxn];

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

vvi EquiPartition(vi &vertex_set)
{
	vvi hey;
	vector<vvi> vertexMapGraph;
	vector<vvpi> edgeMapGraph;
	vvi vertexWeight;

	int set_size=vertex_set.size();
	vvi tempVertexGraph;
	vvpi tempEdgeGraph;

	vi tempVertexCount(set_size,1);
	tempVertexGraph.resize(set_size);
	tempEdgeGraph.resize(set_size);

	map<int,int> m;

	for(int i=0;i<set_size;i++)
	{
		tempVertexGraph[i].pb(vertex_set[i]);
		m[vertex_set[i]]=i;
	}

	for(int i=0;i<set_size;i++)
	{
		for(auto itr:graph[vertex_set[i]])
		{
			if(m.find(itr)==m.end())
				continue;
			int neighbour=m[itr];
			tempEdgeGraph[i].pb({neighbour,1});
		}
	}

	vertexMapGraph.pb(tempVertexGraph);
	edgeMapGraph.pb(tempEdgeGraph);
	vertexWeight.pb(tempVertexCount);

	int k=0;

	while(k<ITERATIONS && vertexMapGraph[k].size()>VERTEX_SET_SIZE)
	{
		k=k+1;
		tempVertexGraph.resize(0);
		tempEdgeGraph.resize(0);
		tempVertexCount.resize(0);
		coarsen(edgeMapGraph[k-1],vertexMapGraph[k-1],vertexWeight[k-1],tempEdgeGraph,tempVertexGraph,tempVertexCount);
		vertexMapGraph.pb(tempVertexGraph);
		edgeMapGraph.pb(tempEdgeGraph);
		vertexWeight.pb(tempVertexCount);
	}
	int kk=k;
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
	return hey;
}

vvi solver(vi &vertex_set,int toPartition)
{
	if(toPartition==1)
	{
		vvi ans;
		ans.pb(vertex_set);
		return ans;
	}

	vvi temp_partition;
	temp_partition=EquiPartition(vertex_set);
	vvi smallerPartition1,smallerPartition2;

	if(temp_partition.size()<2)
	{
		// cout<<temp_partition.size()<<endl;
		return temp_partition;
	}

	#pragma omp parallel
	{
		#pragma omp single nowait
			smallerPartition2=solver(temp_partition[0],(toPartition>>1));
		#pragma omp single nowait
			smallerPartition1=solver(temp_partition[1],(toPartition>>1));			
	}

	for(auto itr:smallerPartition2)
		smallerPartition1.pb(itr);
	return smallerPartition1;
}

int main(int argc,char **argv)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	freopen(argv[1],"r",stdin);
	// freopen(argv[2],"w",stdout);
	partitions=atoi(argv[3]);	
	parseInput();
	// naiveSolution();
	// return 0;
	vi vertex_set;
	vertex_set.resize(vertices);
	for(int i=1;i<=vertices;i++)
		vertex_set[i-1]=i;

	vvi partitioned_graph;
	partitioned_graph=solver(vertex_set,partitions);
}