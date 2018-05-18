#include "global_header.h"

int IDEAL_ITERATIONS=20;
int KL_ITERATIONS=3;
float disturbanceThresh=0.0495;

void update_neighbour(vi &gain,vvpi &new_graph,vi &whichPartition,int partid)
{
	gain[partid]=0;

	for(auto itr:new_graph[partid])
	{
		// cout<<"Begin"<<endl;
		// print_pair(itr);
		if(whichPartition[partid]==whichPartition[itr.x])
		{
			gain[itr.x]-=2*itr.y;
			gain[partid]-=itr.y;
		}
		else
		{
			gain[itr.x]+=2*itr.y;
			gain[partid]+=itr.y;
		}
		// cout<<"End"<<endl;
	}
}

void decoarsen(vvi &old_vector_set,vvpi &new_graph,vi &new_vertex_weight,vi &partition1,vi &partition2,vi &new_partition1,vi &new_partition2)
{
	// cout<<"Hey decoarsen"<<endl;
	// return ;
	int pw1=partition1.size();
	int pw2=partition2.size();
	int s=new_graph.size();
	vector<int> whichPartition(s,0);
	int vertWeightIn1=0;
	int vertWeightIn0=0;
	for(int i=0;i<pw1;i++)
	{
		int ii=partition1[i];
		for(int j=0;j<old_vector_set[ii].size();j++)
		{
			new_partition1.pb(old_vector_set[ii][j]);
			vertWeightIn0+=new_vertex_weight[old_vector_set[ii][j]];
		}
	}
	for(int i=0;i<pw2;i++)
	{
		int ii=partition2[i];		
		for(int j=0;j<old_vector_set[ii].size();j++)
		{
			new_partition2.pb(old_vector_set[ii][j]);
			whichPartition[old_vector_set[ii][j]]=1;
			vertWeightIn1+=new_vertex_weight[old_vector_set[ii][j]];
		}
	}
	// vector<int> gain_part(s,0);

	// cout<<"Hey2"<<endl;
	// return;

	// for(int i=0;i<s;i++)
	// {
	// 	int ss=new_graph[i].size();
	// 	int gain=0;
	// 	for(int j=0;j<ss;j++)
	// 	{
	// 		int r=new_graph[i][j].first;
	// 		if(whichPartition[r]==whichPartition[i])
	// 		{
	// 			gain-=new_graph[i][j].y;
	// 		}
	// 		else
	// 		{
	// 			gain+=new_graph[i][j].y;
	// 		}
	// 	}
	// 	gain_part[i]=gain;
	// }

	// vi isSwapped(s,0);
	vi affected;
	vi swp;
	// cout<<"Mid decoarsen"<<endl;
	int KL_iteration=0;
	int elem1=new_partition1.size();
	int elem2=new_partition2.size();
	int disturbance=(int)(disturbanceThresh*(vertWeightIn0+vertWeightIn1));
	int IterCount=0;
	int LIM=min(1000,(elem2+elem1)/2);

	while(true && IterCount<1000)
	{
		IterCount++;
		int max_gain=-1e9;
		int part_id=-1;

		cout<<elem1<< " "<<elem2<<endl;
		cout<<vertWeightIn0<<" "<<vertWeightIn1<<endl;
		if(vertWeightIn0>vertWeightIn1+disturbance)
		{
			int r=rand()%elem1;
			int x=new_partition1[r];
			whichPartition[x]=1;
			elem1--;
			elem2++;
			swap(whichPartition[r],whichPartition[elem1]);
			vertWeightIn0-=new_vertex_weight[x];
			vertWeightIn1+=new_vertex_weight[x];
		}
		else if(vertWeightIn1>vertWeightIn0+disturbance)
		{
			int r=rand()%elem2;
			int x=new_partition2[r];
			whichPartition[x]=0;
			elem2--;
			elem1++;
			swap(whichPartition[r],whichPartition[elem2]);
			vertWeightIn0+=new_vertex_weight[x];
			vertWeightIn1-=new_vertex_weight[x];
		}

		else break;			
	}

	new_partition1.resize(elem1);
	new_partition2.resize(elem2);
	for(int i=0;i<s;i++)
	{
		if(whichPartition[i])
			new_partition2.pb(i);
		else
			new_partition1.pb(i);
	}
// cout<<"Return Deco"<<endl;
}