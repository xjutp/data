

/**
 * File System
 *
 * @Description:
 * Please use the class "GeneralTree" to simulate a Unix File System.
 * Reference: https://www.geeksforgeeks.org/unix-file-system/
 * But only Ordinary files and Directories will appear in the File System, which is determined by the tag "type" which is "dir" or "file"
 *
 * There are five operations you need to do:
 * 1. mv <source> <destination>
 *  - move the file or the entire directory from <source> to under <destination>
 *  - Replace the files of <destination> if it exists
 *  - Cancel operation if <source> does not exist.
 * 2. cp <source> <destination>
 *  - copy the file or the entire directory from <source> to under <destination>
 *  - Replace the files of <destination> if it exists
 *  - Cancel operation if <source> does not exist.
 * 3. rm <destination>
 *  - remove the file or directory from <destination>
 *  - Cancel operation if <destination> does not exist.
 * 4. touch <destination> <data>
 *  - add a file to <destination> that contains <data>
 *  - Create directories which in the path if it does not exist.
 *  - Replace the files of <destination> if it exists.
 * 5. mkdir <destination>
 *  - add a directory to <destination>
 *  - Create directories which in the path if it does not exist.
 *  - Cancel operation if <destination> already exist.
 * <source> and <destination> are both absolute pathnames.
 * <data> is a string, could be empty.
 *
 * Serialized property of node for File:
 * {
 *  "data":"<data for the file>",
 *  "path":"<relative pathnames for this node>",
 *  "type":"file"
 * }
 *
 * Serialized property of node for Directory:
 * {
 *  "children":[<children of this node>],
 *  "path":"<relative pathnames for this node>",
 *  "type":"dir"
 * }
 *
 * You can add any function or variable if you want.
 * Note: You must use your own "GeneralTree" class or you will get up to 0 points.
 *
 * @Input Description
 * The first line of input is the serialized string of the GeneralTree.
 * The following line til the end will be the operations, one operation per line.
 *
 * @Output Description
 * A serialized string of the GeneralTree after operations with a "\n".
 */
#include <bits/stdc++.h>
#define bu//g
#define bug_link_delet//e
#define bug_search_children_path_//d
#define bug_search_children_path_//f
#define Bug_GeneralTreeNod//e
#define bug_inser//t
#define bug_searc//h
#define bug_deSerializ//e
#define bug_remov//e
#define bug__searc//h
#define bug_m//v
#define bug_c//p
#define bug_set_paren//t
#define bug__search_treenod//e
#define bug_GeneralTreeNod//e
#define bug_add_childre//n
using namespace std;

int VS_string (string lv, string rv)
{
    int x, ll=lv.size(), rl=rv.size();
    for (x=0; x < ll && x < rl && lv[x] == rv[x] ; x++);
    if (x == ll && x == rl)
        return 0;
    else if (x == ll)
        return -1;
    else if (x == rl)
        return 1;
    else if (lv[x] < rv[x])
        return -1;
    else if (lv[x] > rv[x])
        return 1;
}

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
    //Node (Node<T> *o): data(o->data), next(o->next), prev(o->prev) {}
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
            many ++;
        if (tail == NULL)
        {
            head = tail = tmp;
            return tmp;
        }
        tail->set_next(tmp);
        tmp->set_prev(tail);
        tail = tmp;
        return tmp;
    }
    Node<T> * addToHead(T d)
    {
        Node<T> *tmp = new Node<T>(d);
        many ++;
        if (head == NULL)
        {
            tail = head = tmp;
            return tmp;
        }
        head->set_prev(tmp);
        tmp->set_next(head);
        head = tmp;
        return tmp;
    }
    Node<T> * addToNext (Node<T> *at, T d)
    {
        if (at == NULL)
            return NULL;
        Node<T> *tmp;
        for (tmp=head; tmp != NULL && tmp != at; tmp = tmp->get_next());
        if (tmp == NULL) //不在串列中
            return NULL;
        if (tmp == tail) //沒有後一個
            return addToTail(d);
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
#ifdef bug_link_delete
        printf ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf ("in deleteFromHead\n\n");
#endif // bug_link_delete
        if (head == NULL) //沒東西可刪
            return NULL;
        Node<T> *tmp = head;
#ifdef bug_link_delete
        printf ("--> tmp = head\ntmp: ");
        cout<<tmp->get_data()<<endl;
        printf ("   tmp->get_data()->show():\n");
        tmp->get_data()->show();
        printf ("\n\n");
#endif // bug_link_delete
        head = head->get_next();
#ifdef bug_link_delete
        printf ("--> head = head->get_next()\nhead: ");
        if (head == NULL)
            cout << "NULL\n";
        else
            cout<<tmp->get_data()<<endl;
#endif // bug_link_delete
        tmp->set_next(NULL);
        if (head == NULL) //刪的是最後一個
        {
            tail = NULL;
            many --;
            return tmp;
        }
        head->set_prev(NULL);
        many --;
        return tmp;
    }
    Node<T> *deleteFromTail ()
    {
#ifdef bug_link_delete
        printf ("-------------------\n");
        printf ("in deleteFromTail\n\n");
#endif // bug_link_delete
        if (tail == NULL)
            return NULL;
        Node<T> *tmp = tail;
#ifdef bug_link_delete
        printf ("--> tmp = tail\ntmp: ");
        cout<<tmp->get_data()<<endl;
        printf ("   tmp->get_data()->show():\n");
        tmp->get_data()->show();
        printf ("\n\n");
#endif // bug_link_delete
        tail = tail->get_prev();
#ifdef bug_link_delete
        printf ("--> tail = tail->get_prev()\ntail: ");
        if (tail == NULL)
            cout << "NULL\n";
        else
            cout<<tmp->get_data()<<endl;
#endif // bug_link_delete
        tmp->set_prev(NULL);
        if (tail == NULL)
        {
            head = NULL;
            many --;
            return tmp;
        }
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
    Node<T> * deleteData(T d)
    {
#ifdef bug_link_delete
        printf (".....................\n");
        printf ("\tin delete (T d)\n\nd: ");
        cout << d << endl;
#endif // bug_link_delete
        Node<T> *tmp;
        for (tmp = head; tmp != NULL && tmp->get_data() != d; tmp = tmp->get_next());
#ifdef bug_link_delete
if (tmp == NULL)
    printf ("tmp: NULL\n");
else
{
    printf ("find tmp->get_data()->show(): \n");
    tmp->get_data()->show();
    printf ("\n\n");
}
#endif // bug_link_delete
        if (tmp != NULL)
        {
            if (tmp == head)
                return deleteFromHead();
            else if (tmp == tail)
                return deleteFromTail();
            else
                return deleteFromMiddle(tmp);
        }
#ifdef bug_link_delete
        printf ("\tout delete (T d)\n\n");
        printf (".....................\n");
#endif // bug_link_delete
        return NULL;
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
};
/**
 * A abstract class for treenode
 * @tparam T Stored data of the node
 */
template<class T>
class TreeNode
{
protected:
    T data;
    T path;
    T type;
    int level;
    bool string_tail;
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
    virtual void show () const = 0;
    virtual T get_data () const = 0;
    virtual void set_data (T d) = 0;
    virtual T get_path () const = 0;
    virtual void set_path (T d) = 0;
    virtual T get_type () const = 0;
    virtual void set_type (T d) = 0;
    virtual int get_level () const = 0;
    virtual void set_level (int l) = 0;
    virtual void set_string_tail (bool b) = 0;
    virtual bool get_string_tail () const = 0;
    virtual TreeNode<T> *search_children (T d) = 0;
    virtual TreeNode<T> *search_children_path_d (T d) = 0;
    virtual TreeNode<T> *search_children_path_f (T d) = 0;
    virtual TreeNode<T> *add_children (TreeNode<T> *child) = 0;
    virtual void copy_all_children (LinkedList<TreeNode<T> *> *child) = 0;
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
    ~GeneralTreeNode ()
    {
        if (this->children != NULL)
        {
            if (this->children->get_head() != NULL)
            {
                Node<TreeNode<T> *> *t = this->children->get_head();
                while (t != NULL)
                {
                    TreeNode<T> *tmp = t->get_data();
                    Node<TreeNode<T> *> *rm = t;
                    delete tmp;
                    t = t->get_next();
                    delete rm;
                }
            }
            delete this->children;
        }
    }
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
    GeneralTreeNode (TreeNode<T> *p, int l)
    {
        this->level = l;
        this->parent = p;
        this->children = NULL;
        this->string_tail = false;
    }
    GeneralTreeNode (TreeNode<T> *o, TreeNode<T> *p)
    {
        if (o->get_type() == "dir")
        {
#ifdef bug_GeneralTreeNode
            printf ("\tin GeneralTreeNode (TreeNode<T> *o = (%p), TreeNode<T> *p = (%p))\n", o, p);
            printf ("this: %p\n", this);
#endif // bug_GeneralTreeNode
            this->path = o->get_path();
            this->type = "dir";
            this->level = o->get_level();
            this->parent = p;
            this->string_tail = o->get_string_tail();
            copy_all_children(o->get_children());
#ifdef bug_GeneralTreeNode
            printf ("this->show(): \n");
            this->show();
            printf ("\n");
            printf ("\tout GeneralTreeNode (TreeNode<T> *o = (%p), TreeNode<T> *p = (%p))\n\n", o, p);
#endif // bug_GeneralTreeNode
        }
        else if (o->get_type() == "file")
        {
            this->data = o->get_data();
            this->path = o->get_path();
            this->type = "file";
            this->level = o->get_level();
            this->parent = p;
            this->string_tail = o->get_string_tail();
            copy_all_children(o->get_children());
        }
        else
        {
            this->data = o->get_data();
            this->level = o->get_level();
            this->parent = p;
            this->string_tail = o->get_string_tail();
            copy_all_children(o->get_children());
        }
    }
    T get_data () const
    {
        return this->data;
    }
    void set_data (T d)
    {
        this->data = d;
    }
    T get_path () const
    {
        return this->path;
    }
    void set_path (T p)
    {
        this->path = p;
    }
    T get_type () const
    {
        return this->type;
    }
    void set_type (T t)
    {
        this->type = t;
    }
    TreeNode<T> *get_parent () const
    {
        return (TreeNode<T> *)this->parent;
    }
    void set_parent (TreeNode<T> *p)
    {
#ifdef bug_set_parent
        printf ("\tin set_parent\np: %p\n", p);
#endif // bug_set_parent
        this->parent = p;
#ifdef bug_set_parent
        printf ("--> this->parent = p\nthis->parent: %p\n\tout set_parent\n\n", this->parent);
#endif // bug_set_parent
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
    TreeNode<T> *search_children_path_d (T d)
    {
#ifdef bug_search_children_path_d
        printf ("           in search_children_path\n");
        printf ("want search path: ");
        cout << d;
        printf ("\n\n");
#endif // bug_search_children_path_d
        if (this->children == NULL || this->children->get_head() == NULL || this->type == "file")
            return NULL;
        Node<TreeNode<T>*> *t = this->children->get_head();
        while (t != NULL)
        {
            TreeNode<T> *tmp = t->get_data();
#ifdef bug_search_children_path_d
            printf ("   tmp->show:\n");
            tmp->show();
            printf ("\n\n");
#endif // bug_search_children_path_d
            if (tmp->get_path() == d && tmp->get_type() == "dir")
                return tmp;
            t = t->get_next();
        }
        return NULL;
    }
    TreeNode<T> *search_children_path_f (T d)
    {
#ifdef bug_search_children_path_f
        printf ("           in search_children_path\n");
        printf ("want search path: ");
        cout << d;
        printf ("\n\n");
#endif // bug_search_children_path_f
        if (this->children == NULL || this->children->get_head() == NULL || this->type == "file")
            return NULL;
        Node<TreeNode<T>*> *t = this->children->get_head();
        while (t != NULL)
        {
            TreeNode<T> *tmp = t->get_data();
#ifdef bug_search_children_path_f
            printf ("   tmp->show:\n");
            tmp->show();
            printf ("\n\n");
#endif // bug_search_children_path_f
            if (tmp->get_path() == d && tmp->get_type() == "file")
                return tmp;
            t = t->get_next();
        }
        return NULL;
    }
    TreeNode<T> *add_children (TreeNode<T> *child)
    {
#ifdef bug_add_children
                printf ("this->path: ");
                cout << this->path;
                printf ("\n\n");
#endif // bug_add_children
        if (this->children == NULL)
            this->children = new LinkedList<TreeNode<T>*>();
        if (this->children->get_head() == NULL)
            {
#ifdef bug_add_children
                printf ("this->children->get_head() == NULL\n\n");
#endif // bug_add_children
                this->children->addToHead (child);
                return child;
            }
        Node<TreeNode<T> *> *t = this->children->get_head();
        int x;
        while (t != NULL && (x = VS_string (child->get_path(), t->get_data()->get_path())) > 0)
            t = t->get_next();
#ifdef bug_add_children
if (t != NULL)
{
                printf ("VS: %d\tchild->get_path: ", VS_string (child->get_path(), t->get_data()->get_path()));
                cout <<child->get_path();
                printf ("t->get_data(): %p\nt->get_data()->get_path(): ", t->get_data());
                cout << t->get_data()->get_path();
                printf ("\n\n");
}
else
    printf ("t: NULL\n\n");
#endif // bug_add_children
        if (x == 0)
            return NULL;
        if (t == NULL) //尾
            return this->children->addToTail (child)->get_data();
        else if (t == this->children->get_head()) //min --> 頭
            return this->children->addToHead (child)->get_data();
        else
            return this->children->addToNext (t->get_prev(), child)->get_data();
    }
    void copy_all_children (LinkedList<TreeNode<T> *> *child)
    {
        if (child == NULL || child->get_head() == NULL)
        {
            this->children = NULL;
            return ;
        }
        this->children = new LinkedList<TreeNode<T> *>();
        Node<TreeNode<T> *> *tmp = child->get_head();
        while (tmp)
        {
            TreeNode<T> *node = new GeneralTreeNode<T> (tmp->get_data(), this);
            this->add_children (node);
            tmp = tmp->get_next();
        }
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
        cout << "path: "<<this->path<<endl;
        cout << "type: "<<this->type<<endl;
        cout << "level: "<<this->level<<endl;
        cout << "string_tail: "<<this->string_tail<<endl;
        if (this->parent != NULL)
            cout<<"parent: "<<this->parent<<endl;
        else
            cout<<"parent: NULL"<<endl;
        if (this->parent != NULL)
            cout<<"parent->get_path(): "<<this->parent->get_path()<<endl;
        if (this->children != NULL)
            cout<<"children->get_many(): "<<this->children->get_many()<<endl;
        else
            printf ("children->get_many(): NULL");
    }
};

template<class T, class D>
class GeneralTree: public Tree<T, D>
{
    void _display (TreeNode<T> *r, int d)
    {
        //printf ("in _display %d\n", d);
        if (r == NULL)
            return;
        int x;
        for (x=0; x < d; x ++)
            cout << "   ";
        // if (d != 0)
        cout << r->get_path()<<endl;

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
    void _deSerialize (string *tree, TreeNode<T> *p)
    {
        if ((*tree)[0] == '}' || (*tree)[0] == ']')
            return;
        (*tree) = (*tree).substr (2);
        if ((*tree).substr (0, 8) == "children")
        {
            TreeNode<T> *new_node = new GeneralTreeNode<T> (p, p->get_level() + 1);
            if (new_node->get_level() > this->max_level)
                this->max_level = new_node->get_level();
            if (p->get_children() == NULL)
                p->set_children (new LinkedList<TreeNode<T> *>());
            p->get_children()->addToTail (new_node);
            this->many ++;
            (*tree) = (*tree).substr (11);
#ifdef bug_deSerialize
            printf ("_tree (%d): ", p->get_level()+1);
            cout << *tree << "\n\n";
#endif // bug_deSerialize
            _deSerialize (tree, new_node);
#ifdef bug_deSerialize
            printf ("_tree (%d): ", p->get_level()+1);
            cout << *tree << "\n\n";
#endif // bug_deSerialize
            while ((*tree)[0] == ',')
            {
                (*tree) = (*tree).substr (1);
                _deSerialize (tree, new_node);
            }
            (*tree) = (*tree).substr (10);
            string data = "", c="";
            int x, l;
            for (x=0, l=(*tree).size(); x < l && (*tree)[x] != ','; x ++)
            {
                c = (*tree)[x];
                data.insert (data.size(), c);
            }
            data.erase (data.size()-1, 1);
#ifdef bug_deSerialize
            printf ("x: %d   tree[x]: %c\ndata: ", x, (*tree)[x]);
            cout << data << "\n";
            printf ("tree[4+14]: %c\n", (*tree)[x+14]);
            printf ("tree.substr(14): ");
            cout << (*tree).substr (x+14) <<"\n\n";
#endif // bug_deSerialize
            new_node->set_path (data);
            new_node->set_type ("dir");
            (*tree) = (*tree).substr (x+14);
        }
        else if ((*tree).substr (0, 4) == "data")
        {
            TreeNode<T> *new_node = new GeneralTreeNode<T> (p, p->get_level() + 1);
            if (new_node->get_level() > this->max_level)
                this->max_level = new_node->get_level();
            if (p->get_children() == NULL)
                p->set_children (new LinkedList<TreeNode<T> *>());
            p->get_children()->addToTail (new_node);
            this->many ++;
            (*tree) = (*tree).substr (7);
            string data = "", c="";
            int x, l;
            for (x=0, l=(*tree).size(); x < l && (*tree)[x] != ','; x ++)
            {
                c = (*tree)[x];
                data.insert (data.size(), c);
            }
            data.erase (data.size()-1, 1);
            new_node->set_data (data);
            (*tree) = (*tree).substr (x+9); //x在, x+2跳過,"path":"
            data = "";
            for (x=0, l=(*tree).size(); x < l && (*tree)[x] != ','; x ++)
            {
                c = (*tree)[x];
                data.insert (data.size(), c);
            }
            data.erase (data.size()-1, 1);
            new_node->set_path (data);
            new_node->set_type ("file");
            (*tree) = (*tree).substr (x+15);
        }
    }
    void _serialize (TreeNode<T> *t, string *s)
    {
        if (t == NULL)
            return;
        if (t->get_type() == "dir")
        {
            s->append ("{\"children\":[");
            if (t->get_children() != NULL)
            {
                Node<TreeNode<T> *> *child = t->get_children()->get_head();
                while (child != NULL)
                {
                    _serialize (child->get_data(), s);
                    if (child->get_next() != NULL)
                        s->append (",");
                    child = child->get_next();
                }
            }
            s->append ("],\"path\":\"");
            s->append (t->get_path());
            s->append ("\",\"type\":\"dir\"}");
        }
        else if (t->get_type() == "file")
        {
            s->append ("{\"data\":\"");
            s->append (t->get_data());
            s->append ("\",\"path\":\"");
            s->append (t->get_path());
            s->append ("\",\"type\":\"file\"}");
        }
    }
    TreeNode<T> * _search (TreeNode<T> *p, D path, bool ty)
    {
#ifdef bug__search
        printf ("           in _search\n");
#endif // bug__search
        if (p == NULL)
            return NULL;
        if (ty) //dir
            return p->search_children_path_d (path);
        else
            return p->search_children_path_f (path);
#ifdef bug__search
        printf ("           out _search\n");
#endif // bug__search
    }
    TreeNode<T> * _search_treenode (D path)
    {
#ifdef bug__search_treenode
        printf ("\tin _search_treenode\npath: ");
        cout << path;
        printf ("\n\n");
#endif // bug__search_treenode
        TreeNode<T> *p = this->root, *tmp = NULL;
        string ask="";
        int x=0, l=path.size();
        while (1)
        {
            path = path.substr (1);
            for (x=0, l=path.size(), ask = ""; x < l && path[x] != '/'; x++);
            ask.assign (path.substr (0, x));
            path = path.substr (x);
            tmp = _search (p, ask, true);
            if (x == l)
                break;
            if (tmp == NULL) //沒找到
            {
#ifdef bug__search_treenode
        printf ("no find path:(\n");
        cout << path;
        printf (")\n\tout _search_treenode\n\n");
#endif // bug__search_treenode
                return NULL;
            }
            p = tmp;
        }
        if (tmp == NULL)
            tmp = _search (p, ask, false);
#ifdef bug__search_treenode
        printf ("find tmp: %p\ntmp->show():\n", tmp);
        tmp->show();
        printf ("\n\tout _search_treenode\n\n");
#endif // bug__search_treenode
        return tmp;
    }
    TreeNode<T> * insert_dir (TreeNode<T> *p, D path)
    {
        if (p == NULL)
            return NULL;
        TreeNode<T> *nn = new GeneralTreeNode<T> (p, p->get_level() + 1);
        if (nn->get_level() > this->max_level)
            this->max_level = nn->get_level();
        this->many ++;
        nn->set_path(path);
        nn->set_type("dir");
        if (! p->add_children (nn))
        {
            delete nn;
            return NULL;
        }
        return nn;
    }
    TreeNode<T> * insert_file (TreeNode<T> *p, D path, D data)
    {
        if (p == NULL)
            return NULL;
        TreeNode<T> *nn = new GeneralTreeNode<T> (p, p->get_level() + 1);
        if (nn->get_level() > this->max_level)
            this->max_level = nn->get_level();
        this->many ++;
        nn->set_data (data);
        nn->set_path (path);
        nn->set_type ("file");
        if (! p->add_children (nn))
        {
            delete nn;
            return NULL;
        }
        return nn;
    }
    bool insert_pc (TreeNode<T> *p, TreeNode<T> *c)
    {
        if (! p->add_children (c))
            return false;
        c->set_parent (p);
        return true;
    }
    void _replace_ff (TreeNode<T> *p, TreeNode<T> *c, TreeNode<T> *n)
    {
        Node<TreeNode<T>*> *t = p->get_children()->get_head();
        while (t != NULL && t->get_data() != c)
            t = t->get_next();
        t->set_data (n);
        n->set_parent (p);
        c->set_parent (NULL);
    }
    TreeNode<T> * _remove (TreeNode<T> *m)
    {
#ifdef bug_remove
        printf ("           in _remove()\n\n");
#endif // bug_remove
        if (m == NULL)
            return NULL;
#ifdef bug_remove
        printf ("m->show():\n");
        m->show();
        TreeNode<T> *p = m->get_parent();
        printf ("\n\n--> _display(p, 0)\n");
        _display (p, 0);
        printf ("\n");
        printf ("m: %p\np: %p\nm->get_parent(): %p\np->get_children()->get_head()->get_data(): %p\n", m, p, m->get_parent(), p->get_children()->get_head()->get_data());
#endif // bug_remove
        delete m->get_parent()->get_children()->deleteData(m);
#ifdef bug_remove
        printf ("--> delete m->get_parent()->get_children()->deleteData(m)\n");
        printf ("p's child: %d\n\n", m->get_parent()->get_children()->get_many());
        if (p->get_children()->get_head() == NULL)
            printf ("p->get_children()->get_head() == NULL\n");
        else
        {
            p->get_children()->get_head()->get_data()->show();
            printf ("\n\n");
        }
        printf ("m->show()\n");
        m->show();
        printf ("\n\n");
        printf ("--> _display(p, 0)\n");
        _display (p, 0);
        printf ("\n");

#endif // bug_remove
        m->set_parent (NULL);
#ifdef bug_remove
        printf ("--> m->set_parent (NULL)\n");
        printf ("m->show()\n");
        m->show();
        printf ("\n\n");
        printf ("\tout _remove\n\n");
#endif // bug_remove
        return m;
    }
public:
    bool insert(D data)
    {
    }
    bool remove(D data)
    {
    }
    bool search(D data)
    {
    }
    GeneralTree ()  //TreeNode<T> *node = new GeneralTreeNode<T>();
    {
        this->root = NULL;
        this->many = 0;
        this->max_level = 0;
    }
    void mv (D path_i, D path_f)
    {
#ifdef bug_mv
        printf ("\tin mv\npath_i: ");
        cout << path_i;
        printf ("\npath_f: ");
        cout << path_f;
        printf ("\n\n");
#endif // bug_mv
        TreeNode<T> *tmp, *p;
        string ask="";
        tmp = _search_treenode (path_i);
        if (tmp == NULL)
            return;
#ifdef bug_mv
        printf ("--> tmp = _search_treenode (path_i)\ntmp->show():\n");
        tmp->show();
        printf ("\n\n");
#endif // bug_mv
        _remove (tmp);
#ifdef bug_mv
        printf ("--> _remove (tmp)\n\ttmp->show():\n");
        tmp->show();
        printf ("\n\n");
#endif // bug_mv
        p = _search_treenode (path_f);
        if (p == NULL)
        {
            mkdir (path_f);
            p = _search_treenode (path_f);
        }
#ifdef bug_mv
        printf ("--> p = _search_treenode (path_f)\n\np(printf): %p\np(cout): ", p);
        cout << p <<endl;
        printf ("p->show():\n");
        p->show();
        printf ("\n\n");
#endif // bug_mv
        if (p->search_children_path_d (tmp->get_path()) == NULL)
        {
            if (p->search_children_path_f (tmp->get_path()) == NULL)
            {
#ifdef bug_mv
        printf ("--> insert_pc (p: %p, tmp: %p)\n", p, tmp);
#endif // bug_mv
                insert_pc (p, tmp);
#ifdef bug_mv
        printf ("p->show():\n");
        p->show();
        printf ("\n\n");
        printf ("tmp->show():\n");
        tmp->show();
        printf ("\n\n");
#endif // bug_mv
                return;
            }
            _replace_ff (p, p->search_children_path_f (tmp->get_path()), tmp);
            return;
        }
        _replace_ff (p, p->search_children_path_d (tmp->get_path()), tmp);
    }
    void cp (D path_i, D path_f)
    {
#ifdef bug_cp
        printf ("\tin cp\n\n");
        printf ("path_i: ");
        cout << path_i;
        printf ("\npath_f: ");
        cout << path_f;
        printf ("\n\n");
#endif // bug_cp
        TreeNode<T> *tmp=NULL, *p=NULL, *node=NULL;
        string ask="";
        tmp = _search_treenode (path_i);
        if (tmp == NULL)
            return;
#ifdef bug_cp
        printf ("--> tmp = _search_treenode (path_i)\ntmp: %p\ntmp->show():\n", tmp);
        tmp->show();
        printf ("\n\n");
        cout << "p: " << p<<endl;
#endif // bug_cp
        node = new GeneralTreeNode<T> (tmp, p); // p == NULL  只是傳NULL會有歧異
#ifdef bug_cp
        printf ("--> node = new GeneralTreeNode<T> (tmp, p = (NULL))\nnode: %p\ntmp: %p\n--> node->set_parent (NULL)\n", node, tmp);
#endif // bug_cp
        node->set_parent (NULL);
#ifdef bug_cp
        printf ("node->parent(printf): %p\nnode->parent(cout): ", node->get_parent());
        cout << node->get_parent()<<endl;
        printf ("node->show():\n");
        node->show();
        printf ("\n\n");
        printf ("node->parent: %p\n", node->get_parent());
        printf ("tmp: %p\nnode: %p\n", tmp, node);
        printf ("tmp->get_children()->get_head()->get_data(): %p\nnode->get_children()->get_head()->get_data(): %p\n", tmp->get_children()->get_head()->get_data(), node->get_children()->get_head()->get_data());
        printf ("tmp->get_children()->get_head()->get_data()->->get_children()->get_head()->get_data(): %p\n", tmp->get_children()->get_head()->get_data()->get_children()->get_head()->get_data());
        printf ("node->get_children()->get_head()->get_data()->->get_children()->get_head()->get_data(): %p\n\n", node->get_children()->get_head()->get_data()->get_children()->get_head()->get_data());
        printf ("this->root: %p\n", this->root);
        printf ("this->root first child: %p   show:\n", this->root->get_children()->get_head()->get_data());
        this->root->get_children()->get_head()->get_data()->show();
        printf ("\n\n");
        printf ("this->root sec child: %p    show:\n", this->root->get_children()->get_head()->get_next()->get_data());
        this->root->get_children()->get_head()->get_next()->get_data()->show();
        printf ("\nchild: %p\n\n", this->root->get_children()->get_head()->get_next()->get_data()->get_children()->get_head()->get_data());
        printf ("this->root third child: %p    show:\n", this->root->get_children()->get_head()->get_next()->get_next()->get_data());
        this->root->get_children()->get_head()->get_next()->get_next()->get_data()->show();
        printf ("\n\n");
        printf ("node->get_parent: %p\nnode->show():\n", node->get_parent());
        node->show();
        printf ("\n\n");
#endif // bug_cp
        p = _search_treenode (path_f);
        if (p == NULL)
        {
            #ifdef bug_cp
            printf ("@@\n");
            #endif // bug_cp
            mkdir (path_f);
            p = _search_treenode (path_f);
        }
#ifdef bug_cp
        printf ("--> p = _search_treenode (path_f)\n\np(printf): %p\np(cout): ", p);
        cout << p <<endl;
        printf ("p->show():\n");
        p->show();
        printf ("\n\n");
        printf ("tmp->parent: %p\nnode->parent: %p\n", tmp->get_parent(), node->get_parent());
#endif // bug_cp
        if (p->search_children_path_d (node->get_path()) == NULL)
        {
            if (p->search_children_path_f (node->get_path()) == NULL)
            {
#ifdef bug_cp
        printf ("--> insert_pc (p: %p, node: %p)\n", p, node);
#endif // bug_cp
                insert_pc (p, node);
#ifdef bug_cp
        printf ("node->get_parent: %p\nnode->show():\n", node->get_parent());
        node->show();
        printf ("\n\n");
#endif // bug_cp
                return;
            }
            _replace_ff (p, p->search_children_path_f (node->get_path()), node);
            return;
        }
        _replace_ff (p, p->search_children_path_d (node->get_path()), node);
    }
    void rm (D path) //測資不出現重複--> if else
    {
        TreeNode<T> *p = this->root, *tmp = NULL;
        string ask="";
        int x=0, l=path.size();
        while (1)
        {
            path = path.substr (1);
            for (x=0, l=path.size(), ask = ""; x < l && path[x] != '/'; x++);
            ask.assign (path.substr (0, x));
            path = path.substr (x);
            tmp = _search (p, ask, true);
            if (x == l)
                break;
            if (tmp == NULL) //沒找到
                return;
            p = tmp;
        }
        if (tmp == NULL)
            tmp = _search (p, ask, false);
        if (tmp != NULL)
            delete _remove (tmp);
    }
    void mkdir (D path)
    {
        TreeNode<T> *p = this->root, *tmp = NULL;
        string ask="";
        int x=0, l=path.size();
        while (x != l && p != NULL)
        {
            path = path.substr (1);
            for (x=0, l=path.size(), ask = ""; x < l && path[x] != '/'; x++);
            ask.assign (path.substr (0, x));
            path = path.substr (x);
            tmp = _search (p, ask, true);
            if (tmp == NULL) //沒找到
                tmp = insert_dir (p, ask);
            p = tmp;
        }
    }
    void touch (D path, D data)
    {
        TreeNode<T> *p = this->root, *tmp = NULL;
        string ask="";
        int x=0, l=path.size();
        while (1)
        {
            path = path.substr (1);
            for (x=0, l=path.size(), ask = ""; x < l && path[x] != '/'; x++);
            ask.assign (path.substr (0, x));
            path = path.substr (x);
            if (x == l)
                break;
            tmp = _search (p, ask, true);
            if (tmp == NULL) //沒找到
                tmp = insert_dir (p, ask);
            p = tmp;
            if (p == NULL)
                return ;
        }
        tmp = _search (p, ask, false);
        if (tmp == NULL)
            insert_file (p, ask, data);
        else
        {
            TreeNode<T> *n = new GeneralTreeNode<T> ();
            n->set_data (data);
            n->set_path (ask);
            n->set_type ("file");
            _replace_ff (p, tmp, n);
            delete tmp;
        }
    }
    void set_root (TreeNode<T> *r)
    {
        this->root = r;
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
#ifdef bug_deSerialize
        printf ("           in deSerialize\ntree: ");
        cout << tree << "\n\n";
#endif // bug_deSerialize
        tree = tree.substr (8);
#ifdef bug_deSerialize
        printf ("--> tree = tree.substr (8)\ntree: ");
        cout << tree << "\n\n";
#endif // bug_deSerialize
        if (tree[0] != '{')//連根節點都不存在
            return;
        tree = tree.substr (2);
        this->many ++;
        this->max_level = 1;
#ifdef bug_deSerialize
        printf ("--> tree = tree.substr (2)\ntree: ");
        cout << tree << "\n\n";
#endif // bug_deSerialize
        if (tree.substr (0, 8) == "children")
        {
            this->root = new GeneralTreeNode<T> ();
            this->root->set_level (1);
            tree = tree.substr (11);
#ifdef bug_deSerialize
            printf ("_tree (%d): ", this->root->get_level());
            cout << tree << "\n\n";
#endif // bug_deSerialize
            _deSerialize (&tree, this->root);
#ifdef bug_deSerialize
            printf ("_tree (%d): ", this->root->get_level() );
            cout << tree << "\n\n";
#endif // bug_deSerialize
            while (tree[0] == ',')
            {
                tree = tree.substr (1);
                _deSerialize (&tree, this->root);
            }
            this->root->set_path ("/");
            this->root->set_type ("dir");
        }
        else if (tree.substr (0, 4) == "data")
        {
            this->root = new GeneralTreeNode<T> ();
            this->root->set_level (1);
            tree = tree.substr (7);
            string data = "", c="";
            int x, l;
            for (x=0, l=tree.size(); x < l && tree[x] != ','; x ++)
            {
                c = tree[x];
                data.insert (data.size(), c);
            }
            data.erase (data.size()-1, 1);
            this->root->set_data (data);
            this->root->set_path ("/");
            this->root->set_type ("file");
        }
    }
    string serialize()
    {
        string s = "{\"root\":";
        if (this->root != NULL)
            _serialize (this->root, &s);
        s.append ("}");
        return s;
    }
};


int main ()
{
    GeneralTree<string, string> *gt = new GeneralTree<string, string>();
    string question="";
    //ofstream out("test.txt");

    getline (cin, question);
    gt->deSerialize (question);

#ifdef bug
    printf ("tree's many: %d\n", gt->get_many());
    printf ("tree's max_level: %d\n", gt->get_max_level());
    gt->display();
            printf ("***************************************\n");
#endif // bug

    while (cin >> question)
    {
        if (question == "rm")
        {
            string ask="";
            cin >> ask;
            gt->rm (ask);
#ifdef bug
            printf ("\n");
            gt->display();
            printf ("***************************************\n");
#endif // bug
        }
        else if (question == "mkdir")
        {
            string ask="";
            cin >> ask;
            gt->mkdir (ask);
#ifdef bug
            printf ("\n");
            gt->display();
            printf ("***************************************\n");
#endif // bug
        }
        else if (question == "touch")
        {
            string ask="", data="";
            cin >> ask;
            getline (cin, data);
            gt->touch (ask, data.substr(1)); // 前面多吃一個空白
#ifdef bug
            printf ("\n");
            gt->display();
            printf ("***************************************\n");
#endif // bug
        }
        else if (question == "mv")
        {
            string ask="", f="";
            cin >> ask >> f;
            gt->mv (ask, f);
#ifdef bug
            printf ("\n");
            gt->display();
            printf ("***************************************\n");
#endif // bug
        }
        else if (question == "cp")
        {
            string ask="", f="";
            cin >> ask >> f;
            gt->cp (ask, f);
#ifdef bug
            printf ("\n");
            gt->display();
            printf ("***************************************\n");
#endif // bug
        }
    }

    cout << gt->serialize() << endl;

    //out.close();
    return 0;
}

