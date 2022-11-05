#ifndef CHAINEDHASHTABLE_H
#define CHAINEDHASHTABLE_H

template<class T>
class HashTable{

public:
	virtual void insertKey(T key)=0;
	virtual void deleteKey(T key)=0;
	virtual int searchKey(T key)=0;
};

template<class T>
class ChainedHashTable : public HashTable<T>{

private:
	list<T>* array;
	int m;	//number of slots
	int n;	//number of element

public:
	ChainedHashTable<T>(int slots):n(0)
	{
		this->m = slots;
		array = new list<T>[m];
	}

	virtual int hashFunc(T key)=0;

	int searchKey(T key)
	{
		int idx = hashFunc(key);	// indice dato da h(k)
		typename list<T>::iterator i;	
		for (i = array[idx].begin();  i != array[idx].end();  i++)	// begin() torna il puntatore ad inizio lista
		{
			if (*i == key)	// se l'indice punta alla chiave che cerco lo ritorno
				return idx;
		}
		return -1;	// not found
	}

	void searchKey(T key, int& idx, int& pos)	
	{
		// idx rappresenta l'indice dell'array contenente la sottolista in cui cerco
		// pos rappresenta la distanza della chiave dalla testa della idx-esima lista nell'array (profondità)

		idx = hashFunc(key);
		typename list<T>::iterator i;
		for (i = array[idx].begin(); i != array[idx].end(); i++)	//scorro la idx-esima lista dell'array
		{
			if (*i == key)
			{				
				pos = (int) distance(array[idx].begin(), i);	// conto il numero di incrementi che ho fatto per arrivare ad i (profonfità)
				return;
			}
		}		 
		pos = -1;	// not found
	}		 

	void insertKey(T key)
	{
		int index, pos;		
		searchKey(key, index, pos);	// setto le posizioni (slot e prodondità) della chiave cercata

		if (pos == -1)	// se non ho trovato la chiave la inserisco (non voglio duplicati)
		{			
			array[index].push_front(key);	// insertHead()
			n++;
		}
	}

	void deleteKey(T key)
	{		
		int idx = -1;
		int pos = -1;
		searchKey(key, idx, pos);	  // setto le posizioni (slot e prodondità) della chiave cercata
		if (pos != -1)	// se ho trovato la chiave
		{
			typename list<T>::iterator i = array[idx].begin();
			advance(i, pos);	// scendo di pos elementi a partire da i nell' idx-esima lista
			array[idx].erase(i);
			n--;
		}
	}

	friend ostream& operator<< (ostream& os, ChainedHashTable<T>& ref)
	{
		os << endl;
		for (int i=0; i<ref.m; i++)
		{
			os << i;
			for (int x : ref.array[i])
				os << " --> [" << x << "]";
			os << endl;
		}
		return os;
	}

	int slot()const{return this->m;}
};

template<class T>
class DivChainedHashTable : public ChainedHashTable<T>
{

public:
	DivChainedHashTable<T>(int m) : ChainedHashTable<T>(m) {}

private:
	int hashFunc(T key) 
	{
		int h = ((int)key % this->slot());
		return h;
	}
};

template<class T> 
class MultChainedHashTable : public ChainedHashTable<T>
{
public:
	MultChainedHashTable(int m) : ChainedHashTable<T>(m),c(0.7){}

private:
	double c;
	int hashFunc(T x) 
	{
		double y = x * c;
		double a = y - (int)y;
		int h = (int)(a * this->slot());
		return h;
	}
};

#endif