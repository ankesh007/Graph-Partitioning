#include "global_header.h"
   
int ITERATIONS=100;
int VERTEX_SET_SIZE=2;

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
	vvi finalPartition;
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
	vi revMap(set_size,0);

	for(int i=0;i<set_size;i++)
	{
		tempVertexGraph[i].pb(vertex_set[i]);
		m[vertex_set[i]]=i;
		revMap[i]=vertex_set[i];
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
	vi partition1;
	vi partition2;

	gggp(edgeMapGraph[k],vertexMapGraph[k],vertexWeight[k],partition1,partition2);
	// for(int i=0;i<partition1.size();i++)
	// {
	// 	cout<<partition1[i]<<" ";
	// }
	// cout<<endl;
	// for(int i=0;i<partition2.size();i++)
	// {
	// 	cout<<partition2[i]<<" ";
	// }
	// cout<<endl;
	// printCoarsenedGraph(vertexMapGraph,edgeMapGraph,vertexWeight);
	// cout<<"Hi After GGGP"<<endl;

	for(int i=k-1;i>=0;i--)
	{
		vi newPartition1,newPartition2;
		decoarsen(vertexMapGraph[i+1],edgeMapGraph[i],vertexWeight[i],partition1,partition2,newPartition1,newPartition2);
		// cout<<i<<endl;
		// return finalPartition;
		partition1=newPartition1;
		partition2=newPartition2;
	}
	for(int i=0;i<partition1.size();i++)
		partition1[i]=revMap[partition1[i]];
	for(int i=0;i<partition2.size();i++)
		partition2[i]=revMap[partition2[i]];	
	finalPartition.pb(partition1);
	finalPartition.pb(partition2);
	// for(auto itr:finalPartition)
	// {
	// 	for(auto itr2:itr)
	// 		cout<<itr2<<" ";
	// 	cout<<endl;
	// }
	return finalPartition;
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
	// cout<<"Enter EquiPartition"<<endl;
	temp_partition=EquiPartition(vertex_set);
	// cout<<"End EquiPartition"<<endl;
	vvi smallerPartition1,smallerPartition2;

	if(temp_partition.size()<2)
	{
		return temp_partition;
	}

	// for(auto itr:temp_partition)
	// {
	// 	for(auto itr2:itr)
	// 		cout<<itr2<<" ";
	// 	cout<<endl;
	// }
	// cout<<"Before"<<endl;
	// omp_set_numthreads(1);

	#pragma omp parallel num_threads(2)
	{
		#pragma omp single nowait
			smallerPartition2=solver(temp_partition[0],(toPartition>>1));
		#pragma omp single nowait
			smallerPartition1=solver(temp_partition[1],(toPartition>>1));			
	}

	for(auto itr:smallerPartition2)
		smallerPartition1.pb(itr);
	// for(auto itr:smallerPartition1)
	// {
	// 	for(auto itr2:itr)
	// 		cout<<itr2<<" ";
	// 	cout<<endl;
	// }
	return smallerPartition1;
}

int main(int argc,char **argv)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);
	partitions=atoi(argv[3]);	
	parseInput();
	// cout<<"Parsed Input"<<endl;
	// naiveSolution();
	// return 0;
	vi vertex_set;
	vertex_set.resize(vertices);
	for(int i=1;i<=vertices;i++)
		vertex_set[i-1]=i;

	vvi partitioned_graph;
	// cout<<"Enter Solver"<<endl;
	partitioned_graph=solver(vertex_set,partitions);
	vi partition_numb(vertices,0);
	int x=partitioned_graph.size();

	for(int i=0;i<x;i++)
	{
		for(auto itr2:partitioned_graph[i])
		{
			partition_numb[itr2]=i;
			
		}
			// cout<<itr2<<" ";
		// cout<<endl;
	}
	for(int i=0;i<vertices;i++)
		cout<<partition_numb[i]<<" ";
	cout<<endl;
}