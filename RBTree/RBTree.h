#ifndef RBTREE_H
#define RBTREE_H

enum color {BLACK, RED};	//BLACK = 0 	RED = 1

template<class T>
class Node{

private:
	T key;
	int color;
	Node<T>* parent;
	Node<T>* right;
	Node<T>* left;

	template<class C>
	friend class RBTree;
public:
	Node(T key, int color) : key(key), color(color){parent = left = right = nullptr;}

	//Getter
	Node<T>* getParent(){return parent;}
	Node<T>* getRight(){return right;}
	Node<T>* getLeft(){return left;}
	T getKey(){return key;}
	int getColor(){return color;}

	//Setter
	void setParent(Node<T>* parent){this->parent = parent;}
	void setRight(Node<T>* right){this->right = right;}
	void setLeft(Node<T>* left){this->left = left;}
	void setKey(T key){this->key = key;}
	void setColor(int color){this->color = color;}

	friend ostream& operator<< (ostream& os, const Node<T>& b){
		return os << b.key << " (" << (b.color == 1 ? "RED" : "BLACK" )<< ")";
	}
};

template<class T>
class RBTree{

private:
	Node<T>* root;

	double compare(T a, T b){return ((a) - (double)(b));}

	bool isEmpty(){return !root;}

	void swapColors(Node<T>* x, Node<T>* y)
	{
		int aux = x->getColor();
		x->setColor(y->getColor());
		y->setColor(aux);
	}

	void swapKeys(Node<T>* x, Node<T>* y)
	{
		T aux = x->getKey();
		x->setKey(y->getKey());
		y->setKey(aux);
	}

	bool isLeftChild(Node<T>* node){
		if(node->parent)
			return node == node->parent->left;
		return false;
	}

	Node<T>* getSibling(Node<T>* node){
		if(!node->parent)
			return nullptr;

		if(isLeftChild(node))
			return node->parent->right;
		return node->parent->left;
	}

	Node<T>* getUncle(Node<T>* node){
		if(!node->parent || !node->parent->parent)
			return nullptr;
		return getSibling(node->parent);	// torno il fratello del padre
	}

	void insertNodeUp(Node<T>* parent, Node<T>* child) // sposta il padre in basso e mette il figlio al suo posto 
	{
		if (parent->parent)
		{
			if (isLeftChild(parent))	//se parent è figlio sinistro
				parent->parent->left = child;
			else
				parent->parent->right = child;
		}
		else
			root = child;

		child->parent = parent->parent;
		parent->parent = child;
	}

	void leftRotate(Node<T>* x)
	{
		Node<T>* y = x->right; // il nuovo padre sarà l'attuale figlio destro di x			
		insertNodeUp(x, y);		// sposto y sopra x

		x->right = y->left;// trapianta il sottoalbero sinistro di y nel sottoalbero destro di x		
		if (y->left) 
			y->left->parent = x;

		y->left = x; // y diventa il nuovo padre di x
	}

	void rightRotate(Node<T>* x)
	{
		Node<T>* y = x->left; // il nuovo padre sarà l'attuale figlio sinistro di x			
		insertNodeUp(x, y);		// sposto y sopra x

		x->left = y->right;// trapianta il sottoalbero destro di y nel sottoalbero sinistro di x		
		if (y->right) 
			y->right->parent = x;

		y->right = x; // y diventa il nuovo padre di x
	}

	void insertFixUp(Node<T>* node)
	{
		if(node == root)	// Caso 0
		{
			node->color = BLACK;
			return;
		}

		//Parenti stretti di node
		Node<T>* padre = node->parent;
		Node<T>* nonno = padre->parent;
		Node<T>* zio = getUncle(node);
		if (padre->color == RED)
		{
			if (zio && zio->color == RED) // Caso 1
			{
				padre->color = BLACK;
				zio->color = BLACK;
				nonno->color = RED;
				insertFixUp(nonno);
			}
			else // Caso 2 (rotazioni)
			{
				if (isLeftChild(padre))
				{
					if (isLeftChild(node))	   // Caso 2.1 (scambio i colori)
						swapColors(padre, nonno);

					else  // Caso 2.2
					{
						leftRotate(padre);	// ruoto a sinistra per ricondurmi al caso 2.1
						swapColors(node, nonno);
					}
					rightRotate(nonno);	// effettuo comunque una rotazione a destra del nonno
				}
				else	// Caso simmetrico al 2
				{
					if (isLeftChild(node))	// faccio quello che avrei fatto se node fosse figlio destro nel caso precedente
					{
						rightRotate(padre);
						swapColors(node, nonno);
					}
					else
						swapColors(padre, nonno);
					leftRotate(nonno);	// stavolta ruoto a sinistra
				}
			}
		}
	}

public:
	RBTree<T>(){root=nullptr;}

	Node<T>* getRoot(){return root;}

	void setRoot(Node<T>* root){this->root = root;}

	Node<T>* searchKey(T key) //search for a key, return the node if exists otherwise return the last node in th path
	{
		Node<T>* tmp = root;
		while (tmp && compare(key,tmp->key) != 0)
		{
			if (compare(key, tmp->key)<0)
			{
				if (tmp->left)
					tmp = tmp->left;
				else 
					break;
			}
			else
			{
				if (tmp->right)
					tmp = tmp->right;
				else
					break;
			}
		}
		return tmp;
	}

	void insertKey(T key) // insert the given key 
	{
		Node<T>* toInsert = new Node<T>(key, RED);
		if(isEmpty())
			root = toInsert;
		else
		{
			Node<T>* tmp = searchKey(key); //search the key
			if (tmp && compare(key, tmp->key) != 0) //value not found
			{
				toInsert->parent = tmp;

				if (compare(key, tmp->key) < 0)
					tmp->left = toInsert;

				else
					tmp->right = toInsert;
			}
			else 
				return;
		} 
		insertFixUp(toInsert); // fix red red violaton if exists 
	}
};

#endif