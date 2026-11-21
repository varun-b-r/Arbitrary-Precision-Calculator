#include "apc.h"

/* Integer division:
                    quotient is stored in headR/tailR.
                    Remainder is stored in headRem/tailRem */

void division(node *head1, node *head2, node *tail2, node **headQ, node **tailQ, node **headRem, node **tailRem)
{
    // temp1 traverses the dividend from left to right.
    node *temp1 = head1;

    // Temporary list to store the result of each subtraction.
    node *headSub = NULL, *tailSub = NULL;
    int cmp;
    int quotient_digit;

    if (head1 == NULL || head2 == NULL)
    {
        printf(RED "ERROR : Invalid Operand lists\n" RESET);
        return;
    }

    // Check whether the divisor is zero.
    // A normalized zero list contains one node with data 0.
    if (head2->data == 0 && head2->next == NULL)
    {
        printf(RED "ERROR : Division by zero error\n" RESET);
        return;
    }

    // Compare the dividend and divisor.
    cmp = compare_list(head1, head2);

    // If dividend is smaller than divisor,
    // quotient is 0 and remainder is the dividend itself.
    if (cmp == OPERAND2)
    {
        // Insert 0 into the quotient list.
        if (insert_first(headQ, tailQ, 0) == FAILURE)
        {
            printf(RED "Error: Memory allocation failed\n" RESET);
            return;
        }

        // Copy every dividend digit into the remainder list.
        while (temp1 != NULL)
        {
            if (insert_last(headRem, tailRem, temp1->data) == FAILURE)
            {
                // Free both lists if memory allocation fails.
                delete_list(headQ, tailQ);
                delete_list(headRem, tailRem);
                return;
            }
            // Move to the next dividend digit.
            temp1 = temp1->next;
        }

        return;
    }

    // Process the dividend one digit at a time.
    while (temp1 != NULL)
    {
        // Reset the quotient digit for the current position.
        quotient_digit = 0;

        // Append the current dividend digit to the remainder.
        if (insert_last(headRem, tailRem, temp1->data) == FAILURE)
        {
            printf(RED "Error: Memory allocation failed\n" RESET);
            delete_list(headRem, tailRem);
            delete_list(headQ, tailQ);
            return;
        }

        // Remove unnecessary leading zeros from the remainder.
        remove_pre_zeros(headRem);

        // Compare the current remainder with the divisor.
        cmp = compare_list(*headRem, head2);

        // Subtract the divisor while remainder >= divisor.
        while (cmp == SAME || cmp == OPERAND1)
        {

            // Subtract divisor from the current remainder.
            // The result is stored in a temporary list.
            subtraction(*tailRem, tail2, &headSub, &tailSub);

            // If subtraction failed, the result list is empty.
            if (headSub == NULL)
            {
                delete_list(headRem, tailRem);
                delete_list(headQ, tailQ);
                return;
            }

            // Delete the old remainder list.
            delete_list(headRem, tailRem);

            // Make the subtraction result the new remainder.
            *headRem = headSub;
            *tailRem = tailSub;

            // Reset temporary pointers for the next subtraction.
            headSub = tailSub = NULL;

            // One successful subtraction means divisor fits once.
            quotient_digit++;

            // Check whether another subtraction is possible.
            cmp = compare_list(*headRem, head2);
        }

        // Store the quotient digit for this position.
        if (insert_last(headQ, tailQ, quotient_digit) == FAILURE)
        {
            printf(RED "Error: Memory allocation failed\n" RESET);
            delete_list(headRem, tailRem);
            delete_list(headQ, tailQ);
            return;
        }
        // Move to the next digit of the dividend.
        temp1 = temp1->next;
    }
    // Remove leading zeros from the final quotient.
    remove_pre_zeros(headQ);
}
