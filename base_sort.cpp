#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;
int get_i(int num,int i){
	int base=1;
	while(i-->0)
		base*=10;
	if(num>=base){
		return (num/base)%10;
	}
	else{
		return -1;	//failed
	}
}
void base_sort(int *array,int len){
	list<int> bulket[10];
	bool finished=false;
	int start=0;
	int cur=0;	//iterator times
	while(!finished){
		for(int i=start;i<len;i++){
			int pos=get_i(array[i],cur);
			if(pos!= -1){
				bulket[pos].push_back(array[i]);
			}
			else{
				if(i!=start)
					array[start]=array[i];
				start++;
			}
		}
		int put_pos=start;
		for(int j=0;j<10;j++){
			while(!bulket[j].empty()){
				array[put_pos++]=bulket[j].front();
				bulket[j].pop_front();
			}
		}
		cout<<cur+1<<"iterators:"<<endl;
		copy(array,array+len,ostream_iterator<int>(cout," "));
		cout<<endl;
		if(start<len){
			finished=false;
			cur++;
		}
		else
			finished=true;
	}
}
int main(){
	int dd[]={13,12,26,205,24};
	copy(dd,dd+5,ostream_iterator<int>(cout," "));
	cout<<endl;
	base_sort(dd,5);
	copy(dd,dd+5,ostream_iterator<int>(cout," "));
	cout<<endl;
	return 0;
}
