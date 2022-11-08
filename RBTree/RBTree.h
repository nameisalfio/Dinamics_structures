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
		return os << " (" <<  b.key << "," << (b.color == 1 ? "RED" : "BLACK" ) << ")";
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

	void printLevelOrder(Node<T>* x) // level order visit
	{
		queue<Node<T>*> q;
		q.push(x);
		while (!q.empty())
		{
			Node<T>* curr = q.front();
			q.pop();
			if (!curr)
				cout << "(NIL) ";
			else
			{
				cout << *curr;
				q.push(curr->left);
				q.push(curr->right);
			}

		}
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
			else // Caso 2 : lo zio è nero (rotazioni) 
			{
				if (isLeftChild(padre))
				{
					if (isLeftChild(node))	   // Caso 2.1.a : node è esterno quindi i nodi rossi sono entrambi figli sinistri
						swapColors(padre, nonno);	// scambio i colori

					else  // Caso 2.2.a	: node è interno
					{
						leftRotate(padre);	// ruoto a sinistra per ricondurmi al caso 2.1
						swapColors(node, nonno);
					}
					rightRotate(nonno);	// effettuo comunque una rotazione a destra del nonno
				}
				else	// Caso simmetrico al 2.a
				{
					if (isLeftChild(node))	// 2.2.b faccio quello che avrei fatto se node fosse figlio destro nel caso precedente
					{
						rightRotate(padre);
						swapColors(node, nonno);
					}
					else	// 2.2.a : i nodi rossi sono entrambi figli destri 
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

	Node<T>* searchKey(T key) //mi ritorna la chiave cercata se è presente, altrimenti mi restituisce l'ultimo nodo nel percorso
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
			Node<T>* tmp = searchKey(key);	// il nodo che sarebbe padre del nodo da inserire
			if (compare(key, tmp->key) != 0) //chiave non presente nell'albero
			{
				toInsert->parent = tmp;

				if (compare(key, tmp->key) < 0)
					tmp->left = toInsert;

				else
					tmp->right = toInsert;
			}
			else	// chiave già presente nell'albero
				return;
		} 
		insertFixUp(toInsert); // ripristina le violazioni se ve ne sono
	}

	void printLevelOrder() 
	{
		cout << "Level order: " << endl;
		if (isEmpty())
			cout << "NIL" << endl;
		else
			printLevelOrder(root);
		cout << endl;
	}

	void visit(Node<T>* ptr) { cout << "\n" << *ptr << endl; }

	void inOrder(Node<T>* ptr){
		if(!ptr)
			return;

		inOrder(ptr->left);
		visit(ptr);
		inOrder(ptr->right);
	}

	void inOrder(){inOrder(root);}
};

#endif