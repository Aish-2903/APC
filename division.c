#include "apc.h"

int division(Dlist **head1, Dlist **tail1,
             Dlist **head2, Dlist **tail2,
             Dlist **headR)
{
    (void)tail1;
    (void)tail2;

    if (*head1 == NULL || *head2 == NULL)
        return FAILURE;

    Dlist *temp = *head2;
    int divisor = 0;

    while (temp != NULL)
    {
        divisor = divisor * 10 + temp->data;
        temp = temp->next;
    }

    if (divisor == 0)
        return FAILURE;

    temp = *head1;
    int dividend = 0;

    while (temp != NULL)
    {
        dividend = dividend * 10 + temp->data;
        temp = temp->next;
    }

    int quotient = dividend / divisor;

    Dlist *resultTail = NULL;

    if (quotient == 0)
        return apc_push_front(headR, &resultTail, 0);

    int digits[10000];
    int count = 0;

    while (quotient > 0)
    {
        digits[count++] = quotient % 10;
        quotient /= 10;
    }

    while (count > 0)
    {
        if (apc_push_back(headR, &resultTail, digits[--count]) == FAILURE)
            return FAILURE;
    }

    return SUCCESS;
}