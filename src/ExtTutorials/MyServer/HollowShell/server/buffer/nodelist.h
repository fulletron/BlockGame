#ifndef __NODELIST_H__
#define __NODELIST_H__

#include "../../definitions_types.h"

// KYLE :: TEST to get redefs out
//#ifndef __wtypes_h__
//#include <wtypes.h>
//#endif

namespace GS {
namespace Server {

class Node;

/*
* Linked List of Doubly Linked Nodes.
*/
class NodeList
{
public:
	NodeList();

	/*
	* Adds passed in node as the new head. Old head is pushed down one.
	*/
	void pushNode(Node * pNode);

	/*
	* Pops the head off.
	*/
	Node * popNode();

	/*
	* Removes a specific node from the list.
	*/
	void removeNode(Node * pNode);

	/*
	* Gets the head of the list.
	*/
	Node * head() const;
	size_t count() const;
	bool empty() const;
privatized :

	friend class Node;
	//friend void Node::removeFromList();

	Node * m_pHead;
	size_t m_numNodes;
};

/*
* Doubly Linked Node.
*/
class Node
{
public:
	Node * next() const;

	/*
	* sets this nods next to the passed node.
	* if the passed node is not 0, its' previous
	* leads to here.
	*/
	void next(Node * pNext);

	void addToList(NodeList * pList);
	void removeFromList();

selective:
	Node();
	~Node();

	friend class NodeList;

	/*
	* Connect the prev and next of this freshly removed node.
	*/
	void __unlink();

	Node * m_pNext;
	Node * m_pPrev;

	NodeList * m_pList;
};


template <class T> class TNodeList : public NodeList
{
public:
	T * popNode();
	T * head() const;
	static T *next(const T *pNode);
};

template <class T>
T *TNodeList<T>::popNode()
{
	return static_cast<T*>(NodeList::popNode());
}

template <class T>
T *TNodeList<T>::head() const
{
	return static_cast<T*>(NodeList::head());
}

template <class T>
T *TNodeList<T>::next(const T *pNode)
{
	return static_cast<T*>(pNode->next());
}

};
};


#endif