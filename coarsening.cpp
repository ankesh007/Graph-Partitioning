#include "global_header.h"
// vector<vector<int>>  vector_set;
int p=16;
void coarsen(vector<vector<pii > >  old_graph,vector < vector<int> >  old_vector_set,vector<vector<pii > >  new_graph,vector < vector<int> >  new_vector_set)
{
	vector<int>  matching(old_graph.size(),0);
	int s=old_graph.size();
	vector<int>  mapping(old_graph.size(),0);
	while(s>0)
	{
		int x;
		do
		{
			x=rand()%(old_graph.size());
		}while(matching[x]==1);
		int max_weight=0;
		int max_index=0;
		int max_id;
		for(int i=0;i<old_graph[x].size();i++)
		{
			if(matching[old_graph[x][i].first]==0 and old_graph[x][i].second>max_weight){
				max_id=old_graph[x][i].first;
				max_weight=old_graph[x][i].second;
			}
		}
		if(max_weight==0){
			vector<int> a;
			a.pb(x);
			new_vector_set.pb(a),
			mapping[x]=new_vector_set.size();
			matching[x]=1;
			s=s-1;
			continue;
		}
		vector<int> a;
		matching[x]=1;
		matching[max_id]=1;
		a.pb(x);
		a.pb(max_id);
		new_vector_set.pb(a);
		mapping[x]=new_vector_set.size();
		mapping[max_id]=new_vector_set.size();
		s=s-2;
		// for(int i=0;i<graph[max_id-1].size();i++)
		// {
		// 	int id=graph[max_id-1][i].first;
		// 	int weight=graph[max_id-1][i].second;
		// 	int found=0;
		// 	for(int i1=0;i1<graph[id-1].size();i1++)
		// 	{
		// 		if(graph[id-1][i1].first==x)
		// 		{
		// 			found=1;
		// 			graph[id-1][i1].second+=weight;
		// 		}
		// 		if(graph[id-1][i1].first==max_id-1)
		// 		{
		// 			// found=1;
		// 			graph[id-1].erase(graph[id-1].begin()+i1);
		// 			i1=i1-1;
		// 		}
		// 	}
		// 	if(found==0){
		// 		graph[id-1][graph[id-1].size()].first=x;
		// 		graph[id-1][graph[id-1].size()].second=weight;
		// 	}
		// }

		// graph.erase(graph.begin()+max_id-1);
		// matching.erase(matching.begin()+max_id-1);
		// s=s-2;
	}
	new_graph.resize(new_vector_set.size());
	for(int i=0;i<old_graph.size();i++)
	{
		for (int j=0;j<old_graph[i].size();j++)
		{
			if(matching[i]!=matching[j]){
				int found=0;
				int ur=new_graph[matching[i]].size();
				for(int i1=0;i1<ur;i++)
				{
					if(new_graph[matching[i]][i1].first==matching[j])
					{
						found=1;
						new_graph[matching[i]][i1].second+=old_graph[i][j].second;
					}
				}
				if(found==0)
				{
					new_graph[matching[i]][ur].first=matching[j];
					new_graph[matching[i]][ur].second=old_graph[i][j].second;
				}
			}
		}
	}
}
// int main()
// {
// 	omp_set_num_threads(p);
// 	omp_set_nested(1);

// 	int p1=sqrt(p);
// 	int subgraph_length=graph.size()/p1;

// 	// for (int q=0;q<p1;q++){
// 	// 	for (int i=q*subgraph_length;i<(q+1)*subgraph_length;i++)
// 	// 	{

// 	// 	}
// 	// }
// 	vector<vector<vector<pii > >>  graph_set;
// 	vector< vector < vector<int> > >  vector_set;
// 	int count=0;
// 	while(graph.size()>100)
// 	{
// 		graph_set[count]=graph;
// 		count=count+1;
// 		vector<int>  matching(graph.size(),0);
// 		int s=graph.size();
// 		while(s>0){
// 			int x;
// 			do{
// 				x=rand()%(graph.size());
// 			}while(matching[x]==1);
// 			int max_weight=0;
// 			int max_index=0;
// 			int max_id;
// 			for(int i=0;i<graph[x].size();i++)
// 			{
// 				if(matching[graph[x][i].first]==0 and graph[x][i].second>max_weight){
// 					max_id=graph[x][i].first;
// 					max_weight=graph[x][i].second;
// 				}
// 			}
// 			if(max_weight==0){
// 				matching[x]=1;
// 				s=s-1;
// 				continue;
// 			}
// 			for(int i=0;i<graph[max_id-1].size();i++)
// 			{
// 				int id=graph[max_id-1][i].first;
// 				int weight=graph[max_id-1][i].second;
// 				int found=0;
// 				for(int i1=0;i1<graph[id-1].size();i1++)
// 				{
// 					if(graph[id-1][i1].first==x)
// 					{
// 						found=1;
// 						graph[id-1][i1].second+=weight;
// 					}
// 					if(graph[id-1][i1].first==max_id-1)
// 					{
// 						// found=1;
// 						graph[id-1].erase(graph[id-1].begin()+i1);
// 						i1=i1-1;
// 					}
// 				}
// 				if(found==0){
// 					graph[id-1][graph[id-1].size()].first=x;
// 					graph[id-1][graph[id-1].size()].second=weight;
// 				}
// 			}

// 			graph.erase(graph.begin()+max_id-1);
// 			matching.erase(matching.begin()+max_id-1);
// 			s=s-2;
// 		}
// 	}
// 	// #pragma omp parallel
// 	// {
// 	// 	int id=omp_get_thread_num();
// 	// 	int i=id/p1;
// 	// 	int j=id%p1;
// 	// 	if(i==j){
// 	// 		// x=rand()%subgraph_length;
// 	// 		// x=x+(i*subgraph_length);
// 	// 		// // for (int q=i*subgraph_length;q<(i+1)*subgraph_length;q++)
// 	//   // //   	{
// 	// 		// int max_id=0;
// 	// 		// int max_weight=0;
// 	//   //   	if(graph[x][q][0]>i*subgraph_length && graph[x][q][0]<
// 	//     	// }
// 	// 	}

// 	// 	cout<<i<<" "<<j<<endl;
// 	// }
// }