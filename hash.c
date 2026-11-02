
#include <stdio.h>

#define SIZE 10

int hashTable[SIZE];
int occupied[SIZE];

/* Calculate a valid hash index */
int hashFunction(int key)
{
    return ((key % SIZE) + SIZE) % SIZE;
}

/* Insert a key into the hash table */
void insert(int key)
{
    int index = hashFunction(key);
    int start = index;

    /* Search for an empty slot */
    while (occupied[index] == 1)
    {
        index = (index + 1) % SIZE;

        /* Stop if the table is full */
        if (index == start)
        {
            printf("Hash table is full. Cannot insert %d.\n", key);
            return;
        }
    }

    hashTable[index] = key;
    occupied[index] = 1;

    printf("Inserted %d at index %d\n", key, index);
}

/* Display the hash table */
void display(void)
{
    int i;

    printf("\nHash Table:\n");
    printf("--------------------\n");

    for (i = 0; i < SIZE; i++)
    {
        if (occupied[i] == 1)
        {
            printf("Index %d : %d\n", i, hashTable[i]);
        }
        else
        {
            printf("Index %d : Empty\n", i);
        }
    }

    printf("--------------------\n");
}

int main(void)
{
    int n, key, i;

    /* Mark every slot as empty */
    for (i = 0; i < SIZE; i++)
    {
        occupied[i] = 0;
    }

    printf("Enter the number of keys (0-%d): ", SIZE);

    if (scanf("%d", &n) != 1 || n < 0 || n > SIZE)
    {
        printf("Invalid number of keys.\n");
        return 1;
    }

    printf("Enter %d keys:\n", n);

    for (i = 0; i < n; i++)
    {
        if (scanf("%d", &key) != 1)
        {
            printf("Invalid input.\n");
            return 1;
        }

        insert(key);
    }

    display();

    return 0;
}










heap


#include <stdio.h>

/* Function to maintain the max heap property */
void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int temp;

    /* Check whether the left child is larger */
    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    /* Check whether the right child is larger */
    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    /* If the largest element is not the root */
    if (largest != i)
    {
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        /* Restore the heap property */
        heapify(arr, n, largest);
    }
}

/* Function to perform heap sort */
void heapSort(int arr[], int n)
{
    int i, temp;

    /* Step 1: Build a max heap */
    for (i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    /* Step 2: Move the largest element to the end */
    for (i = n - 1; i > 0; i--)
    {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        /* Restore the heap for the remaining elements */
        heapify(arr, i, 0);
    }
}

int main(void)
{
    int arr[100];
    int n, i;

    printf("Enter the number of elements (1-100): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 100)
    {
        printf("Invalid number of elements.\n");
        return 1;
    }

    printf("Enter %d elements: ", n);

    for (i = 0; i < n; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Invalid input.\n");
            return 1;
        }
    }

    heapSort(arr, n);

    printf("Sorted array in ascending order: ");

    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}


bfs
#include <stdio.h>
#include <stdlib.h>

/* Breadth First Search on an undirected graph (adjacency matrix) */

#define MAX 20

void bfs(int adj[MAX][MAX], int n, int start) {
    int visited[MAX] = {0};
    int queue[MAX], front = 0, rear = 0, i, u;

    visited[start] = 1;
    queue[rear++] = start;
    printf("BFS order: ");
    while (front < rear) {
        u = queue[front++];
        printf("%d ", u);
        for (i = 0; i < n; i++) {
            if (adj[u][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
}

int main() {
    int adj[MAX][MAX] = {0};
    int n, e, u, v, start, i;

    printf("Number of vertices (0 to %d): ", MAX - 1);
    scanf("%d", &n);
    printf("Number of edges: ");
    scanf("%d", &e);
    printf("Enter each edge as 'u v' (undirected):\n");
    for (i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }
    printf("Start vertex: ");
    scanf("%d", &start);
    bfs(adj, n, start);
    return 0;
}

bst
#include <stdio.h>
#include <stdlib.h>

/* Binary Search Tree: Create, Insert, Traversals, Delete, Search */

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node *newNode(int val) {
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    n->data = val;
    n->left = n->right = NULL;
    return n;
}

/* b) Insertion (duplicates are ignored) */
struct Node *insert(struct Node *root, int val) {
    if (root == NULL) return newNode(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);
    else
        printf("%d already exists, skipped.\n", val);
    return root;
}

/* a) Create: build a BST from n values typed by the user */
struct Node *create() {
    struct Node *root = NULL;
    int n, val, i;
    printf("How many nodes? ");
    scanf("%d", &n);
    printf("Enter %d values: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &val);
        root = insert(root, val);
    }
    return root;
}

/* c) Traversals */
void inorder(struct Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(struct Node *root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Node *root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

/* smallest node in a subtree (used by deletion) */
struct Node *minNode(struct Node *root) {
    while (root->left != NULL) root = root->left;
    return root;
}

/* d) Deletion */
struct Node *deleteNode(struct Node *root, int key) {
    if (root == NULL) {
        printf("%d not found.\n", key);
        return NULL;
    }
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        /* Case 1 & 2: zero or one child */
        if (root->left == NULL) {
            struct Node *tmp = root->right;
            free(root);
            return tmp;
        }
        if (root->right == NULL) {
            struct Node *tmp = root->left;
            free(root);
            return tmp;
        }
        /* Case 3: two children -> use inorder successor */
        struct Node *succ = minNode(root->right);
        root->data = succ->data;
        root->right = deleteNode(root->right, succ->data);
    }
    return root;
}

/* e) Searching */
struct Node *search(struct Node *root, int key) {
    if (root == NULL || root->data == key) return root;
    if (key < root->data) return search(root->left, key);
    return search(root->right, key);
}

int main() {
    struct Node *root = NULL;
    int ch, val;
    do {
        printf("\n--- BST MENU ---\n");
        printf("1. Create\n2. Insert\n3. Inorder\n4. Preorder\n5. Postorder\n");
        printf("6. Delete\n7. Search\n0. Back\n");
        printf("Choice: ");
        scanf("%d", &ch);
        switch (ch) {
        case 1: root = create(); break;
        case 2:
            printf("Value: "); scanf("%d", &val);
            root = insert(root, val);
            break;
        case 3: printf("Inorder: ");   inorder(root);   printf("\n"); break;
        case 4: printf("Preorder: ");  preorder(root);  printf("\n"); break;
        case 5: printf("Postorder: "); postorder(root); printf("\n"); break;
        case 6:
            printf("Value to delete: "); scanf("%d", &val);
            root = deleteNode(root, val);
            break;
        case 7:
            printf("Value to search: "); scanf("%d", &val);
            if (search(root, val)) printf("%d FOUND.\n", val);
            else printf("%d NOT found.\n", val);
            break;
        }
    } while (ch != 0);
    return 0;
}
