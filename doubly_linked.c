/*
Project title: Doubly linked list to remove duplicate data

This program:
1. Creates a doubly linked list containing 200 random integers.
2. Each integer is in the range 0–49.
3. Removes duplicate values by comparing each node with the remaining nodes in the list.

Author: Jisnu Praharaj
Date: June 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} Node;


// Create a new node with the given value
Node *createNode(int value)
{
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}


// Insert a node at the end of the list
void append(Node **head, Node **tail, int value)
{
    Node *newNode = createNode(value);

    if (*head == NULL)
    {
        *head = newNode;
        *tail = newNode;
    }
    else
    {
        newNode->prev = *tail;
        (*tail)->next = newNode;
        *tail = newNode;
    }
}


// Display the list
void display(Node *head)
{
    Node *current = head;

    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }

    printf("\n");
}


// Remove duplicate values
void removeDuplicates(Node **head, Node **tail)
{
    Node *current;
    Node *runner;
    Node *temp;

    current = *head;

    while (current != NULL)
    {
        runner = current->next;

        while (runner != NULL)
        {
            temp = runner->next;

            if (runner->data == current->data)
            {
                if (runner->prev != NULL)
                    runner->prev->next = runner->next;

                if (runner->next != NULL)
                    runner->next->prev = runner->prev;

                if (runner == *tail)
                    *tail = runner->prev;

                free(runner);
            }

            runner = temp;
        }

        current = current->next;
    }
}


// Free all memory
void freeList(Node *head)
{
    Node *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}


// Main program
int main(void)
{
    Node *head;
    Node *tail;
    int i;

    head = NULL;
    tail = NULL;

    srand((unsigned)time(NULL));

    // Generate 200 random integers from 0 to 49
    for (i = 0; i < 200; i++)
    {
        append(&head, &tail, rand() % 50);
    }

    printf("Original List\n");
    display(head);

    removeDuplicates(&head, &tail);

    printf("\nList After Removing Duplicates\n");
    display(head);

    freeList(head);

    return 0;
}