

#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int data;
    struct Node *prev, *next;
};
void initLinkList(struct Node **head)
{
    (*head) = NULL;
}
void addToHead(struct Node **head, int data)
{
    struct Node *tmp = malloc (sizeof(struct Node));
    tmp->data = data;
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
void addToTail(struct Node **head, int data)
{
    struct Node *tmp = malloc (sizeof(struct Node));
    tmp->data = data;
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
    if (tail == (*head)) // 刪的為最後一個
    {
        (*head) = NULL;
        return tmp;
    }
    tail = tail->prev;
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
void deleteData(struct Node **head, int data)
{
    struct Node *tmp;
    for (tmp=(*head); tmp != NULL && tmp->data != data; tmp = tmp->next);
    if (tmp != NULL)
    {
        if (tmp == (*head))
            deleteFromHead (head);
        else
            deleteFromMiddle (head, tmp);
    }
}
void deleteDatas(struct Node **head, int data, int n)
{
    struct Node *tmp = (*head), *at;
    while (n > 0 && tmp != NULL)
    {
        for (; tmp != NULL && tmp->data != data; tmp = tmp->next);
        if (tmp != NULL)
        {
            at = tmp;
            tmp = tmp->next;
            if (at == (*head))
                deleteFromHead(head);
            else
                deleteFromMiddle(head, at);
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
            printf ("%d, ", tmp->data);
        printf ("%d", tmp->data);
    }
    printf (")\n");
}
void push(struct Node **stack, int data)
{
    addToHead (stack, data);
}
int pop(struct Node **stack)
{
    if ((*stack) != NULL)
    {
        struct Node *s = deleteFromHead (stack);
        int t = s->data;
        free (s);
        return t;
    }
}
int top(struct Node *stack)
{
    if (stack != NULL)
        return stack->data;
}
int isEmpty(struct Node *stack)
{
    if (stack == NULL)
        return 1;
    return 0;
}
int size(struct Node *stack)
{
    //struct Node *tmp = stack;
    int size = 0;
    while (stack != NULL)
    {
        size ++;
        stack = stack->next;
    }
    return size;
}


void free_list (struct Node **Stack)
{
    while ((*Stack) != NULL)
        pop (Stack);
}

void take_to (struct Node **stack_i, struct Node **stack_f)
{
    push(stack_f, pop (stack_i));
}

void part1 (struct Node **stack_a, struct Node **stack_b, struct Node **stack_c, int *move_times)
{
    take_to (stack_a, stack_b);
    take_to (stack_a, stack_c);
    take_to (stack_b, stack_c);
    (*move_times) += 3;
}
void part2 (struct Node **stack_a, struct Node **stack_b, struct Node **stack_c, int *move_times)
{
    take_to (stack_c, stack_a);
    take_to (stack_c, stack_b);
    take_to (stack_a, stack_b);
    (*move_times) += 3;
}
void part3 (struct Node **stack_a, struct Node **stack_b, struct Node **stack_c, int *move_times)
{
    take_to (stack_b, stack_c);
    take_to (stack_b, stack_a);
    take_to (stack_c, stack_a);
    (*move_times) += 3;
}


int main()
{
    int ini;


    while (scanf ("%d", &ini) != -1)
    {
        struct Node *stack_a, *stack_b, *stack_c;
        int move_times = 0;
        initLinkList(&stack_a);
        initLinkList(&stack_b);
        initLinkList(&stack_c);

        if (ini == 0)
            goto End;
        if (ini == 1)
        {
            move_times = 1;
            goto End;
        }

        for (; ini > 0; ini --)
            push(&stack_a, ini);

        while (1)
        {
            part1 (&stack_a, &stack_b, &stack_c, &move_times);
            if (isEmpty(stack_a) && isEmpty(stack_b))
                break;
            if (isEmpty(stack_b)) // ab
            {
                take_to (&stack_a, &stack_b); //ab
                move_times ++;
            }
            else if (isEmpty(stack_a))
            {
                take_to (&stack_b, &stack_a); //ba
                move_times ++;
            }
            else if (top(stack_a) < top(stack_b))
            {
                take_to (&stack_a, &stack_b); //ab
                move_times ++;
            }
            else // a > b
            {
                take_to (&stack_b, &stack_a); //ba
                move_times ++;
            }
            part2 (&stack_a, &stack_b, &stack_c, &move_times);
            if (isEmpty(stack_a) && isEmpty(stack_c))
                break;
            if (isEmpty(stack_c)) //ac
            {
                take_to (&stack_a, &stack_c); //ac
                move_times ++;
            }
            else if (isEmpty(stack_a)) //ca
            {
                take_to (&stack_c, &stack_a); //ca
                move_times ++;
            }
            else if (top(stack_a) < top(stack_c)) //ac
            {
                take_to (&stack_a, &stack_c); //ac
                move_times ++;
            }
            else //ca
            {
                take_to (&stack_c, &stack_a); //ca
                move_times ++;
            }
            part3 (&stack_a, &stack_b, &stack_c, &move_times);
            if (isEmpty(stack_c))
            {
                take_to (&stack_b, &stack_c); //bc
                move_times ++;
            }
            else if (isEmpty(stack_b))
            {
                take_to (&stack_c, &stack_b); //cb
                move_times ++;
            }
            else if (top(stack_b) < top(stack_c))
            {
                take_to (&stack_b, &stack_c); //bc
                move_times ++;
            }
            else
            {
                take_to (&stack_c, &stack_b); //cb
                move_times ++;
            }
        }

End:
        printf ("%d\n", move_times);

        free_list (&stack_a);
        free_list (&stack_b);
        free_list (&stack_c);
    }
    return 0;
}
