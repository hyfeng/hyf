#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;
template <typename T>
void shell_sort(T* array,int length)
{
	int del=length/2;
	while(del>=1){
		for(int i=del;i<length;i++){
				T temp=array[i];
				int k;
				for(k=i-del;k>=0;k-=del){
					if(temp<array[k])
						array[k+del]=array[k];
					else 
						break;
				}
				array[k+del]=temp;
			}
		del/=2;
	}
}
int main(){
	int da[]={23,4,56,112,32,8,9};
	copy(da,da+7,ostream_iterator<int>(cout," "));
	cout<<endl;
	shell_sort<int>(da,7);
	copy(da,da+7,ostream_iterator<int>(cout," "));
	cout<<endl;
	return 0;
}
