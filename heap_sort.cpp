#include <iostream>
#include <iterator>
#include <cstddef>	//for NULL
#include <algorithm>
using namespace std;
//the type of data T must implement operator < 
/*
С������һ����ȫ������
n Ϊ�ڵ���� ��nΪż��ʱn1=1(1�Ƚڵ���),nΪ����n1=0��n2=n0-1;n0=(n+1)/2
*/
template<typename T>
class HeapSort{
	T* arr;
	int len;
	HeapSort operator=(const HeapSort&);
	bool isRoot(int index){
		return index==0;	//0�Ǹ��ڵ�
	}
	bool isLeaf(int index){//jude the node is a leaf or not
		return index>=(len-1)/2;
	}
	int parent(int index){
		return ((index-1)/2>=0)?(index-1)/2:-1;	//�󸸽ڵ�
	}
	int lchild(int index){
		return ((index*2+1)>=len)?-1:(index*2+1);	//������
	}
	int rchild(int index){
		return ((index*2+2)>=len)?-1:(index*2+2);	//���Һ���
	}
	int start_build_point(){	//������ʱ��ʼ�ĵ����㣬�����һ����Ҷ�ӽڵ�
		return (len-1)/2-1;
	}
	bool exist(int index){
		return index>=0&&index<len;	//�ڵ��Ƿ����
	}
	int prepoint(int index){	//��ǰһ���ڵ�
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
	void adjust_bottom_to_up(int start){//start ��������ײ�㣬��Ҷ�ӽڵ�
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
		if(isRoot(start))//�Ǹ��ڵ����
			return;
		adjust_bottom_to_up(parent(start));//�������ڵ�
	}
	void build_heap(){//ͨ���������ϵ�����������
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
