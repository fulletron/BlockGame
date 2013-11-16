#ifndef __GSHASHMAP_H_
#define __GSHASHMAP_H_

template<typename DATA_TYPE>
class GSHashNode
{
public:
	GSHashNode(int a_key, DATA_TYPE a_value) :
	  _key(a_key), _value(a_value), _next(0)
	{}
	
	int key(){return _key;}
	DATA_TYPE value(){return _value;}
	GSHashNode* next(){return _next;}

	void set_value(DATA_TYPE a_value){_value = a_value;}
	void set_next(GSHashNode* a_next){_next = a_next;}

private:
	int					_key;
	DATA_TYPE			_value;
	GSHashNode *		_next;
};

template<typename DATA_TYPE>
class GSHashMap
{
public:
	GSHashMap() :
	  _allocated(16)
	{
		_table = new GSHashNode<DATA_TYPE>*[_allocated];
		for(int i = 0; i < _allocated; ++i)
			_table[i] = 0;
	}

	GSHashMap(int a_size) :
	  _allocated(a_size)
	{
		_table = new GSHashNode<DATA_TYPE>*[_allocated];
		for(int i = 0; i < _allocated; ++i)
			_table[i] = 0;
	}

	~GSHashMap() {
		for(int i = 0; i < _allocated; ++i)
		{
			GSHashNode<DATA_TYPE>* entry = _table[i];
			while(entry != 0)
			{
				GSHashNode<DATA_TYPE>* prev = entry;
				entry = entry->next();
				delete prev;
			}
		}
	}

	DATA_TYPE get(int a_key)
	{
		int hash_val = __hashFunc(a_key);
		GSHashNode<DATA_TYPE>* entry = _table[hash_val];

		while(entry != 0)
		{
			if(entry->key() == a_key)
			{
				return entry->value();
			}
			entry = entry->next();
		}

		/// THIS MAY NOT WORK!
		return 0;
	}

	/** if entry exists, does not set and returns false */
	bool put(int a_key, DATA_TYPE a_value)
	{
		int hash_val = __hashFunc(a_key);
		GSHashNode<DATA_TYPE>* prev = 0;
		GSHashNode<DATA_TYPE>* entry = _table[hash_val];

		while(entry != 0 && entry->key() != a_key)
		{
			prev = entry;
			entry = entry->next();
		}

		if(entry == 0)
		{
			entry = new GSHashNode<DATA_TYPE>(a_key, a_value);
			if(prev == 0) 
			{
				_table[hash_val] = entry;
			}
			else
			{
				prev->set_next(entry);
			}
		}
		else
		{
			return false;
			//entry->set_value(a_value);
		}
		return true;
	}

	void remove(int a_key)
	{
		int hash_val = __hashFunc(a_key);
		GSHashNode<DATA_TYPE>* entry = _table[hash_val];

		GSHashNode<DATA_TYPE>* prev = 0;

		while(entry != 0)
		{
			if(entry->key() == a_key)
				break;

			prev = entry;
			entry = entry->next();
		}

		if(entry == 0)
			return;
		else 
		{
			if(prev == 0)
			{
				_table[hash_val] = entry->next();
			}
			else
			{
				prev->set_next(entry->next());
			}
			delete entry;
		}
	}

private:
	int __hashFunc(int a_key){return a_key % _allocated;}

	GSHashNode<DATA_TYPE> **			_table;
	int									_allocated;
};

#endif