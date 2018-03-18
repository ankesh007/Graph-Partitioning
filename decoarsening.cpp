#include "global_header.h"

int IDEAL_ITERATIONS=20;
int KL_ITERATIONS=3;

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
	int nwp1=new_partition1.size();
	int nwp2=new_partition2.size();
	vector<int> gain_part(s,0);

	// cout<<"Hey2"<<endl;
	// return;

	for(int i=0;i<s;i++)
	{
		int ss=new_graph[i].size();
		int gain=0;
		for(int j=0;j<ss;j++)
		{
			int r=new_graph[i][j].first;
			if(whichPartition[r]==whichPartition[i])
			{
				gain-=new_graph[i][j].y;
			}
			else
			{
				gain+=new_graph[i][j].y;
			}
		}
		gain_part[i]=gain;
	}

	vi isSwapped(s,0);
	vi affected;
	vi swp;
	// cout<<"Mid decoarsen"<<endl;
	int KL_iteration=0;

	while(KL_iteration<KL_ITERATIONS)
	{
		int toto=0;
		KL_iteration++;
		int losing=0;

		while(toto<1000)
		{
			toto++;
			// cout<<toto<<endl;
			// cout<<"Hi"<<endl;
			int max_gain=-1e9;
			int part_id=-1;

			if(vertWeightIn0>vertWeightIn1)
			{
				for(int i=0;i<nwp1;i++)
				{
					int ii=new_partition1[i];
					if(isSwapped[ii]==0)
					{
						if(gain_part[ii]>max_gain)
						{
							max_gain=gain_part[ii];
							part_id=ii;
						}
					}
				}
			}

			else
			{
				for(int i=0;i<nwp2;i++)
				{
					int ii=new_partition2[i];
					if(isSwapped[ii]==0)
					{
						if(gain_part[ii]>max_gain)
						{
							max_gain=gain_part[ii];
							part_id=ii;
						}
					}
				}
			}
			// cout<<"After else"<<endl;
			if(part_id!=-1)
			{			
				if(max_gain<=0)
				{
					losing=losing+1;
				}
				else{
					losing=0;
					swp.clear();
				}
				isSwapped[part_id]=1;
				swp.pb(part_id);
				affected.pb(part_id);
				whichPartition[part_id]=1-whichPartition[part_id];


				if(whichPartition[part_id])
				{
					vertWeightIn0-=(new_vertex_weight[part_id]);
					vertWeightIn1+=(new_vertex_weight[part_id]);
				}
				else
				{
					vertWeightIn0+=(new_vertex_weight[part_id]);
					vertWeightIn1-=(new_vertex_weight[part_id]);
				}
				// cout<<"Before Update "<<endl;
				// int kkk=0;

				// for(auto itr:new_graph)
				// {
				// 	cout<<kkk<<endl;kkk++;
				// 	for(auto itr2:itr)
				// 		print_pair(itr2);
				// }
				
				update_neighbour(gain_part,new_graph,whichPartition,part_id);
			}
			if(losing>=IDEAL_ITERATIONS || part_id==-1)
			{
				int x=swp.size();
				for(int i=x-1;i>=0;i--)
				{
					whichPartition[swp[i]]=1-whichPartition[swp[i]];
					update_neighbour(gain_part,new_graph,whichPartition,swp[i]);
				}
				swp.clear();
				for(auto itr:affected)
					isSwapped[itr]=0;
				affected.clear();
				break;
			}
		}

			// cout<<"Hey3"<<endl;
			// return;
		new_partition1.resize(0);
		new_partition2.resize(0);
		for(int i=0;i<s;i++)
		{
			if(whichPartition[i])
				new_partition2.pb(i);
			else
				new_partition1.pb(i);
		}
		pw1=new_partition1.size();
		pw2=new_partition2.size();
	}
	// cout<<"Return Deco"<<endl;
}