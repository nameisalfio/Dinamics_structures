#ifndef RBTREE_H
#define RBTREE_H

#include "RBNode.h"

template<typename T>
class RBTree{
	RBNode<T>* root;
	bool verbose;
public:
	RBTree(bool verbose = false) : verbose(verbose){root = nullptr;}

	RBNode<T>* getRoot(){return this->root;}
	bool isEmpty(){return !root;}

	void swapColors(RBNode<T>* x, RBNode<T>* y){
		int aux = x->getColor();
		x->setColor(y->getColor());
		y->setColor(aux);
	}
	void swapKeys(RBNode<T>* x, RBNode<T>* y){
		T aux = x->getKey();
		x->setKey(y->getKey());
		y->setKey(aux);
	}

	bool isLeftChild(RBNode<T>* node){
		if(node->parent)
			return node == node->parent->left;
		return false;
	}

	RBNode<T>* getSibling(RBNode<T>* node){		//restituisce il nodo fratello
		if(!node->parent)
			return nullptr;

		if(isLeftChild(node))
			return node->parent->right;
		return node->parent->left;
	}
	RBNode<T>* getUncle(RBNode<T>* node){		//restituisce il nodo zio
		if(!node->parent || !node->parent->parent)
			return nullptr;
		return getSibling(node->parent);
	}

	void inOrder(){inOrder(root);}
	void inOrder(RBNode<T>* ptr){
		if(!ptr)
			return;
		inOrder(ptr->left);
		visit(ptr);
		inOrder(ptr->right);
	}
	void visit(RBNode<T>* ptr) { 
		if(verbose)
		{
			if(ptr == root){
			cout <<  *ptr << "(root)" << endl; 
			return;
			}
			if(isLeftChild(ptr))
				cout << *ptr << "(left child of " << *ptr->parent << ")" << endl; 
			else
				cout << *ptr << "(right child of " << *ptr->parent << ")" << endl; 
		}
		else
		{
			if(ptr == root){
				cout << "\n" << *ptr << "(root)" << endl; 
				return;
			}
			cout << "\n" << *ptr << endl;
		}
	}

	void insert(T key)
	{
		RBNode<T>* toinsert = new RBNode<T>(key, RED);
		insert(toinsert);
	}
	void insert(RBNode<T>* toinsert)
	{
		if(isEmpty())
		{
			T key = toinsert->key;
			root = new RBNode<T>(key, BLACK);
			return ;
		}

		RBNode<T>* ptr = root; 
		while(true)
		{
			if(toinsert->key <= ptr->key)
			{
				if(!ptr->left) 
					break;
				ptr = ptr->left;
			}
			else
			{
				if(!ptr->right) 
					break;
				ptr = ptr->right;
			}
		}
		toinsert->parent = ptr;

		if(toinsert->key < ptr->key) 
			ptr->left=toinsert;
		else 
			ptr->right=toinsert;

		insertFixUp(toinsert);
		root->color = BLACK;
	}

	void insertUp(RBNode<T>* node, RBNode<T>* parent){	//node = x	parent = y
		if(node->parent)	//se esiste p (genitore di x)
		{
			if(isLeftChild(node))
				node->parent->left = parent;	//se x è figlio sx di p, y diventa il nuovo figlio sx di p

			else
				node->parent->right = parent;	//se x è figlio dx di p, y diventa il nuovo figlio dx di p
		}else
			root = parent;	//y diventa la nuova radice
		
		parent->parent = node->parent;		//il genitore di y diventa p
		node->parent = parent;		//il genitore di x diventa y
	}
	void leftRotate(RBNode<T>* node){
		RBNode<T>* parent = node->right;
		insertUp(node, parent);	//sposta il nodo "parent" sopra il nodo "node"
		node->right = node->left;
		if(parent->left)
			parent->left->parent = node;
		parent->left = node;
	}
	void rightRotate(RBNode<T>* node){
		RBNode<T>* parent = node->left;
		insertUp(node, parent);	//sposta il nodo "parent" sopra il nodo "node"
		node->left = node->right;
		if(parent->right)
			parent->right->parent = node;
		parent->right = node;
	}
	void insertFixUp(RBNode<T>* node){	//node = x
		//Caso 0: x è la radice dell'albero
		if(node == root)
		{
			node->color = BLACK;
			return;
		}
		//se x non è radice devo verificare che non abbia un genitore rosso
		RBNode<T>* parent = node->parent;
		RBNode<T>* granpa = parent->parent;
		RBNode<T>* uncle = getUncle(node);

		//1)Controlla se parent è rosso
		if(parent->color == RED)
		{
			//Caso 1: controllo il colore dello zio di x
			if(uncle && uncle->color == RED) 
			{
				granpa->color = RED;	//il nonno diventa rosso
				parent->color = BLACK;	 //i figli del nonno diventano neri
				uncle->color = BLACK;	
				insertFixUp(granpa);	//controllo se il nonno è radice ricorsivamente
			}
			else	//Caso 2: controllo se il genitore è un figlio sx o dx
			{
				if(isLeftChild(parent))	  //il genitore di x è un figlio sx
				{
					if(isLeftChild(node))	//Caso 2a:  x è figlio sx
					{
						swapColors(parent, granpa);
					}
					else		//Caso 2b:  x è figlio dx
					{					
						leftRotate(parent);	  //faccio risalire x
						swapColors(node, granpa);
					}
					rightRotate(granpa);	//ricado in uno dei due casi precenti(2a o 2b)
				}
				else //il genitore di x è un figlio dx
				{
					if(isLeftChild(node))
					{
						rightRotate(parent);	  //faccio risalire x
						swapColors(node, granpa);
					}
					else	//x è figlio dx
					{
						swapColors(parent, granpa);
					}
					leftRotate(granpa);		//ricado in uno dei due casi precenti
				}
			}
		}
		//se il genitore di x è nero usciamo

	}

	RBNode<T>* max(){return max(root);}
	RBNode<T>* max(RBNode<T>* from){
		if(isEmpty())
            throw out_of_range("Empty red-black tree...");

		RBNode<T>* ptr = from;
		while(ptr->right)
			ptr = ptr->right;
		return ptr;
	}

	RBNode<T>* min(){return min(root);}
	RBNode<T>* min(RBNode<T>* from){
		if(isEmpty())
            throw out_of_range("Empty red-black tree...");

		RBNode<T>* ptr = from;
		while(ptr->left)
			ptr = ptr->left;
		return ptr;
	}

    RBNode<T>* successor(T key){
        RBNode<T>* ptr = search(key);
        if(!ptr || ptr == min())
            throw out_of_range("...successor doesn't exist...");
        return successor(ptr);
    }
	RBNode<T>* successor(RBNode<T>* x){
		if(isEmpty())
			return nullptr;

		if(x->right) 
			return min(x->right);

		RBNode<T>* y = x->parent;
		while(x && !(isLeftChild(x)))  //fino a che x non è un figlio sinistro
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

    RBNode<T>* predecessor(T key){
        RBNode<T>* ptr = search(key);
        if(!ptr || ptr == min())
            throw out_of_range("...predecessor doesn't exist...");
        return predecessor(ptr);
    }
	RBNode<T>* predecessor(RBNode<T>* x){
		if(isEmpty())
			return nullptr;

		if(x->left)
			return max(x->left);

		RBNode<T>* y = x->parent;
		while(x && ifLeftChild(x))  //fino a che x non è un figlio destro
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	RBNode<T>* search(T key){
		if(isEmpty())
            throw out_of_range("Empty red-black tree...");

		return search(root, key);
	}
	RBNode<T>* search(RBNode<T>*ptr , T key){
		if(!ptr)
			return nullptr;

		if(ptr->key == key)
			return ptr;

		if(key <= ptr->key)
			return search(ptr->left, key);

		else
			return search(ptr->right, key);
	}

	RBNode<T>* remove(RBNode<T>* node){ 

		//Caso 1: node è una foglia
		if(!node->left && !node->right)
		{
			if(isLeftChild(node))
				node->parent->left = nullptr;
			else
				node->parent->right = nullptr;
			return node;
		}

		//Caso 2: node ha un solo figlio
		if(!node->right && node->left)
		{
			node->left->setParent(node->parent);

			if(isLeftChild(node))
				node->parent->left = node->left;
			else
				node->parent->right = node->left;
			return node;
		}

		if(!node->left && node->right)
		{
			node->right->setParent(node->parent);

			if(isLeftChild(node))
				node->parent->left = node->right;
			else 
				node->parent->right = node->right;
			return node;
		}
		return nullptr;
	}
	RBNode<T>* remove(T key){
		if(isEmpty()) //albero vuoto
			return nullptr;

		RBNode<T>* node = search(key);

		if(!node)  //nodo non trovato
			return nullptr;

		RBNode<T>* toDelete = remove(node);

		//se non sono nel terzo caso mi ritorno il valore del nodo, che ho comunque cancellato con "remove(node)"

		if(toDelete != nullptr) 
			return toDelete;

		//Caso 3 -> Voglio eliminare un nodo con due figli

		//Sostituisco il nodo da cancellare con il successore
		RBNode<T>* next = successor(node);

		//Sostituisco la chiave
		T swap = node->key;
		node->key = next->key;
		next->key = swap;

		toDelete = remove(next); //stavolta sono sicuramente in uno dei due casi precedenti
		return toDelete;
	}
};

#endif