

#include <iostream>
#include <string>
using namespace std;

/**
 * A Node class of Doublely Linked List class
 */
template<class T>
class Node
{
private:
    Node<T> *prev;
    Node<T> *next;
    T data;
public:

    /**
     * Construct a new Node object with no parameter
     */
    Node(): data(0), prev(NULL), next(NULL) {}

    /**
     * Construct a new Node object with parameter
     * @param data data to put in
     */
    Node(T _data): data(_data), prev(NULL), next(NULL) {}

    /**
     * Construct a new Node object with parameters
     * @param data data to put in
     * @param prev pointer to the previous node
     * @param next pointer to the next node
     */
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

/**
 * A Doublely Linked List class
 */
template<class T>
class LinkedList
{
private:
    Node<T> *head;
    Node<T> *tail;
public:

    /**
     * Construct a new LinkedList object with no parameter
     */
    LinkedList(): head(NULL), tail(NULL) {}
    ~LinkedList()
    {
        while (head != NULL)
            delete deleteFromHead();
    }
    /**
     * Add a node to the tail of the linked list
     * @param data data to put in
     */
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

    /**
     * Add a node to the head of the linked list
     * @param data data to put in
     */
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
    /**
     * Delete a node from the linked list with the given data from the head
     * If there are no data to be deleted, then do nothing
     * @param data data to delete
     */
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

    /**
     * Delete valid n nodes from the linked list with the given data from the head
     * If there are no more data to be deleted, then just skip
     * @param data data to delete
     * @param n max number of nodes to delete
     */
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

    /**
     * Overload the operator << to print out all the data in the linked list from the head
     * There is a \n in the end of each print
     *
     * Output example:
     * If your linked list data is 5, 4, 3, 2, 1
     * then you should print out "(5, 4, 3, 2, 1)" with the content in quotes but without the quotes
     */
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
/**
 * A Stack class
 */
template<class T>
class Stack
{
private:
    LinkedList<T> *list;
public:

    /**
     * Construct a new Stack object with no parameter
     */
    Stack()
    {
        list = new LinkedList<T>;
    }
    ~Stack ()
    {
        delete list;
    }
    /**
     * Add a data to stack
     * @param data data to be added to stack
     */
    void push(T data)
    {
        list->addToTail(data);
    }

    /**
     * Remove a data from stack and return it
     * @return the data removed from stack
     */
    T pop()
    {
        if (list->get_tail() != NULL)
            return list->deleteFromTail()->get_data();
    }

    /**
     * @return the last element in the stack
     */
    T top()
    {
        if (list->get_tail() != NULL)
            return list->get_tail()->get_data();
    }

    /**
     * @return true if stack is empty, false otherwise
     */
    bool isEmpty()
    {
        if (list->get_tail() == NULL)
            return true;
        return false;
    }

    /**
     * @return the size of the stack
     */
    int size()
    {
        return list->get_many();
    }

};
