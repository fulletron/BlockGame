#ifndef __GSREFERENCEBINARYTREE_H_
#define __GSREFERENCEBINARYTREE_H_

#include "gsvector.h"

namespace GS {
namespace UtilitiesNS {

template<typename KEY_TYPE, typename DATA_TYPE>
struct GSBTReferenceNode
{
	KEY_TYPE m_key;
	DATA_TYPE m_data;
	int m_referenceCount;
	GSBTReferenceNode<KEY_TYPE, DATA_TYPE> * p_left;
	GSBTReferenceNode<KEY_TYPE, DATA_TYPE> * p_right;
};

template<typename KEY_TYPE, typename DATA_TYPE>
class GSReferenceBinaryTree
{
public:
	GSReferenceBinaryTree(){m_root = 0;}
	~GSReferenceBinaryTree(){}

	bool add(KEY_TYPE a_key, DATA_TYPE a_data)
	{
		if(m_root != 0)
		{
			return __add(a_key, a_data, m_root);
		}
		else
		{
			m_root = new GSBTReferenceNode<KEY_TYPE, DATA_TYPE>;
			m_root->m_key = a_key;
			m_root->m_data = a_data;
			m_root->m_referenceCount = 1;
			m_root->p_left = 0;
			m_root->p_right = 0;
			return true;
		}
	}

	DATA_TYPE subtract(KEY_TYPE a_key)
	{
		if(m_root->m_key == a_key)
		{
			m_root->m_referenceCount--;
			if(m_root->m_referenceCount <= 0)
			{
				if(m_root->p_left)
				{
					GSBTReferenceNode<KEY_TYPE, DATA_TYPE> * deleteable = m_root;
					m_root = m_root->p_left;
					if(deleteable->p_right)
						__reinsert(deleteable->p_right, m_root);
					DATA_TYPE returnable = m_root->m_data;
					delete deleteable;
					return returnable;
				}
				else if(m_root->p_right)
				{
					GSBTReferenceNode<KEY_TYPE, DATA_TYPE> * deleteable = m_root;
					m_root = m_root->p_right;
					DATA_TYPE returnable = m_root->m_data;
					delete deleteable;
					return returnable;
				}
				else
				{
					DATA_TYPE returnable = m_root->m_data;
					delete m_root;
					m_root = 0;
					return returnable;
				}
			}
			else
			{
				return 0;
			}
		}
		else if((__int64)(a_key) < (__int64)(m_root->m_key))
		{
			if(m_root->p_left != 0)
				return __subtract(a_key, m_root, m_root->p_left);
			else
				return 0; /// NO ELEMENT FOUND TO REMOVE
		}
		else
		{
			if(m_root->p_right != 0)
				return __subtract(a_key, m_root, m_root->p_right);
			else
				return 0; /// NO ELEMENT FOUND TO REMOVE
		}
	}

	GSBTReferenceNode<KEY_TYPE, DATA_TYPE> * search(KEY_TYPE a_key){ return __search(a_key,m_root); }
	void destroy_tree(){ __destroy_tree(m_root); }

	void gatherIds(GSVector<KEY_TYPE> * out_keys)
	{
		__takeId(m_root, out_keys);
	}
	
protected:
	void __takeId(GSBTReferenceNode<KEY_TYPE, DATA_TYPE>* a_leaf, GSVector<KEY_TYPE> * out_keys)
	{
		if(a_leaf->p_left)
			__takeId(a_leaf->p_left, out_keys);

		out_keys->add(a_leaf->m_key);

		if(a_leaf->p_right)
			__takeId(a_leaf->p_right, out_keys);
	}

	void __destroy_tree(GSBTReferenceNode<KEY_TYPE, DATA_TYPE>* a_leaf)
	{
		if(a_leaf == 0)
			return;
		__destroy_tree(a_leaf->p_left);
		__destroy_tree(a_leaf->p_right);
		delete a_leaf;
	}

	bool __add(KEY_TYPE a_key, DATA_TYPE a_data, GSBTReferenceNode<KEY_TYPE, DATA_TYPE>* a_leaf)
	{
		if((__int64)(a_key) < (__int64)(a_leaf->m_key))
		{
			if(a_leaf->p_left != 0)
				return __add(a_key, a_data, a_leaf->p_left);
			else
			{
				a_leaf->p_left = new GSBTReferenceNode<KEY_TYPE, DATA_TYPE>;
				a_leaf->p_left->m_key = a_key;
				a_leaf->p_left->m_data = a_data;
				a_leaf->p_left->m_referenceCount = 1;
				a_leaf->p_left->p_left = 0;
				a_leaf->p_left->p_right = 0;
				return true;
			}
		}
		else if((__int64)a_key > (__int64)(a_leaf->m_key))
		{
			if(a_leaf->p_right != 0)
				return __add(a_key, a_data, a_leaf->p_right);
			else
			{
				a_leaf->p_right = new GSBTReferenceNode<KEY_TYPE, DATA_TYPE>;
				a_leaf->p_right->m_key = a_key;
				a_leaf->p_right->m_data = a_data;
				a_leaf->p_right->m_referenceCount = 1;
				a_leaf->p_right->p_left = 0;
				a_leaf->p_right->p_right = 0;
				return true;
			}
		}
		else if((__int64)(a_key) == (__int64)(a_leaf->m_key))
		{
			a_leaf->m_referenceCount++;
			return true;
		}
		return false;
	}

	DATA_TYPE __subtract(KEY_TYPE a_key, GSBTReferenceNode<KEY_TYPE, DATA_TYPE>* a_nodeFrom, GSBTReferenceNode<KEY_TYPE, DATA_TYPE>* a_currentLeaf)
	{
		if((__int64)a_key == (__int64)a_currentLeaf->m_key)
		{
			a_currentLeaf->m_referenceCount--;
			if(a_currentLeaf->m_referenceCount <= 0)
			{
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
				GSBTReferenceNode<KEY_TYPE, DATA_TYPE> * deleteable = a_currentLeaf;
				DATA_TYPE returnable = m_root->m_data;
				delete deleteable;
				return returnable;
			}
		}
		else if((__int64)a_key < (__int64)a_currentLeaf->m_key)
		{
			if(a_currentLeaf->p_left)
				return __subtract(a_key, a_currentLeaf, a_currentLeaf->p_left);
		}
		else
		{
			if(a_currentLeaf->p_right)
				return __subtract(a_key, a_currentLeaf, a_currentLeaf->p_right);
		}
		return 0;
	}
	void __reinsert(GSBTReferenceNode<KEY_TYPE, DATA_TYPE>* a_nodeFindingNewHome, GSBTReferenceNode<KEY_TYPE, DATA_TYPE> * a_currentLeaf)
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

	GSBTReferenceNode<KEY_TYPE, DATA_TYPE>* __search(KEY_TYPE a_key, GSBTReferenceNode<KEY_TYPE, DATA_TYPE>* a_leaf)
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

	GSBTReferenceNode<KEY_TYPE, DATA_TYPE>* m_root;
};


};
};

#endif