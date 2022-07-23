#ifndef BTSNODE_H
#define BTSNODE_H

template<typename T>
class BSTNode{

	T key;
	BSTNode<T>* parent;
	BSTNode<T>* right;
	BSTNode<T>* left;
	bool verbose;

	template<typename C>
	friend class BST;

public:

	BSTNode(T key, bool verbose = false) : key(key), verbose(verbose){
		parent = nullptr;
		right = nullptr;
		left = nullptr;
	}

	//Getter
	BSTNode<T>* getParent(){return this->parent;}
	BSTNode<T>* getRight(){return this->right;}
	BSTNode<T>* getLeft(){return this->left;}
	T getKey(){return this->key;}

	//Setter
	void setParent(BSTNode<T>* parent){this->parent = parent;}
	void setRight(BSTNode<T>* right){this->right = right;}
	void setLeft(BSTNode<T>* left){this->left = left;}
	void setKey(T key){this->key = key;}

	friend ostream& operator<< (ostream& os, BSTNode<T>& b){

		if(b.verbose){
			os << "BSTNode: " << &b << endl;
			os << "Key =" << b.key << endl;
			os << "left->" << b.left << "\t right->" << b.right << "\t parent->" << b.parent << endl;
			return os;
		}

		return os << "Key = " << b.key << endl;
	}
	
};

#endif