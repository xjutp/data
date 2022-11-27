/**
 * Tower of Hanoi
 *
 * @Description
 * Tower of Hanoi is a mathematical puzzle where we have three rods and n disks. The objective of the puzzle is to move the entire stack to another rod, obeying the following simple rules:
 * 1. Only one disk can be moved at a time.
 * 2. Each move consists of taking the upper disk from one of the stacks and placing it on top of another stack i.e. a disk can only be moved if it is the uppermost disk on a stack.
 * 3. No disk may be placed on top of a smaller disk.
 *
 * There are only 3 rods "A", "B" and "C", you need to move all the disks from rod "A" to rod "C" and print the minimum number of moves required to complete the question.
 *
 * Note: You must use your own "Stack" class, no recursive function can be used and no formula like 2^N-1 can be used, or you will get up to 0 points.
 *
 * @Input Description
 * The number of the disks on the rod "A", ends up with line-break or end-of-file.
 *
 * @Output Description
 * The minimum number of moves required, ending with a "\n" of each line
 */
#include <iostream>
#include <string>
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
    int many;
public:
    LinkedList(): head(NULL), tail(NULL), many(0) {}

    void addToTail(T d)
    {
        Node<T> *tmp = new Node<T>(d);
        if (tail == NULL)
        {
            head = tail = tmp;
            many ++;
            return;
        }
        tail->set_next(tmp);
        tmp->set_prev(tail);
        tail = tmp;
        many ++;
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
        many ++;
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
            many ++;
            return true;
        }
        tmp = new Node<T>(d);
        tmp->set_prev(at);
        tmp->set_next(at->get_next());
        at->set_next(tmp);
        (tmp->get_next())->set_prev(tmp);
        many ++;
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
            many --;
            return tmp;
        }
        tmp->set_next(NULL);
        head->set_prev(NULL);
        many --;
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
            many --;
            return tmp;
        }
        tmp->set_prev(NULL);
        tail->set_next(NULL);
        many --;
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
        many --;
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
    int get_many () const
    {
        return many;
    }
};

template<class T>
class Stack
{
private:
    LinkedList<T> *list;
public:
    Stack()
    {
        list = new LinkedList<T>;
    }
    void push(T data)
    {
        list->addToTail(data);
    }
    T pop()
    {
        if (list->get_tail() != NULL)
            return list->deleteFromTail()->get_data();
    }
    T top()
    {
        if (list->get_tail() != NULL)
            return list->get_tail()->get_data();
    }
    bool isEmpty()
    {
        if (list->get_tail() == NULL)
            return true;
        return false;
    }
    int size()
    {
        return list->get_many();
    }
    void take_to (Stack<T> *o)
    {
        T take;
        take = this->pop();
        o->push(take);
    }
};
template<class T>
void show_all (Stack<T> *A, Stack<T> *B, Stack<T> *C, int *move_times)
{
    printf ("A:\n");
    A->show();
    printf ("B:\n");
    B->show();
    printf ("C:\n");
    C->show();
    printf ("move_times: %d\n\n", *move_times);
}
template<class T>
void part1 (Stack<T> *A, Stack<T> *B, Stack<T> *C, int *move_times)
{
    A->take_to(B); //ab
    (*move_times) ++;
    A->take_to(C); //ac
    (*move_times) ++;
    B->take_to(C); //bc
    (*move_times) ++;
}
template<class T>
void part2 (Stack<T> *A, Stack<T> *B, Stack<T> *C, int *move_times)
{
    C->take_to(A); //ca
    (*move_times) ++;
    C->take_to(B); //cb
    (*move_times) ++;
    A->take_to(B); //ab
    (*move_times) ++;
}
template<class T>
void part3 (Stack<T> *A, Stack<T> *B, Stack<T> *C, int *move_times)
{
    B->take_to(C); //bc
    (*move_times) ++;
    B->take_to(A); //ba
    (*move_times) ++;
    C->take_to(A); //ca
    (*move_times) ++;
}

int main()
{
    int initial, move_times;
    Stack<int> *A, *B, *C;
    while (cin >> initial)
    {
        A = new Stack<int>;
        B = new Stack<int>;
        C = new Stack<int>;
        move_times = 0;
        /**輸入**/
        if (initial == 1)
        {
            move_times = 1;
            goto End;
        }
        for (; initial > 0; initial--)
            A->push(initial);
        /* printf ("cin:\nA:\n");
         A->show();
         printf ("\n\n");*/
        /**計算**/
        while (1)
        {
            part1(A, B, C, &move_times);
            if (A->isEmpty() && B->isEmpty())
                break;
            if (B->isEmpty()) // ab
            {
                A->take_to(B); //ab
                move_times ++;
            }
            else if (A->isEmpty())
            {
                B->take_to(A); //ba
                move_times ++;
            }
            else if (A->top() < B->top())
            {
                A->take_to(B); //ab
                move_times ++;
            }
            else // a > b
            {
                B->take_to(A); //ba
                move_times ++;
            }
            part2(A, B, C, &move_times);
            if (A->isEmpty() && C->isEmpty())
                break;
            if (C->isEmpty()) //ac
            {
                A->take_to(C); //ac
                move_times ++;
            }
            else if (A->isEmpty()) //ca
            {
                C->take_to(A); //ca
                move_times ++;
            }
            else if (A->top() < C->top()) //ac
            {
                A->take_to(C); //ac
                move_times ++;
            }
            else //ca
            {
                C->take_to(A); //ca
                move_times ++;
            }
            part3(A, B, C, &move_times);
            if (C->isEmpty())
            {
                B->take_to(C); //bc
                move_times ++;
            }
            else if (B->isEmpty())
            {
                C->take_to(B); //cb
                move_times ++;
            }
            else if (B->top() < C->top())
            {
                B->take_to(C); //bc
                move_times ++;
            }
            else
            {
                C->take_to(B); //cb
                move_times ++;
            }

        }
End:
        cout << move_times << "\n";
        /* if (move_times != 1)
             show_all(A, B, C, &move_times);*/
        delete A;
        delete B;
        delete C;
    }




    return 0;
}
