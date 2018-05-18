#include "global_header.h"

int IDEAL_ITERATIONS=20;
int KL_ITERATIONS=6;
float disturbanceThresh=0.0495;
int ITERATION_LIM=1100;

// set<pii,Comparator> gainSet0,gainSet1;

void update_neighbour(vi &gain,vvpi &new_graph,vi &whichPartition,vi &isSwapped,int partid,set<pii,Comparator> &gainSet0,set<pii,Comparator> &gainSet1)
{
	gain[partid]=0;

	for(auto itr:new_graph[partid])
	{
		if(whichPartition[itr.x])
			gainSet1.erase({gain[itr.x],itr.x});
		else
			gainSet0.erase({gain[itr.x],itr.x});

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
		if(isSwapped[itr.x])
			continue;
		if(whichPartition[itr.x])
			gainSet1.insert({gain[itr.x],itr.x});
		else
			gainSet0.insert({gain[itr.x],itr.x});
	}
}

void decoarsen(vvi &old_vector_set,vvpi &new_graph,vi &new_vertex_weight,vi &partition1,vi &partition2,vi &new_partition1,vi &new_partition2)
{
	// cout<<"Hey decoarsen"<<endl;
	set<pii,Comparator> gainSet0,gainSet1;
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
		if(whichPartition[i])
			gainSet1.insert({gain,i});
		else
			gainSet0.insert({gain,i});
	}

	vi isSwapped(s,0);
	vi affected;
	vi swp;
	// cout<<"Mid decoarsen"<<endl;
	int KL_iteration=0;
	int disturbance=(int)(disturbanceThresh*(vertWeightIn0+vertWeightIn1));

	while(KL_iteration<KL_ITERATIONS)
	{
		int itertionCount=0;
		KL_iteration++;
		int losing=0;

		while(true)
		{
			itertionCount++;
			// cout<<toto<<endl;
			int max_gain=-1e9,max_gain0=-1e9,max_gain1=-1e9;
			int part_id=-1,part_id0=-1,part_id1=-1;
			// cout<<vertWeightIn0<<" "<<vertWeightIn1<<" "<<disturbance<<endl;

			if(!gainSet0.empty())
			{
				auto itr=*(gainSet0.begin());
				max_gain0=itr.x;
				part_id0=itr.y;
			}
			if(!gainSet1.empty())
			{
				auto itr=*(gainSet1.begin());
				max_gain1=itr.x;
				part_id1=itr.y;
			}
			if(vertWeightIn0>vertWeightIn1+disturbance)
			{
				max_gain=max_gain0;
				part_id=part_id0;
			}
			else if(vertWeightIn1>vertWeightIn0+disturbance)
			{
				max_gain=max_gain1;
				part_id=part_id1;
			}
			else
			{
				if(max_gain0>max_gain1)
				{
					max_gain=max_gain0;
					part_id=part_id0;
				}
				else
				{
					max_gain=max_gain1;
					part_id=part_id1;				
				}
			}			
			
			if(part_id!=-1)
			{
				if(whichPartition[part_id])
					gainSet1.erase({max_gain,part_id});
				else
					gainSet0.erase({max_gain,part_id});

				if(max_gain<0)
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
				
				update_neighbour(gain_part,new_graph,whichPartition,isSwapped,part_id,gainSet0,gainSet1);
			}
			if(losing>=IDEAL_ITERATIONS || part_id==-1 || itertionCount>ITERATION_LIM)
			{
				int x=swp.size();
				for(int i=x-1;i>=0;i--)
				{
					whichPartition[swp[i]]=1-whichPartition[swp[i]];
					if(whichPartition[swp[i]])
					{
						vertWeightIn1+=new_vertex_weight[swp[i]];
						vertWeightIn0-=new_vertex_weight[swp[i]];
					}
					else
					{
						vertWeightIn0+=new_vertex_weight[swp[i]];
						vertWeightIn1-=new_vertex_weight[swp[i]];						
					}
					update_neighbour(gain_part,new_graph,whichPartition,isSwapped,swp[i],gainSet0,gainSet1);
				}
				
				swp.clear();
				for(auto itr:affected)
				{
					if(whichPartition[itr])
						gainSet1.insert({gain_part[itr],itr});
					else
						gainSet0.insert({gain_part[itr],itr});
					isSwapped[itr]=0;
				}
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
		// cout<<pw1<<" "<<pw2<<" "<<"LOW"<<endl;
	}
	// cout<<"Return Deco"<<endl;
}