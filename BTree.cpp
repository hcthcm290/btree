#include "BTree.h"
#include <iostream>

using namespace std;


Btree::Btree()
{
	this->Root = new node;
}

Btree::~Btree()
{
	
}

void Btree::travel()
{
	this->Root->travel();
}

void Btree::insert(int k)
{
	if (this->Root->getNumberOfKey() == 2 * this->Root->getMaxDegree() - 1)
	{
		node* temp;
		temp = new node;
		temp->setPointer(this->Root, 0);
		this->Root = temp;
		this->Root->splitNode(0);
		this->Root->insertNonFull(k);
	}
	else
	{
		this->Root->insertNonFull(k);
	}
}

node::node()
{
	this->n = 0;
	this->t = 2;
	this->isLeaf = true;
	this->key = new int[2 * t - 1];
	this->pointer = new node*[2*t];
}

node::~node()
{
	delete[] key;
	delete[] pointer;
}

void node::travel()
{
	if (this->checkLeaf() == true)
	{
		for(int i=0; i<this->getNumberOfKey(); i++)
		{
			cout << this->getKey(i) << " ";
		}
	}
	else
	{
		for (int i = 0; i <= this->getNumberOfKey(); i++)
		{
			this->getPointer(i)->travel();
		}
		for (int i = 0; i < this->getNumberOfKey(); i++)
		{
			cout << this->getKey(i) << " ";
		}
	}
}

bool node::checkLeaf()
{
	return isLeaf;
}

void node::setLeaf(bool x)
{
	this->isLeaf = x;
}

int node::getNumberOfKey()
{
	return this->n;
}

void node::setNumberOfKey(int x)
{
	this->n = x;
}

int node::getMaxDegree()
{
	return this->t;
}

int node::getKey(int k)
{
	return this->key[k];
}

node* node::getPointer(int k)
{
	return this->pointer[k];
}

void node::splitNode(int location)
{
	node* temp = this->getPointer(location);
	node* left;
	left = new node;
	left->setLeaf(temp->checkLeaf());
	left->setNumberOfKey(temp->getMaxDegree() - 1);

	node* right;
	right = new node;
	right->setLeaf(temp->checkLeaf());
	right->setNumberOfKey(temp->getMaxDegree() - 1);

	// copy keys
	for (int i = 0; i < temp->getMaxDegree() - 1; i++)
	{
		left->setKey(temp->getKey(i), i);
		right->setKey(temp->getKey(i + temp->getMaxDegree()), i);
	}

	// copy pointer
 	for (int i = 0; i <= temp->getMaxDegree() - 1; i++)
	{
		left->setPointer(temp->getPointer(i), i);
		right->setPointer(temp->getPointer(i + temp->getMaxDegree()), i);
	}

	// put key to the location in upper node
	for (int i = this->getNumberOfKey(); i > location; i--)
	{
		this->setKey(this->getKey(i - 1), i);
	}
	this->setKey(temp->getKey(temp->getMaxDegree() - 1), location);

	// set pointer split at the position of a node being insert to upper node
	for (int i = this->getNumberOfKey(); i >= location; i--)
	{
		this->setPointer(this->getPointer(i), i + 1);
	}
	this->setPointer(left, location);
	this->setPointer(right, location + 1);
	this->setNumberOfKey(this->getNumberOfKey() + 1);
	this->setLeaf(false);
	delete temp;
}

void node::setKey(int info, int k)
{
	this->key[k] = info;
}

void node::setPointer(node* p, int k)
{
	this->pointer[k] = p;
}

void node::insertNonFull(int k)
{
	int i = this->getNumberOfKey() - 1;
	if (this->checkLeaf())
	{
		for (; i >= 0 && k < this->key[i]; i--)
		{
			key[i + 1] = key[i];
		}
		key[i + 1] = k;
		n += 1;
	}
	else
	{
		for (; i >= 0 && k < key[i]; i--)
		{
		
		}
		i = i + 1;
		if (this->pointer[i]->n == 2 * this->pointer[i]->t - 1)
		{
			this->splitNode(i);
			if (k < this->key[i])
			{
				this->pointer[i]->insertNonFull(k);
			}
			else
			{
				this->pointer[i + 1]->insertNonFull(k);
			}
		}
		else
		{
			this->pointer[i]->insertNonFull(k);
		}
	}
}

