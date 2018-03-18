#include <stdio.h>
#include "omp.h"
#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>


using namespace std;

unsigned int microseconds=1000000;
int n,e,k;
string str1,str2;  
int main(int argc,char* argv[]){
	
	str1= argv[1];
	str2= argv[2];	
	k = atoi(argv[3]);
	// cout<< stoi("3")<<'\n';
	// str1 = "file";
	// k = 64;
    // cout << k << '\n';
	ifstream inFile;
	inFile.open(str1);

	if (!inFile) {
        cout << "Unable to open file \n";
        exit(1); // terminate with error
    }

    inFile >> n ;
    inFile >> e ;
    // cout << n << '\n';
    // cout << e << '\n';
    
    // string line;    
    // while (getline(inFile, line)) {   
    // cout << line << '\n';
    // char *token = std::strtok(line, " ");
    // int counter=0;
    // while (token != NULL) {
    //     std::cout << token << '\n';
    //     if(counter==0){
    //     	n=stoi(token);
    //     }
    //     else{
    //     	k=stoi(token);
    //     }
    //     token = std::strtok(NULL, " ");
    //     counter++;
    // }
    // break;
    // }

    int ar [n];
    int limit[k];
    int a = n/k;
    int b = n%k;
    // if(n%k==0){
    // 	b=0;
    // }else{
    // 	b=1;
    // }

    for(int i=0;i<k;i++){
    	if(b==0){
    		limit[i]=a;
    	}else{
    		limit[i]=a+1;
    		b--;
    	}
    }
    ofstream myfile;
    myfile.open (str2);
    usleep(microseconds);
    int output;
    for(int i=0;i<n;i++){
    	output = rand() % (k);
    	if(limit[output] > 0){
    		ar[i]=output;
    		limit[output]--;
    	}else{
    		while(true){
    			if(limit[output]>0){
    				limit[output]--;
    				ar[i]=output;
    				break;
    			}else{
    				output++;
    				output=output%(k);
    			}
    		}
    	}
    	myfile<< ar[i] <<'\n';
    	// cout<<i<<"  "<<ar[i]<<'\n';
    }
    myfile.close();

    



}