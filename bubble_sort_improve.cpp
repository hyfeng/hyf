#include <iostream>
#include <algorithm>
using namespace std;
template <typename T>
void bubble_sort_improve(T* array , int num){
	bool changed = true; // 
	int i=num-1,j=0;
	int count=0;
	while(changed){
		//bubble the max data from head to tail
		int k;
		changed=false;
		for(k=j;k<i;++k){
			if(array[k+1]<array[k]){
				swap(array[k],array[k+1]);
				changed = true;
			}
		}
		if(!changed)
			break;
		//bubble the min data from tail to head
		i--;
		for(k=i;k>j;--k){
			if(array[k]<array[k-1]){
				swap(array[k],array[k-1]);
				changed=true;
			}
		}
		j++;
	}
}
int main(){
	int ad[5]={5,4,3,2,1};
	for(int i=0;i<5;i++)
		cout<<ad[i]<<' ';
	cout<<endl;
	bubble_sort_improve(ad,5);
	for(int i=0;i<5;i++)
		cout<<ad[i]<<' ';
	cout<<endl;
	return 0;
}