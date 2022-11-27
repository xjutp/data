#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#define L 1000

using namespace std;
// 例外處理 216、壞掉

template<class T>
class Node
{
protected:
    T *data;
public:
    Node()
    {
        data = new T;
    }
    Node(T d)
    {
        data = new T;
        (*data) = d;
    }
    Node &operator=(T d)
    {
        (*data) = d;
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &out, Node n)
    {
        out<<*(n.data);
        return out;
    }
    friend std::ostream &operator<<(std::ostream &out, Node *n)
    {
        out<<*(n->data);
        return out;
    }
    void setData(T d)
    {
        *data = d;
    }
    T &getData() const
    {
        return *data;
    }
};

template<class T>
class ListNode : public Node<T>
{
private:
    ListNode *prev, *next;
public:
    ListNode() : Node<T>()
    {
        prev = NULL;
        next = NULL;
    }
    ListNode(T d) : Node<T>(d)
    {
        prev = NULL;
        next = NULL;
    }
    ListNode(ListNode *p, ListNode *n) : Node<T>()
    {
        prev = p;
        next = n;
    }
    ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d)
    {
        prev = p;
        next = n;
    }
    ListNode *getNext() const
    {
        return next;
    }
    ListNode *getPrev() const
    {
        return prev;
    }
    void setNext(ListNode *n)
    {
        next = n;
    }
    void setPrev(ListNode *p)
    {
        prev = p;
    }
    ListNode &operator=(T d)
    {
        this->setData(d);
        return *this;
    }
};

template<class T>
class LinkList
{
protected:
    ListNode<T> *head, *tail;
public:
    LinkList()
    {
        head = NULL;
        tail = NULL;
    }
    void addFromHead(T d)
    {
        ListNode<T> *node = new ListNode<T>(d);
        if(head != NULL)
        {
            head->setPrev(node);
        }
        node->setNext(head);
        head = node;
        if(tail == NULL)
            tail = node;
    }
    void addFromTail(T d)
    {
        ListNode<T> *node = new ListNode<T>(d);
        if(tail != NULL)
        {
            tail->setNext(node);
        }
        node->setPrev(tail);
        tail = node;
        if(head == NULL)
            head = node;
    }
    void addAfter(ListNode<T> *at, T d)
    {
        if(!exist(at))
            return;
        ListNode<T> *node = new ListNode<T>(d);
        if(at->getNext() != NULL)
            at->getNext()->setPrev(node);
        node->setNext(at->getNext());
        at->setNext(node);
        node->setPrev(at);
        if(node->getNext() == NULL)
            tail = node;
    }
    ListNode<T> *removeFromHead()
    {
        ListNode<T> *n = head;
        if(head != NULL)
        {
            head = head->getNext();
            if(head != NULL)
                head->setPrev(NULL);
            else
                tail = NULL;
            n->setNext(NULL);
        }
        return n;
    }
    ListNode<T> *removeFromTail()
    {
        ListNode<T> *n = tail;
        if(tail != NULL)
        {
            tail = tail->getPrev();
            if(tail != NULL)
                tail->setNext(NULL);
            else
                head = NULL;
            n->setPrev(NULL);
        }
        return n;
    }
    ListNode<T> *remove(ListNode<T> *n)
    {
        if(!exist(n))
            return NULL;
        if(n == head)
            return removeFromHead();
        if(n == tail)
            return removeFromTail();
        n->getPrev()->setNext(n->getNext());
        n->getNext()->setPrev(n->getPrev());
        n->setNext(NULL);
        n->setPrev(NULL);
        return n;
    }
    ListNode<T> *exist(T d)
    {
        ListNode<T> *j = head;
        while(j != NULL)
        {
            if(j->getData() == d)
                return j;
            j = j->getNext();
        }
        return NULL;
    }
    bool exist(ListNode<T> *n)
    {
        ListNode<T> *j = head;
        while(j != NULL)
        {
            if(j == n)
                return true;
            j = j->getNext();
        }
        return false;
    }
    ListNode<T> &operator[](int i)
    {
        ListNode<T> *j = head;
        int k;
        for(k = 0; k < i && j != NULL; k ++)
            j = j->getNext();
        if(j == NULL)
            throw std::invalid_argument("index does not exist.");
        return *j;
    }
    void print() const
    {
        ListNode<T> *j;
        j = head;
        while(j != NULL)
        {
            std::cout<<(*j)<<" "; // 只有Node operator <<
            j = j->getNext();
        }
        std::cout<<std::endl;
    }
};

/*
	Please finish the TreeNode class, TreeNode class respresent a node in a general tree.
	A general tree is different from binary tree, every node in binary tree have at most two child node, but a node in general tree may have more than two child node.
*/
template<class T>
class TreeNode : public Node<T>
{
private:
    LinkList<TreeNode<T> *> *child;
public:
    TreeNode() : Node<T>()
    {
        child = new LinkList<TreeNode<T> *>;
    }
    TreeNode(T d) : Node<T>(d)
    {
        child = new LinkList<TreeNode<T> *>;
    }
    /*
    	Add a child to this node.
    */
    void addChild(TreeNode *n)
    {
        child->addFromTail(n);
    }
    /*
    	Add a child to this node.
    */
    void addChild(T d)
    {
        TreeNode<T> *tmp = new TreeNode<T>(d);
        addChild(tmp);
    }
    /*
    	Return the nth child of the node.
    */
    TreeNode<T> *operator[](int n)
    {
        try
        {
            return (*child)[n].getData();
        }
        catch (std::invalid_argument &e)
        {
            throw std::invalid_argument("index does not exist.");
        }
    }


};

/*
	Please finish the Tree class. Tree class respresent a general tree, that means node on this tree may have more than two child node.

*/
template<class T>
class Tree
{
private:
    TreeNode<T> *root;

    void RC (TreeNode<T> *n)
    {
        cout << n->getData() << " ";
        int x;
        for (x=0; ; x++)
        {
            try
            {
                (*n)[x];
            }
            catch (std::invalid_argument &e)
            {
                break;
            }
            RC ((*n)[x]);
        }
    }
    void CR (TreeNode<T> *n)
    {
        int x;
        for (x=0; ; x++)
        {
            try
            {
                (*n)[x];
            }
            catch (std::invalid_argument &e)
            {
                break;
            }
            RC ((*n)[x]);
        }
        cout << n->getData() << " ";
    }

public:
    Tree(): root(NULL) {}
    /*
    	return the nth node on this tree with level order.
    */
    TreeNode<T> *operator[](int n)
    {
        TreeNode<T> *p, *q[L]= {0};
        int x, y, z;
        q[0] = root;
        for (y=0, x=1, p=q[y]; y < x && x <= n; y++, p=q[y])
            for (z=0; ; z++, x++)
            {
                try
                {
                    (*p)[z];
                }
                catch (std::invalid_argument &e)
                {
                    break;
                }
                q[x] = (*p)[z];
            }
        if (x >= n)
            return q[n];
        throw std::invalid_argument("index does not exist.");
    }
    /*
    	return the number of nodes on this tree.
    */
    int count()
    {
        TreeNode<T> *p, *q[L]= {0};
        int x, y, z;
        if (root == NULL)
            return 0;
        q[0] = root;
        for (y=0, x=1, p=q[y]; y < x; y++, p=q[y])
            for (z=0; ; z++, x++)
            {
                try
                {
                    (*p)[z];
                }
                catch (std::invalid_argument &e) ///
                {
                    break;
                }
                q[x] = (*p)[z];
            }
        //printf ("count: %d\n", y);
        return y;
    }
    /*
    	print all the node on this tree with level order.
    */
    void levelOrder()
    {
        TreeNode<T> *p, *q[L]= {0};
        int x, y, z;
        q[0] = root;
        for (y=0, x=1, p=q[y]; y < x; y++, p=q[y])
            for (z=0; ; z++, x++)
            {
                try
                {
                    (*p)[z];
                }
                catch (std::invalid_argument &e)
                {
                    break;
                }
                q[x] = (*p)[z];
            }
        for (x=0, p=q[x]; x < y; x++, p=q[x])
            cout << p->getData() << " ";
    }
    /*
    	print all the node on this tree with preorder.
    */
    void preorder()
    {
        RC (root);
    }
    /*
    	print all the node on this tree with postorder.
    */
    void postorder()
    {
        CR (root);
    }
    /*
    	set the root of this tree.
    */
    void setRoot(T d)
    {
        root = new TreeNode<T>(d);
    }
};

int main()
{
    Tree<int> *tree = new Tree<int>();
    //printf ("%d", sizeof(*tree)); time(NULL)
    srand(0);
    int j, k, i;
    for(j = 0; j < 20; j ++)
    {
        if(tree->count() == 0)
            tree->setRoot(rand() % 100);
        else
        {
            //printf ("\n\n");
            k = rand() % tree->count();
            //printf ("k: %d\n", k);
            (*tree)[k]->addChild(rand() % 100);
        }
    }
    tree->levelOrder();
    printf ("\n");
    tree->preorder();
    printf ("\n");
    tree->postorder();
    printf ("\n");

    /*
       LinkList<int> l;
       l.addFromTail(3);
       l.addFromTail(4);
       l.addFromTail(5);
       l.addFromTail(6);
       l.print();
    */
}



