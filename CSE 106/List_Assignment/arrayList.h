#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int *array;
    // declare variables you need
} arrayList;

void init(arrayList* list)
{
    // implement initialization
}

void free_list(arrayList* list)
{
    // implement destruction of list
}

void increase_capacity(arrayList* list)
{
    // implement capacity increase
}

void decrease_capacity(arrayList* list)
{
    // implement capacity decrease
}

void print(arrayList* list)
{
    // implement list printing
}

void insert(int item, arrayList* list)
{
    // implement insert function
}

int delete_cur(arrayList* list)
{
    // implement deletion of current index function
}

void append(int item, arrayList* list)
{
    // implement append function
}

int size(arrayList* list)
{
    // implement size function
}

void prev(int n, arrayList* list)
{
    // implement prev function
}

void next(int n, arrayList* list)
{
    // implement next function
}

int is_present(int n, arrayList* list)
{
    // implement presence checking function
}

void clear(arrayList* list)
{
    // implement list clearing function
}

void delete_item(int item, arrayList* list)
{
    // implement item deletion function
}

void swap_ind(int ind1, int ind2, arrayList* list)
{
    // implement swap function
}

// you can define helper functions you need