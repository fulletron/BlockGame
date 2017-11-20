#include "nodelist.h"

namespace GS {
namespace Server {

NodeList::NodeList()
	:	m_pHead(0),
		m_numNodes(0)
{
}

void NodeList::pushNode(Node * pNode)
{
	pNode->addToList(this);
	pNode->next(m_pHead);
	m_pHead = pNode;
	++m_numNodes;
}

Node * NodeList::popNode()
{
	Node * pNode = m_pHead;
	if (pNode)
	{
		removeNode(pNode);
	}
	return pNode;
}

Node * NodeList::head() const
{
	return m_pHead;
}

size_t NodeList::count() const
{
	return m_numNodes;
}

bool NodeList::empty() const
{
	return (0 == m_numNodes);
}

void NodeList::removeNode(Node * pNode)
{
	if (pNode == m_pHead)
	{
		m_pHead = pNode->next();
	}

	pNode->__unlink();

	--m_numNodes;
}

Node::Node()
	: m_pNext(0),
	m_pPrev(0),
	m_pList(0)
{
}

Node::~Node()
{
	removeFromList();

	m_pNext = 0;
	m_pPrev = 0;
	m_pList = 0;
}

Node * Node::next() const
{
	return m_pNext;
}

void Node::next(Node * pNext)
{
	m_pNext = pNext;
	if (pNext)
	{
		pNext->m_pPrev = this;
	}
}

void Node::addToList(NodeList * pList)
{
	m_pList = pList;
}

void Node::removeFromList()
{
	if (m_pList)
	{
		m_pList->removeNode(this);
	}
}

void Node::__unlink()
{
	if (m_pPrev)
		m_pPrev->m_pNext = m_pNext;
	if (m_pNext)
		m_pNext->m_pPrev = m_pPrev;

	m_pNext = 0;
	m_pPrev = 0;
	m_pList = 0;
}

};
};