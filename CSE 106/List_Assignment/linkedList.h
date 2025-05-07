#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int element;
    struct node* next;
    struct node* prev;
} node;

typedef struct 
{
    // declare head, tail, cur and other variables you need
    node* head;
    node* tail;
    node* cur;
} linkedList;


// Prototypes
node* createNode(int value);
node* findItem(int n, linkedList* list);
node* getAt(int idx, linkedList* list);
void insertNode(int value, node* curr);
void deleteNode(node* curr);


void init(linkedList* list)
{
    // implement initialization
    list->head = createNode(0); // Dummy node
    list->tail = list->cur = list->head;
}

void free_list(linkedList* list)
{
    // implement destruction of list
    node* toFree;
    if (list->head != NULL)
    {
        toFree = list->head;
        list->head = list->head->next;
        free(toFree);
    }
    list->tail = list->cur = list->head = NULL;
}

void print(linkedList* list)
{
    // implement list printing
    node* curr = list->head->next;
    printf("[");
    if (curr == NULL) printf(".");

    else
    {
        while (curr != NULL)
        {
            printf(" %d", curr->element);
            if (curr == list->cur) printf("|");
            curr = curr->next;
        }
        printf(" ");
    }
    printf("]\n");
}

void insert(int item, linkedList* list)
{
    // implement insert function
    insertNode(item, list->cur);
    if (list->tail == list->cur) list->tail = list->tail->next;
    list->cur = list->cur->next;

    print(list);
}

int delete_cur(linkedList* list)
{
    // implement deletion of current index function
    if (list->cur->prev != NULL)
    {
        node* toDel = list->cur;
        int value = toDel->element;
        if (list->cur->next != NULL) list->cur = list->cur->next;
        
        else list->tail = list->cur = list->cur->prev;

        deleteNode(toDel);
        print(list);
        return value;
    }

    else return -1;
}

void append(int item, linkedList* list)
{
    // implement append function
    insertNode(item, list->tail);
    list->tail = list->tail->next;
    if (list->cur->prev == NULL) list->cur = list->tail;

    print(list);
}

int size(linkedList* list)
{
    // implement size function
    int l = 0;
    node* curr = list->head;
    while (curr->next != NULL)
    {
        curr = curr->next;
        l++;
    }
    return l;
}

void prev(int n, linkedList* list)
{
    // implement prev function
    for (int i = 0; i < n && list->cur->prev->prev != NULL; i++) list->cur = list->cur->prev;

    print(list);
}

void next(int n, linkedList* list)
{
    // implement next function
    for (int i = 0; i < n && list->cur->next != NULL; i++) list->cur = list->cur->next;

    print(list);
}

int is_present(int n, linkedList* list)
{
    // implement presence checking function
    if (findItem(n, list) != NULL) return 1;
    else return 0;
}

void clear(linkedList* list)
{
    // implement list clearing function
    free_list(list);
    init(list);

    print(list);
}

void delete_item(int item, linkedList* list)
{
    // implement item deletion function
    node* toDel = findItem(item, list);
    if (toDel == NULL) printf("%d not found\n", item);

    else
    {
        if (list->cur == toDel) list->cur = list->cur->next;
        deleteNode(toDel);
        print(list);
    }
}

void swap_ind(int ind1, int ind2, linkedList* list)
{
    // implement swap function
    node* node1 = getAt(ind1, list);
    node* node2 = getAt(ind2, list);

    if (node1 != NULL && node2 != NULL)
    {
        int tmp = node1->element;
        node1->element = node2->element;
        node2->element = tmp;
    }

    print(list);
}

// you can define helper functions you need
node* createNode(int value)
{
    node* newNode = (node*) malloc(sizeof(node));
    if (newNode == NULL) printf("Memory allocation fault!\n");

    else
    {
        newNode->element = value;
        newNode->next = newNode->prev = NULL;
    }
    return newNode;
}

node* findItem(int n, linkedList* list)
{
    node* head = list->head->next;
    while (head != NULL)
    {
        if (head->element == n) return head;
        head = head->next;
    }
    return NULL;
}

node* getAt(int idx, linkedList* list)
{
    node* head = list->head->next;
    for (int i = 0; head != NULL; i++, head = head->next)
    {
        if (i == idx) return head;
    }
    return NULL;
}

void insertNode(int value, node* curr)
{
    // Set newNode
    node* newNode = createNode(value);
    if (newNode == NULL) return;
    newNode->prev = curr;
    newNode->next = curr->next;

    // Set address to prev and next node
    if (curr->next != NULL) curr->next->prev = newNode;
    curr->next = newNode;
}

void deleteNode(node* curr)
{
    curr->prev->next = curr->next;
    if (curr->next != NULL) curr->next->prev = curr->prev;
    free(curr);
}