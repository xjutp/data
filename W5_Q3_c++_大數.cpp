/**
 * BigDecimal
 *
 * @Description:
 * Please finish the class "BigDecimal"
 * You can add any function or variable in class "BigDecimal" if you want.
 *
 * Note: You must use your own "LinkedList" class or you will get up to 0 points.
 */

#include<bits/stdc++.h>
#include <iostream>
#include <string>
#define Accuracy_question 3
#define Accuracy_question_d 4
#define Accuracy 18 //�����16��N�������17��
#define Me
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
        return;
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
        return;
    }
    bool addToNext (Node<T> *at, T d)
    {
        Node<T> *tmp;
        for (tmp=head; tmp != NULL && tmp != at; tmp = tmp->get_next());
        if (tmp == NULL) //���b��C��
            return false;
        if (tmp == tail) //�S����@��
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
        #ifdef Mem
        printf ("         in deleteFromHead\n");
        #endif // Mem
        if (head == NULL) //�S�F��i�R
            return NULL;
        Node<T> *tmp = head;
        head = head->get_next();
        #ifdef Mem
        printf ("head != NULL\n--> tmp = head\n--> head = head->get_next()\n");
        cout << "tmp->get_data(): "<<tmp->get_data()<<"\n";
        #endif // Mem
        if (head == NULL) //�R���O�̫�@��
        {
        #ifdef Mem
            printf ("head == NULL\n\n");
        #endif // Mem
            tail = NULL;
        #ifdef Mem
        printf ("           end deleteFromHead\n");
        #endif // Mem
            return tmp;
        }
        #ifdef Mem
        printf ("head != NULL\n");
        cout << "head: "<<head->get_data()<<"\n";
        #endif // Mem
        tmp->set_next(NULL);
        head->set_prev(NULL);
        #ifdef Mem
        printf ("           end deleteFromHead\n");
        #endif // Mem
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
        if (tmp->get_next() == NULL) //���b��C��
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
        return out;
    }
};

class Formula
{
public:
    static string calculate (string lv, char operation, string rv)
    {
        //printf ("in calculate\n");
        //S->show();
        try
        {
            clear_vstring (&lv, &rv);
            //cout << "lv: " << lv << "\nrv: " << rv <<"\n\n";
            if (operation == '^')
            {
                if (rv.find ('.') == -1)
                    return calculate_p_i (lv, rv);
                return calculate_p_d (lv, rv);
            }
            else if (operation == '*')
                return calculate_m (lv, rv);
            else if (operation == '/')
                return calculate_d (lv, rv);
            else if (operation == '+')
                return calculate_a (lv, rv);
            else if (operation == '-')
                return calculate_s (lv, rv);
            else
                throw invalid_argument("");
        }
        catch (invalid_argument &e)
        {
            throw invalid_argument("");
        }
    }
    static string calculate_p_d (string lv, string rv, bool b=true)
    {// exp(b * ln(a)) = exp(ln(C)) --> exp(b * ln(a)) = C = a^b
        if (lv == "0" || lv[0] == '-')
            throw invalid_argument("");
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
        for (c = v ; VS (c, "0.00") > 0 ; c = calculate_s (c, "1")) // �]�� ��c_s�i�� �ҥH �eVS "0.00"
            tmp = calculate_m (tmp, c, false);
        return tmp;
    }
    static string calculate_p_i (string lv, string rv, bool b=true)
    {
        clear_vstring (&lv, &rv);
        if (lv == "")
            lv = "0";
        if (rv == "")
            rv = "0";
        if (lv == "0")
            throw invalid_argument("");
        else if (rv == "0")
            return "1.00";
        else if (rv[0] == '-') //   a ^ -b --> 1 / a ^ b
        {
            if (b)
                return calculate_d ("1", calculate_p_i (lv, calculate_s ("0", rv, false), false));
            else
                return calculate_d ("1", calculate_p_i (lv, calculate_s ("0", rv, false), false), b, Accuracy);
        }
        else if (lv[0] == '-' && (rv[rv.size()-1]-48)%2 == 1) //-a ^ b  b�O��� --> - (a ^ b)
            return calculate_s ("0", calculate_p_i (calculate_s ("0", lv, false), rv, b), b);
        else if (lv[0] == '-' && (rv[rv.size()-1]-48)%2 == 0) //-a ^ b  b�O���� -->   (a ^ b)
            return calculate_p_i (calculate_s ("0", lv, false), rv, b);
        string tmp="", c="";
        int x, y, z;
        for (c="0", tmp="1" ; VS (c, rv) < 0 ; c = calculate_a (c, "1"))
            tmp = calculate_m (tmp, lv, false);
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
        /**********�B��********************/
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
        /********����B�R�s*******************/
        tmp = move_d_zero (tmp);// �p���I�᭱�R�s
        tmp = string(tmp.rbegin(), tmp.rend());//����
        tmp = move_i_zero (tmp);//��ƫe�R�s
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

        if (l_dot != -1 && r_dot != -1) // �P�� 10 ^ n
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
            v = "0"; // �����p�ƾ���
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
        if (c == lv) // �Q���Ƥp�󰣼ơA��Ʀ�Ƭ��s
            tmp.append ("0");
        lv = c; // �l��
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
        add_zero (&lv, &rv); // �ɹs
        /***********�B��*******************/
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
        /********����B�R�s*******************/
        tmp = move_d_zero (tmp);// �p���I�᭱�R�s
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
            if (b)
                return rounding (lv);
            else
                return lv; //rounding (lv, Accuracy) ���ۤv����ܸ��Ϊ��A���T�w�|���|�v�T�p��X������
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
        add_zero (&lv, &rv); // �ɹs
        /***********�B��*******************/
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
        /********����B�R�s*******************/
        tmp = move_d_zero (tmp);// �p���I�᭱�R�s
        tmp = string(tmp.rbegin(), tmp.rend());//����
        tmp = move_i_zero (tmp);//��ƫe�R�s
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
    static string move_d_zero (string v) // v �˱�
    {
        int x;
        if (v.find('.') == -1) // �S���p��
            return v;
        for (x=0; v[x] != '.' && v[x] == '0' ; x++);
        if (v[x] == '.') //�p���I�᳣�O�s
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
        /*******�ɹs*********/
        if (l_dot > r_dot)// ���
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
        if (lv->size() > rv->size())//�p��
            *rv = add_d_zero (*rv, rv->size(), lv->size(), rv->size() == dot);
        else if (lv->size() < rv->size())
            *lv = add_d_zero (*lv, lv->size(), rv->size(), lv->size() == dot);
    }
    static string rounding (string str, int d=Accuracy_question)
    {
        int dot = str.find ('.');
        if (dot == -1 || str.size()-dot-1 < d)
            return str;
        if ((str[dot+d] > '5') || (str[dot+d] == '5' && (str[dot+d-1]-48)%2 == 1 && str.size() == dot+d+1) || (str[dot+d] == '5' && str.size() > dot+d+1)) // 6�J || 5�ᬰ�šA��i���� || 5�ᤣ���šA�i
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
class BigDecimal
{
private:
    LinkedList<string> *integer;
    LinkedList<string> *decimal;
public:
    BigDecimal()
    {
        integer = new LinkedList<string>();
        decimal = new LinkedList<string>();
    }
    BigDecimal(string data)
    {
        integer = new LinkedList<string>();
        decimal = new LinkedList<string>();
        int x;
        string tmp="";
        x = data.find ('.');
        if (x == -1)//�S���p��
            integer->addToTail(data);
        else
        {
            tmp = data.substr (0, x);
            integer->addToHead(tmp);
            tmp = data.substr (x+1);
            decimal->addToHead(tmp);
        }
    }
    BigDecimal* operator+(BigDecimal *bigDecimal)
    {
        try
        {
        string lv, rv;
        BigDecimal*ans;
        to_string (&lv, &rv, bigDecimal);
        ans = new BigDecimal (Formula::calculate_a (lv, rv));
        return ans;
        }
        catch (invalid_argument &e)
        {
            throw invalid_argument ("");
        }
    }
    BigDecimal* operator-(BigDecimal *bigDecimal)
    {
        try
        {
        string lv, rv;
        BigDecimal*ans;
        to_string (&lv, &rv, bigDecimal);
        ans = new BigDecimal (Formula::calculate_s (lv, rv));
        return ans;
        }
        catch (invalid_argument &e)
        {
            throw invalid_argument ("");
        }
    }
    BigDecimal* operator*(BigDecimal *bigDecimal)
    {
        try
        {
        string lv, rv;
        BigDecimal*ans;
        to_string (&lv, &rv, bigDecimal);
        ans = new BigDecimal (Formula::calculate_m (lv, rv));
        return ans;
        }
        catch (invalid_argument &e)
        {
            throw invalid_argument ("");
        }
    }
    BigDecimal* operator/(BigDecimal *bigDecimal)
    {
        try
        {
        string lv, rv;
        BigDecimal*ans;
        to_string (&lv, &rv, bigDecimal);
        ans = new BigDecimal (Formula::calculate_d (lv, rv));
        return ans;
        }
        catch (invalid_argument &e)
        {
            throw invalid_argument ("");
        }
    }
    BigDecimal* operator^(BigDecimal *bigDecimal)
    {
        try
        {
        string lv, rv;
        bool dot=false;
        BigDecimal *ans;
        to_string (&lv, &rv, bigDecimal);
        if (rv.find('.') != -1)
            dot = true;
        /*cout << "lv: "<<lv<<"\n";
        cout << "rv: "<<rv<<"\n";*/
        if (dot)
            ans = new BigDecimal (Formula::calculate_p_d (lv, rv));
        else
            ans = new BigDecimal (Formula::calculate_p_i (lv, rv));
        return ans;
        }
        catch (invalid_argument &e)
        {
            throw invalid_argument ("");
        }
    }
    LinkedList<string> *get_integer () const
    {
        return (LinkedList<string> *)integer;
    }
    LinkedList<string> *get_decimal () const
    {
        return (LinkedList<string> *)decimal;
    }
    void show () const
    {
        cout << integer->get_head()->get_data();
        if (decimal->get_head() == NULL)
            return;
        cout << "." <<decimal->get_head()->get_data();
        return;
    }
    void to_string (string *lv, string *rv, BigDecimal *bigDecimal)
    {
        *lv = this->get_integer()->get_head()->get_data();
        if (this->get_decimal()->get_head() != NULL)
        {
            lv->append (".");
            lv->append (this->get_decimal()->get_head()->get_data());
        }
        *rv = bigDecimal->get_integer()->get_head()->get_data();
        if (bigDecimal->get_decimal()->get_head() != NULL)
        {
            rv->append (".");
            rv->append (bigDecimal->get_decimal()->get_head()->get_data());
        }
        Formula::clear_vstring (lv, rv);
    }
    friend std::ostream &operator<<(std::ostream &out, BigDecimal *bigDecimal)
    {
        if (bigDecimal->get_integer()->get_head() == NULL)
        {
            out << "NULL\n";
            return out;
        }
        out << bigDecimal->get_integer()->get_head()->get_data();
        if (bigDecimal->get_decimal()->get_head() == NULL)
        {
            out << ".00\n";
            return out;
        }
        string tmp = bigDecimal->get_decimal()->get_head()->get_data();
        if (tmp.size() >= 2)
            out << "." << tmp[0] << tmp[1]<<endl;
        else if (tmp.size() == 1)
            out << "." << tmp << "0"<<endl;
        return out;
    }
    friend std::istream &operator>>(std::istream &in, BigDecimal *data)
    {
        #ifdef Mem
        printf ("           in operator>>\n");
        #endif // Mem
        Node<string> *tmp=NULL;
        while (data->get_integer()->get_head() != NULL)
        {
        #ifdef Mem
            printf ("data->get_integer()->get_head() != NULL\n");
            cout << "show linked list --- data->get_integer(): " << data->get_integer()<<endl;
        #endif // Mem
            tmp = data->get_integer()->deleteFromHead();
           /* printf ("i    %p\n", tmp);
            cout << tmp->get_data()<<endl;*/
            delete tmp;
        }
        while (data->get_decimal()->get_head() != NULL)
        {
        #ifdef Mem
            printf ("data->get_decimal()->get_head() != NULL\n");
            cout << "show linked list --- data->get_decimal(): " << data->get_decimal()<<endl;
        #endif // Mem
            tmp = data->get_decimal()->deleteFromHead();
           /* printf ("d    %p\n", tmp);
            cout << tmp->get_data()<<endl;*/
            delete tmp;
        }
        string d;
        in >> d;
        #ifdef Mem
        cout << "--> in >> d: "<< d<<"\n";
        #endif // Mem
        BigDecimal b(d);

        data->get_integer()->addToHead(b.get_integer()->get_head()->get_data());
        tmp = b.get_integer()->deleteFromHead();
        delete tmp;
        #ifdef Mem
        printf ("--> tmp = b.get_integer()->deleteFromHead()\n--> delete tmp\n");
        #endif // Mem
        if (b.get_decimal()->get_head() != NULL)
        {
            data->get_decimal()->addToHead(b.get_decimal()->get_head()->get_data());
            tmp = b.get_decimal()->deleteFromHead();
            delete tmp;
        #ifdef Mem
        printf ("--> tmp = b.get_decimal()->deleteFromHead()\n--> delete tmp\n");
        #endif // Mem
        }
        return in;
    }
};
int main()
{
    BigDecimal *bigDecimal1 = new BigDecimal();
    BigDecimal *bigDecimal2 = new BigDecimal();
    char operation;
    /*cin >> bigDecimal1;
    printf ("after cin\n");
    cout << bigDecimal1;*/
        #ifdef Mem
    cout << bigDecimal1<<endl;
    cout << bigDecimal2<<endl;
        #endif // Mem
    while(cin >> bigDecimal1 >> operation >> bigDecimal2)
    {
        //cout << bigDecimal1 << operation << bigDecimal2 << endl;
        #ifdef Mem
    cout << bigDecimal1<<endl;
    cout << bigDecimal2<<endl;
        #endif // Mem
       try
       {
        switch (operation)
        {
        case '+':
            cout << (*bigDecimal1 + bigDecimal2);
            break;
        case '-':
            cout << (*bigDecimal1 - bigDecimal2);
            break;
        case '*':
            cout << (*bigDecimal1 * bigDecimal2);
            break;
        case '/':
            cout << (*bigDecimal1 / bigDecimal2);
            break;
        case '^':
            cout << (*bigDecimal1 ^ bigDecimal2);
            break;
        default:
            break;
        }
       }
        catch (invalid_argument &e)
        {
            goto ERROR;
        }

        if (0)
        {
ERROR:
            cout << "ERROR\n";
        }
    }
    return 0;
}
/*

369.00 ^ 3.14 ��ǫ׶}��31�|�� --> 21 OK --> 16 ok --> �A�U�h�N����

*/
