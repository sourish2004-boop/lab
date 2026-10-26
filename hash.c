
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
