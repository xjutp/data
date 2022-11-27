
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

struct Stack
{
    int data[SIZE];
    int top;
};

int push(struct Stack *stack, int data)
{
    if (stack->top < SIZE)
    {
        stack->top ++;
        stack->data[stack->top] = data;
        return 1;
    }
    return -1;
}

int *pop(struct Stack *stack)
{
    if (stack->top >= 0)
    {
        int *de = malloc (sizeof (int));
        (*de) = stack->data[stack->top];
        stack->top --;
        return de;
    }
    return NULL;
}

int main()
{
    int data, *temp;
    char command[50];
    struct Stack stack;
    stack.top = -1;
    while(1)
    {
        scanf("%s", command);
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "push") == 0)
        {
            printf("Please input a integer data:");
            scanf("%d", &data);
            if(push(&stack, data) == 1)
            {
                printf("Successfully push data into stack.\n");
            }
            else
            {
                printf("Failed to push data into stack.\n");
            }
        }
        else if(strcmp(command, "pop") == 0)
        {
            temp = pop(&stack);
            if(temp == NULL)
            {
                printf("Failed to pop a data from stack.\n");
            }
            else
            {
                printf("Pop data %d from stack.\n", *temp);
            }
        }
    }
}
