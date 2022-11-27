
/**
 * Binary Search Tree II
 *
 * @Description:
 * Please finish the class "BinarySearchTree" and use it in the main function
 * You can add any function or variable if you want.
 *
 * @Input Description
 *  Each line will contain the following information till the end-of-file:
 *  ．First part will be a string that needs to be deserialized to the tree, which is separated by ","
 *  and the null pointer is indicated by "NULL", there is no space in this string.
 *  ．Second part will be multiple strings which is the value that needs to be added to the tree.
 *  Example: assume the input is "15,6,23,NULL,7 71 50 5", then 15,6,23,NULL,7 is the string that needs to be deserialized, "71 50 5" is to be added.
 *  Suggest data type for TreeNode: int
 *
 *
 * @Output Description
 * Result of the serialized tree after add and delete, no space between and ending with a "\n" of each line.
 */

#include <bits/stdc++.h>
#define Bu//g
#define debug_inser//t
#define serialize_stac//k
using namespace std;

/**
 * A TreeNode class of binarySearchTree class
 */
template<class T>
class TreeNode
{
private:
    int level;
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
public:
    TreeNode(T d, int l=0): data(d), level(l), left(NULL), right(NULL) {}
    T get_data () const
    {
        return data;
    }
    void set_data (T d)
    {
        data = d;
    }
    int get_level () const
    {
        return level;
    }
    void set_level (int l)
    {
        level = l;
    }
    TreeNode<T> *get_left () const
    {
        return (TreeNode<T> *)left;
    }
    void set_left (TreeNode<T> *l)
    {
        left = l;
    }
    TreeNode<T> *get_right () const
    {
        return (TreeNode<T> *)right;
    }
    void set_right (TreeNode<T> *r)
    {
        right = r;
    }
    void show () const
    {
        cout << "data: "<<data<<"\n";
        cout << "level: "<<level<<"\n";
        cout << "left: "<<left<<"\n";
        cout << "right: "<<right<<"\n";
    }
};

/**
 * A binarySearchTree abstract class for BinarySearchTree class
 */
template<class T>
class binarySearchTree
{
protected:
    TreeNode<T> *root;
public:
    virtual void preorder() = 0;
    virtual void inorder() = 0;
    virtual void postorder() = 0;
    virtual void levelorder() = 0;
    virtual bool insert(T data) = 0;
    virtual void setRoot(T data) = 0;
    virtual bool serach(T target) = 0;

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
};

template<class T>
class BinarySearchTree: public binarySearchTree<T>
{
    int many;
    int max_level;
    //不用遞迴的話，也可以用stack
    //pre 一個，post 兩個
    void TLR (TreeNode<T> *n, int *m)
    {
        cout << n->get_data();
        (*m) ++;
        //printf ("m: %d\n", *m);
        if (*m != many)
            cout << ",";
        else
            cout << "\n";
        if (n->get_left() != NULL)
            TLR (n->get_left(), m);
        if (n->get_right() != NULL)
            TLR (n->get_right(), m);
    }
    void LTR (TreeNode<T> *n, int *m)
    {
        if (n->get_left() != NULL)
            LTR (n->get_left(), m);
        cout << n->get_data();
        (*m) ++;
        //printf ("m: %d\n", *m);
        if (*m != many)
            cout << ",";
        else
            cout << "\n";
        if (n->get_right() != NULL)
            LTR (n->get_right(), m);
    }
    void LRT (TreeNode<T> *n, int *m)
    {
        if (n->get_left() != NULL)
            LRT (n->get_left(), m);
        if (n->get_right() != NULL)
            LRT (n->get_right(), m);
        cout << n->get_data();
        (*m) ++;
        //printf ("m: %d\n", *m);
        if (*m != many)
            cout << ",";
        else
            cout << "\n";
    }
    void _display (TreeNode<T> *n, int l)
    {
        if (n == NULL)
            return;
        _display (n->get_right(), l+1);
        for (int x=0; x < l; x++)
            printf ("\t");
        cout << n->get_data()<<"\n";
        _display (n->get_left(), l+1);
    }
public:
    BinarySearchTree(): many(0), max_level(0)
    {
        this->root = NULL;
    }
    ~BinarySearchTree()
    {
        if (this->root != NULL)
        {
            queue<TreeNode<T> *> q;
            TreeNode<T> *tmp;
            q.push (this->root);
            while (!q.empty())
            {
                if (q.front()->get_left() != NULL)
                    q.push (q.front()->get_left());
                if (q.front()->get_right() != NULL)
                    q.push (q.front()->get_right());
                tmp = q.front();
                q.pop();
                delete tmp;
            }
        }
    }
    void preorder()
    {
        if (this->root == NULL)
        {
            cout << "\n";
            return;
        }
        //printf ("many: %d\n", many);
        int m=0;
        TLR (this->root, &m);
    }
    void inorder()
    {
        if (this->root == NULL)
        {
            cout << "\n";
            return;
        }
        int m=0;
        LTR (this->root, &m);
    }
    void postorder()
    {
        if (this->root == NULL)
        {
            cout << "\n";
            return;
        }
        int m=0;
        LRT (this->root, &m);
    }
    void levelorder()
    {
        if (this->root == NULL)
        {
            cout << "\n";
            return;
        }
        queue<TreeNode<T> *> q;
        q.push (this->root);
        cout<<q.front()->get_data();
        if (q.front()->get_left() != NULL)
            q.push (q.front()->get_left());
        if (q.front()->get_right() != NULL)
            q.push (q.front()->get_right());
        q.pop();
        while (!q.empty())
        {
            cout<<","<<q.front()->get_data();
            if (q.front()->get_left() != NULL)
                q.push (q.front()->get_left());
            if (q.front()->get_right() != NULL)
                q.push (q.front()->get_right());
            q.pop();
        }
        cout << "\n";
    }
    bool insert(T data)
    {
#ifdef debug_insert
        printf ("           in insert\n");
#endif // debug_insert
        if (this->root == NULL)
        {
            setRoot (data);
            return true;
        }
        if (serach (data))
            return false;
        TreeNode<T> *tmp = this->root, *n = new TreeNode<T>(data);
        while (1)
        {
            if (tmp->get_data() < data)
            {
                if (tmp->get_right() == NULL)
                {
                    n->set_level (tmp->get_level()+1);
                    tmp->set_right(n);
                    if (n->get_level() > max_level)
                        max_level = n->get_level();
                    many ++;
#ifdef debug_insert
                    printf ("the data:\n");
                    n->show();
                    printf ("insert data: %d right\n\n", tmp->get_data());
#endif // debug_insert
                    return true;
                }
                tmp = tmp->get_right();
            }
            else // == 前面被serach判斷掉了
            {
                if (tmp->get_left() == NULL)
                {
                    n->set_level (tmp->get_level()+1);
                    tmp->set_left(n);
                    if (n->get_level() > max_level)
                        max_level = n->get_level();
                    many ++;
#ifdef debug_insert
                    printf ("the data:\n");
                    n->show();
                    printf ("insert data: %d left\n\n", tmp->get_data());
#endif // debug_insert
                    return true;
                }
                tmp = tmp->get_left();
            }
        }
    }
    void setRoot(T data)
    {
        this->root = new TreeNode<T>(data, 1);
        many ++;
        max_level = 1;
    }
    bool serach(T target)
    {
        if (this->root == NULL)
            return false;
        TreeNode<T> *tmp = this->root;
        while (tmp != NULL)
        {
            if (tmp->get_data() == target)
                return true;
            else if (tmp->get_data() < target)
                tmp = tmp->get_right();
            else if (tmp->get_data() > target)
                tmp = tmp->get_left();
        }
        return false;
    }
    void deSerialize(string tree)
    {
#ifdef Bug
        printf ("\nin deSerialize, tree: ");
        cout << tree << "\n\n";
#endif // Bug
        stringstream ss;
        int x, add;
        char c;
        ss.str ("");
        ss.clear ();
        for (x=0; x < tree.size() && tree[x] != '\0' ; x++)
            if (tree[x] == 'N')
            {
#ifdef Bug
                printf ("after tree[%d]: (%c)\n", x-2, tree[x-2]);
                printf ("find tree[%d]: (%c)\n", x, tree[x]);
#endif // Bug
                tree.erase (x-1, 5);
#ifdef Bug
                printf ("--> tree.erase (x-1, x+4)\n");
                printf ("the tree change (");
                cout << tree << ")\n\n";
#endif // Bug
                x --;
            }
        ss << tree;
        while (ss >> add)
        {
            insert (add);
            ss >> c;
        }
    }
    virtual string serialize()
    {
#ifdef serialize_stack
        printf ("           in serialize\n");
#endif // serialize_stack
        if (this->root == NULL)
            return "NULL";
        string tree="", v="";
        stringstream ss;
        queue<TreeNode<T> *> q;
        stack<string> s;

        q.push (this->root);
        ss.str (""), ss.clear();
        ss << q.front()->get_data();
        ss >> v;
        s.push (v);
#ifdef serialize_stack
        printf ("push (");
        cout << v;
        printf (") in stack\n");
#endif // serialize_stack
        if (q.front()->get_left() != NULL)
        {
            q.push (q.front()->get_left());
            ss.str (""), ss.clear();
            ss << q.front()->get_left()->get_data();
            ss >> v;
            s.push (v);
#ifdef serialize_stack
            printf ("push (");
            cout << v;
            printf (") in stack\n");
#endif // serialize_stack
        }
        else
        {
            s.push ("NULL");
#ifdef serialize_stack
            printf ("push (");
            cout << NULL;
            printf (") in stack (%d left)\n", q.front()->get_data());
#endif // serialize_stack
        }
        if (q.front()->get_right() != NULL)
        {
            q.push (q.front()->get_right());
            ss.str (""), ss.clear();
            ss << q.front()->get_right()->get_data();
            ss >> v;
            s.push (v);
#ifdef serialize_stack
            printf ("push (");
            cout << v;
            printf (") in stack\n");
#endif // serialize_stack
        }
        else
        {
            s.push ("NULL");
#ifdef serialize_stack
            printf ("push (");
            cout << NULL;
            printf (") in stack (%d right)\n", q.front()->get_data());
#endif // serialize_stack
        }
        if (q.front()->get_left() == NULL && q.front()->get_right() == NULL && q.front()->get_level() == max_level)
        {
            s.pop(), s.pop();
#ifdef serialize_stack
            printf ("pop (");
            cout << NULL;
            printf (") out stack (%d)\n", q.front()->get_data());
            printf ("pop (");
            cout << NULL;
            printf (") out stack (%d)\n", q.front()->get_data());
#endif // serialize_stack
        }
        q.pop();
        while (!q.empty())
        {
            /*  ss.str (""), ss.clear();
              ss << q.front()->get_data();
              ss >> v;
              s.push (v);
            #ifdef serialize_stack
              printf ("push (");
              cout << v;
              printf (") in stack\n");
            #endif // serialize_stack*/
            if (q.front()->get_left() != NULL)
            {
                q.push (q.front()->get_left());
                ss.str (""), ss.clear();
                ss << q.front()->get_left()->get_data();
                ss >> v;
                s.push (v);
#ifdef serialize_stack
                printf ("push (");
                cout << v;
                printf (") in stack\n");
#endif // serialize_stack
            }
            else
            {
                s.push ("NULL");
#ifdef serialize_stack
                printf ("push (");
                cout << NULL;
                printf (") in stack (%d left)\n", q.front()->get_data());
#endif // serialize_stack
            }
            if (q.front()->get_right() != NULL)
            {
                q.push (q.front()->get_right());
                ss.str (""), ss.clear();
                ss << q.front()->get_right()->get_data();
                ss >> v;
                s.push (v);
#ifdef serialize_stack
                printf ("push (");
                cout << v;
                printf (") in stack\n");
#endif // serialize_stack
            }
            else
            {
                s.push ("NULL");
#ifdef serialize_stack
                printf ("push (");
                cout << NULL;
                printf (") in stack (%d right)\n", q.front()->get_data());
#endif // serialize_stack
            }
            if (q.front()->get_left() == NULL && q.front()->get_right() == NULL && q.front()->get_level() == max_level)
            {
                s.pop(), s.pop();
#ifdef serialize_stack
                printf ("pop (");
                cout << NULL;
                printf (") out stack (%d)\n", q.front()->get_data());
                printf ("pop (");
                cout << NULL;
                printf (") out stack (%d)\n", q.front()->get_data());
#endif // serialize_stack
            }
            q.pop();
        }
        for (tree=s.top(), s.pop(); !s.empty() ; s.pop())
        {
            tree.insert (0, ",");
            v = s.top();
            tree.insert (0, v);
        }
        while (tree[tree.size()-1] == 'L')
            tree.erase (tree.size()-5);
        return tree;
    }
    void display ()
    {
        _display (this->root, 0);
    }
};


int main()
{
    string question="";
    BinarySearchTree<int> *T;
    stringstream ss;
    int x, add;
    while (getline (cin, question))
    {
#ifdef Bug
        cout  << "question: " << question << "\n";
#endif // Bug
        T = new BinarySearchTree<int>();
        ss.str("");
        ss.clear();
        for (x=0; question[x] != '\0' && question[x] != ' ' ; x++);
#ifdef Bug
        printf ("after question[%d]: (%c)\n", x-1, question[x-1]);
        printf ("find question[%d]: (%c)\n", x, question[x]);
        printf ("put (");
        cout << string (question.substr (0, x));
        printf (") in T->deSerialize\n");
#endif // Bug
        if (question[x] == ' ' || question[x] == '\0')
            T->deSerialize(string (question.substr (0, x)));
        else
            continue;
#ifdef Bug
        printf ("T->levelorder():\n");
        T->levelorder();
#endif // Bug
        ss << string (question.substr (x));
#ifdef Bug
        printf ("-->  ss << string (question.substr (x))\n");
        //printf ("ss: ");
#endif // Bug
        while (ss >> add)
        {
#ifdef Bug
            printf ("--> ss >> add\n");
            printf ("insert add: %d\n", add);
#endif // Bug
            T->insert (add);
        }
#ifdef Bug
        printf ("T->levelorder():\n");
        T->levelorder();
#endif // Bug
        T->display();
        cout << T->serialize() << "\n";

        delete T;
    }
    return 0;
}
