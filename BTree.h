#pragma once

class node
{
protected:
	int t;
	int n;
	int* key;
	node** pointer;
	bool isLeaf;

public:
	node();
	~node();
	void travel();
	bool checkLeaf();
	void setLeaf(bool x);
	int getNumberOfKey();
	void setNumberOfKey(int x);
	int getMaxDegree();
	int getKey(int k);
	node* getPointer(int k);
	void splitNode(int i);
	void setKey(int info, int k);
	void setPointer(node* p, int k);
	void insertNonFull(int k);
};

class Btree
{
private:
	node* Root;
public:
	Btree();
	~Btree();
	void travel();
	void insert(int k);
	void deleteKey(int k);
};
