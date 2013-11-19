#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstddef>	//for NULL

using namespace std;
//the data type T must implete the operator <= 
template <typename T>
class QSort{
	T* array;
	int len;
	QSort operator=(const QSort&);

	//put the head element into the right position
	int one_partition(int start,int end){
		T temp=array[start];
		int i=start;
		int j=end-1;
		while(i<j){
			while(i<j&&temp<=array[j])
				j--;
			if(i<j)
				array[i]=array[j];
			while(i<j&&array[i]<=temp)
				i++;
			if(i<j)
				array[j]=array[i];
		}
		array[j]=temp;
		return j;
	}

	//recursivly put all element into right position throughout ope_partition function.
	void quick_sort(int start,int end){
		if(end<=start+1)
			return;
		int mid=one_partition(start,end);
		if(start+1<mid)
			quick_sort(start,mid);
		if(mid+2<end)
			quick_sort(mid+1,end);
	}
public:
	explicit QSort(T* dd=NULL,int length= 0):array(dd),len(length){}
	void operator()(){
		quick_sort(0,len);	
	}
};
int main(){
	int da[5]={5,4,3,2,1};
	copy(da,da+5,ostream_iterator<int>(cout," "));
	cout<<endl;
	QSort<int> qs(da,5);
	qs();
	copy(da,da+5,ostream_iterator<int>(cout," "));
	cout<<endl;
	return EXIT_SUCCESS;
}
