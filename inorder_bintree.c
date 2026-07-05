/*
Program: Binary Tree Inorder Traversal from File Input
Author: Jisnu Praharaj
Date: July 2026

Description:
Reads integers from a file where the first value indicates
how many numbers follow. Inserts values into a binary search tree
and prints them using inorder traversal (sorted output).
 */

#include <stdio.h>
#include <stdlib.h>

// Tree node structure
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Function prototypes
Node* insert(Node* root, int value);
void inorder(Node* root);
Node* createNode(int value);
void freeTree(Node* root);

int main() {
    // Create sample input file
    FILE *testFile = fopen("input.txt", "w");

    if (testFile == NULL) {
        printf("Error: could not create test file.\n");
        return 1;
    }

    // Sample data: 4 values → 9, 11, 4, 5
    fprintf(testFile, "4\n9 11 4 5\n");
    fclose(testFile);

    // Open file for reading
    FILE *fp = fopen("input.txt", "r");

    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return 1;
    }

    int n;

    // Read number of values
    fscanf(fp, "%d", &n);

    int *data = malloc(n * sizeof(int));

    if (data == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return 1;
    }

    // Read integers into array
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d", &data[i]);
    }

    fclose(fp);

    // Build binary search tree
    Node *root = NULL;

    for (int i = 0; i < n; i++) {
        root = insert(root, data[i]);
    }

    // Inorder traversal output
    printf("Inorder traversal (sorted): ");
    inorder(root);
    printf("\n");

    free(data);
    freeTree(root);

    return 0;
}

// Create a new tree node
Node* createNode(int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert into BST
Node* insert(Node* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

// Inorder traversal: left → root → right
void inorder(Node* root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// Free memory of tree
void freeTree(Node* root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}