#include "global_header.h"
   
int ITERATIONS=100;
int VERTEX_SET_SIZE=100;

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

int getMoreThreads(int requested)
{
	int sendThreads=0;
	#pragma omp critical
	{
		sendThreads=min(availableThreads,requested);
		availableThreads-=sendThreads;
	}
	return sendThreads;
}

void freeThreads(int number)
{
	#pragma omp critical
	{
		availableThreads+=number;
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
	// vvi tempVertexGraph;
	// vvpi tempEdgeGraph;

	// vi tempVertexCount(set_size,1);
	vertexWeight[0].resize(set_size,1);
	edgeMapGraph[0].resize(set_size);
	vertexMapGraph[0].resize(set_size);
	// tempVertexGraph.resize(set_size);
	// tempEdgeGraph.resize(set_size);

	map<int,int> m;
	vi revMap(set_size,0);

	for(int i=0;i<set_size;i++)
	{
		// tempVertexGraph[i].pb(vertex_set[i]);
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
			// tempEdgeGraph[i].pb({neighbour,1});
		}
	}

	// vertexMapGraph.pb(tempVertexGraph);
	// edgeMapGraph.pb(tempEdgeGraph);
	// vertexWeight.pb(tempVertexCount);
	vi partition1_best;
	vi partition2_best;
	int min_cost=-1;
	// int cost=0;
	for (int s=0;s<10;s++)
	{	
	int k=0;
	edgeMapGraph.resize(k+1);
	vertexMapGraph.resize(k+1);
	vertexWeight.resize(k+1);
	// cout<<"****Coarsening*****"<<endl;
	while(k<ITERATIONS && vertexMapGraph[k].size()>VERTEX_SET_SIZE)
	{
		k=k+1;
		edgeMapGraph.resize(k+1);
		vertexMapGraph.resize(k+1);
		vertexWeight.resize(k+1);
		// tempVertexGraph.resize(0);
		// tempEdgeGraph.resize(0);
		// tempVertexCount.resize(0);
		coarsen(edgeMapGraph[k-1],vertexMapGraph[k-1],vertexWeight[k-1],edgeMapGraph[k],vertexMapGraph[k],vertexWeight[k]);
		// vertexMapGraph.pb(tempVertexGraph);
		// edgeMapGraph.pb(tempEdgeGraph);
		// vertexWeight.pb(tempVertexCount);
		// cout<<k<<" "<<vertexMapGraph[k].size()<<endl;
	}
	// int best_index=0;
	
		
		vi partition1;
		vi partition2;
		int s1=vertexMapGraph[k].size();
		int x=rand()%(s1);
		// cout<<x<<"Vertex"<<endl;
		gggp(x,edgeMapGraph[k],vertexMapGraph[k],vertexWeight[k],partition1,partition2);
		for(int i=k-1;i>=0;i--)
		{
			// cout<<i<<endl;
			vi newPartition1,newPartition2;
			decoarsen(vertexMapGraph[i+1],edgeMapGraph[i],vertexWeight[i],partition1,partition2,newPartition1,newPartition2);
			partition1=newPartition1;
			partition2=newPartition2;
		}
		
		int ss=vertexMapGraph[0].size();
		vi myPartition(ss,0);
		for(int ii=0;ii<partition2.size();ii++)
		{
			myPartition[partition2[ii]]=1;
		}
		int cost=0;
		for(int pi=0;pi<ss;pi++)
		{
			for(auto itr:edgeMapGraph[0][pi])
			{
				if(myPartition[itr.x]!=myPartition[pi])
					cost++;
			}
		}
		cout<<(cost/2)<<endl;
		if(min_cost==-1){
			min_cost=cost;
			partition1_best=partition1;
			partition2_best=partition2;
		}
		if(cost<min_cost){
			min_cost=cost;
			partition1_best=partition1;
			partition2_best=partition2;
		}

	}
	// int min_cost=0;
	// int cost=0;
	// for(int ii=0;ii<5;ii++)
	// {
	// 	for(int i=1;i<=vertices;i++)
	// 	{
	// 		for(auto itr:graph[i])
	// 		{
	// 			if(myPartition[itr.x]!=myPartition[i])
	// 				cost++;
	// 		}
	// 	}
	// 	if(min_cost==0){
	// 		min_cost=cost;
	// 	}
	// 	if(cost<min_cost)
	// }
	// for(int k=0;k<partition1;k++)
	// cout<<"****UnCoarsening*****"<<endl;
	
	// for(auto itr:finalPartition)
	// {
	// 	for(auto itr2:itr)
	// 		cout<<itr2<<" ";
	// 	cout<<endl;
	// }
	for(int i=0;i<partition1_best.size();i++)
		partition1_best[i]=revMap[partition1_best[i]];
	for(int i=0;i<partition2_best.size();i++)
		partition2_best[i]=revMap[partition2_best[i]];	
	finalPartition.pb(partition1_best);
	finalPartition.pb(partition2_best);
	return finalPartition;
}

void solver(vi &vertex_set,int s,int e,vvi &finalPartitionList)
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
	int response=getMoreThreads(1);
	#pragma omp parallel num_threads(1+response)
	{
		#pragma omp single nowait
			solver(temp_partition[0],s,mid,finalPartitionList);
		#pragma omp single nowait
			solver(temp_partition[1],mid+1,e,finalPartitionList);			
	}
	if(response)
		freeThreads(response);
	// cout<<"Exit Parallel"<<endl;
}

int main(int argc,char **argv)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	srand(time(NULL));
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
	solver(vertex_set,0,partitions-1,partitioned_graph);
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