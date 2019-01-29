#include<math.h>
#include<iostream>
using namespace std;

int bit_in_which(int num, int i)
{
	return num % int(pow(10, i + 1)) / pow (10, i);
}

int main(void)
{
	int a = 1001;
	int b = 1010;
	for(int i=0;i<8;i++)
	{
		cout<<"Weight "<<pow(2,i)<<":";
		for(int j = 0;j<4;j++)
		{
			for(int k = 0;k<4;k++)
			{
				if(k + j == i)
				{
					cout<<bit_in_which(a,k) * bit_in_which(b,j)<<" ";
				}
			}
		}
		cout<<endl;
	}
 } 
