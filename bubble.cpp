#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;
//数据类型T需要实现 operator <
template <class T>
void bubble_sort(T *array,int num){
	for(int i=num-1;i>0;--i)
		for(int j=0;j<i;++j)
			if(array[j+1]<array[j])
				swap(array[j],array[j+1]);
}

int main(){
	int da[5]={5,4,3,2,1};
	int i;
	for(i=0;i<5;++i)
		cout<<da[i]<<' ';
	cout<<endl;
	bubble_sort(da,5);
	for(i=0;i<5;++i)
		cout<<da[i]<<' ';
	cout<<endl;
	return EXIT_SUCCESS;
}
