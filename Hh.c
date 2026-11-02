/*
 * Hashing with Separate Chaining (Linked List)
 * Table size : 7  (indices 0 to 6)
 * Hash func  : index = key % 7
 * Operations : insert, search, delete, display
 */
#include <stdio.h>
#include <stdlib.h>

#define SIZE 7

/* Node of a chain */
struct Node {
    int key;
    struct Node *next;
};

/* Hash table: array of head pointers, one per index */
struct Node *table[SIZE];

/* Hash function */
int hash(int key) {
    return key % SIZE;
}

/* Insert at the end of the chain (ignores duplicates) */
void insert(int key) {
    int idx = hash(key);
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    struct Node *temp;

    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->key = key;
    newNode->next = NULL;

    if (table[idx] == NULL) {            /* empty chain */
        table[idx] = newNode;
        printf("Inserted %d at index %d\n", key, idx);
        return;
    }

    temp = table[idx];
    while (1) {
        if (temp->key == key) {          /* duplicate */
            printf("Key %d already exists at index %d\n", key, idx);
            free(newNode);
            return;
        }
        if (temp->next == NULL)
            break;
        temp = temp->next;
    }
    temp->next = newNode;                /* append at tail (collision) */
    printf("Inserted %d at index %d (collision, chained)\n", key, idx);
}

/* Search for a key */
void search(int key) {
    int idx = hash(key);
    struct Node *temp = table[idx];
    int pos = 1;

    while (temp != NULL) {
        if (temp->key == key) {
            printf("Key %d FOUND at index %d, position %d in chain\n", key, idx, pos);
            return;
        }
        temp = temp->next;
        pos++;
    }
    printf("Key %d NOT found\n", key);
}

/* Delete a key */
void delete(int key) {
    int idx = hash(key);
    struct Node *temp = table[idx];
    struct Node *prev = NULL;

    while (temp != NULL && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Key %d not found, cannot delete\n", key);
        return;
    }
    if (prev == NULL)
        table[idx] = temp->next;         /* deleting head */
    else
        prev->next = temp->next;         /* deleting middle/tail */

    free(temp);
    printf("Deleted %d from index %d\n", key, idx);
}

/* Display the whole table */
void display(void) {
    int i;
    struct Node *temp;

    printf("\n--- Hash Table ---\n");
    for (i = 0; i < SIZE; i++) {
        printf("[%d] -> ", i);
        temp = table[i];
        while (temp != NULL) {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("NULL\n");
    }
    printf("------------------\n\n");
}

/* Free all memory */
void freeTable(void) {
    int i;
    struct Node *temp, *next;

    for (i = 0; i < SIZE; i++) {
        temp = table[i];
        while (temp != NULL) {
            next = temp->next;
            free(temp);
            temp = next;
        }
        table[i] = NULL;
    }
}

int main(void) {
    int choice, key, i;

    for (i = 0; i < SIZE; i++)
        table[i] = NULL;

    while (1) {
        printf("1.Insert  2.Search  3.Delete  4.Display  5.Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
            break;

        switch (choice) {
            case 1:
                printf("Enter key: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                printf("Enter key: ");
                scanf("%d", &key);
                search(key);
                break;
            case 3:
                printf("Enter key: ");
                scanf("%d", &key);
                delete(key);
                break;
            case 4:
                display();
                break;
            case 5:
                freeTable();
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
    freeTable();
    return 0;
}
