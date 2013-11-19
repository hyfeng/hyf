#include <iostream>
using namespace std;
//the datatype T must implete operator <
template<typename T>
void insert_sort(T* array,int length){
	T key;
	for(int j=1;j<length;++j){
		key=array[j];
		int i;
		for(i=j-1;i>=0;--i)
			if(key<array[i])
				array[i+1]=array[i];
			else 
				break;
		array[i+1]=key;
	}
}
int main(){
	int ad[5]={5,4,3,2,1};
	for(int i=0;i<5;i++)
		cout<<ad[i]<<' ';
	cout<<endl;
	insert_sort(ad,5);
	for(int i=0;i<5;i++)
		cout<<ad[i]<<' ';
	cout<<endl;
	return 0;
}
