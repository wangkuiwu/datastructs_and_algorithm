
#ifndef DOUBLE_LINK_HXX
#define DOUBLE_LINK_HXX

template<class T> 
class DNode 
{
	public:
		T value;
		DNode *prev;
		DNode *next;
	public:
		DNode() { }
		DNode(T t, DNode *prev, DNode *next) {
			this->value = t;
			this->prev  = prev;
			this->next  = next;
	   	}
};

template<class T> 
class DoubleLink 
{
	public:
		DoubleLink();
		~DoubleLink();

		int size();
		int is_empty();

		T get(int index);
		T get_first();
		T get_last();

		int insert(int index, T t);
		int insert_first(T t);
		int append_last(T t);

		int del(int index);
		int delete_first();
		int delete_last();

	private:
		int count;
		DNode<T> *phead;
	private:
		DNode<T> *get_node(int index);
};

#endif
