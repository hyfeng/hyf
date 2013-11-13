#include <iostream>
#include <algorithm>
using namespace std;
template <typename T>
void select_sort(T* array,int num){
	for(int i=0;i<num-1;++i){
		int x=i;
		for(int j=i;j<num;++j){
			if(array[j]<array[x]){
				x=j;
			}
		}
		swap(array[x],array[i]);
	}
}
int main(){
	int da[5]={5,4,3,2,1};
	for(int i=0;i<5;i++)
		cout<<da[i]<<' ';
	cout<<endl;
	select_sort(da,5);
	for(int i=0;i<5;i++)
		cout<<da[i]<<' ';
	cout<<endl;
	return 0;
}
