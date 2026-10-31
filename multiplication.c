#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1,
                   Dlist **head2, Dlist **tail2,
                   Dlist **headR)
{
    if (*head1 == NULL || *head2 == NULL)
        return FAILURE;

    int a[10000], b[10000];
    int result[20000] = {0};

    int n = 0, m = 0;

    Dlist *temp = *tail1;

    while (temp != NULL && n < 10000)
    {
        a[n++] = temp->data;
        temp = temp->prev;
    }

    temp = *tail2;

    while (temp != NULL && m < 10000)
    {
        b[m++] = temp->data;
        temp = temp->prev;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            result[i + j] += a[i] * b[j];
        }
    }

    for (int i = 0; i < n + m; i++)
    {
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }

    int size = n + m;

    while (size > 1 && result[size - 1] == 0)
        size--;

    Dlist *resultTail = NULL;

    /* Insert digits in the correct order */
    for (int i = 0; i < size; i++)
    {
        if (apc_push_front(headR, &resultTail, result[i]) == FAILURE)
            return FAILURE;
    }

    return SUCCESS;
}