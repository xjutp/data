/**
 * Trie
 *
 * @Description:
 * Please finish the class "GeneralTree" and use it in the main function to fulfill the request.
 * You can add any function or variable if you want.
 * Note: You must use your own "GeneralTree" class or you will get up to 0 points.
 *
 * @Input Description
 * Input starts with two integers n and m, followed by the n line. Each line is a word, use GeneralTree to create a trie with the n word. Next m line, each line is a word, check if the word exists in the trie.
 *
 * @Output Description
 * Output "1" if the word exists, and "0" if not with a "\n" of each line.
 * And finally, output the serialized string of the trie with a "\n".
 */
#include <bits/stdc++.h>
#define Bug_GeneralTreeNod//e
#define bug_inser//t
#define bug_searc//h
#define bug_set_roo//t
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
    LinkedList(T d): head(NULL), tail(NULL), many(0)
    {
        addToHead (d);
    }
    Node<T> * addToTail(T d)
    {
        Node<T> *tmp = new Node<T>(d);
        if (tail == NULL)
        {
            head = tail = tmp;
            many ++;
            return tmp;
        }
        tail->set_next(tmp);
        tmp->set_prev(tail);
        tail = tmp;
        many ++;
        return tmp;
    }
    Node<T> * addToHead(T d)
    {
        Node<T> *tmp = new Node<T>(d);
        if (head == NULL)
        {
            tail = head = tmp;
            return tmp;
        }
        head->set_prev(tmp);
        tmp->set_next(head);
        head = tmp;
        many ++;
        return tmp;
    }
    Node<T> * addToNext (Node<T> *at, T d)
    {
        Node<T> *tmp;
        for (tmp=head; tmp != NULL && tmp != at; tmp = tmp->get_next());
        if (tmp == NULL) //不在串列中
            return NULL;
        if (tmp == tail) //沒有後一個
        {
            addToTail(d);
            many ++;
            return tmp;
        }
        tmp = new Node<T>(d);
        tmp->set_prev(at);
        tmp->set_next(at->get_next());
        at->set_next(tmp);
        (tmp->get_next())->set_prev(tmp);
        many ++;
        return tmp;
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
        return out;
    }
    int get_many () const
    {
        return many;
    }

};
template<class T>
class Queue
{
private:
    LinkedList<T> *list;
public:
    Queue()
    {
        list = new LinkedList<T>;
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
/**
 * A abstract class for treenode
 * @tparam T Stored data of the node
 */
template<class T>
class TreeNode
{
protected:
    int level;
    bool string_tail;
    T data;
    TreeNode<T> *parent;
    LinkedList<TreeNode<T>*> *children;
public:
    /**
     * @brief Get the Parent
     *
     * @return TreeNode<T>* parent
     */
    virtual TreeNode<T>* get_parent() const = 0;
    /**
     * @brief Set the Parent
     * @param parent to set
     */
    virtual void set_parent(TreeNode<T>* parent) = 0;
    /**
     * @brief Get the Children
     * @return LinkedList<TreeNode<T>*>* children
     */
    virtual LinkedList<TreeNode<T>*>* get_children() const = 0;
    /**
     * @brief Set the Children
     * @param children to set
     */
    virtual void set_children(LinkedList<TreeNode<T>*>* children) = 0;
    virtual T get_data () const = 0;
    virtual void set_data (T d) = 0;
    virtual int get_level () const = 0;
    virtual void set_level (int l) = 0;
    virtual TreeNode<T> *search_children (T d) = 0;
    virtual bool get_string_tail () const = 0;
    virtual void set_string_tail (bool b) = 0;
    virtual void show () const = 0;
};

/**
 * A abstract class for tree
 *
 * @tparam T Stored data in each node of the tree
 * @tparam D Data type that is used to insert and remove.
 */
template<class T, class D>
class Tree
{
protected:
    /**
    * First layer of the tree will be the children of root
    */
    TreeNode<T>* root;
    int max_level;
    int many;
public:
    virtual void levelorder() = 0;
    /**
     * Insert a node to the tree with the given data if it not exists.
     * @param data data to insert
     * @return true if the node is inserted, false if the node already exists
     */
    virtual bool insert(D data) = 0;
    /**
     * Remove a node from the tree with the given data if it exists.
     * @param data data to insert
     * @return true if the node is removed successfully, false if the node is not found
     */
    virtual bool remove(D data) = 0;
    /**
     * Find a node with the given data if it exists.
     * @param data data to insert
     * @return true if the node is found, false if the node is not found
     */
    virtual bool search(D data) = 0;
    /**
     * Set the Root object
     * @param root to set to root
     */
    virtual void set_root(TreeNode<T> *root) = 0;
    /**
     * Rules for Serialize and Deserialize:
     * 1. The serialized string should be in the following format which is standard JSON format but without any spaces:
     * {"root":{"data":"","children":[{"data":"a","children":[{"data":"d","children":[]},{"data":"p","children":[]}]},{"data":"b","children":[]}]}}
     *
     * 2. All nodes in the same layer should be sorted in alphabetical order if is a character type, and sorted by numerical order if is a number type.
     * 3. LinkedList is treated as Array in serialization and deserialization.
     */
    /**
     * Deserialize the string to a tree with levelorder traversal
     * @param tree to be deserialized
     */
    virtual void deSerialize(string tree) = 0;
    /**
     * Serialize the tree to a string with levelorder traversal
     * @return the serialized string
     */
    virtual string serialize() = 0;
    virtual int get_many () const = 0;
    virtual int get_max_level () const = 0;
};

template<class T>
class GeneralTreeNode: public TreeNode<T>
{
public:
    GeneralTreeNode ()
    {
        this->level = 0;
        this->parent = NULL;
        this->children = NULL;
        this->string_tail = false;
    }
    GeneralTreeNode (T d, TreeNode<T> *p, int l)
    {
        this->data = d;
        this->level = l;
        this->parent = p;
        this->children = NULL;
        this->string_tail = false;
    }
    T get_data () const
    {
        return this->data;
    }
    void set_data (T d)
    {
        this->data = d;
    }
    TreeNode<T> *get_parent () const
    {
        return (TreeNode<T> *)this->parent;
    }
    void set_parent (TreeNode<T> *p)
    {
        this->parent = p;
    }
    LinkedList<TreeNode<T>*> *get_children () const
    {
        return (LinkedList<TreeNode<T>*> *)this->children;
    }
    void set_children (LinkedList<TreeNode<T>*> *c)
    {
        this->children = c;
    }
    int get_level () const
    {
        return this->level;
    }
    void set_level (int l)
    {
        this->level = l;
    }
    TreeNode<T> *search_children (T d)
    {
        if (this->children == NULL || this->children->get_head() == NULL)
            return NULL;
        Node<TreeNode<T>*> *t = this->children->get_head();
        while (t != NULL)
        {
            TreeNode<T> *tmp = t->get_data();
            if (tmp->get_data() == d)
                return tmp;
            t = t->get_next();
        }
        return NULL;
    }
    bool get_string_tail () const
    {
        return this->string_tail;
    }
    void set_string_tail (bool b)
    {
        this->string_tail = b;
    }
    void show () const
    {
        cout << "data: "<<this->data<<endl;
        if (this->parent != NULL)
            cout<<"parent: "<<this->parent<<endl;
        else
            cout<<"parent: NULL"<<endl;
        if (this->parent != NULL)
            cout<<"parent->get_data(): "<<this->parent->get_data()<<endl;
        cout<<"children->get_many(): "<<this->children->get_many()<<endl;
    }
};

template<class T, class D>
class GeneralTree: public Tree<T, D>
{
    void _display (TreeNode<T> *r, int d)
    {
        if (r == NULL)
            return;
        int x;
        for (x=0; x < d; x ++)
            cout << "   ";
        if (d != 0)
            cout << r->get_data()<<endl;

        if (r->get_children() != NULL)
        {
            Node<TreeNode<T>*> *t = r->get_children()->get_head();
            while (t != NULL)
            {
                TreeNode<T> *tmp = t->get_data();
                _display (tmp, d + 1);
                t = t->get_next();
            }
        }
    }
    void _serialize (TreeNode<T> *t, string *s)
    {
        char c = '"';
        string v, cc;
        v = c;
        s->append ("{");
        s->append (v);
        s->append ("children");
        s->append (v);
        s->append (":");
        s->append ("[");
        if (t->get_children() != NULL)
        {
            Node<TreeNode<T> *> *tree = t->get_children()->get_head();
            while (1)
            {
                _serialize (tree->get_data(), s);
                tree = tree->get_next();
                if (tree != NULL)
                    s->append (",");
                else
                    break;
            }
        }
        s->append ("]");
        s->append (",");
        s->append (v);
        s->append ("data");
        s->append (v);
        s->append (":");
        s->append (v);
        if (t != this->root)
        {
            cc = t->get_data();
            s->append (cc);
        }
        s->append (v);
        if (t->get_string_tail())
        {
            s->append (",");
            s->append (v);
            s->append ("end");
            s->append (v);
            s->append (":");
            s->append (v);
            s->append ("true");
            s->append (v);
        }
        s->append ("}");
    }
public:
    GeneralTree ()  //TreeNode<T> *node = new GeneralTreeNode<T>();
    {
        this->root = NULL;
        this->many = 0;
        this->max_level = 0;
    }
    bool insert (D d)
    {
#ifdef bug_insert
        printf ("           in insert\n");
#endif // bug_insert
        stringstream ss;
        string data="";
        int x=0;
        ss.str(""), ss.clear();
        ss << d;
        ss >> data;
        if (data == "" || search (data))
            return false;
#ifdef bug_insert
        printf ("not search in tree\n");
#endif // bug_insert
        if (this->root == NULL)
            set_root (new GeneralTreeNode<T>());
        if (this->root->get_children() == NULL)
            this->root->set_children(new LinkedList<TreeNode<T> *>());
        /******************************************************************/
        TreeNode<T> *tmp = this->root;
        TreeNode<T> *f = tmp->search_children(data[x]);
        TreeNode<T> *node;
        Node<TreeNode<T> *> *t;
        while (1)
        {
#ifdef bug_insert
            printf ("       in while (x < data.size())\n");
            printf ("tmp: (");
            cout << tmp;
            printf (")\n");
            printf ("f: (");
            cout << f;
            printf (")\n");
#endif // bug_insert
            if (f == NULL)
            {
#ifdef bug_insert
                printf ("-->TreeNode<T> *node = new GeneralTreeNode<T>(data[x], tmp)\n");
#endif // bug_insert
                node = new GeneralTreeNode<T>(data[x], tmp, tmp->get_level()+1);
                if (tmp->get_children() == NULL)
                    tmp->set_children (new LinkedList<TreeNode<T> *>());
                t = tmp->get_children()->get_head();
                while (t != NULL && data[x] > t->get_data()->get_data())
                    t = t->get_next();
                if (t == NULL) // 空或尾
                    tmp = tmp->get_children()->addToTail (node)->get_data(); // tmp == node
                else if (t == tmp->get_children()->get_head()) //插入為min --> 從頭加
                    tmp = tmp->get_children()->addToHead (node)->get_data();
                else
                    tmp = tmp->get_children()->addToNext (t->get_prev(), node)->get_data();
                this->many ++;
                if (tmp->get_level() > this->max_level)
                    this->max_level = tmp->get_level();
                if (x == data.size()-1)
                    tmp->set_string_tail(true);
            }
            else
            {
                tmp = f;
                if (x == data.size()-1)
                    tmp->set_string_tail(true);
            }
            x ++;
            if (x == data.size())
                break;
            if (tmp->get_children() == NULL)
                tmp->set_children(new LinkedList<TreeNode<T>*>());
            f = tmp->search_children(data[x]);
        }
        return true;
    }
    bool remove (D data)
    {

    }
    bool search (D d)
    {
#ifdef bug_search
        printf ("           in search\n");
#endif // bug_search
        stringstream ss;
        string data="";
        int x=0;

        ss.str(""), ss.clear();
        ss << d;
        ss >> data;

        if (data == "" || this->root == NULL)
            return false;
        TreeNode<T> *tmp = this->root;
        TreeNode<T> *f = tmp->search_children(data[x]);
        while (f != NULL)
        {
            tmp = f;
#ifdef bug_search
            printf ("       in while (tmp != NULL)\n");
#endif // bug_search
            if (x == data.size()-1 && tmp->get_string_tail())
                return true;
            x ++;
            if (x == data.size())
                break;
            f = tmp->search_children (data[x]);
#ifdef bug_search
            if (f == NULL)
                printf ("NULL\n");
#endif // bug_search
        }
        return false;
    }
    void set_root (TreeNode<T> *r)
    {
#ifdef bug_set_root
        printf ("           in set_root\n");
#endif // bug_set_root
        this->root = r;
#ifdef bug_set_root
        printf ("           out set_root\n");
#endif // bug_set_root
    }
    int get_many () const
    {
        return this->many;
    }
    int get_max_level () const
    {
        return this->max_level;
    }
    void levelorder ()
    {
        Queue<TreeNode<T> *> q;
        Node<TreeNode<T>*> *t;
        TreeNode<T> *tmp;

        q.enqueue (this->root);
        while (!q.isEmpty())
        {
            tmp = q.dequeue();
            if (tmp != this->root)
                cout << tmp->get_data();
            if (tmp->get_children() != NULL)
            {
                t = tmp->get_children()->get_head();
                while (t != NULL)
                {
                    TreeNode<T> *tmp = t->get_data();
                    q.enqueue (tmp);
                    t = t->get_next();
                }
            }
        }
    }
    void display ()
    {
        _display (this->root, 0);
    }
    void deSerialize(string tree)
    {

    }
    string serialize()
    {
        string s="";
        char c = '"';
        string v="";
        v = c;
        s.append ("{");
        s.append (v);
        s.append ("root");
        s.append (v);
        s.append (":");
        _serialize (this->root, &s);
        s.append ("}");
        return s;
    }
};


int main ()
{
    GeneralTree<char, string> *gt = new GeneralTree<char, string>();
    string word="";
    //ofstream out("test.txt");
    int N, M;

    cin >> N >> M;
    while (N--)
    {
        cin >> word;
        gt->insert (word);
    }
    //gt->display();
    while (M--)
    {
        cin >> word;
        cout << gt->search (word) << "\n";
        //out << gt->search (word)<< endl;
    }
    cout << gt->serialize() << endl;
    //gt->display();
   //out.close();
    /*while (cin >> word)
    {
        gt->insert (word);

    }*/

    /*gt->insert ("asdb");
    cout <<gt->search ("asd")<<"\n";
    gt->insert ("asd");
    cout <<gt->search ("asd")<<"\n";
    cout << "many tree node: "<<gt->get_many()<<endl;
    cout << "max tree level: "<<gt->get_max_level()<<endl;
    gt->levelorder();
    cout <<"\n";*/
    return 0;
}
