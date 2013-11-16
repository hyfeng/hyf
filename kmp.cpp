//the kmp algorithm
//the datatype T must implate operator ==
#include <iostream>
#include <cstring>
#include <cstddef>	//for NULL
#include <vector>
using std::cout;
using std::endl;
using namespace std;
template < typename T>
class KMP{
	T * des;	//the object string
	int len_des;	//the length of des
	T * pat;	//the pattern string
	int len_pat;	//the length of pattern
	int *next;	//the next array
	int *nextvar;	//the improved algorithm use the array
	const KMP& operator = (const KMP&);
	KMP();
	KMP(const KMP&);
public:
	explicit KMP(T* destination,int des_len,T* pattern,int pattern_len):des(destination),len_des(des_len),pat(pattern),len_pat(pattern_len),next(NULL),nextvar(NULL){
		next= cal_next(pat,len_pat);	
	}
	~KMP(){
		if(next!=NULL)
			delete []next;
		if(nextvar!=NULL)
			delete[]nextvar;
	}
	void show_next()const{
		for(int i= 0 ;i< len_pat;++i)
			cout<<next[i]<<' ';
		cout<<endl;
	}
	int* operator()(int& num){//return a array of the head subscript of the matched substring; num  is the prewanted number of the substring,if num is -1,implite get all of the matched substrings and then set the 'num' the total number.
		vector<int> sub;
		int count=0;
		int pat_i=0,des_j=0;
		while(des_j<= len_des&&(num== -1||count<num)){
			if(pat[pat_i]== des[des_j]){
				pat_i++;
				des_j++;
				if(pat_i==len_pat){
					des_j=des_j-len_pat;
					pat_i=0;
					sub.push_back(des_j);
					count++;
					des_j++;
				}
			}
			else{
				if(pat_i==0){
					des_j++;
				}
				else{
					pat_i=next[pat_i-1]+1;
				}
			}
		}
		int * result= new int[count];
		for(int i=0;i<count;i++)
			result[i]=sub[i];
		num=count;
		return result;
	}	
	static int* cal_next(const T* pattern,int len){
		int *next = new int[len];
		int i=0;
		next[i]= -1;
		for(i = 1;i< len;++i){
			int t= next[i-1];
			while(t!= -1){
				if(pattern[i]== pattern[t+ 1]){
					next[i]= t+ 1;
					break;
				}
				else
					t= next[t];
			}
			if(t== -1){
				if(pattern[i]== pattern[t+ 1])
					next[i]= t+ 1;
				else 
					next[i]= t;
			}
		}
		return next;
	}
};
int main(){
	char des[]="abaaabaaabccdabaaabaaababaacdbab";
	char ss[10]={'a','b','a','a','a','b','a','a','a','b'};
	int *next=KMP<char>::cal_next(ss,10);
	for(int i=0;i<10;++i)
		cout<<next[i]<<' ';
	cout<<endl;
	delete[] next;
	KMP<char> kp(des,strlen(des),ss,10);
	kp.show_next();
	int num=-1;
	int *re=kp(num);
	cout<<num<<endl;
	for(int i=0;i<num;i++)
		cout<<re[i]<<' ';
	cout<<endl;
	delete []re;
	return 0;
}
