#ifndef __GSREFERENCEMAP_H_
#define __GSREFERENCEMAP_H_

#include "gsreferencebinarytree.h"

namespace GS {
namespace UtilitiesNS {

template<typename KEY_TYPE, typename DATA_TYPE>
class GSReferenceMap
{
public:
	static const int _MAXIMUM_KEY_BYTESIZE = 8;

	bool add(KEY_TYPE a_key, DATA_TYPE a_data)
	{ 
		return _m_bTree.add(a_key, a_data); 
	}

	DATA_TYPE subtract(KEY_TYPE a_key)
	{
		return _m_bTree.subtract(a_key);
	}

	DATA_TYPE get(KEY_TYPE a_key)
	{
		GSBTReferenceNode<KEY_TYPE, DATA_TYPE>* targetNode = _m_bTree.search(a_key);
		if(targetNode)
			return targetNode->m_data;
		else
			return 0;
	}

	void clear(){_m_bTree->destroy_tree();}
	void gatherIds(GSVector<KEY_TYPE> * out_keys){_m_bTree.gatherIds(out_keys);}

	GSReferenceMap(){}
	~GSReferenceMap(){}
protected:
	GSReferenceBinaryTree<KEY_TYPE, DATA_TYPE> _m_bTree;
};

};
};

#endif