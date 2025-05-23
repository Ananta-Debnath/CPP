#include <stdio.h>
#include <stdlib.h>


typedef struct 
{
    int *array;
    int cur;
    int size;
    int length;
    // declare variables you need
} arrayList;


// Prototypes
void resize(arrayList* list);
void insert_idx(int idx, int value, arrayList* list);
void delete_idx(int idx, arrayList* list);


void init(arrayList* list)
{
    // implement initialization
    list->array = (int*)malloc(2 * sizeof(int));
    if (list->array == NULL)
    {
        printf("Memory allocation fault!\n");
        return;
    }
    list->cur = -1;
    list->size = 2;
    list->length = 0;
}

void free_list(arrayList* list)
{
    // implement destruction of list
    if (list->array != NULL)
    {
        free(list->array);
        list->array = NULL;
    }
    
    list->cur = -1;
    list->size = 2;
    list->length = 0;
}

void increase_capacity(arrayList* list)
{
    // implement capacity increase
    int* newArray = (int*)malloc(sizeof(int) * list->size * 2);
    if (newArray == NULL)
    {
        printf("Memory allocation fault!\n");
        return;
    }

    printf("Capacity increased from %d to ", list->size);
    list->size *= 2;
    printf("%d\n", list->size);

    for (int i = 0; i < list->length; i++)
    {
        newArray[i] = list->array[i];
    }
    free(list->array);
    list->array = newArray;
}

void decrease_capacity(arrayList* list)
{
    // implement capacity decrease
    if (list->size > 2)
    {
        int* newArray = (int*)malloc(sizeof(int) * list->size / 2);
        if (newArray == NULL)
        {
            printf("Memory allocation fault!\n");
            return;
        }

        printf("Capacity decreased from %d to ", list->size);
        list->size /= 2;
        printf("%d\n", list->size);

        for (int i = 0; i < list->length; i++)
        {
            newArray[i] = list->array[i];
        }
        free(list->array);
        list->array = newArray;
    }
}

void print(arrayList* list)
{
    // implement list printing
    if (list->length == 0) printf("[.]\n");

    else
    {
        printf("[ ");
        for (int i = 0; i <= list->cur; i++) printf("%d ", list->array[i]);
        printf("\b| ");
        for(int i = list->cur + 1; i < list->length; i++) printf("%d ", list->array[i]);
        printf("]\n");
    }
}

void insert(int item, arrayList* list)
{
    // implement insert function
    list->cur++;
    insert_idx(list->cur, item, list);
    print(list);
}

int delete_cur(arrayList* list)
{
    // implement deletion of current index function
    if (list->length > 0)
    {
        int value = list->array[list->cur];
        delete_idx(list->cur, list);
        if (list->cur >= list->length) list->cur = list->length - 1;
        print(list);
        return value;
    }

    else return -1;
}

void append(int item, arrayList* list)
{
    // implement append function
    insert_idx(list->length, item, list);
    if (list->cur == -1) list->cur = 0;
    print(list);
}

int size(arrayList* list)
{
    // implement size function
    return list->length;
}

void prev(int n, arrayList* list)
{
    // implement prev function
    list->cur -= n;
    if (list->length == 0) list->cur = -1;
    else if (list->cur < 0) list->cur = 0;
    print(list);
}

void next(int n, arrayList* list)
{
    // implement next function
    list->cur += n;
    if (list->cur >= list->length) list->cur = list->length - 1;
    print(list);
}

int is_present(int n, arrayList* list)
{
    // implement presence checking function
    int flag = 0;
    for (int i = 0; i < list->length; i++)
    {
        if (list->array[i] == n)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

void clear(arrayList* list)
{
    // implement list clearing function
    free_list(list);
    init(list);
    print(list);
}

void delete_item(int item, arrayList* list)
{
    // implement item deletion function
    int found = 0;
    for (int i = 0; i < list->length; i++)
    {
        if (list->array[i] == item)
        {
            found = 1;
            if (i < list->cur) list->cur--;
            delete_idx(i, list);
            if (list->cur >= list->length) list->cur = list->length-1;
            print(list);
            break;
        }
    }

    if (found == 0) printf("%d not found\n", item);
}

void swap_ind(int ind1, int ind2, arrayList* list)
{
    // implement swap function
    int l = list->length;
    if (ind1 < l && ind1 >= 0 && ind2 < l && ind2 >= 0)
    {
        int tmp = list->array[ind1];
        list->array[ind1] = list->array[ind2];
        list->array[ind2] = tmp;
        print(list);
    }

    else printf("Invalid index\n");
}


// you can define helper functions you need
void resize(arrayList* list)
{
    if (list->length * 2 > list->size) increase_capacity(list);

    else if (list->length * 4 < list->size) decrease_capacity(list);
}

void insert_idx(int idx, int value, arrayList* list)
{
    list->length++;
    resize(list);
    for (int i = list->length; i > idx; i--) list->array[i] = list->array[i-1];
    list->array[idx] = value;
}

void delete_idx(int idx, arrayList* list)
{
    if (list->length > 0)
    {
        list->length--;
        for (int i = idx; i < list->length; i++)
        {
            list->array[i] = list->array[i+1];
        }
        resize(list);
    }
}