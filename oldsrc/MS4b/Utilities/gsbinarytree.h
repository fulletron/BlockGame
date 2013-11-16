#ifndef __GSBINARYTREE_H_
#define __GSBINARYTREE_H_

#include "gsvector.h"

namespace GS {
namespace UtilitiesNS {


template<typename KEY_TYPE, typename DATA_TYPE>
struct GSBTNode
{
	KEY_TYPE m_key;
	DATA_TYPE m_data;
	GSBTNode<KEY_TYPE, DATA_TYPE> * p_left;
	GSBTNode<KEY_TYPE, DATA_TYPE> * p_right;
};

template<typename KEY_TYPE, typename DATA_TYPE>
class GSBinaryTree
{
public:
	GSBinaryTree(){m_root = 0;}
	~GSBinaryTree(){}

	bool insert(KEY_TYPE a_key, DATA_TYPE a_data)
	{
		if(m_root != 0)
		{
			return __insert(a_key, a_data, m_root);
		}
		else
		{
			m_root = new GSBTNode<KEY_TYPE, DATA_TYPE>;
			m_root->m_key = a_key;
			m_root->m_data = a_data;
			m_root->p_left = 0;
			m_root->p_right = 0;
			return true;
		}
	}

	void remove(KEY_TYPE a_key)
	{
		if(m_root->m_key == a_key)
		{
			if(m_root->p_left)
			{
				GSBTNode<KEY_TYPE, DATA_TYPE> * deleteable = m_root;
				m_root = m_root->p_left;
				if(deleteable->p_right)
					__reinsert(deleteable->p_right, m_root);
				delete deleteable;
			}
			else if(m_root->p_right)
			{
				GSBTNode<KEY_TYPE, DATA_TYPE> * deleteable = m_root;
				m_root = m_root->p_right;
				delete deleteable;
			}
			else
			{
				delete m_root;
				m_root = 0;
			}
		}
		else if((__int64)(a_key) < (__int64)(m_root->m_key))
		{
			if(m_root->p_left != 0)
				__remove(a_key, m_root, m_root->p_left);
			else
				return; /// NO ELEMENT FOUND TO REMOVE
		}
		else
		{
			if(m_root->p_right != 0)
				__remove(a_key, m_root, m_root->p_right);
			else
				return; /// NO ELEMENT FOUND TO REMOVE
		}
	}

	GSBTNode<KEY_TYPE, DATA_TYPE> * search(KEY_TYPE a_key){ return __search(a_key,m_root); }
	void destroy_tree(){ __destroy_tree(m_root); }

	void gatherIds(GSVector<KEY_TYPE> * out_keys)
	{
		__takeId(m_root, out_keys);
	}
	
protected:
	void __takeId(GSBTNode<KEY_TYPE, DATA_TYPE>* a_leaf, GSVector<KEY_TYPE> * out_keys)
	{
		if(a_leaf->p_left)
			__takeId(a_leaf->p_left, out_keys);

		out_keys->add(a_leaf->m_key);

		if(a_leaf->p_right)
			__takeId(a_leaf->p_right, out_keys);
	}

	void __destroy_tree(GSBTNode<KEY_TYPE, DATA_TYPE>* a_leaf)
	{
		if(a_leaf == 0)
			return;
		__destroy_tree(a_leaf->p_left);
		__destroy_tree(a_leaf->p_right);
		delete a_leaf;
	}

	bool __insert(KEY_TYPE a_key, DATA_TYPE a_data, GSBTNode<KEY_TYPE, DATA_TYPE>* a_leaf)
	{
		if((__int64)(a_key) < (__int64)(a_leaf->m_key))
		{
			if(a_leaf->p_left != 0)
				return __insert(a_key, a_data, a_leaf->p_left);
			else
			{
				a_leaf->p_left = new GSBTNode<KEY_TYPE, DATA_TYPE>;
				a_leaf->p_left->m_key = a_key;
				a_leaf->p_left->m_data = a_data;
				a_leaf->p_left->p_left = 0;
				a_leaf->p_left->p_right = 0;
				return true;
			}
		}
		else if((__int64)a_key > (__int64)(a_leaf->m_key))
		{
			if(a_leaf->p_right != 0)
				return __insert(a_key, a_data, a_leaf->p_right);
			else
			{
				a_leaf->p_right = new GSBTNode<KEY_TYPE, DATA_TYPE>;
				a_leaf->p_right->m_key = a_key;
				a_leaf->p_right->m_data = a_data;
				a_leaf->p_right->p_left = 0;
				a_leaf->p_right->p_right = 0;
				return true;
			}
		}
		//else if(key >=)
		return false;
	}

	void __remove(KEY_TYPE a_key, GSBTNode<KEY_TYPE, DATA_TYPE>* a_nodeFrom, GSBTNode<KEY_TYPE, DATA_TYPE>* a_currentLeaf)
	{
		if((__int64)a_key == (__int64)a_currentLeaf->m_key)
		{
			/// THIS IS THE MAGIC STICK!
			if((__int64)a_key > (__int64)a_nodeFrom->m_key)
			{
				a_nodeFrom->p_right = a_currentLeaf->p_left;
				__reinsert(a_currentLeaf->p_right, a_currentLeaf->p_left);
			}
			else
			{
				a_nodeFrom->p_left = a_currentLeaf->p_right;
				__reinsert(a_currentLeaf->p_left, a_currentLeaf->p_right);
			}
			delete a_currentLeaf;
		}
		else if((__int64)a_key < (__int64)a_currentLeaf->m_key)
		{
			if(a_currentLeaf->p_left)
				__remove(a_key, a_currentLeaf, a_currentLeaf->p_left);
		}
		else
		{
			if(a_currentLeaf->p_right)
				__remove(a_key, a_currentLeaf, a_currentLeaf->p_right);
		}
	}
	void __reinsert(GSBTNode<KEY_TYPE, DATA_TYPE>* a_nodeFindingNewHome, GSBTNode<KEY_TYPE, DATA_TYPE> * a_currentLeaf)
	{
		if((__int64)(a_nodeFindingNewHome->m_key) < (__int64)(a_currentLeaf->m_key))
		{
			if(a_currentLeaf->p_left != 0)
				__reinsert(a_nodeFindingNewHome, a_currentLeaf->p_left);
			else
			{
				a_currentLeaf->p_left = a_nodeFindingNewHome;
			}
		}
		else if((__int64)(a_nodeFindingNewHome->m_key) > (__int64)(a_currentLeaf->m_key))
		{
			if(a_currentLeaf->p_right != 0)
				__reinsert(a_nodeFindingNewHome, a_currentLeaf->p_right);
			else
			{
				a_currentLeaf->p_right = a_nodeFindingNewHome;
			}
		}
		/// THERE SHOULD BE NO ELSE, AS IN, CATACLYSMIC FAILURE. THE NODE FINDING A NEW HOME SHOULD NEVER HAVE AN IDENTICAL KEY AS ANYTHING ELSE
	}

	GSBTNode<KEY_TYPE, DATA_TYPE>* __search(KEY_TYPE a_key, GSBTNode<KEY_TYPE, DATA_TYPE>* a_leaf)
	{
		if(a_leaf != 0)
		{
			if((__int64)a_key == (__int64)a_leaf->m_key)
				return a_leaf;
			if((__int64)a_key < (__int64)a_leaf->m_key)
				return __search(a_key, a_leaf->p_left);
			else
				return __search(a_key, a_leaf->p_right);
		}
		return 0;
	}

	GSBTNode<KEY_TYPE, DATA_TYPE>* m_root;
};


};
};

#endif