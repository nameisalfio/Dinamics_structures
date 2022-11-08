#include<iostream>
#include<queue>
using namespace std;

#include"RBTree.h"

int main()
{
	RBTree<int> tree;
	tree.insertKey(50);
	tree.insertKey(20);
	tree.insertKey(40);
	tree.inOrder();
}