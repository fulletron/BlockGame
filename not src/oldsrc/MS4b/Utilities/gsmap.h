#ifndef __GSMAP_H_
#define __GSMAP_H_

#include "gsbinarytree.h"

namespace GS {
namespace UtilitiesNS {

template<typename KEY_TYPE, typename DATA_TYPE>
class GSMap
{
public:
	static const int _MAXIMUM_KEY_BYTESIZE = 8;

	bool insert(KEY_TYPE a_key, DATA_TYPE a_data){ return _m_bTree.insert(a_key, a_data); }
	void remove(KEY_TYPE a_key){_m_bTree.remove(a_key);}
	DATA_TYPE get(KEY_TYPE a_key){return _m_bTree.search(a_key)->m_data;}
	void clear(){_m_bTree->destroy_tree();}
	void gatherIds(GSVector<KEY_TYPE> * out_keys){_m_bTree.gatherIds(out_keys);}
protected:
	GSBinaryTree<KEY_TYPE, DATA_TYPE> _m_bTree;
};

};
};

#endif