#include<iostream>
#include<cmath>
using namespace std;

#include "OpenHash.h"

int main()
{
	cout << "Standard Version of Linear Probing" << endl;
	LinearTombstoneOpenHashTable<int> tab(11);
	tab.insertKey(72);
	tab.insertKey(90);
	tab.insertKey(57);
	tab.insertKey(38);
	tab.insertKey(34);
	tab.insertKey(4);

	tab.print();
	cout << "Rimuovo 72 e 34: " << endl;
	tab.deleteKey(72);

	cout << "Cerco la chiave 4: " << tab.searchKey(4) << endl;

	cout << "Non-standard Version of Quadratic Probing" << endl;
	QuadraticDeleteShiftOpenHashTable<int> tab2(11);
	tab2.insertKey(4);
	tab2.insertKey(44);
	tab2.insertKey(33);
	tab2.insertKey(77);
	tab2.insertKey(87);
	tab2.insertKey(50);

	tab2.print();

	cout << "Cerco la chiave 87: " << tab2.searchKey(87) << endl;
	cout << "Elimino la chiave 4: " << endl;
	tab2.deleteKey(4);
	tab2.print();

	cout << "Insert key 77 e 22 " << endl;
	tab2.insertKey(77);
	tab2.insertKey(22);

	tab2.print();

	cout << "Cancello i nodi con chiavi 77 e 87: " << endl;
	tab2.deleteKey(77);
	tab2.deleteKey(87);

	tab2.print();	
}