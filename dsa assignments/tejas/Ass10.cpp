/*Read the marks obtained by students of second year in an online examination of 
particular subject. Find out maximum and minimum marks obtained in that subject. 
Use heap data structure. Analyze the algorithm.*/

#include<iostream>
using namespace std;
class Heap
{
	int n;
	int *minheap,*maxheap;
	public:
	void get();
	void displayMin(){cout<<"Minimum marks are :"<<minheap[0]<<endl;}
	void displayMax(){cout<<"Maximum marks are :"<<maxheap[0]<<endl;}
	void upAdjust(bool,int);
};
void Heap::get()
{
	cout<<"Enter number of students."<<endl;
	cin>>n;
	int k;
	minheap=new int[n];
	maxheap=new int[n];
	cout<<"Enter marks of students."<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>k;
		minheap[i]=k;
		upAdjust(0,i);
		maxheap[i]=k;
		upAdjust(1,i);
	}
}
void Heap::upAdjust(bool m,int l)
{
	int s;
	if(!m)
	{
		while(minheap[(l-1)/2]<minheap[l])
		{
			s=minheap[l];
			minheap[l]=minheap[(l-1)/2];
			minheap[(l-1)/2]=s;
			l=(l-1)/2;
			if(l==-1)
				break;
		}
	}
	else
	{
		while(maxheap[(l-1)/2]>maxheap[l])
		{
			s=maxheap[l];
			maxheap[l]=maxheap[(l-1)/2];
			maxheap[(l-1)/2]=s;
			l=(l-1)/2;
			if(l==-1)
				break;
		}
	}
}
main()
{
	Heap H;
	H.get();
	H.displayMin();
	H.displayMax();
	return(0);
}

/*OUTPUT:
owner@owner-Inspiron-3520:~$ cd 2269_ADSL
owner@owner-Inspiron-3520:~/2269_ADSL$ g++ assign9.cpp
owner@owner-Inspiron-3520:~/2269_ADSL$ ./a.out
Enter number of students.
10
Enter marks of students.
12
35
43
22
18
45
33
37
41
16
Minimum marks are :45
Maximum marks are :12
owner@owner-Inspiron-3520:~/2269_ADSL$ ./a.out
Enter number of students.
13
Enter marks of students.
13
16
17
18
13
50
50
35
23
33
43
56
56
Minimum marks are :56
Maximum marks are :13
*/