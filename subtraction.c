#include "apc.h"

int subtraction(Dlist **head1, Dlist **tail1,
                Dlist **head2, Dlist **tail2,
                Dlist **headR)
{
    (void)tail1;
    (void)tail2;

    Dlist *resultTail = NULL;

    int comparison = apc_compare(*head1, *head2);

    if (comparison == 0)
    {
        return apc_push_front(headR, &resultTail, 0);
    }

    if (comparison > 0)
    {
        if (apc_sub_abs(*head1, *head2, headR, &resultTail) == FAILURE)
            return FAILURE;
    }
    else
    {
        if (apc_sub_abs(*head2, *head1, headR, &resultTail) == FAILURE)
            return FAILURE;

        if (*headR != NULL)
            (*headR)->data = -((*headR)->data);
    }

    return SUCCESS;
}