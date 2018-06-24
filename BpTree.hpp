//
// Created by DUAN Yuxuan & YAN Ge on 2018.5.15.
//

#ifndef DATABASECODE_BPTREE_HPP
#define DATABASECODE_BPTREE_HPP

#include "bpt.h"
#include <cstring>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <thread>

typedef int key_type;
typedef value_t value_type;

class BpTree
{
private:
	bpt::bplus_tree *tree;
	mutable std::shared_mutex treeMutex;
	std::map<key_type, std::shared_mutex> mutexMap;
	
public:
	BpTree(const char* filename)
	{
		tree = new bpt::bplus_tree(filename);
		mutexMap.clear();
	}
	
	bool find(const key_type & key)
	{
		value_type *p = new value_type("");
		int rtn = tree->search(key, p);
		if(rtn == 0)
			return true;
		else
			return false;
	}
	
	value_type get(const key_type & key)
	{
		std::shared_lock<std::shared_mutex> lock(mutexMap[key]);
		
		value_type *p = new value_type("");
		int temp = tree->search(key, p);
		if(temp != 0)
			return value_type("");
		else
		{
			return (*p);
		}
	}
	
	bool insert(const key_type & key, const value_type & value)
	{
		std::unique_lock<std::shared_mutex> bigLock(treeMutex);
		
		value_type *p = new value_type("");
		int rtn = tree->search(key, p);
		if(rtn == 0)
			tree->update(key, value);
		else
			tree->insert(key, value);
		return 1;
	}
	
	bool update(const key_type & key, const value_type & value)
	{
		std::unique_lock<std::shared_mutex> lock(mutexMap[key]);
		
		value_type *p = new value_type("");
		int rtn = tree->search(key, p);
		if(rtn == 0)
			tree->update(key, value);
		else
			tree->insert(key, value);
		return 1;
	}
	
	bool erase(const key_type & key)
	{
		std::unique_lock<std::shared_mutex> bigLock(treeMutex);
		
		value_type *p = new value_type("");
		int rtn = tree->search(key, p);
		if(rtn == 0)
		{
			tree->remove(key);
			return true;
		}
		else
			return false;
	}
	
	~BpTree()
	{
		if(tree)
			delete tree;
	}
};


#endif //DATABASECODE_BPTREE_HPP
