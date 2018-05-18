#include "global_header.h"
   
int ITERATIONS=0;
int VERTEX_SET_SIZE=100;
int RANDOM_ITERATIONS=1;
int globalPartition[20][1000100];
char temp[Maxn];
int gain[20][1000100];
int matching[20][1000100];

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

void EquiPartition(vi &vertex_set,vvi &finalPartition,int curNo,int depth)
{
	// vertexMapGraph.resize(1);
	// edgeMapGraph.resize(1);
	// vertexWeight.resize(1);

	// vertexWeight[0].resize(set_size,1);
	// edgeMapGraph[0].resize(set_size);
	// vertexMapGraph[0].resize(set_size);

	// map<int,int> m;
	// vi revMap(set_size,0);

	// for(int i=0;i<set_size;i++)
	// {
	// 	vertexMapGraph[0][i].pb(vertex_set[i]);
	// 	m[vertex_set[i]]=i;
	// 	revMap[i]=vertex_set[i];
	// }

	// for(int i=0;i<set_size;i++)
	// {
	// 	for(auto itr:graph[vertex_set[i]])
	// 	{
	// 		if(m.find(itr)==m.end())
	// 			continue;
	// 		int neighbour=m[itr];
	// 		edgeMapGraph[0][i].pb({neighbour,1});
	// 	}
	// }

	// double start=clock();

		// int k=0;
		// // cout<<"****Coarsening*****"<<endl;
		// while(k<ITERATIONS && vertexMapGraph[k].size()>VERTEX_SET_SIZE)
		// {
		// 	k=k+1;
		// 	edgeMapGraph.resize(k+1);
		// 	vertexMapGraph.resize(k+1);
		// 	vertexWeight.resize(k+1);
		// 	coarsen(edgeMapGraph[k-1],vertexMapGraph[k-1],vertexWeight[k-1],edgeMapGraph[k],vertexMapGraph[k],vertexWeight[k]);
		// }

		// double endd=clock();
		// cout<<"Coarsening"<<(endd-start)/CLOCKS_PER_SEC<<endl;
		// start=endd;

		int vert=vertex_set.size();
		int random_node=rand()%vert;
		random_node=vertex_set[random_node];

		finalPartition.resize(2);
		gggp2(random_node,vertex_set,finalPartition[0],finalPartition[1],curNo,depth);
		// endd=clock();
		// cout<<"GGGP"<<(endd-start)/CLOCKS_PER_SEC<<endl;
		// start=endd;

		// cout<<"****UnCoarsening*****"<<endl;
		// for(int i=k-1;i>=0;i--)
		// {
		// 	// cout<<i<<endl;
		// 	vi newPartition1,newPartition2;
		// 	decoarsen(vertexMapGraph[i+1],edgeMapGraph[i],vertexWeight[i],partition1,partition2,newPartition1,newPartition2);
		// 	partition1=newPartition1;
		// 	partition2=newPartition2;
		// }
		// endd=clock();
		// cout<<"decoarsen"<<(endd-start)/CLOCKS_PER_SEC<<endl;
		// start=endd;

		// int ss=vertexMapGraph[0].size();
		// vi myPartition(ss,0);
		// for(int ii=0;ii<partition2.size();ii++)
		// {
		// 	myPartition[partition2[ii]]=1;
		// }

	// for(int i=0;i<partition1.size();i++)
	// 	partition1[i]=revMap[partition1[i]];
	// for(int i=0;i<partition2.size();i++)
	// 	partition2[i]=revMap[partition2[i]];	
	// finalPartition.pb(partition1);
	// finalPartition.pb(partition2);

}

void solver(vi &vertex_set,int s,int e,vvi &finalPartitionList,int numProcessors,int depth,int a,int b,int curNo)
{
	if(s==e)
	{
		finalPartitionList[s]=vertex_set;
		return;
	}

	vvi temp_partition(2);
	// cout<<"Enter EquiPartition"<<endl;
	EquiPartition(vertex_set,temp_partition,curNo,depth);
	// cout<<"End EquiPartition"<<endl;

	if(temp_partition.size()<2)
	{
		cout<<"Partitions not a Power of 2"<<endl;
		exit(0);
	}

	int mid=(s+e)>>1;
	int open=1+(numProcessors>1);
	int refineP=max(1,(numProcessors>>1));
	depth++;

	for(auto itr:temp_partition[0])
		globalPartition[depth][itr]=a;
	for(auto itr:temp_partition[1])
		globalPartition[depth][itr]=b;

	#pragma omp parallel sections num_threads(open)
	{
		#pragma omp section
			solver(temp_partition[0],s,mid,finalPartitionList,refineP,depth,2*a+1,2*a+2,a);
		#pragma omp section
			solver(temp_partition[1],mid+1,e,finalPartitionList,refineP,depth,2*b+1,2*b+2,b);			
	}
	// cout<<"Exit Parallel"<<endl;
}

int partition_numb[1000010];

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
	double start=clock();

	parseInput();
	double e=clock();
	cout<<"Coarsening"<<(e-start)/CLOCKS_PER_SEC<<endl;
	cout<<"Hi"<<endl;
	start=e;
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
	solver(vertex_set,0,partitions-1,partitioned_graph,availableThreads,0,1,2,0);
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