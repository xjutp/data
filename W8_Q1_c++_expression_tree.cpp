
/**
 * Expression Tree
 *
 * @Description:
 * Please replace the class "Stack" with the class "BinarySearchTree" to redo the question "Arithmetic II".
 * All the rules are the same as the Arithmetic problem, except there are no parentheses.
 * Serialize and deserialize rules are the same as the question "Binary Search Tree II".
 * You need to deserialize the string with levelorder traversal and then read the expression tree with inorder traversal.
 * You can add any function or variable if you want.
 * You must use your own class "BinarySearchTree" you wrote or you will get up to 0 points.
 *
 * @Input Description
 * A serialized string that represents the expression tree.
 *
 *
 * @Output Description
 * Result of the expression tree to the 2nd decimal place, "ERROR" when operation error, ending with a "\n" of each line
 */
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#define Bu//g
#define debug_inser//t
#define serialize_stac//k
#define deSerialize_strin//g
#define debug_insert_deSerializ//e
#define debug__calculat//e
#define Accuracy_question 3
#define Accuracy_question_d 4
#define Accuracy 18 //取到第16位代表往後找到第17位
using namespace std;
class Formula
{
public:
    static string calculate_p_d (string lv, string rv, bool b=true)
    {// exp(b * ln(a)) = exp(ln(C)) --> exp(b * ln(a)) = C = a^b
        clear_vstring (&lv, &rv);
        if (lv == "")
            lv = "0";
        if (rv == "")
            rv = "0";
        if (lv == "0" || lv[0] == '-')
            throw invalid_argument("");
        else if (rv == "0" || lv == "1")
            return "1.00";
        else if (rv[0] == '-') //   a ^ -b --> 1 / a ^ b
        {
            if (b)
                return calculate_d ("1", calculate_p_d (lv, calculate_s ("0", rv, false), false));
            else
                return calculate_d ("1", calculate_p_d (lv, calculate_s ("0", rv, false), false), b, Accuracy);
        }
        string tmp="1";//, i="1"
        int r_dot = rv.find('.');
        if (r_dot != -1)
        {
            tmp = calculate_p_i (lv, string(rv.substr(0, r_dot)));
            rv = rv.substr(r_dot);
            rv.insert (0, "0");
        }
        tmp = calculate_m (tmp, exponential (calculate_m (rv, nature_log (lv), false)), false);
        if (b)
            return rounding (tmp);
        else
            return rounding (tmp, Accuracy);
    }

    static string nature_log (string v) //  t = (x-1) / (x+1)
    {//   ln(x) = 2t * (  1 + t^2/3  +  t^4/5  + t^6/7 + .... )
        string tmp="1", c, t, n, n_1;
        int x;
        t = calculate_d (calculate_s (v, "1", false), calculate_a (v, "1", false), false, Accuracy);
        for (c="2", n=t, n_1="", tmp="1" ;  ;  c = calculate_a (c, "2"))
        {
            n_1 = calculate_d (calculate_p_i (t, c, false), calculate_a (c, "1"), false, Accuracy);
            if (VS (calculate_s (n, n_1, false), "0.0000000000000001") < 0)
                break;
            tmp = calculate_a (tmp, n_1, false);
            n = n_1;
        }
        return calculate_m (calculate_m (t, "2", false), tmp, false);
    }
    static string exponential (string v)
    {// exp(v) = 1 + v + v^2/2! + v^3/3! + ...
        v = move_zero_d (v);
        string tmp = "", c, n, n_1;
        tmp = calculate_a ("1", v, false); // 1 + v
        for (c = "2", n=v, n_1="" ; ; c = calculate_a (c, "1"))
        {
            n_1 = calculate_d (calculate_p_i (v, c, false), order (c), false, Accuracy);
            if (VS (calculate_s (n, n_1, false), "0.0000000000000001") < 0)
                break;
            tmp = calculate_a (tmp, n_1, false);
            n = n_1;
        }
        return tmp;
    }
    static string order (string v) // v! == v * v-1 * v-2 * ... * 1
    {
        if (v.find (".") != -1)
            return "";
        string tmp = "1", c;
        for (c = v ; VS (c, "0.00") > 0 ; c = calculate_s (c, "1")) // 因為 後c_s進位 所以 前VS "0.00"
            tmp = calculate_m (tmp, c, false);
        return tmp;
    }
    static string calculate_p_i (string lv, string rv, bool b=true)
    {
        //printf ("in _p_i\n");
        clear_vstring (&lv, &rv);
        if (lv == "")
            lv = "0";
        if (rv == "")
            rv = "0";
        if (lv == "0")
            throw invalid_argument("");
        else if (rv == "0" || lv == "1")
            return "1.00";
        else if (rv[0] == '-') //   a ^ -b --> 1 / a ^ b
        {
            if (b)
                return calculate_d ("1", calculate_p_i (lv, calculate_s ("0", rv, false), false));
            else
                return calculate_d ("1", calculate_p_i (lv, calculate_s ("0", rv, false), false), b, Accuracy);
        }
        else if (lv[0] == '-' && (rv[rv.size()-1]-48)%2 == 1) //-a ^ b  b是基數 --> - (a ^ b)
            return calculate_s ("0", calculate_p_i (calculate_s ("0", lv, false), rv, b), b);
        else if (lv[0] == '-' && (rv[rv.size()-1]-48)%2 == 0) //-a ^ b  b是偶數 -->   (a ^ b)
            return calculate_p_i (calculate_s ("0", lv, false), rv, b);
        string tmp="", c="";
        int x, y, z;
        //cout << "lv: "<<lv<<"\n";
        //cout << "rv: "<<rv<<"\n";
        for (c="0", tmp="1" ; VS (c, rv) < 0 ; c = calculate_a (c, "1"))
            tmp = calculate_m (tmp, lv, false);
        //printf ("out for\n");
        if (b)
            return rounding (tmp);
        else
            return rounding (tmp, Accuracy);
    }

    static string calculate_m (string lv, string rv, bool b=true)
    {
        if (lv == "0" || rv == "0")
            return "0.00";
        else if ((lv[0] == '-' && rv[0] != '-') || (lv[0] != '-' && rv[0] == '-')) // -a * b || a * -b --> -(a * b)
            return calculate_s ("0", calculate_m(calculate_s("0", lv, false), rv, b), b);
        else if (lv[0] == '-' && rv[0] == '-') // -a * -b --> a * b
            return calculate_m (calculate_s("0", lv, false), calculate_s("0", rv, false), b);
        string tmp="", c="";
        int l_dot = lv.find('.'), r_dot = rv.find('.'), dot=0, x, y, z, m, k, d;
        if (l_dot != -1)
            dot += lv.size() - l_dot - 1;
        if (r_dot != -1)
            dot += rv.size() - r_dot - 1;
        if (lv.size() > rv.size())
            rv = add_i_zero (rv, lv.size()-rv.size());
        else if (lv.size() < rv.size())
            lv = add_i_zero (lv, rv.size()-lv.size());
        /**********運算********************/
        for (x=lv.size()-1, d=0, k=0; x >= 0; x--, d++)
        {
            if (lv[x] == '.')
            {
                d--;
                continue;
            }
            for (y=rv.size()-1, z=d; y >= 0 ; y--, z++)
            {
                if (rv[y] == '.')
                {
                    z--;
                    continue;
                }
                m = (lv[x]-48) * (rv[y]-48);
                while (tmp.size() <= z+1)
                    tmp.append ("0");
                tmp[z] += m%10;
                while (tmp[z] > 57)
                {
                    tmp[z] -= 10;
                    k ++;
                }
                tmp[z+1] += m/10 + k;
                k = 0;
            }
        }
        tmp.insert (dot, ".");
        /********倒轉、刪零*******************/
        tmp = move_d_zero (tmp);// 小數點後面刪零
        tmp = string(tmp.rbegin(), tmp.rend());//倒轉
        tmp = move_i_zero (tmp);//整數前刪零
        if (b)
            return rounding (tmp);
        else
            return rounding (tmp, Accuracy);
    }
    static string calculate_d (string lv, string rv, bool b=true, int d=Accuracy_question_d)
    {
        clear_vstring (&lv, &rv);
        if (lv == "")
            lv = "0";
        if (rv == "")
            rv = "0";
        if (lv == "0")
            return "0.00";
        else if (rv == "0")
            throw invalid_argument("");
        else if (rv == "1")
        {
            if (b)
                return rounding (lv);
            else
                return rounding (lv, Accuracy);
        }
        else if (lv == rv)
            return "1.00";
        else if ((lv[0] == '-' && rv[0] != '-') || (lv[0] != '-' && rv[0] == '-')) // -a / b || a / -b --> -(a / b)
            return calculate_s ("0", calculate_d(calculate_s("0", lv, false), rv, b, d));
        else if (lv[0] == '-' && rv[0] == '-') // -a / -b --> a / b
            return calculate_d (calculate_s("0", lv, false), calculate_s("0", rv, false), b, d);
        string tmp="", c="", v="";
        bool do_d, dot_add=false;
        int l_dot = lv.find('.'), r_dot = rv.find('.'), dot=0;
        int  x, y, z;

        if (l_dot != -1 && r_dot != -1) // 同乘 10 ^ n
        {
            if (lv.size()-l_dot-1 > rv.size()-r_dot-1)
                y = rv.size()-r_dot-1;
            else
                y = lv.size()-l_dot-1;
            lv.erase (l_dot, 1);
            rv.erase (r_dot, 1);
            l_dot += y;
            r_dot += y;
            if (lv.size() > l_dot)
                lv.insert (l_dot, ".");
            if (rv.size() > r_dot)
                rv.insert (r_dot, ".");
            lv = move_i_zero (lv), rv = move_i_zero (rv);
            l_dot = lv.find('.'), r_dot = rv.find('.');
        }

        if (l_dot == -1 && r_dot != -1) // int && double
        {
            y = rv.size() - r_dot - 1;
            rv.erase (r_dot, 1);
            for (x=0; x < y; x++)
                lv.append ("0");
            lv = move_i_zero (lv), rv = move_i_zero (rv);
        }
        else if (l_dot != -1 && r_dot == -1) // double && int
        {
            y = lv.size() - l_dot - 1;
            lv.erase (l_dot, 1);
            for (x=0; x < y; x++)
                rv.append ("0");
            lv = move_i_zero (lv), rv = move_i_zero (rv);
        }
D:
        for (x=0, c=""; x < lv.size(); x++)
        {
            v = lv[x];
            c.append (v);
            v = "0"; // 之後當計數器用
            do_d = false;
            while (VS (c, rv) >= 0)
            {
                c = calculate_s (c, rv, false);
                v = calculate_a (v, "1");
                do_d = true;
            }
            if (VS (v, "0") > 0 || (v == "0" && tmp.size() > 0 && !dot_add)) // ex. 1/1000
            {
                tmp.append (v);
                if (dot_add)
                    dot_add = false;
            }
            if (c == "0")
                c = "";
        }
        if (c == lv) // 被除數小於除數，整數位數為零
            tmp.append ("0");
        lv = c; // 餘數
        if (dot < d && lv != "")
        {
            if (VS(lv, "1") >= 0)
                dot_add = true;
            lv = calculate_m (lv, "10", false);
            dot ++;
            goto D;
        }
        x = tmp.size()-dot;
        if (x > 0 && x < tmp.size())
            tmp.insert (x, ".");
        else if (x == 0)
            tmp.insert (x, "0.");
        else if (x < 0)
        {
            while (x < 0)
            {
                tmp.insert (0, "0");
                x ++;
            }
            tmp.insert (x, "0.");
        }
        tmp = move_zero_d(tmp);
        if (b)
            return rounding (tmp);
        else
            return rounding (tmp, Accuracy);
    }

    static string calculate_a (string lv, string rv, bool b=true)
    {
        if (lv[0] == '-' && rv[0] != '-')// -a + b --> b - a
            return calculate_s (rv, (calculate_s("0", lv, false)));
        else if (lv[0] != '-' && rv[0] == '-')// a + -b --> a - b
            return calculate_s (lv, calculate_s("0", rv, false));
        else if (lv[0] == '-' && rv[0] == '-')// -a + -b --> - (a + b)
            return calculate_s ("0", calculate_a(calculate_s("0", lv, false), calculate_s("0", rv, false)));
        string tmp="", c="";
        int x, y, z;
        add_zero (&lv, &rv); // 補零
        /***********運算*******************/
        for (x=lv.size()-1, y=0, z=0; x >= 0 ; x--, z++)
        {
            if (lv[x] == '.')
            {
                c = lv[x];
                tmp.append(c);
                continue;
            }
            c = lv[x] + rv[x] - 48 + y;
            tmp.append(c);
            y=0;
            if (tmp[z] > 57)
            {
                tmp[z] -= 10;
                y = 1;
            }
        }
        if (y > 0)
            tmp.append ("1");
        /********倒轉、刪零*******************/
        tmp = move_d_zero (tmp);// 小數點後面刪零
        tmp = string (tmp.rbegin(), tmp.rend());
        if (b)
            return rounding (tmp);
        else
            return rounding (tmp, Accuracy);
    }
    static string calculate_s (string lv, string rv, bool b=true)
    {
        clear_vstring (&lv, &rv);
        if (lv == "")
            lv = "0";
        if (rv == "")
            rv = "0";
        //cout << "in calculate_s    lv: "<<lv<<"    rv: "<<rv<<"\n";
        if (lv == rv)
            return "0";
        else if (lv == "0")
        {
            if (rv[0] != '-')
            {
                lv.assign ("-");
                lv.append (rv);
            }
            else
                lv = string (rv.substr(1));
//            if (b)
//                return rounding (lv);
//            else
                return lv; //rounding (lv, Accuracy) 給自己單純變號用的，不確定會不會影響計算出的答案
        }
        if (lv[0] == '-' && rv[0] != '-')// -a - b --> - (a + b)
            return calculate_s ("0", calculate_a(calculate_s("0", lv, false), rv));
        else if (lv[0] != '-' && rv[0] == '-')// a - -b --> a + b
            return calculate_a (lv, calculate_s("0", rv, false));
        else if (lv[0] == '-' && rv[0] == '-')// -a - -b --> b - a
            return calculate_s (calculate_s("0", rv, false), calculate_s("0", lv, false));
        else if (VS(lv, rv) == -1)// a - b (a < b) --> -(b - a)
            return calculate_s ("0", calculate_s(rv, lv));
        string tmp="", c="";
        int x, y, z;
        add_zero (&lv, &rv); // 補零
        /***********運算*******************/
        for (x=lv.size()-1, y=0, z=0; x >= 0; x--)
        {
            if (lv[x] == '.')
            {
                tmp.append (".");
                continue;
            }
            lv[x] += y;
            y = 0;
            if (lv[x] < rv[x])
            {
                lv[x] += 10;
                y = -1;
            }
            c = lv[x] - rv[x] + 48;
            tmp.append (c);
        }
        /********倒轉、刪零*******************/
        tmp = move_d_zero (tmp);// 小數點後面刪零
        tmp = string(tmp.rbegin(), tmp.rend());//倒轉
        tmp = move_i_zero (tmp);//整數前刪零
        if (tmp == "")
            tmp.append ("0");
        if (b)
            return rounding (tmp);
        else
            return rounding (tmp, Accuracy);
    }


    static void clear_vstring (string *lv, string *rv)
    {
        *lv = move_i_zero (*lv), *rv = move_i_zero (*rv);
        *lv = move_zero_d (*lv), *rv = move_zero_d (*rv);
    }
    static int VS (string lv, string rv)
    {
        clear_vstring (&lv, &rv);
        /* if (lv == "0")
         {
             cout << "\n   in VS:\n";
             cout << "lv: "<<lv<<"\nrv: "<<rv<<endl;
         }*/

        int l_dot = lv.find('.'), r_dot = rv.find('.'), x;
        if (l_dot == -1)
            l_dot = lv.size();
        if (r_dot == -1)
            r_dot = rv.size();

        if (l_dot > r_dot) //lv > rv
            return 1;
        else if (l_dot < r_dot) //lv < rv
            return -1;
        for (x=0; x < lv.size() && x < rv.size() && lv[x] == rv[x] ; x++);
        if (x == lv.size() && x == rv.size())
            return 0;
        if ((x == rv.size() && x < lv.size()) || lv[x] > rv[x])
            return 1;
        else if ((x == lv.size() && x < rv.size()) || lv[x] < rv[x])
            return -1;
    }
    static string add_i_zero (string v, int d)
    {
        string tmp="";
        int x;
        for (x=0; x < d; x++)
            tmp.append ("0");
        tmp.append (v);
        return tmp;
    }
    static string add_d_zero (string v, int i, int f, bool no_dot)
    {
        if (no_dot)
        {
            v.append (".");
            i ++;
        }
        for (; i < f; i++)
            v.append ("0");
        return v;
    }
    static string move_i_zero (string v)
    {
        int x;
        for (x=0; x < v.size() && v[x] == '0' ; x++);
        if (v[x] == '.')
            x--;
        return string (v.substr(x));
    }
    static string move_d_zero (string v) // v 倒敘
    {
        int x;
        if (v.find('.') == -1) // 沒有小數
            return v;
        for (x=0; v[x] != '.' && v[x] == '0' ; x++);
        if (v[x] == '.') //小數點後都是零
            v = string (v.substr(x+1));
        else
            v = string (v.substr(x));
        return v;
    }
    static string move_zero_d (string v)
    {
        string tmp = move_d_zero (string(v.rbegin(), v.rend()));
        return string(tmp.rbegin(), tmp.rend());
    }
    static void add_zero (string *lv, string *rv)
    {
        int l_dot = lv->find('.'), r_dot = rv->find('.'), dot;
        if (l_dot == -1)
            l_dot = lv->size();
        if (r_dot == -1)
            r_dot = rv->size();
        /*******補零*********/
        if (l_dot > r_dot)// 整數
        {
            *rv = add_i_zero (*rv, l_dot-r_dot);
            dot = l_dot;
        }
        else if (l_dot < r_dot)
        {
            *lv = add_i_zero (*lv, r_dot-l_dot);
            dot = r_dot;
        }
        else
            dot = l_dot;
        if (lv->size() > rv->size())//小數
            *rv = add_d_zero (*rv, rv->size(), lv->size(), rv->size() == dot);
        else if (lv->size() < rv->size())
            *lv = add_d_zero (*lv, lv->size(), rv->size(), lv->size() == dot);
    }
    static string rounding (string str, int d=Accuracy_question)
    {
        int dot = str.find ('.');
        if (dot == -1 || str.size()-dot-1 < d)
            return str;
        if ((str[dot+d] > '5') || (str[dot+d] == '5' && (str[dot+d-1]-48)%2 == 1 && str.size() == dot+d+1) || (str[dot+d] == '5' && str.size() > dot+d+1)) // 6入 || 5後為空，基進偶捨 || 5後不為空，進
        {
            str = str.substr (0, dot+d);
            if (d == Accuracy_question)
                str = calculate_a (str, "0.01");
            else if (d == Accuracy) //17
                str = calculate_a (str, "0.0000000000000001", false);
        }
        else
            str = str.substr (0, dot + d);
        return str;
    }
};
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
        if (tmp == NULL) //ぃ﹃い
            return false;
        if (tmp == tail) //⊿Τ
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
        if (head == NULL) //⊿狥﹁
            return NULL;
        Node<T> *tmp = head;
        head = head->get_next();
        if (head == NULL) //琌程
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
        if (tmp->get_next() == NULL) //ぃ﹃い
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
      if (list->get_head() == NULL) //薄猵繷Ю夹穦
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
    ~Stack ()
    {
        delete list;
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
    //硂贺ぃノ患癹杠ノstack
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
    void _display (TreeNode<T> *r, int d)
    {
        if (r == NULL)
            return;
        _display (r->get_right(), d+1);
        int x;
        for (x=0; x < d; x ++)
            cout << "\t\t";
        cout << r->get_data()<<endl;
        _display (r->get_left(), d+1);
    }
    void insert_deSerialize (T data, int w)//
    {
#ifdef debug_insert_deSerialize
        printf ("           in insert_deSerialize, data: ");
        cout << data << ", w: " << w << "\n\n";
#endif // debug_insert_deSerialize
        if (w == 1)
        {
            setRoot (data);
#ifdef debug_insert_deSerialize
            printf ("--> setRoot (data)\n");
            printf ("           out insert_deSerialize\n\n");
#endif // debug_insert_deSerialize
            return;
        }
        TreeNode<T> *tmp = this->root, *n = new TreeNode<T>(data);
        int f = 1;
        while (f <= w)
        {
            f = f << 1;
#ifdef debug_insert_deSerialize
            printf ("f: %d\n", f);
#endif // debug_insert_deSerialize

        }
        f = f >> 2;
        while (f > 1)
        {
#ifdef debug_insert_deSerialize
            printf ("tmp: ");
            cout <<tmp->get_data()<<"\n";
#endif // debug_insert_deSerialize
            if (f & w)
                tmp = tmp->get_right();
            else
                tmp = tmp->get_left();
            f = f >> 1;
        }
#ifdef debug_insert_deSerialize
            printf ("tmp: ");
            cout <<tmp->get_data()<<"\n";
#endif // debug_insert_deSerialize
        if (f & w)
            tmp->set_right (n);
        else
            tmp->set_left (n);
        n->set_level (tmp->get_level() + 1);
        if (n->get_level() > max_level)
            max_level = n->get_level();
        many ++;
#ifdef debug_insert_deSerialize
        printf ("           out insert_deSerialize\n\n");
#endif // debug_insert_deSerialize
    }
    string _calculate (TreeNode<T> *tmp)
    {
#ifdef debug__calculate
        printf ("           in _calculate\n\n");
#endif // debug__calculate
            if (tmp == NULL)
                return "";
            if (tmp->get_left() == NULL && tmp->get_right() == NULL)
                return tmp->get_data();
            string lv, rv, v;
            char operation;
            if (tmp->get_left() != NULL)
                lv = _calculate (tmp->get_left());
            if (tmp->get_right() != NULL)
                rv = _calculate (tmp->get_right());
            v = tmp->get_data();
            operation = v[0];
        if (lv == "" || rv == "")
            throw invalid_argument("");
#ifdef debug__calculate
printf ("operation: ");
            cout << tmp->get_data();
            printf ("\nlv: ");
            cout << lv;
            printf ("\nrv: ");
            cout << rv<< "\n\n";
#endif // debug__calculate
        try
        {
            switch (operation)
            {
            case '+':
                return Formula::calculate_a (lv, rv);//, false
            case '-':
                return Formula::calculate_s (lv, rv);//, false
            case '*':
                return Formula::calculate_m (lv, rv);//, false
            case '/':
                return Formula::calculate_d (lv, rv);//, false
            case '^':
                if (rv.find ('.') != -1)
                    return Formula::calculate_p_d (lv, rv);//, false
                else
                    return Formula::calculate_p_i (lv, rv);//, false
            default:
                throw invalid_argument("");
            }

        }
        catch (invalid_argument &e)
        {
            throw invalid_argument("");
        }
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
            Queue<TreeNode<T> *> q;
            TreeNode<T> *tmp;
            q.enqueue (this->root);
            while (!q.isEmpty())
            {
                if (q.front()->get_left() != NULL)
                    q.enqueue (q.front()->get_left());
                if (q.front()->get_right() != NULL)
                    q.enqueue (q.front()->get_right());
                tmp = q.front();
                q.dequeue();
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
        Queue<TreeNode<T> *> q;
        q.enqueue (this->root);
        cout<<q.front()->get_data();
        if (q.front()->get_left() != NULL)
            q.enqueue (q.front()->get_left());
        if (q.front()->get_right() != NULL)
            q.enqueue (q.front()->get_right());
        q.dequeue();
        while (!q.isEmpty())
        {
            cout<<","<<q.front()->get_data();
            if (q.front()->get_left() != NULL)
                q.enqueue (q.front()->get_left());
            if (q.front()->get_right() != NULL)
                q.enqueue (q.front()->get_right());
            q.dequeue();
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
                    printf ("insert data: ");
                    cout << tmp->get_data();
                    printf (" right\n\n");
#endif // debug_insert
                    return true;
                }
                tmp = tmp->get_right();
            }
            else // == 玡砆serach耞奔
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
                    printf ("insert data: ");
                    cout << tmp->get_data();
                    printf (" left\n\n");
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
    void display ()
    {
        _display (this->root, 0);
    }
    TreeNode<T> *operator [] (int w)
    {
        if (this->root == NULL)
            return NULL;
        Queue<TreeNode<T> *> q;
        TreeNode<T> *tmp;
        int n=0;
        q.push (this->root);
        while (!q.empty())
        {
            if (q.front()->get_left() != NULL)
                q.push (q.front()->get_left());
            if (q.front()->get_right() != NULL)
                q.push (q.front()->get_right());
            tmp = q.pop();
            if (n == w)
                return tmp;
            n ++;
        }
        return NULL;
    }
    string calculate ()
    {
        try
        {
            return _calculate (this->root);
        }
        catch (invalid_argument &e)
        {
            throw invalid_argument("");
        }
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
#ifdef deSerialize_string
        printf ("\nin deSerialize, tree: ");
        cout << tree << "\n\n";
#endif // deSerialize_string
        string c="", data="";
        Queue<string> s;
        Queue<TreeNode<T> *> t;
        TreeNode<T> *tmp, *new_node;
        int x, y, l;
        bool n;
        l = tree.size();
#ifdef deSerialize_string
        printf ("l: %d\n", l);
#endif // deSerialize_string
        for (x=0, y=1; x < l ; x++)
        {
#ifdef deSerialize_string
            printf ("tree[%d]: (%c)\n", x, tree[x]);
#endif // deSerialize_string
            if (tree[x] == ',')
            {
#ifdef deSerialize_string
                printf ("data: ");
                cout << data<<"\n";
#endif // deSerialize_string
                    s.enqueue (data);
                data = "";
                //y ++;
                continue;
            }
            c = tree[x];
            data.append (c);
#ifdef deSerialize_string
            cout << "c: " << c << endl;
            cout << "data: " << data << "\n\n";
#endif // deSerialize_string
        }
        s.enqueue (data);
        setRoot (s.dequeue());
        t.enqueue (this->root);
        n = true;
        while (!s.isEmpty())
        {
#ifdef deSerialize_string
printf ("in while\n");
printf ("s.front(): ");
cout<<s.front()<<endl;
printf ("t.front(): ");
cout<<t.front()->get_data()<<"\n";
printf ("n: %d\n", n);
#endif // deSerialize_string
            if (s.front() == "NULL" && t.front()->get_left() == NULL && n)
            {
                n = false;
                s.dequeue();
#ifdef deSerialize_string
printf ("--> s.dequeue()\n");
printf ("n: %d\n", n);
#endif // deSerialize_string
                continue;
            }
            else if (s.front() == "NULL" && (t.front()->get_left() != NULL || !n))
            {
                t.dequeue();
                s.dequeue();
                n = true;
#ifdef deSerialize_string
printf ("--> s.dequeue()\n");
printf ("--> t.dequeue()\n");
printf ("n: %d\n", n);
#endif // deSerialize_string
                continue;
            }
            new_node = new TreeNode<T> (s.dequeue());
            t.enqueue (new_node);
#ifdef deSerialize_string
printf ("new_node: ");
cout<<new_node->get_data()<<endl;
printf ("t.front(): ");
cout<<t.front()->get_data()<<"\n";
#endif // deSerialize_string
            if (t.front()->get_left() == NULL && n)
            {
                t.front()->set_left(new_node);
#ifdef deSerialize_string
printf ("--> new_node set t.front()->left\n");
#endif // deSerialize_string
            }
            else
            {
                t.front()->set_right (new_node);
#ifdef deSerialize_string
printf ("--> new_node set t.front()->right\n");
#endif // deSerialize_string
            }
            new_node->set_level (t.front()->get_level() + 1);
            if (new_node->get_level() > max_level)
                max_level = new_node->get_level();
            many ++;
            if (t.front()->get_right() != NULL) //t.front()->get_left() != NULL &&
              {
                  t.dequeue();
                  n = true;
#ifdef deSerialize_string
printf ("--> t.dequeue()\n\n\n");
#endif // deSerialize_string
              }
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
        Queue<TreeNode<T> *> q;
        Stack<string> s;

        q.enqueue (this->root);
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
            q.enqueue (q.front()->get_left());
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
            q.enqueue (q.front()->get_right());
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
        q.dequeue();
        while (!q.isEmpty())
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
                q.enqueue (q.front()->get_left());
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
                q.enqueue (q.front()->get_right());
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
            q.dequeue();
        }
        for (tree=s.top(), s.pop(); !s.isEmpty() ; s.pop())
        {
            tree.insert (0, ",");
            v = s.top();
            tree.insert (0, v);
        }
        while (tree[tree.size()-1] == 'L')
            tree.erase (tree.size()-5);
        return tree;
    }
};

int main()
{
    string question="", ans="";
    BinarySearchTree<string> *T;
    stringstream ss;
    int x, add, dot;
    while (getline (cin, question))
    {
#ifdef Bug
        cout  << "question: " << question << "\n";
#endif // Bug
        T = new BinarySearchTree<string>();
        ans = "";
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
            goto ERROR;
#ifdef Bug
        printf ("T->levelorder():\n");
        T->levelorder();
        T->display ();
#endif // Bug
        try
        {
            ans = T->calculate();
            ans = Formula::rounding(ans);
            dot = ans.find('.');
            if (dot == -1)
                ans.append (".00");
            else if (dot != -1 && ans.size()-dot-1 < 2)
                ans.append ("0");
            cout << ans << endl;
        }
        catch (invalid_argument &e)
        {
            goto ERROR;
        }

        if (0)
        {
ERROR:
            printf ("ERROR\n");
        }
        delete T;
    }
    return 0;
}

