#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

struct Node *append(struct Node *head, int value)
{
    Node *cur = head;
    if (cur == NULL)
    {
        head = (Node *)malloc(sizeof(Node));
        cur = head;
    }
    else
    {
        while (cur->next != NULL)
            cur = cur->next;

        cur->next = (Node *)malloc(sizeof(Node));
        cur = cur->next;
    }

    cur->data = value;
    cur->next = NULL;
    return head;
}

struct Node *insert_node(struct Node *head, struct Node *position, int value)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = value;

    if (head == NULL)
    {
        new->next == NULL;
        head = new;
    }
    else if (position == NULL)
    {
        new->next = head;
        head = new;
    }
    else
    {
        new->next = position->next;
        position->next = new;
    }

    return head;
}

struct Node *insert_index(struct Node *head, int position, int value)
{

    if (position == 0)
    {
        Node *new = (Node *)malloc(sizeof(Node));
        new->data = value;
        new->next = head;
        head = new;
    }
    else
    {
        Node *cur = head;
        for (int i = 1; i < position; i++)
            cur = cur->next;

        return insert_node(head, cur, value);
    }
    return head;
}

void print(struct Node *head)
{
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
}

struct Node *merge_sorted_lists(struct Node *head1, struct Node *head2)
{
    Node head;
    Node *tmp = &head;
    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data < head2->data)
        {
            tmp->next = head1;
            head1 = head1->next;
        }
        else
        {
            tmp->next = head2;
            head2 = head2->next;
        }
        tmp = tmp->next;
    }

    if (head1 == NULL)
    {
        tmp->next = head2;
    }

    else
        tmp->next = head1;

    return head.next;
}

int main()
{
    Node *head1 = NULL;

    head1 = insert_index(head1, 0, 6);
    head1 = append(head1, 10);
    head1 = append(head1, 16);
    head1 = append(head1, 19);
    head1 = insert_index(head1, 0, 4);

    Node *head2 = NULL;

    head2 = append(head2, 11);
    head2 = append(head2, 14);
    head2 = append(head2, 21);

    Node *head = merge_sorted_lists(head1, head2);

    print(head);
}