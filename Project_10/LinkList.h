#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

template<typename ElemType>
struct Node {
	ElemType value;
	struct Node *next;
	Node() :next(NULL) {}
	Node(ElemType v, Node *link = NULL) :
		value(v), next(link) {
	}
};

template<typename ElemType>
class LinkList {
public:
	LinkList();
	~LinkList();
	void InsertLast(ElemType elem);
	void DeleteFirst(ElemType &elem);
	bool Empty()const;
private:
	Node<ElemType> *head, *tail;
};


template<typename ElemType>
LinkList<ElemType>::LinkList() {
	head = tail = new Node<ElemType>();
}

template<typename ElemType>
LinkList<ElemType>::~LinkList() {
	ElemType elem;
	while (!Empty())
		DeleteFirst(elem);
	delete head;
}

template<typename ElemType>
bool LinkList<ElemType>::Empty()const {
	return head == tail;
}

template<typename ElemType>
void LinkList<ElemType>::InsertLast(ElemType elem) {
	tail->next = new Node<ElemType>(elem);
	tail = tail->next;
}

template<typename ElemType>
void LinkList<ElemType>::DeleteFirst(ElemType &elem) {
	if (Empty())return;
	Node<ElemType> *del = head->next, *after = del->next;
	head->next = after;
	elem = del->value;
	delete del;
	if (after == NULL)
		tail = head;
}

#endif