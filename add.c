#include "apc.h"

// Add two large numbers using doubly linked lists.
//  We start from the tail because addition begins
//  with the rightmost digit of each number.
void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    // sum    -> Stores the addition of two digits and carry.
    // carry  -> Stores the carry for the next position.
    // digit1 -> Current digit from the first operand.
    // digit2 -> Current digit from the second operand.
    // result -> Digit to be inserted into the result list.
    int sum, carry = 0;
    int digit1, digit2, result;

    // Step 1: Continue while at least one operand has digits
    // remaining or a carry is still present.

    // The carry condition is important.
    // Example: 999 + 1 = 1000
    // After processing all operand digits, carry is still 1.
    while (tail1 != NULL || tail2 != NULL || carry != 0)
    {
        // Step 2: Initially assume both digits are zero.

        // This handles numbers with different lengths.
        // If one operand has no digit at the current position,
        // its value is treated as zero.
        digit1 = 0;
        digit2 = 0;

        // Step 3: Get the current digit from the first operand.
        //
        // Read the digit stored in the current tail node.
        // Then move to the previous node.
        if (tail1 != NULL)
        {
            digit1 = tail1->data;
            tail1 = tail1->prev;
        }

        // Step 4: Get the current digit from the second operand.
        if (tail2 != NULL)
        {
            digit2 = tail2->data;
            tail2 = tail2->prev;
        }

        // Step 5: Add both digits and the previous carry.
        sum = digit1 + digit2 + carry;

        // Step 6: Extract the digit to be stored.
        result = sum % 10;

        // Step 7: Calculate the carry for the next position.
        carry = sum / 10;

        // Step 8: Insert the result digit at the beginning.

        // We process digits from right to left.
        // Inserting each digit at the beginning builds
        // the final result in the correct order.
        if (insert_first(headR, tailR, result) == FAILURE)
        {
            delete_list(headR, tailR);
            return;
        }
    }
    // The complete addition result is available in headR/tailR.
}

/*
Important concepts for your viva
1. Why do we use tail1 and tail2?

Because addition starts from the rightmost digit. The tail gives direct access to that digit, and prev lets us move towards the left.

2. Why do we use insert_first() instead of insert_last()?

We process digits from right to left, but the final number must be stored from left to right. Inserting at the beginning gives the correct order.

3. Why is the loop condition carry != 0 included?

Because a carry may remain even after both operands are completely processed. For example, 999 + 1 = 1000.

4. Why are digit1 and digit2 initialized to zero in every iteration?

Because the operands may have different numbers of digits. When one list ends, the missing digit must be treated as zero.
*/