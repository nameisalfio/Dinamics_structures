#ifndef RBNODE_H
#define RBNODE_H

enum color {BLACK, RED};	//BLACK = 0 	RED = 1

template<typename T>
class RBNode{
	T key;
	int color;
	RBNode<T>* parent;
	RBNode<T>* right;
	RBNode<T>* left;

	template<typename C>
	friend class RBTree;
public:
	RBNode(T key, int color) : key(key), color(color){parent = left = right = nullptr;}
	RBNode(){parent = left = right = nullptr;}

	//Getter
	RBNode<T>* getParent(){return this->parent;}
	RBNode<T>* getRight(){return this->right;}
	RBNode<T>* getLeft(){return this->left;}
	T getKey(){return this->key;}
	int getColor(){return this->color;}

	//Setter
	void setParent(RBNode<T>* parent){this->parent = parent;}
	void setRight(RBNode<T>* right){this->right = right;}
	void setLeft(RBNode<T>* left){this->left = left;}
	void setKey(T key){this->key = key;}
	void setColor(int color){this->color = color;}

	friend ostream& operator<< (ostream& os, const RBNode<T>& b){
		return os << b.key << " (" << (b.color == 1 ? "RED" : "BLACK" )<< ")";
	}
};

#endif