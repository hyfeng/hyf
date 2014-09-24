#include <cstddef>
#include <iostream>
using namespace std;
class Node{
	public:
		static Node NIL;
	public:
		typedef int DataType;
		enum Color{BLACK,RED};
	public:
		Color color;
		DataType key;
		Node * left;
		Node * right;
		Node * p;
	public:
		Node():color(BLACK),key(DataType()),left(NULL),right(NULL),p(NULL){}
		Node(const DataType& data):color(BLACK),key(data),left(NULL),right(NULL),p(NULL){}
		DataType getKey()const{
			return key;
		}
		void setColor(const Color& color);
		void setLeft(Node *address);
		void setRight(Node *address);
		void setKey(const DataType& data);
		void setParent(Node *parent);
		bool operator<(const Node& node);
};
Node Node:: NIL=Node();
void Node::setKey(const DataType& data){
	this->key=data;
}
void Node::setParent(Node * parent){
	this->p=parent;
}
void Node::setRight(Node *address){
	this->right=address;
}
void Node::setLeft(Node *address){
	this->left=address;
}

void Node::setColor(const Color& color){
	this->color=color;
}
bool Node::operator<(const Node& node){
	return this->key < node.key;
}

class RBTree{
	public:
		typedef Node::DataType DataType;
	private:
		Node* root;
	public:
		RBTree():root(&Node::NIL){}
		~RBTree();
		void rbInsert(DataType key);
		void rbDelete(Node *z);
		Node* treeSuccessor(Node*x);
	private:
		void rbDeleteFixup(Node *x);
		void rbInsertFixup(Node *z);
		void leftRotate(Node *x);
		void rightRotate(Node *y);
};
void RBTree::rbDeleteFixup(Node *x){
	while(x!=root&&x->color==Node::BLACK){
		if(x==x->p->left){
			Node *w=x->p->right;
			if(w->color==Node::RED){
				w->color=Node::BLACK;
				x->p->color=Node::RED;
				leftRotate(x->p);
				w=x->p->right;
			}
			if(w->left->color==Node::BLACK&&w->right->color==Node::BLACK){
				w->color=Node::RED;
				x=x->p;
			}
			else{
				if(w->right->color==Node::BLACK){
					w->left->color=Node::BLACK;
					w->color=Node::BLACK;
					rightRotate(w);
					w=x->p->right;
				}
				w->color=x->p->color;
				x->p->color=Node::BLACK;
				w->right->color=Node::BLACK;
				leftRotate(x->p);
				x=root;
			}
		}
		else{
			Node* w=x->p->left;
			if(w->color==Node::RED){
				w->color=Node::BLACK;
				x->p->color=Node::RED;
				rightRotate(x->p);
				w=x->p->left;
			}
			if(w->left->color==Node::BLACK&&w->right->color==Node::BLACK){
				w->color=Node::RED;
				x=x->p;
			}
			else{
				if(w->left->color==Node::BLACK){
					w->right->color=Node::BLACK;
					w->color=Node::RED;
					leftRotate(w);
					w=x->p->left;
				}
				w->color=x->p->color;
				x->p->color=Node::BLACK;
				w->left->color=Node::BLACK;
				rightRotate(x->p);
				x=root;
			}
		}
	}
	x->color=Node::BLACK;
}
void RBTree::rbDelete(Node *z){
	Node *y;
	Node *x;
	if(z->left==&Node::NIL||z->right==&Node::NIL){
		y=z;
	}
	else{
		y=treeSuccessor(z);
	}
	if(y->left!=&Node::NIL){
		x=y->left;
	}
	else{
		x=y->right;
	}
	x->p=y->p;
	if(y->p==&Node::NIL){
		root=x;
	}
	else if(y==y->p->left){
		y->p->left=x;
	}
	else{
		y->p->right=x;
	}
	if(y!=z){
		z->key=y->key;
	}
	if(y->color==Node::BLACK){
		rbDeleteFixup(x);
	}
	delete y;
}
Node* RBTree::treeSuccessor(Node* x){
	Node* y=x->right;
	Node* z=&Node::NIL;
	while(y!=&Node::NIL){
		z=y;
		y=z->left;
	}
	return z;
}
void RBTree::rbInsertFixup(Node *z){
	while(z->p->color==Node::RED){
		if(z->p==z->p->p->left){
			Node* y=z->p->p->right;
			if(y->color==Node::RED){
				z->p->color=Node::BLACK;
				y->color=Node::BLACK;
				z->p->p->color=Node::RED;
				z=z->p->p;
			}
			else if(z==z->p->right){
				z=z->p;
				leftRotate(z);
			}
			else{
				z->p->color=Node::BLACK;
				z->p->p->color=Node::RED;
				rightRotate(z->p->p);
			}
		}
		else{
			Node *y=z->p->p->left;
			if(y->color==Node::RED){
				z->p->color=Node::BLACK;
				y->color=Node::BLACK;
				z->p->p->color=Node::RED;
				z=z->p->p;
			}
			else if(z==z->p->left){
				z=z->p;
				rightRotate(z);
			}
			else{
				z->p->color=Node::BLACK;
				z->p->p->color=Node::RED;
				leftRotate(z->p->p);
			}
		}
	}
	root->color=Node::BLACK;
}
void RBTree::rbInsert(DataType key){
	Node* z=new Node(key);	
	z->color=Node::RED;
	z->p=&Node::NIL;
	z->left=&Node::NIL;
	z->right=&Node::NIL;
	Node* x=root;
	Node* y=&Node::NIL;
	while(x!=&Node::NIL){
		y=x;
		if(*z<*x){
			x=x->left;
		}
		else{
			x=x->right;
		}
	}
	z->p=y;
	if(y==&Node::NIL){
		root=z;
	}
	else if(*z<*y){
		y->left=z;
	}
	else{
		y->right=z;
	}
	rbInsertFixup(z);
}
void RBTree::rightRotate(Node *y){
	if(y==NULL||y==&Node::NIL||y->left==&Node::NIL)
		return;
	Node *x=y->left;
	x->p=y->p;
	y->left=x->right;
	y->left->p=y;
	x->right=y;
	y->p=x;
	if(x->p==&Node::NIL){
		root=x;
	}
	else
	{
		if(x->p->left==y){
			x->p->left=x;
		}
		else{
			x->p->right=x;
		}
	}
}
void RBTree::leftRotate(Node *x){
	if(x==NULL||x==&Node::NIL||x->right==&Node::NIL)
		return;
	Node * y=x->right;
	y->p=x->p;
	x->right=y->left;
	x->right->p=x;
	y->left=x;
	x->p=y;
	if(y->p==&Node::NIL){
		root=y;
	}
	else
	{
		if(y->p->left==x)
			y->p->left=y;
		else
			y->p->right=y;
	}
}

RBTree::~RBTree(){
	Node* p=root;
	while(p!=&Node::NIL){
		if(p->left!=&Node::NIL){
			p=p->left;
		}
		else if(p->right!=&Node::NIL){
			p=p->right;
		}
		else{
			Node *temp=p;
			p=p->p;
			if(temp==p->left){
				p->left=&Node::NIL;
			}
			else{
				p->right=&Node::NIL;
			}
			delete temp;
		}
	}
}
int main(){
	RBTree rbtree;
	int keys[]={1,2,7,11,8,14,5,15};
	for(int i=0;i<8;i++){
		rbtree.rbInsert(keys[i]);
	}
	return 0;
}
