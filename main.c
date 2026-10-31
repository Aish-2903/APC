
#include "apc.h"

int main(void)
{
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *headR = NULL, *tailR = NULL;

    char num1[10000], num2[10000];
    char operator;
    char option = 'y';

    do
    {
        printf("\n====================================\n");
        printf("     ARBITRARY PRECISION CALCULATOR\n");
        printf("====================================\n");

        printf("Enter first number: ");
        if (scanf("%9999s", num1) != 1)
            break;

        printf("Enter operator (+, -, *, /): ");
        if (scanf(" %c", &operator) != 1)
            break;

        printf("Enter second number: ");
        if (scanf("%9999s", num2) != 1)
            break;

        if (apc_parse(num1, &head1, &tail1) == FAILURE ||
            apc_parse(num2, &head2, &tail2) == FAILURE)
        {
            printf("Invalid input. Enter positive whole numbers only.\n");
        }
        else
        {
            int status = FAILURE;

            switch (operator)
            {
                case '+':
                    status = addition(&head1, &tail1,
                                      &head2, &tail2, &headR);
                    break;

                case '-':
                    status = subtraction(&head1, &tail1,
                                         &head2, &tail2, &headR);
                    break;

                case '*':
                    status = multiplication(&head1, &tail1,
                                            &head2, &tail2, &headR);
                    break;

                case '/':
                    status = division(&head1, &tail1,
                                      &head2, &tail2, &headR);
                    break;

                default:
                    printf("Invalid operator.\n");
                    break;
            }

            if (status == SUCCESS)
            {
                printf("\nResult: ");
                apc_print(headR);
                printf("\n");
            }
            else if (operator == '+' || operator == '-' ||
                     operator == '*' || operator == '/')
            {
                printf("Operation failed. Check the input or division by zero.\n");
            }
        }

        apc_clear(&head1, &tail1);
        apc_clear(&head2, &tail2);
        apc_clear(&headR, &tailR);

        printf("\nWant to continue? Press [y/Y] or [n/N]: ");

        if (scanf(" %c", &option) != 1)
            break;

    } while (option == 'y' || option == 'Y');

    printf("\nThank you for using APC!\n");

    return 0;
}
