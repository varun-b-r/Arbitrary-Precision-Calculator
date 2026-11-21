#include "apc.h"

// Subtract two large numbers using doubly linked lists.

// The magnitude of the first operand must be greater than
// or equal to the magnitude of the second operand.
//
// We process digits from right to left, just like normal
// subtraction on paper.
void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    // digit1 -> Current digit from the first operand.
    // digit2 -> Current digit from the second operand.
    // result -> Difference to be inserted into the result list.
    // borrow -> Indicates whether the previous position
    //           borrowed one from the current position.
    int digit1, digit2, result;
    int borrow = 0;

    // Step 1: Continue until both operand lists are processed.
    while (tail1 != NULL || tail2 != NULL)
    {

        // Step 2: Initialize both digits to zero.

        // This handles operands having different lengths.
        // If one operand has no digit at this position,
        // its digit is treated as zero.
        digit1 = 0;
        digit2 = 0;

        // Step 3: Read the current digit from the first operand.
        if (tail1 != NULL)
        {
            digit1 = tail1->data;
            tail1 = tail1->prev;
        }

        // Step 4: Read the current digit from the second operand.
        if (tail2 != NULL)
        {
            digit2 = tail2->data;
            tail2 = tail2->prev;
        }

        // Step 5: Apply any borrow received from the previous
        // position to the current first-operand digit.
        digit1 = digit1 - borrow;

        // Step 6: Reset borrow before checking the current digits.
        borrow = 0;

        // Step 7: Check whether the first digit is smaller
        // than the second digit.
        //
        // If digit1 < digit2, we need to borrow from the
        // next position on the left.
        //
        // Adding 10 represents the borrowed value.
        if (digit1 < digit2)
        {
            digit1 = digit1 + 10;
            borrow = 1;
        }

        // Step 8: Calculate the difference between the digits.
        result = digit1 - digit2;

        // Step 9: Insert the result digit at the beginning.
        //
        // We process from right to left.
        // Inserting at the beginning builds the result
        // in the correct left-to-right order.
        if (insert_first(headR, tailR, result) == FAILURE)
        {
            delete_list(headR, tailR);
            return;
        }
    }
    // Step 10: Remove unnecessary zeros from the beginning.
    // At least one zero is retained if the result is zero.
    remove_pre_zeros(headR);
}
