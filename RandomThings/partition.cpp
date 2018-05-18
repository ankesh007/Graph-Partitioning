#include "global_header.h"
   
int ITERATIONS=100;
int VERTEX_SET_SIZE=100;
int RANDOM_ITERATIONS=1;

char temp[Maxn];

void naiveSolution(ofstream &myfile)
{
	int counter=0;
	for(int i=1;i<=vertices;i++)
	{
		myfile<<counter<<" ";
		counter++;
		counter%=partitions;
	}
	myfile<<endl;
	myfile.close();
}

vvi EquiPartition(vi &vertex_set)
{
	vvi finalPartition;
	vector<vvi> vertexMapGraph;
	vector<vvpi> edgeMapGraph;
	vvi vertexWeight;

	int set_size=vertex_set.size();
	vertexMapGraph.resize(1);
	edgeMapGraph.resize(1);
	vertexWeight.resize(1);

	vertexWeight[0].resize(set_size,1);
	edgeMapGraph[0].resize(set_size);
	vertexMapGraph[0].resize(set_size);

	map<int,int> m;
	vi revMap(set_size,0);

	for(int i=0;i<set_size;i++)
	{
		vertexMapGraph[0][i].pb(vertex_set[i]);
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
			edgeMapGraph[0][i].pb({neighbour,1});
		}
	}

		int k=0;
		// cout<<"****Coarsening*****"<<endl;
		while(k<ITERATIONS && vertexMapGraph[k].size()>VERTEX_SET_SIZE)
		{
			k=k+1;
			edgeMapGraph.resize(k+1);
			vertexMapGraph.resize(k+1);
			vertexWeight.resize(k+1);
			coarsen(edgeMapGraph[k-1],vertexMapGraph[k-1],vertexWeight[k-1],edgeMapGraph[k],vertexMapGraph[k],vertexWeight[k]);
		}
		vi partition1;
		vi partition2;

		int vert=vertexMapGraph[k].size();
		int random_node=rand()%vert;

		gggp(random_node,edgeMapGraph[k],vertexMapGraph[k],vertexWeight[k],partition1,partition2);

		// cout<<"****UnCoarsening*****"<<endl;
		for(int i=k-1;i>=0;i--)
		{
			// cout<<i<<endl;
			vi newPartition1,newPartition2;
			decoarsen(vertexMapGraph[i+1],edgeMapGraph[i],vertexWeight[i],partition1,partition2,newPartition1,newPartition2);
			partition1=newPartition1;
			partition2=newPartition2;
		}

	for(int i=0;i<partition1.size();i++)
		partition1[i]=revMap[partition1[i]];
	for(int i=0;i<partition2.size();i++)
		partition2[i]=revMap[partition2[i]];	
	finalPartition.pb(partition1);
	finalPartition.pb(partition2);

	return finalPartition;
}

void solver(vi &vertex_set,int s,int e,vvi &finalPartitionList,int numbPartitions)
{
	if(s==e)
	{
		finalPartitionList[s]=vertex_set;
		return;
	}

	vvi temp_partition;
	// cout<<"Enter EquiPartition"<<endl;
	temp_partition=EquiPartition(vertex_set);
	// cout<<"End EquiPartition"<<endl;
	vvi smallerPartition1,smallerPartition2;

	if(temp_partition.size()<2)
	{
		cout<<"Partitions not a Power of 2"<<endl;
		exit(0);
	}

	int mid=(s+e)>>1;
	int open=1+(numbPartitions>1);
	int refineP=max(1,(numbPartitions>>1));
	#pragma omp parallel sections num_threads(open)
	{
		#pragma omp section
			solver(temp_partition[0],s,mid,finalPartitionList,refineP);
		#pragma omp section
			solver(temp_partition[1],mid+1,e,finalPartitionList,refineP);			
	}
	// cout<<"Exit Parallel"<<endl;
}

int main(int argc,char **argv)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	srand(time(NULL));
	omp_set_nested(1);
	FILE* _=freopen(argv[1],"r",stdin);
	ofstream myfile;
	myfile.open(argv[2]);
	// freopen(argv[2],"w",stdout);
	partitions=atoi(argv[3]);	
	if((partitions&(partitions-1)))
	{
		cout<<"Number of Partitions not a Power of 2"<<endl;
		return 0;
	}
	parseInput();
	// cout<<"Parsed Input"<<endl;
	// naiveSolution(myfile);
	// return 0;
	vi vertex_set;
	vertex_set.resize(vertices);
	for(int i=1;i<=vertices;i++)
		vertex_set[i-1]=i;

	vvi partitioned_graph;
	partitioned_graph.resize(partitions);
	// cout<<"Enter Solver"<<endl;
	solver(vertex_set,0,partitions-1,partitioned_graph,availableThreads);
	vi partition_numb(vertices+1,0);
	// cout<<"Partitioned"<<endl;
	int x=partitions;

	for(int i=0;i<x;i++)
	{
		for(auto itr2:partitioned_graph[i])
		{
			partition_numb[itr2]=i;
			// cout<<itr2<<" ";
		}
			// cout<<partitioned_graph[i].size()<<" ";
		// cout<<endl;
	}
	for(int i=1;i<=vertices;i++)
		myfile<<partition_numb[i]<<" ";
	myfile<<endl;
	myfile.close();
}