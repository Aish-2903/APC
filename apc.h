#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1

typedef int data_t;

typedef struct node
{
    struct node *prev;
    data_t data;
    struct node *next;
} Dlist;

/* Function declarations */
int addition(Dlist **head1, Dlist **tail1,
             Dlist **head2, Dlist **tail2, Dlist **headR);

int subtraction(Dlist **head1, Dlist **tail1,
                Dlist **head2, Dlist **tail2, Dlist **headR);

int multiplication(Dlist **head1, Dlist **tail1,
                   Dlist **head2, Dlist **tail2, Dlist **headR);

int division(Dlist **head1, Dlist **tail1,
             Dlist **head2, Dlist **tail2, Dlist **headR);

/* Free a linked list */
static void apc_clear(Dlist **head, Dlist **tail)
{
    Dlist *temp = *head;

    while (temp != NULL)
    {
        Dlist *next = temp->next;
        free(temp);
        temp = next;
    }

    *head = NULL;
    *tail = NULL;
}

/* Insert at beginning */
static int apc_push_front(Dlist **head, Dlist **tail, int value)
{
    Dlist *newnode = malloc(sizeof(Dlist));

    if (newnode == NULL)
        return FAILURE;

    newnode->data = value;
    newnode->prev = NULL;
    newnode->next = *head;

    if (*head != NULL)
        (*head)->prev = newnode;
    else
        *tail = newnode;

    *head = newnode;

    return SUCCESS;
}

/* Insert at end */
static int apc_push_back(Dlist **head, Dlist **tail, int value)
{
    Dlist *newnode = malloc(sizeof(Dlist));

    if (newnode == NULL)
        return FAILURE;

    newnode->data = value;
    newnode->next = NULL;
    newnode->prev = *tail;

    if (*tail != NULL)
        (*tail)->next = newnode;
    else
        *head = newnode;

    *tail = newnode;

    return SUCCESS;
}

/* Remove unnecessary leading zeroes */
static void apc_trim(Dlist **head, Dlist **tail)
{
    while (*head != NULL && (*head)->data == 0 &&
           (*head)->next != NULL)
    {
        Dlist *temp = *head;
        *head = temp->next;
        (*head)->prev = NULL;
        free(temp);
    }
}

/* Convert a string into a linked list */
static int apc_parse(const char *number, Dlist **head, Dlist **tail)
{
    apc_clear(head, tail);

    if (number == NULL || *number == '\0')
        return FAILURE;

    for (int i = 0; number[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)number[i]))
        {
            apc_clear(head, tail);
            return FAILURE;
        }

        if (apc_push_back(head, tail, number[i] - '0') == FAILURE)
        {
            apc_clear(head, tail);
            return FAILURE;
        }
    }

    apc_trim(head, tail);
    return SUCCESS;
}

/* Display the result */
static void apc_print(Dlist *head)
{
    if (head == NULL)
    {
        printf("0");
        return;
    }

    if (head->data < 0)
    {
        printf("-");
        head->data = -head->data;
    }

    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }
}

/* Compare two positive numbers */
static int apc_compare(Dlist *a, Dlist *b)
{
    int countA = 0, countB = 0;
    Dlist *p;

    for (p = a; p != NULL; p = p->next)
        countA++;

    for (p = b; p != NULL; p = p->next)
        countB++;

    if (countA > countB)
        return 1;

    if (countA < countB)
        return -1;

    while (a != NULL && b != NULL)
    {
        if (a->data > b->data)
            return 1;

        if (a->data < b->data)
            return -1;

        a = a->next;
        b = b->next;
    }

    return 0;
}

/* Addition of magnitudes */
static int apc_add_abs(Dlist *a, Dlist *b,
                       Dlist **result, Dlist **resultTail)
{
    int carry = 0;
    Dlist *p = a;
    Dlist *q = b;

    while (p->next != NULL)
        p = p->next;

    while (q->next != NULL)
        q = q->next;

    apc_clear(result, resultTail);

    while (p != NULL || q != NULL || carry)
    {
        int sum = carry;

        if (p != NULL)
        {
            sum += p->data;
            p = p->prev;
        }

        if (q != NULL)
        {
            sum += q->data;
            q = q->prev;
        }

        if (apc_push_front(result, resultTail, sum % 10) == FAILURE)
        {
            apc_clear(result, resultTail);
            return FAILURE;
        }

        carry = sum / 10;
    }

    return SUCCESS;
}

/* Subtraction of magnitudes: a must be >= b */
static int apc_sub_abs(Dlist *a, Dlist *b,
                       Dlist **result, Dlist **resultTail)
{
    int borrow = 0;
    Dlist *p = a;
    Dlist *q = b;

    while (p->next != NULL)
        p = p->next;

    while (q->next != NULL)
        q = q->next;

    apc_clear(result, resultTail);

    while (p != NULL)
    {
        int value = p->data - borrow;

        if (q != NULL)
        {
            value -= q->data;
            q = q->prev;
        }

        if (value < 0)
        {
            value += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        if (apc_push_front(result, resultTail, value) == FAILURE)
        {
            apc_clear(result, resultTail);
            return FAILURE;
        }

        p = p->prev;
    }

    apc_trim(result, resultTail);
    return SUCCESS;
}

#endif