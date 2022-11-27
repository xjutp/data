
#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int data;
    struct Node *prev, *next;
};
/*
    function initLinkList will initialize the head of a linked list.
    parameter head represent the head of a linked list.
*/
void initLinkList(struct Node **head)
{
    (*head) = NULL;
}
/*
    function addToHead will insert a node which hold data into linked list from head of the linked list.
    parameter head represent the head of a linked list.
    parameter data represent the data to insert.
*/
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
/*
    function addToHead will insert a node which hold data into linked list from tail of the linked list.
    parameter head represent the head of a linked list.
    parameter data represent the data to insert.
*/
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

/*
int addToNext (struct Node *head, struct Node *at, int d)
{
    struct Node *tmp;
    for (tmp=head; tmp != NULL && tmp != at; tmp = tmp->next);
    if (tmp == NULL)
        return 0;




    tmp = malloc (sizeof(struct Node));
    tmp->data = data;
    tmp->next = tmp->prev = NULL;
}*/

/*
    function deleteData will search from head to find the first node which hold the data and remove it.
    parameter head represent the head of a linked list.
    parameter data represent the data to be search.
*/
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
/*
    function deleteData will search from head to find the first n node which hold the data and remove it.
    parameter head represent the head of a linked list.
    parameter data represent the data to be search.
    parameter n represent the max number of node to be removed.
*/
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
/*
    function display will print out all the data in the linked list from the head
    there is a \n in the end of each print
    output example:
    if your linked list data is 5, 4, 3, 2, 1
    then you should print out "(5, 4, 3, 2, 1)" with the content in quotes but without the quotes
    parameter head represent the head of a linked list.
*/
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
/*
    function enqueue will insert a data into queue
    parameter queue represent the queue
    parameter data represent the data to be insert
*/
void enqueue(struct Node **queue, int data)
{
    addToTail (queue, data);
}
/*
    function dequeue will remove a data from queue
    parameter queue represent the queue
    this function should return the data that be removed
*/
int dequeue(struct Node **queue)
{
    struct Node *tmp;
    if ((*queue) != NULL)
        tmp = deleteFromHead (queue);
    if (tmp != NULL)
        return tmp->data;
}
/*
    function front will give the next remove data in the given queue
    parameter queue represent the queue
    this function should return the next remove data
*/
int front(struct Node *queue)
{
    if (queue != NULL)
        return queue->data;
}
/*
    function isEmpty will determine if the given queue is empty or not
    parameter queue represent the queue
    this function should return 1 if the given queue is empty, 0 if not
*/
int isEmpty(struct Node *queue)
{
if (queue == NULL)
    return 1;
return 0;
}


int main() {
  struct Node *queue;

  initLinkList(&queue);

  enqueue(&queue, 1);
  enqueue(&queue, 2);
  enqueue(&queue, 3);
  enqueue(&queue, 4);
  enqueue(&queue, 5);
  printf("%d", dequeue(&queue));
  printf("%d", front(queue));
  printf("%d", dequeue(&queue));
  printf("%d", dequeue(&queue));
  printf("%d", dequeue(&queue));
  printf("%d", dequeue(&queue));

  return 0;
}
