#include <iostream>
//#include <iterator>
#include <cstdlib>
#include <algorithm>
using namespace std;
//the data type T must implete operator < & assign(=)function.
template <typename T>
void merge_sort(T* array,int length){//use the iterator methord
	if(length<2)
		return;
	T* origin=array;
	T* au=new T[length];
	int del=1;
	while(del<length){
		int i=0;
		int k=0;
		while(i+del<length){
			int j=i+del;
			int t=i;
			while(t<i+del&&j<length&&j<i+2*del){
				if(origin[j]<origin[t])
					au[k++]=origin[j++];
				else au[k++]=origin[t++];
			}
			while(t<i+del)
				au[k++]=origin[t++];
			while(j<length&&j<i+2*del)
				au[k++]=origin[j++];
			i=j;
		}
		while(i<length)
			au[k++]=origin[i++];
		del*=2;
		T*temp=origin;
		origin=au;
		au=temp;
	}
	if(origin!=array){
		for(int i=0;i<length;i++)
			array[i]=origin[i];
		delete[] origin;
	}
	else
		delete[]au;
	au=NULL;
}

//then, use the recursive methord
template <typename T>
void merge_sort_recursive(T* array,int start,int end){
	if(end<=start+1)
		return;
	if(start+2 == end){
		if(array[end-1]<array[start]){
			T temp=array[start];
			array[start]=array[end-1];
			array[end-1]=temp;
		}
	}
	else{
		int mid=(start+end)/2;
		merge_sort_recursive(array,start,mid+1);
		merge_sort_recursive(array,mid+1,end);
		T* au=new T[end-start];
		int k=0;
		int i=start;
		int j=mid+1;
		while(i<mid+1&&j<end){
			if(array[j]<array[i])
				au[k++]=array[j++];
			else 
				au[k++]=array[i++];
		}
		while(i<mid+1)
			au[k++]=array[i++];
		while(j<end)
			au[k++]=array[j++];
		for(i=0;i<k;i++)
			array[start+i]=au[i];
		delete[]au;
	}
}


int main(){
	int da[5]={5,4,3,2,1};
	copy(da,da+5,ostream_iterator<int>(cout," "));
	cout<<endl;
	//merge_sort(da,5);
	merge_sort_recursive(da,0,5);
	copy(da,da+5,ostream_iterator<int>(cout," "));
	cout<<endl;
	return EXIT_SUCCESS;
}
