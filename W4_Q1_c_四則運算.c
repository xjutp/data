
/**
 * Arithmetic
 *
 * @Description:
 *  Please write a program that reads in an expression and gives its result.
 *  The expression will contain addition, subtraction, multiplication, division, power, and parentheses.
 *  Please follow PEMDAS rules and round to the second round place after every operation.
 *  You must use the class "Stack" you wrote last week or you will get up to 0 points.
 *
 * Rounding rule:
 * Banker's rounding
 * Symbol example:
 * addition: "+"
 * subtraction: "-"
 * multiplication: "*"
 * division: "/"
 * power: "^"
 * parentheses: "()"
 *
 * @Input Description
 * Expressions end up with line-break or end-of-file.
 *
 * @Output Description
 * Result of the expression to the 2nd decimal place, "ERROR" when parentheses count does not match or operation error, ending with a "\n" of each line
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define L 1000
#define Accuracy_question 3
#define Accuracy 17 //取到第16位代表往後找到第17位

#define bu//g
#define bug_calculat//e
#define bug_calculate_p_//i

struct Node
{
    char *data;
    struct Node *prev, *next;
};
void initLinkList(struct Node **head)
{
    (*head) = NULL;
}
void addToHead(struct Node **head, char *str, int l)
{
    struct Node *tmp = malloc (sizeof(struct Node));
    tmp->data = malloc (sizeof(char) * (l+1));
    strcpy (tmp->data, str);
    tmp->next = tmp->prev = NULL;

    if ((*head) == NULL)
    {
        (*head) = tmp;
        return;
    }
    (*head)->prev = tmp;
    tmp->next = (*head);
    (*head) = tmp;
}
void addToTail(struct Node **head, char *str, int l)
{
    struct Node *tmp = malloc (sizeof(struct Node));
    tmp->data = malloc (sizeof(char) * (l+1));
    strcpy (tmp->data, str);
    tmp->next = tmp->prev = NULL;
    if ((*head) == NULL)
    {
        (*head) = tmp;
        return;
    }
    struct Node *tail = (*head);
    while (tail->next != NULL)
        tail = tail->next;
    tail->next = tmp;
    tmp->prev = tail;
}
struct Node *addToNext (struct Node *head, struct Node *at, char *str, int l)
{
    struct Node *tmp;
    for (tmp=head; tmp != NULL && tmp != at; tmp = tmp->next);
    if (tmp == NULL)
        return NULL;
    tmp = malloc (sizeof(struct Node));
    tmp->data = malloc (sizeof(char) * (l+1));
    strcpy (tmp->data, str);
    tmp->next = tmp->prev = NULL;
    if (at->next == NULL)
    {
        tmp->prev = at;
        at->next = tmp;
        return tmp;
    }
    tmp->prev = at;
    tmp->next = at->next;
    at->next = tmp;
    tmp->next->prev = tmp;
    return tmp;
}
struct Node *deleteFromHead (struct Node **head)
{
    if ((*head) == NULL) //沒東西可刪
        return NULL;
    struct Node *tmp = (*head);
    (*head) = (*head)->next;
    if ((*head) == NULL) //刪的是最後一個
        return tmp;
    tmp->next = NULL;
    (*head)->prev = NULL;
    return tmp;
}
struct Node *deleteFromTail (struct Node **head)
{
    if ((*head) == NULL) //沒東西可刪
        return NULL;
    struct Node *tail = (*head);
    while (tail->next != NULL)
        tail = tail->next;
    struct Node *tmp = tail;
    tail = tail->prev;
    if (tail == NULL)
        return tmp;
    tmp->prev = NULL;
    tail->next = NULL;
    return tmp;
}
struct Node *deleteFromMiddle (struct Node **head, struct Node *at)
{
    struct Node *tmp;
    for (tmp=(*head); tmp->next != NULL && tmp->next != at; tmp = tmp->next);
    if (tmp->next == NULL) //不在串列中
        return NULL;
    tmp->next = at->next;
    if (at->next != NULL)
        at->next->prev = tmp;
    at->prev = at->next = NULL;
    return at;
}
void deleteData(struct Node **head, char *data)
{
    struct Node *tmp;
    for (tmp=(*head); tmp != NULL && strcmp(tmp->data, data) != 0; tmp = tmp->next);
    if (tmp != NULL)
    {
        if (tmp == (*head))
            free (deleteFromHead (head));
        else
            free (deleteFromMiddle (head, tmp));
    }
}
void deleteDatas(struct Node **head, char *data, int n)
{
    struct Node *tmp = (*head), *at;
    while (n > 0 && tmp != NULL)
    {
        for (; tmp != NULL && strcmp(tmp->data, data) != 0; tmp = tmp->next);
        if (tmp != NULL)
        {
            at = tmp;
            tmp = tmp->next;
            if (at == (*head))
                free (deleteFromHead (head));
            else
                free (deleteFromMiddle (head, at));
            n--;
        }
    }
}
void display(struct Node *head)
{
    printf ("(");
    if (head != NULL)
    {
        struct Node *tmp;
        for (tmp=head; tmp->next != NULL; tmp = tmp->next)
            printf ("%s, ", tmp->data);
        printf ("%s", tmp->data);
    }
    printf (")\n");
}
void push(struct Node **stack, char *str)
{
    addToHead (stack, str, strlen(str));
}
char *pop(struct Node **stack)
{
    if ((*stack) != NULL)
        return deleteFromHead (stack)->data;
    return NULL;
}
char *top(struct Node *stack)
{
    if (stack != NULL)
        return stack->data;
    return NULL;
}
int isEmpty(struct Node *stack)
{
    if (stack == NULL)
        return 1;
    return 0;
}
int size(struct Node *stack)
{
    struct Node *tmp = stack;
    int size = 0;
    while (tmp != NULL)
    {
        size ++;
        tmp = tmp->next;
    }
    return size;
}

char Ans[L]= {};

void append (char *tmp, char s[])
{
    int x, y;
    for (x=strlen(tmp), y=0; s[y] != '\0'; y++, x++)
        tmp[x] = s[y];
    tmp[x] = '\0';
}
void insert (char *tmp, int d, char s[])
{
    int x, y;
    char v[L]= {};
    for (x=0; x < d; x++)
        v[x] = tmp[x];
    for (y=0; s[y] != '\0'; y++, x++)
        v[x] = s[y];
    for (; tmp[d] != '\0'; d++, x++)
        v[x] = tmp[d];
    v[x] = '\0';
    strcpy (tmp, v);
}
void ht (char *v)
{
    char s[L]= {};
    int x, y;
    for (x=strlen(v)-1, y=0; x >= 0; x --, y++)
        s[y] = v[x];
    s[y] = '\0';
    strcpy (v, s);
}
int find (char *v, char ch)
{
    int x;
    for (x=0; v[x] != '\0' && v[x] != ch; x++);
    return x;
}
void erase (char *v, int i, int d)
{
    int x, y;
    for (x=i, y=i+d; v[y] != '\0'; x++, y++)
        v[x] = v[y];
    v[x] = '\0';
}

char *calculate_p_i (double lv, double rv, int d)
{
#ifdef bug_calculate_p_i
    printf ("\tin calculate_p_i\n");
    printf ("lv: %lf\nrv: %lf\n\n", lv, rv);
#endif // bug_calculate_p_i

    int x;
    double ans;
    if (lv == 0)
        return "error";
    if (rv == 0)
    {
        strcpy (Ans, "1.00");
        return Ans;
    }
    if (rv < 0) //   a ^ -b --> 1 / a ^ b
        ans = (double)atof (calculate_p_i (lv, (0-rv), Accuracy_question));
    else
        for (x=0, ans=1; x < (int)rv; x++)
            ans *= lv;

    ans *= 100;
    if (ans > 0 && (ans - (int) ans > 0.5 || (ans - (int)ans == 0.5 && (int)ans % 10 % 2 == 1)))
        ans += 1;
    else if (ans < 0 && (ans - (int) ans < -0.5 || (ans - (int)ans == -0.5 && (int)ans % 10 % 2 == -1)))
        ans -= 1;
    sprintf (Ans, "%.2lf", ((int)ans)/100.0);
    return Ans;
}

char *calculate (struct Node **Stack, char operation)
{
#ifdef bug_calculate
    printf ("\tin calculate\n");
    display (*Stack);
#endif // bug_calculate
    char vl[L]= {}, vr[L]= {};
    double lv, rv, ans;

    strcpy (vr, pop(Stack));

#ifdef bug_calculate
    printf ("--> strcpy (vr, pop(Stack)\n");
    printf ("vr: %s\n", vr);
    display (*Stack);
    printf ("\n");
#endif // bug_calculate

    if (strcmp(vr, "") == 0)
        return "error";
    strcpy (vl, pop(Stack));

#ifdef bug_calculate
    printf ("--> strcpy (vl, pop(Stack)\n");
    printf ("vl: %s\n", vl);
    display (*Stack);
    printf ("\n");
#endif // bug_calculate

    if (strcmp(vl, "") == 0)
        return "error";

    lv = (double)atof (vl);
    rv = (double)atof (vr);

#ifdef bug_calculate
    printf ("lv: %lf\noperation: %c\nrv: %lf\n\n", lv, operation, rv);
#endif // bug_calculate

    if (operation == '^')
    {
        if (rv - (int)rv == 0)
            ans = (double)atof (calculate_p_i (lv, rv, Accuracy_question));
        else
            ans = pow (lv, rv);
    }
    else if (operation == '*')
        ans = lv * rv;
    else if (operation == '/')
        ans = lv / rv;
    else if (operation == '+')
        ans = lv + rv;
    else if (operation == '-')
        ans = lv - rv;
    else
        return "error";
#ifdef bug_calculate
    printf ("ans: %lf\n", ans);
#endif // bug_calculate
    ans *= 100;
#ifdef bug_calculate
    printf ("--> ans *= 100\n");
    printf ("ans: %lf\n", ans);
    printf ("d: %lf\n", ans - (int)ans, (int)ans % 10 % 2);
    printf ("(int)ans: %d\n(int)ans % 10: %d\n(int)ans % 10 % 2: %d\n", (int)ans, (int)ans % 10, (int)ans % 10 % 2);
#endif // bug_calculate

    if (ans > 0 && (ans-(int)ans > 0.5 || (ans-(int)ans == 0.5 && (int)ans % 10 % 2 == 1)))
        ans += 1;
    else if (ans < 0 && (ans - (int) ans < -0.5 || (ans - (int)ans == -0.5 && (int)ans % 10 % 2 == -1)))
        ans -= 1;


#ifdef bug_calculate
    printf ("--> rounding\n");
    printf ("ans: %lf\n", ans);
#endif // bug_calculate
    sprintf (Ans, "%.2lf", ((int)ans)/100.0);
#ifdef bug_calculate
    printf ("Ans: %s\n", Ans);
    display (*Stack);
    printf ("\tout calculate\n\n\n");
#endif // bug_calculate
    return Ans;
}

int main()
{
    char question[L]= {};
    struct Node *Stack;
    initLinkList(&Stack);

    while (fgets (question, L, stdin) != NULL)
    {
        if (question[strlen(question)-1] == '\n')
            question[strlen(question)-1] = '\0';
        insert (question, 0, "(");
        insert (question, strlen(question), ")");
#ifdef bug
        printf ("\tin main while fgets\n");
        printf ("question: %s\n\n", question);
#endif // bug
        char postfix[L]= {}, tmp[3]= {}, answer[L]= {};
        int x=0, y=0, dot=0, l=strlen(question);
        double z;
        for (x=0; x < l ; x++)
            if (question[x] == '-' && x+1 < l && (question[x+1]+2)/10 == 5 && x-1 >= 0 && (question[x-1]+2)/10 != 5)
                question[x] = ':';
#ifdef bug
        printf ("--> '-' change ':'\n");
        printf ("question: %s\n\n", question);
#endif // bug
        for (x=0; x < l ; x++) // 中序轉後序
        {
#ifdef bug
            printf ("in while question[%d]: %c\n", x, question[x]);
            printf ("in while postfix: %s\n", postfix);
#endif // bug
            if ((question[x]+2)/10 == 5 || question[x] == '.' || question[x] == ':') // 數字
            {
                tmp[0] = question[x];
                append (postfix, tmp);
            }//非數字
            else if (question[x] == '(')// 左括號直接丟
            {
                tmp[0] = question[x];
                push(&Stack, tmp);
            }
            else if (question[x] == '^') //運算子
            {
                append (postfix, " ");
                tmp[0] = question[x];
                push(&Stack, tmp);
            }
            else if (question[x] == '*' || question[x] == '/') //運算子
            {
                if (strcmp(top(Stack), "^") == 0 || strcmp(top(Stack), "*") == 0 || strcmp(top(Stack), "/") == 0)
                    append (postfix, pop(&Stack));
                append (postfix, " ");
                tmp[0] = question[x];
                push(&Stack, tmp);
            }
            else if (question[x] == '+' || question[x] == '-') //運算子
            {
                if (strcmp(top(Stack), "^") == 0 || strcmp(top(Stack), "*") == 0 || strcmp(top(Stack), "/") == 0 || strcmp(top(Stack), "+") == 0 || strcmp(top(Stack), "-") == 0)
                    append (postfix, pop(&Stack));
                append (postfix, " ");
                tmp[0] = question[x];
                push(&Stack, tmp);
            }
            else if (question[x] == ')')
            {
#ifdef bug
                display (Stack);
#endif // bug
                while (!isEmpty(Stack) && strcmp (top(Stack), "(") != 0)
                {
                    strcpy (answer, pop (&Stack));
                    if (strcmp(answer, "") != 0)
                        append (postfix, answer);
                    else
                        goto ERROR;
                }
                if (isEmpty (Stack))
                    goto ERROR;
                pop (&Stack);
            }
            else
                goto ERROR;
        }
#ifdef bug
        printf ("after postfix: %s\n", postfix);
#endif // bug
        for (x=0, l=strlen(postfix), strcpy(question, ""); x < l; x++)
        {
#ifdef bug
            printf ("in for postfix[%d]: %c\n", x, postfix[x]);
            display (Stack);
#endif // bug
            if (postfix[x] == ' ' || postfix[x] == '^' || postfix[x] == '*' || postfix[x] == '/' || postfix[x] == '+' || postfix[x] == '-')
            {
                if (strcmp(question, "") != 0)
                    push (&Stack, question);
                strcpy (question, "");
                if (postfix[x] == '^' || postfix[x] == '*' || postfix[x] == '/' || postfix[x] == '+' || postfix[x] == '-')
                {
                    if (size (Stack) < 2)
                        goto ERROR;
                    strcpy (question, calculate (&Stack, postfix[x]));
#ifdef bug
                    printf ("after calculate question: %s\n\n\n", question);
#endif // bug
                    if (strcmp(question, "error") == 0)
                        goto ERROR;
#ifdef bug
                    display (Stack);
#endif // bug
                    push (&Stack, question);
                    strcpy (question, "");
#ifdef bug
                    printf ("--> push\n");
                    display (Stack);
                    printf ("\n\n");
#endif // bug
                }
            }
            else if (postfix[x] == ':' && ((x > 0 && (postfix[x-1]+2)/10 != 5) || x == 0) && x < l-1 && (postfix[x+1]+2)/10 == 5)
                append (question, "-");
            else if ((postfix[x]+2)/10 == 5)
            {
                tmp[0] = postfix[x];
                append (question, tmp);
            }
            else if (postfix[x] == '.' && x > 0 && (postfix[x-1]+2)/10 == 5 && x < l-1 && (postfix[x+1]+2)/10 == 5)
            {
                tmp[0] = postfix[x];
                append (question, tmp);
            }
            else
                goto ERROR;
        }
#ifdef bug
        display (Stack);
#endif // bug
        z = (double)atof (pop(&Stack));
        sprintf (answer, "%.2lf", z);

        dot = find (answer, '.');
        if (answer[dot] == '\0')
            append (answer, ".00");
        else if (answer[dot] != '\0' && strlen (answer) - dot - 1 < 2)
            append (answer, "0");

#ifdef bug
        printf ("answer: ");
#endif // bug
        printf ("%s\n", answer);

        if (0)
        {
ERROR:
            printf ("ERROR\n");
        }
        while (!isEmpty(Stack))
            pop(&Stack);
    }

    return 0;
}
