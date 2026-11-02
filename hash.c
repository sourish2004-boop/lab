
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
