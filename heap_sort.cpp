#include <iostream>
#include <iterator>
#include <cstddef>	//for NULL
#include <algorithm>
using namespace std;
//the type of data T must implement operator < 
/*
小根堆是一颗完全二叉树
n 为节点个数 当n为偶数时n1=1(1度节点数),n为奇数n1=0；n2=n0-1;n0=(n+1)/2
*/
template<typename T>
class HeapSort{
	T* arr;
	int len;
	HeapSort operator=(const HeapSort&);
	bool isRoot(int index){
		return index==0;	//0是根节点
	}
	bool isLeaf(int index){//jude the node is a leaf or not
		return index>=(len-1)/2;
	}
	int parent(int index){
		return ((index-1)/2>=0)?(index-1)/2:-1;	//求父节点
	}
	int lchild(int index){
		return ((index*2+1)>=len)?-1:(index*2+1);	//求左孩子
	}
	int rchild(int index){
		return ((index*2+2)>=len)?-1:(index*2+2);	//求右孩子
	}
	int start_build_point(){	//创建堆时开始的调整点，即最后一个非叶子节点
		return (len-1)/2-1;
	}
	bool exist(int index){
		return index>=0&&index<len;	//节点是否存在
	}
	int prepoint(int index){	//求前一个节点
		return index-1;
	}
	void adjust_up_to_bottom(int start){
		int index=lchild(start);
		int r=rchild(start);
		if(exist(r)&&arr[r]<arr[index])
			index=r;
		if(arr[index]<arr[start]){
			T temp=arr[start];
			arr[start]=arr[index];
			arr[index]=temp;
			if(!isLeaf(index))
				adjust_up_to_bottom(index);
		}
	}
	void adjust_bottom_to_up(int start){//start 调整的最底层点，非叶子节点
		int index=lchild(start);
		int r=rchild(start);
		if(exist(r)&&arr[r]<arr[index]){
			index=r;
		}
		if(arr[index]<arr[start]){
			T temp = arr[start];
			arr[start]=arr[index];
			arr[index]=temp;
			if(!isLeaf(index))
				adjust_up_to_bottom(index);
		}
		if(isRoot(start))//是根节点结束
			return;
		adjust_bottom_to_up(parent(start));//调整父节点
	}
	void build_heap(){//通过不断向上调整，创建堆
		for(int start=start_build_point();exist(start);start=prepoint(start)){
			adjust_bottom_to_up(start);
		}
	}
	void sort_heap(){//base on the builed heap
		int n=len;
		while(len>1){
			T temp=arr[len-1];
			arr[len-1]=arr[0];
			arr[0]=temp;
			len--;
			adjust_up_to_bottom(0);
		}
		//reverse
		len=n;
		for(int i=0;i<len/2;i++){
			swap(arr[i],arr[len-1-i]);
		}
	}
public:
	explicit HeapSort(T* array=NULL,int length=0):arr(array),len(length){}
	void test(){
		copy(arr,arr+len,ostream_iterator<int>(cout," "));
		cout<<endl;
		build_heap();
		copy(arr,arr+len,ostream_iterator<int>(cout," "));
		cout<<endl;
	}
	void operator()(){
		build_heap();
		sort_heap();
	}
};
int main(){
	int da[5]={5,4,3,2,1};
	HeapSort<int> heap(da,5);
	//heap.test();
	copy(da,da+5,ostream_iterator<int>(cout," "));
	cout<<endl;

	heap();
	copy(da,da+5,ostream_iterator<int>(cout," "));
	cout<<endl;
	return EXIT_SUCCESS;
}
