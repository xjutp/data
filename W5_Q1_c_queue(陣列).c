
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 100

/*
    int enqueue(int d)
    {
        if (sola)
        {
            if (head == -1)
                head ++;
            data[index] = d;
            index ++;
            if (index == SIZE)
                index -= SIZE;
            if (index == head) // 全滿
                sola = false;
            return 1;
        }
        return -1;
    }
    int *dequeue()
    {
        sola = true;
        if (head >= 0)
        {
            int *de = new int (data[head]);
            head ++;
            if (head == SIZE)
                head -= SIZE;
            if (head == index) // 全空
            {
                head = -1;
                index = 0;
            }
            return de;
        }
        return NULL;
    }
*/
/*
int main()
{
    int data, *temp;
    char command[50];
    Queue *queue = new Queue();
    while(1)
    {
        cin>>command;
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "enqueue") == 0)
        {
            cout<<"Please input a integer data:";
            cin>>data;
            if(queue->enqueue(data) == 1)
            {
                cout<<"Successfully enqueue data "<<data<<" into queue."<<endl;
            }
            else
            {
                cout<<"Failed to enqueue data into queue."<<endl;
            }
        }
        else if(strcmp(command, "dequeue") == 0)
        {
            temp = queue->dequeue();
            if(temp == NULL)
            {
                cout<<"Failed to dequeue a data from queue.\n";
            }
            else
            {
                cout<<"Dequeue data "<<*temp<<" from queue."<<endl;
            }
        }
    }
}
*/



struct Queue
{
    int data[SIZE];
    int head, index;
    bool sola;
};

int enqueue(struct Queue *queue, int data)
{
    if (queue->sola)
    {
        if (queue->head == -1)
            queue->head ++;
        queue->data[queue->index] = data;
        queue->index ++;
        if (queue->index == SIZE)
            queue->index -= SIZE;
        if (queue->index == queue->head)
            queue->sola = false;
        return 1;
    }
    return -1;
}

int *dequeue(struct Queue *queue)
{
    queue->sola = true;
    if (queue->head >= 0)
    {
        int *de = malloc (sizeof (int));
        (*de) = queue->data[queue->head];
        queue->head ++;
        if (queue->head == SIZE)
            queue->head -= SIZE;
        if (queue->head == queue->index)
        {
            queue->head = -1;
            queue->index = 0;
        }
        return de;
    }
    return NULL;
}

int main()
{
    int data, *temp;
    char command[50]={};
    struct Queue queue;
    queue.head = -1;
    queue.index = 0;
    queue.sola = true;

    while(1)
    {
        scanf("%s", command);
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "enqueue") == 0)
        {
            printf("Please input a integer data:");
            scanf("%d", &data);
            if(enqueue(&queue, data) == 1)
            {
                printf("Successfully enqueue data %d into queue.\n");
            }
            else
            {
                printf("Failed to enqueue data into queue.\n");
            }
        }
        else if(strcmp(command, "dequeue") == 0)
        {
            temp = dequeue(&queue);
            if(temp == NULL)
            {
                printf("Failed to dequeue a data from queue.\n");
            }
            else
            {
                printf("Dequeue data %d from queue.\n", *temp);
            }
        }
    }
}
