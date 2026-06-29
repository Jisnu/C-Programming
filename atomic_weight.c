/*
Program: Periodic Table Linked List

Description:
This program uses a structure to store an element's name,
atomic symbol, and atomic weight. The user enters the first
ten elements of the periodic table, which are stored in a
singly linked list. The list is then displayed in a formatted
table, and all allocated memory is freed before the program
ends.

Author: Jisnu Praharaj
Date: June 2026
*/

#include <stdio.h>
#include <stdlib.h>

// Struct to store information about an atomic element
struct Element {
    char name[30];         // Name of the element (e.g., Hydrogen)
    char symbol[5];        // Chemical symbol (e.g., H)
    float atomicWeight;    // Atomic weight of the element
};

// Struct representing a node in the linked list
struct Node {
    struct Element data;   // Stores the element information
    struct Node *next;     // Pointer to the next node
};

/*
Function: createNode()

Allocates memory for a new node, copies the element data into
the node, initializes the next pointer to NULL, and returns
the address of the new node.
*/
struct Node* createNode(char name[], char symbol[], float weight) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    int i = 0;

    // Copy the element name
    while (name[i] != '\0') {
        newNode->data.name[i] = name[i];
        i++;
    }
    newNode->data.name[i] = '\0';

    // Copy the element symbol
    i = 0;
    while (symbol[i] != '\0') {
        newNode->data.symbol[i] = symbol[i];
        i++;
    }
    newNode->data.symbol[i] = '\0';

    // Store the atomic weight
    newNode->data.atomicWeight = weight;

    // New node points to nothing initially
    newNode->next = NULL;

    return newNode;
}

/*
Function: appendNode()

Adds a newly created node to the end of the linked list.
If the list is empty, the new node becomes the head of the list.
Otherwise, the function traverses the list until it reaches the
last node and attaches the new node.
*/
void appendNode(struct Node **head, char name[], char symbol[], float weight) {

    // Create a node containing the element data
    struct Node *newNode = createNode(name, symbol, weight);

    // If the list is empty, the new node becomes the head
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // Traverse to the last node
    struct Node *temp = *head;
    while (temp->next != NULL)
        temp = temp->next;

    // Link the last node to the new node
    temp->next = newNode;
}

/*
Function: displayList()

Traverses the linked list from beginning to end and prints
each element's information in a formatted table.
*/
void displayList(struct Node *head) {

    printf("\n-----------------------------------------------------\n");
    printf("%-5s %-15s %-10s %-15s\n",
           "No.", "Element", "Symbol", "Atomic Weight");
    printf("-----------------------------------------------------\n");

    int i = 1;

    // Continue until the end of the linked list
    while (head != NULL) {

        printf("%-5d %-15s %-10s %-15.3f\n",
               i,
               head->data.name,
               head->data.symbol,
               head->data.atomicWeight);

        head = head->next;
        i++;
    }

    printf("-----------------------------------------------------\n");
}


int main() {

    // Head pointer for the linked list
    struct Node *head = NULL;

    // Variables used for user input
    char name[30], symbol[5];
    float weight;

    printf("Enter details for the first 10 elements:\n\n");

    // Read information for ten elements
    for (int i = 0; i < 10; i++) {

        printf("Element %d\n", i + 1);

        printf("Name: ");
        scanf("%s", name);

        printf("Symbol: ");
        scanf("%s", symbol);

        printf("Atomic Weight: ");
        scanf("%f", &weight);

        // Add the element to the linked list
        appendNode(&head, name, symbol, weight);

        printf("\n");
    }

    // Display the completed linked list
    displayList(head);

    // Free all allocated memory to avoid memory leaks
    struct Node *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}