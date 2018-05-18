#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	cout<<n<<" "<<(n*(n-1))/2<<endl;

	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i==j)
				continue;
			cout<<j<<" ";
		}
		cout<<endl;
	}
}