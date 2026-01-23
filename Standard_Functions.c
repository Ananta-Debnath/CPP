#include <stdio.h>
#include <time.h>



int selection_sort(int* a, int l)
{
    int idx, tmp;
    for (int i = 0; i < l-1; i++)
    {
        idx = i;
        for (int j = i+1; j < l; j++)
        {
            if (a[j] < a[idx])
            {
                idx = j;
            }
        }
        tmp = a[i];
        a[i] = a[idx];
        a[idx] = tmp;
    }
    return 0;
}

int merge(int* left, int a, int* right, int b)
{
    int i=0, j=0;
    int l = a+b;
    int sorted[l];
    while(i<a && j<b)
    {
        if(left[i]<right[j])
        {
            sorted[i+j] = left[i];
            i++;
        }
        else
        {
            sorted[i+j] = right[j];
            j++;
        }
    }

    while(i<a)
    {
        sorted[i+j] = left[i];
        i++;
    }
    while(j<b)
    {
        sorted[i+j] = right[j];
        j++;
    }

    while(l--)
    {
        left[l] = sorted[l];
    }
    return 0;
}

int merge_sort(int* list, int l)
{
    if(l == 1)
    {
        return 1;
    }
    int a = l/2;
    int b = a + (l%2);
    merge_sort(list, a);
    merge_sort(&list[a], b);
    merge(list, a, &list[a], b);
    return 0;
}

int binary_search(int* a, int l, int t)
{
    int first=0, last=l-1, mid, idx = -1;
    while(first<=last)
    {
        mid = (first + last)/2;
        if(a[mid]<t) first = mid + 1;
        else if(a[mid]>t) last = mid -1;
        else
        {
            idx = mid;
            break;
        }
    }
    return idx;
}

int find_gcd(int a, int b)
{
    if(a < b)
    {
        int tmp = b;
        b = a;
        a = tmp;
    }

    int remainder = a % b;
    while (remainder != 0)
    {
        a = b;
        b = remainder;
        remainder = a % b;
    }

    return b;
}

int find_lcm(int a, int b)
{
    int x = a, y = b;
    if(a < b)
    {
        int tmp = b;
        b = a;
        a = tmp;
    }

    int remainder = a % b;
    while (remainder != 0)
    {
        a = b;
        b = remainder;
        remainder = a % b;
    }

    int lcm = (x*y) / b;
    return lcm;
}

int node_list_create()
{
    struct ListNode
    {
        int val;
        struct ListNode *next;
    };



    int n;
    printf("Number of Elements: ");
    scanf("%d", &n);
    struct ListNode* tmp = (struct ListNode*)malloc(sizeof(struct ListNode));;
    struct ListNode* ptr = tmp;
    
    for (int i = 0; i < n; i++)
    {
        ptr->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        ptr = ptr->next;
        ptr->next = NULL;
        printf("Number %d: ", i + 1);
        scanf("%d", &(ptr->val));
    }
    struct ListNode* head = tmp->next;
    free(tmp);

    int* dist = nodesBetweenCriticalPoints(head, &n);
    
    printf("%d %d\n", dist[0], dist[1]);

    return 0;
}

int time_count()
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", cpu_time_used);
    return 0;
}

