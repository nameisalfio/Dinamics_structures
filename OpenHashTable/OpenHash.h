#ifndef OPENHASH_H
#define OPENHASH_H

template <class T> 
class HashTable
{
public:
	virtual void insertKey(T key) = 0;
	virtual int searchKey(T key) = 0;
	virtual void deleteKey(T key) = 0;
	virtual void print() = 0;
};

template <class T> 
class OpenHashTable : public HashTable<T>
{
protected:
	virtual int hashFunc(T key, int i) = 0;	
	virtual void insertKey(T key) = 0;
	virtual void deleteKey(T key) = 0;
    virtual int searchKey(T key) = 0;
	int m;
	int n;
	T** table;		

public:

	OpenHashTable<T>(int m):m(m),n(0)
	{				
		table = new T* [m];
		for (int i = 0; i < m; i++)
			table[i] = NULL;
	}

	int getM(){return m;}
};

template <class T> 
class TombstoneOpenHashTable : public OpenHashTable<T>
{
protected:
	virtual int hashFunc(T key, int i) = 0;
	T* deleted;	// punta ad un area di memoria non definita
	
public:
	TombstoneOpenHashTable<T>(int m) : OpenHashTable<T>(m){deleted = new T();}	

	void insertKey(T key)
	{		
		if (this->n == this->m)
			return;	

		for (int i=0; i<this->m; i++)
		{
			int idx = hashFunc(key, i);
			if (this->table[idx] == NULL || this->table[idx] == deleted)
			{
				this->table[idx] = new T(key);
				this->n++;
				return;
			}			
		}
		return;
	}

	int searchKey(T key)
	{
		if (this->n == 0)	  // non ci sono elementi
			return -1;	

		for (int i=0; i < this->m; i++)
		{
			int idx = hashFunc(key, i);	
			if (this->table[idx] == NULL)
				return -1;
			if (this->table[idx] != deleted && *(this->table[idx]) == key)	// unico caso in cui ritorno la chiave
				return idx;			
		}
		return -1;	
	}

	void deleteKey(T key)
	{		
		int pos = searchKey(key);
		if (pos > -1)
		{
			delete this->table[pos];
			this->table[pos] = deleted;
			this->n--;			
		}
		return;
	}

	void print()
	{
		for (int i=0; i<this->m; i++)
		{
			cout << i;
			if (this->table[i] != deleted && this->table[i])
				cout << "-> " << "[" << *(this->table[i]) << "]";
			else
				cout << "-> []";
			cout << endl;
		}
		cout << endl;
	}
};

template <class T> 
class DeleteShiftOpenHashTable : public OpenHashTable<T>
{
private:
	virtual int hashFunc(T key, int i) = 0;

public:
	DeleteShiftOpenHashTable<T>(int m) : OpenHashTable<T>(m) {}

	void insertKey(T key)
	{
		if (this->n == this->m)
			return;		

		for (int i=0; i<this->m; i++)
		{
			int idx = hashFunc(key, i);
			if (this->table[idx] == NULL)
			{				
				this->table[idx] = new T(key);
				this->n++;
				return;
			}			
		}
		return;
	}

	int searchKey(T key)
	{
		if (this->n == 0)
			return -1;	

		for (int i=0; i<this->m; i++)
		{			
			int idx = hashFunc(key, i);
			if (this->table[idx] == NULL)
				return -1;
			if (*(this->table[idx]) == key)
				return idx;			
		}
		return -1;
	}

	void deleteKey(T key)
	{
		if (this->n == 0)
			return;	
		
		for (int i=0; i<this->m; i++)
		{
			int idx = hashFunc(key, i);
			if (this->table[idx] == NULL)
				return;
			if (*(this->table[idx]) == key)
			{
				delete this->table[idx];	
				this->table[idx] = NULL;
				this->n--;
				i++;
				for (; i<this->m; i++)
				{					
					int idx2 = hashFunc(key, i);
					this->table[idx] = (this->table[idx2]);
					if (this->table[idx2] == NULL)
						return;			
					idx = idx2;
				} 				
				return;				
			}			
		}	
		return;		
	}

	void print()
	{
		for (int i=0; i<this->m; i++)
		{
			cout << i;
			if (this->table[i])
				cout << "-> " << "[" << *(this->table[i]) << "]";
			else
				cout << "-> []";
			cout << endl;
		}
		cout << endl;
	}
};

template <class T> 
class LinearHashFunction	  // scansione lineare 
{
protected:
	int hashFunc(T key, int i, int m)
	{ 
		return (((int)key % m) + i) % m; 
	}
};

template <class T> 
class QuadraticHashFunction 	 // scansione quadratica
{
private:
	double c1;
	double c2;
protected:
	int hashFunc(T key, int i, int m)
	{
		return ((int)(((int)key % m) + c1 * i + c2 * pow(i, 2))) % m;
	}
public:
	QuadraticHashFunction(double key, double y)
	{
		c1 = key;
		c2 = y;
	}
};

template <class T> 
class LinearTombstoneOpenHashTable : public TombstoneOpenHashTable<T>, LinearHashFunction<T>
{
protected:
	int hashFunc(T key, int i)
	{
		return LinearHashFunction<T>::hashFunc(key, i, this->m);
	}
public:
	LinearTombstoneOpenHashTable(int m) : TombstoneOpenHashTable<T>(m) {}
};

template <class T> 
class LinearDeleteShiftOpenHashTable : public DeleteShiftOpenHashTable<T>, LinearHashFunction<T>
{
protected:
	int hashFunc(T key, int i)
	{
		return LinearHashFunction<T>::hashFunc(key, i, this->m);
	}
public:
	LinearDeleteShiftOpenHashTable(int m) : DeleteShiftOpenHashTable<T>(m) {}
};

template <class T> 
class QuadraticTombstoneOpenHashTable : public TombstoneOpenHashTable<T>, QuadraticHashFunction<T>
{
private:
	int hashFunc(T key, int i)
	{
		return QuadraticHashFunction<T>::hashFunc(key, i, this->m);
	}
public:
	QuadraticTombstoneOpenHashTable(int m) : TombstoneOpenHashTable<T>(m), QuadraticHashFunction<T>(1/2, 1/2) {}
};

template <class T> 
class QuadraticDeleteShiftOpenHashTable : public DeleteShiftOpenHashTable<T>, QuadraticHashFunction<T>
{
private:
	int hashFunc(T key, int i)
	{
		return QuadraticHashFunction<T>::hashFunc(key, i, this->m);
	}
public:
	QuadraticDeleteShiftOpenHashTable(int m) : DeleteShiftOpenHashTable<T>(m), QuadraticHashFunction<T>(1/2, 1/2) {}
};

#endif