// Min Heap 
#include<iostream>
#include<vector>
using namespace std;
#pragma once
template <typename T>

struct heap
{

	struct HeapEntry
	{
		int key;
		T data;
		HeapEntry(){}
		HeapEntry(int i,const T&d)
		{
			key=i;
			data=d;
		}
	};

	vector<HeapEntry> tree;
	int parent(int i)                   // index of parent of any entry
	{
		return i/2;
	}

	int left(int i)                   // left child index
	{
		return 2*i;
	}

	int Right(int i)
	{
		return (2*i+1);
	}

	int last()               // last element of heap
	{

		return(tree.size()-1);
	}

	heap()
	{

		tree.push_back(HeapEntry());
	}

	bool empty()
	{
		return tree.size()==1;
	}

	bool GetMin(int & key,T & data)                     // return the value and key of root 
	{
		if(empty())
			return false;
		else
		{
			key=tree[1].key;
			data=tree[1].data;
			return true;
		}
	}
	
	int size()
	{
		return tree.size()-1;
	}

	void Insert(int key,const T &data)
	{
		tree.push_back(HeapEntry(key,data));                // insertion at the end of vector 
		int i=last();

		while(i>1 && (tree[i].key < tree[parent(i)].key ) )     // compare if parent is smaller then child it will swap
		{
			swap(tree[i],tree[parent(i)]);
			i=parent(i);                                      // index at parent
		} 
	}

	void MinHeapify(int i)
	{
		int l=left(i);
		int r1=Right(i);
		int smallest=i;

		if(l>=1 && l<=last() && tree[l].key<tree[smallest].key)                     // firstly find smallest parent and left child 
			smallest=l;

		if(r1>=1 && r1<=last() && tree[r1].key<tree[smallest].key)            // find smallest right child and above smallest
			smallest=r1;

		if(smallest!=i)
		{
			swap(tree[i],tree[smallest]);
			MinHeapify(smallest);
		}
	}

	bool remove()
	{
		if(empty())
			return false;

		else
		{
			swap(tree[1],tree[last()]);
			tree.pop_back();
			MinHeapify(1);
		}
		return true;
	}

	void print()
	{
		for (int i=1; i<tree.size(); i++)
		{
			cout<<tree[i].key<<","<<tree[i].data->dat<<"   ";

		}
	}


};