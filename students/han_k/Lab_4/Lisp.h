#ifndef LISP_H
#define LISP_H

template <typename T>
class Lisp
{
	struct Node
	{
		T elem;
		Node *next;
		Node *prev;
		Node( T newElem ){elem = newElem; next = prev = NULL;}
	};
	Node *HEAD,*CURR;
	unsigned int count;
public:
	Lisp<typename T>();
	~Lisp<typename T>();

	void insert( T elem );			//������� � ������ ��������
	void insertHead( T elem );		//������� �������� � ������
	void delCurr();					//������� �������
	bool isNull(){return HEAD==NULL;}
	void moveL();					//�������� � ����� �������
	void moveR();					//�������� � ������ �������
	void moveHead();				
	void editCurr( T elem );		//�������� ������� �������
	T	 getCurr();					//������� ������� �������
	int  getSize(){return count;}	//������ ������
	void clear();
};

template <typename T>
Lisp<T>::Lisp()
{
	count = 0;
	HEAD = CURR = NULL;
}

template <typename T>
Lisp<T>::~Lisp()
{
	HEAD = CURR = NULL;
	count = 0;
}

template <typename T>
void Lisp<T>::insert( T elem )
{
	Node *p = new Node( elem );
	if( HEAD == NULL )
	{
		HEAD = CURR = p;
		p->next = p->prev = HEAD;
	}
	else
	{
		p->next = CURR->next;
		CURR->next = p;
		(p->next)->prev = p;
		p->prev = CURR;
		CURR = p;
	}
	count++;
}

template <typename T>
void Lisp<T>::insertHead( T elem )
{
	Node *p = new Node( elem );
	p->prev = HEAD->prev;
	HEAD->prev->next = p;
	p->next = HEAD;
	HEAD->prev = p;
	HEAD = CURR = p;
	count++;
}

template <typename T>
void Lisp<T>::delCurr()
{
	if( isNull() ) return ;

	Node *p = CURR;

	if( count == 1 )
	{
		delete( HEAD->elem );
		delete( HEAD );
		HEAD = CURR = NULL;
	}
	else
	{
		CURR->prev->next = CURR->next;
		CURR->next->prev = CURR->prev;

		if( CURR == HEAD )		CURR = HEAD = CURR->next;
		else					CURR = CURR->next;

		delete( p->elem );
		delete( p );
	}
	count--;
}

template <typename T>
void Lisp<T>::moveR()
{
	if( isNull() )return;
	CURR = CURR->next;
}

template <typename T>
void Lisp<T>::moveL()
{
	if( isNull() )return;
	cout << CURR << " " << CURR->prev << endl;
	CURR = CURR->prev;
}

template <typename T>
void Lisp<T>::moveHead()
{
	if( isNull() ) return;
	CURR = HEAD;
}

template <typename T>
void Lisp<T>::editCurr(T elem)
{
	if( isNull() ) return ;
	CURR->elem = elem;
}

template <typename T>
T Lisp<T>::getCurr()
{
	if( isNull() ) return NULL;
	return CURR->elem;
}

template <typename T>
void Lisp<T>::clear()
{
	while( count != 0 )
	{
		delCurr();
	}
	HEAD = CURR = NULL;
	count = 0;
}

#endif