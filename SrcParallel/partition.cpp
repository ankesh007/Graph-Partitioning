#include "global_header.h"
   
int ITERATIONS=50;
int VERTEX_SET_SIZE=100;
int RANDOM_ITERATIONS=10;

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

void constructGraph(vvi &vertexMapGraph,vi &vertexWeight,vvi &newvertexMapGraph,vi &newvertexWeight,vpi &pairList,vi &componentNo,int s)
{
	cout<<"Hi"<<endl;

	for(auto itr:pairList)
	{
		cout<<itr.x<<" "<<itr.y<<endl;
		newvertexMapGraph[s].pb(itr.x);
		newvertexWeight[s]+=vertexWeight[itr.x];
		componentNo[itr.x]=s;
		if(itr.y!=-1)
		{
			newvertexMapGraph[s].pb(itr.y);
			newvertexWeight[s]+=vertexWeight[itr.y];
			componentNo[itr.y]=s;			
		}
		s++;		
	}
}

void condenseEdges(vi &componentNo,vvpi &newedgeMapGraph,vvpi &oldedgeMapGraph,vpi &pairList)
{
	map<pii,int> mapp;
	for(auto itr:pairList)
	{
		for(auto itr2:oldedgeMapGraph[itr.x])
		{
			mapp[{componentNo[itr.x],componentNo[itr2.x]}]+=itr2.y;		
		}
		if(itr.y==-1)
			continue;
		for(auto itr2:oldedgeMapGraph[itr.y])
		{
			mapp[{componentNo[itr.y],componentNo[itr2.x]}]+=itr2.y;		
		}
	}
	for(auto itr:mapp)
	{
		newedgeMapGraph[itr.x.x].pb({itr.x.y,itr.y});
	}
}

void EquiPartition(vi &vertex_set,int processors,vvi &finalPartition)
{
	
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
	vi componentNo(set_size,-1);

	map<int,int> m;
	vi revMap(set_size,0);

	for(int i=0;i<set_size;i++)
	{
		vertexMapGraph[0][i].pb(vertex_set[i]);
		m[vertex_set[i]]=i;
		revMap[i]=vertex_set[i];
	}

	int whichIsLess=min(set_size,processors);
	int root_proc=whichIsLess;

	#pragma omp parallel for num_threads(whichIsLess)
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

	cout<<"coarsening"<<endl;

	int k=0;
	while(k<ITERATIONS && vertexMapGraph[k].size()>VERTEX_SET_SIZE)
	{
		k=k+1;
		edgeMapGraph.resize(k+1);
		vertexMapGraph.resize(k+1);
		vertexWeight.resize(k+1);
		cout<<k<<endl;

		int foronethread=(set_size+root_proc-1)/root_proc;
		vector<vector<pair<int,int> > > pairList;
		pairList.resize(processors);
		vector<int> numbers(root_proc+1,0);
		
		#pragma omp parallel for num_threads(root_proc)
		for(int i=0;i<root_proc;i++)
		{
			int s=i*foronethread;
			int e=min((i+1)*foronethread,set_size);
			coarsen(edgeMapGraph[k-1],s,e,pairList[i]);
		}
		cout<<"AfterCoarsen"<<endl;
		numbers[0]=0;
		for(int i=1;i<=root_proc;i++)
			numbers[i]=numbers[i-1]+((int)pairList[i-1].size());
		// for(int i=1;i<=root_proc;i++)
		// 	cout<<numbers[i]<<"balleballe";
		// cout<<endl;


		cout<<"Hi"<<endl;
		cout<<numbers[root_proc]<<endl;
		vertexMapGraph[k].resize(numbers[root_proc]);
		cout<<"UOO"<<endl;
		vertexWeight[k].resize(numbers[root_proc]);

		#pragma omp parallel for num_threads(root_proc)
		for(int i=0;i<root_proc;i++)
		{
			cout<<i<<endl;
			constructGraph(vertexMapGraph[k-1],vertexWeight[k-1],vertexMapGraph[k],vertexWeight[k],pairList[i],componentNo,numbers[i]);
		}
		cout<<"After constructGraph"<<endl;

		edgeMapGraph[k].resize(numbers[root_proc]);

		#pragma omp parallel for num_threads(root_proc)
		for(int i=0;i<root_proc;i++)
		{
			cout<<i<<endl;
			condenseEdges(componentNo,edgeMapGraph[k],edgeMapGraph[k-1],pairList[i]);
		}		
	}
	vi partition1;
	vi partition2;

	int vert=vertexMapGraph[k].size();
	int random_node=rand()%vert;

	gggp(random_node,edgeMapGraph[k],vertexMapGraph[k],vertexWeight[k],partition1,partition2);

	cout<<"****UnCoarsening*****"<<endl;
	for(int i=k-1;i>=0;i--)
	{
		// cout<<i<<endl;
		vi newPartition1,newPartition2;
		decoarsen(vertexMapGraph[i+1],edgeMapGraph[i],vertexWeight[i],partition1,partition2,newPartition1,newPartition2);
		partition1=newPartition1;
		partition2=newPartition2;
	}
	cout<<"Hi"<<endl;

	int ss=vertexMapGraph[0].size();
	int x1=partition1.size();
	int x2=partition2.size();

	finalPartition.resize(2);
	finalPartition[0].resize(x1);
	finalPartition[1].resize(x2);
	cout<<"Wtf"<<endl;

	#pragma omp parallel for num_threads(whichIsLess)
	for(int i=0;i<set_size;i++)
	{
		if(i<x1)
			finalPartition[0][i]=revMap[partition1[i]];
		else
			finalPartition[1][i-x1]=revMap[partition2[i-x1]];
	}
}

void solver(vi &vertex_set,int s,int e,vvi &finalPartitionList,int numbPartitions)
{
	if(s==e)
	{
		finalPartitionList[s]=vertex_set;
		return;
	}

	vvi temp_partition;
	cout<<"Enter EquiPartition"<<endl;
	EquiPartition(vertex_set,numbPartitions,temp_partition);
	cout<<"End EquiPartition"<<endl;

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