#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
template<class T>
class Node
{
private:
    Node<T> *prev;
    Node<T> *next;
    T data;
public:
    Node(): data(0), prev(NULL), next(NULL) {}
    Node(T _data): data(_data), prev(NULL), next(NULL) {}
    Node(T _data, Node<T> *_prev, Node<T> *_next): data(_data), prev(_prev), next(_next) {}

    T get_data () const
    {
        return data;
    }
    void set_data (T d)
    {
        data = d;
    }
    Node<T> *get_prev () const
    {
        return (Node<T> *)prev;
    }
    void set_prev (Node<T> *p)
    {
        prev = p;
    }
    Node<T> *get_next () const
    {
        return (Node<T> *)next;
    }
    void set_next (Node<T> *n)
    {
        next = n;
    }
    void show () const
    {
        cout << "data: "<<data<<endl;
        if (prev != NULL)
            cout<<"prev: "<<prev<<endl;
        else
            cout<<"prev: NULL"<<endl;
        if (next != NULL)
            cout<<"next: "<<next<<endl;
        else
            cout<<"next: NULL"<<endl;
    }
};

template<class T>
class LinkedList
{
private:
    Node<T> *head;
    Node<T> *tail;
public:
    LinkedList(): head(NULL), tail(NULL) {}
    ~LinkedList()
    {
        while (head != NULL)
            delete deleteFromHead();
    }
    void addToTail(T d)
    {
        Node<T> *tmp = new Node<T>(d);
        if (tail == NULL)
        {
            head = tail = tmp;
            return;
        }
        tail->set_next(tmp);
        tmp->set_prev(tail);
        tail = tmp;
    }
    void addToHead(T d)
    {
        Node<T> *tmp = new Node<T>(d);
        if (head == NULL)
        {
            tail = head = tmp;
            return;
        }
        head->set_prev(tmp);
        tmp->set_next(head);
        head = tmp;
    }
    bool addToNext (Node<T> *at, T d)
    {
        Node<T> *tmp;
        for (tmp=head; tmp != NULL && tmp != at; tmp = tmp->get_next());
        if (tmp == NULL) //不在串列中
            return false;
        if (tmp == tail) //沒有後一個
        {
            addToTail(d);
            return true;
        }
        tmp = new Node<T>(d);
        tmp->set_prev(at);
        tmp->set_next(at->get_next());
        at->set_next(tmp);
        (tmp->get_next())->set_prev(tmp);
        return true;
    }
    Node<T> *deleteFromHead ()
    {
        if (head == NULL) //沒東西可刪
            return NULL;
        Node<T> *tmp = head;
        head = head->get_next();
        if (head == NULL) //刪的是最後一個
        {
            tail = NULL;
            return tmp;
        }
        tmp->set_next(NULL);
        head->set_prev(NULL);
        return tmp;
    }
    Node<T> *deleteFromTail ()
    {
        if (tail == NULL)
            return NULL;
        Node<T> *tmp = tail;
        tail = tail->get_prev();
        if (tail == NULL)
        {
            head = NULL;
            return tmp;
        }
        tmp->set_prev(NULL);
        tail->set_next(NULL);
        return tmp;
    }
    Node<T> *deleteFromMiddle (Node<T> *at)
    {
        Node<T> *tmp;
        for (tmp=head; tmp->get_next() != NULL && tmp->get_next() != at; tmp = tmp->get_next());
        if (tmp->get_next() == NULL) //不在串列中
            return NULL;
        tmp->set_next(at->get_next());
        (at->get_next())->set_prev(tmp);
        at->set_prev(NULL);
        at->set_next(NULL);
        return at;
    }
    void deleteData(T d)
    {
        Node<T> *tmp;
        for (tmp = head; tmp != NULL && tmp->get_data() != d; tmp = tmp->get_next());
        if (tmp != NULL)
        {
            if (tmp == head)
                deleteFromHead();
            else if (tmp == tail)
                deleteFromTail();
            else
                deleteFromMiddle(tmp);
        }
    }
    void deleteData(T d, int n)
    {
        Node<T> *tmp = head, *at;
        while (n > 0 && tmp != NULL)
        {
            for (; tmp != NULL && tmp->get_data() != d; tmp = tmp->get_next());
            if (tmp != NULL)
            {
                at = tmp;
                tmp = tmp->get_next();
                if (at == head)
                    deleteFromHead();
                else if (at == tail)
                    deleteFromTail();
                else
                    deleteFromMiddle(at);
                n--;
            }
        }
    }
    Node<T> *get_head () const
    {
        return (Node<T> *)head;
    }
    Node<T> *get_tail () const
    {
        return (Node<T> *)tail;
    }
    friend std::ostream &operator<<(std::ostream &out, LinkedList * n)
    {
        Node<T> *tmp;
        out << "(";
        for (tmp=n->get_head(); tmp != n->get_tail() ; tmp = tmp->get_next())
            out << tmp->get_data()<<", ";
        out << tmp->get_data()<< ")\n";
    }

};
template<class T>
class Queue {
  private:
    LinkedList<T> *list;
  public:
  Queue()
  {
      list = new LinkedList<T>;
  }
  ~Queue ()
  {
      delete list;
  }
  void enqueue(T data)
  {
      list->addToTail(data);
  }
  T dequeue()
  {
      if (list->get_head() != NULL)
      return list->deleteFromHead()->get_data();
  }
  T front()
  {
      if (list->get_head() != NULL)
      return list->get_head()->get_data();
  }
  bool isEmpty()
  {
      if (list->get_head() == NULL) //全空的情況下頭尾指標才會空
        return true;
      return false;
  }
};

class Tree
{
    void LTR (int index, int *m)
    {
        if (index >= 2000 || root[index] == -1)
            return;
        LTR (index * 2 + 2, m);
        printf ("%d", root[index]);
        (*m) ++;
        if ((*m) != many)
            printf (",");
        LTR (index * 2 + 1, m);
    }
    void TLR (int index, int *m)
    {
        if (index >= 2000 || root[index] == -1)
            return;
        printf ("%d", root[index]);
        (*m) ++;
        if ((*m) != many)
            printf (",");
        TLR (index * 2 + 2, m);
        TLR (index * 2 + 1, m);
    }
    void LRT (int index, int *m)
    {
        if (index >= 2000 || root[index] == -1)
            return;
        LRT (index * 2 + 2, m);
        LRT (index * 2 + 1, m);
        printf ("%d", root[index]);
        (*m) ++;
        if ((*m) != many)
            printf (",");
    }
    void _display (int index, int l)
    {
        if (index >= 2000 || root[index] == -1)
            return;
        _display (index * 2 + 2, l+1);
        for (int x=0; x < l; x ++)
            printf ("   ");
        printf ("%d\n", root[index]);
        _display (index * 2 + 1, l+1);
    }

public:
	Tree()
	{
		int j;
		for(j = 0;j < 2000;j ++)
			root[j] = -1;
        many = 0;
	}
	int insert(int node)
	{
		int index = 0;
		while(index < 2000 && root[index] != -1)
		{
			if(root[index] < node)
				index = index * 2 + 2;
			else
				index = index * 2 + 1;
		}
		root[index] = node;
		many ++;
	}
	void inorder()
	{
	    int m = 0;
	    LTR (0, &m);
	}
	void preorder()
	{
	    int m = 0;
	    TLR (0, &m);
	}
	void postorder()
	{
	    int m = 0;
	    LRT (0, &m);
	}
	void levelorder()
	{
	    int x, y;
	    for (x=0, y=0; x < 2000; x++)
            if (root[x] != -1)
            {
                printf ("%d", root[x]);
                y ++;
                if (y < many)
                    printf (",");
            }
	}
	void display ()
	{
	    _display (0, 0);
	}
private:
	int root[2000];
	int many;
};

int main()
{
	Tree *tree = new Tree();
	int j, node;
	srand(time(NULL));
	for(j = 0;j < 10;j ++)
	{
		node = rand();
		tree->insert(node);
	}
	tree->display ();
	printf ("-----------------------------\n");
	tree->inorder();
	printf("\n");
	tree->preorder();
	printf("\n");
	tree->postorder();
	printf("\n");
	tree->levelorder();
	printf("\n");
}

