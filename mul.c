
#include "apc.h"

// Multiply a large number by a single digit.
// digit ->  One digit from the second operand.
// headP -> Head of the partial product list.
// tailP -> Tail of the partial product list.
// This is a helper function used only inside mul.c.
// Therefore, it is declared static.
static int multiply_digit(node *tail1, int digit, node **headP, node **tailP)
{
    int product, carry = 0;
    int result; // digit to insert into the partial product

    // Traverse first operand from right to left
    while (tail1 != NULL)
    {
        // Multiply the current digit by the given digit
        // and add any carry from the previous position.
        product = tail1->data * digit + carry;

        // Extract the digit to store in the result.
        result = product % 10;

        // Calculate the carry for the next position.
        carry = product / 10;

        // Insert result digit at the beginning
        if (insert_first(headP, tailP, result) == FAILURE)
        {
            delete_list(headP, tailP);
            return FAILURE;
        }

        // Step 6: Move to the previous digit of the first operand.
        tail1 = tail1->prev;
    }

    // After all digits are processed,
    //  check whether any carry remains.
    if (carry != 0)
    {
        // Insert the remaining carry at the beginning.
        if (insert_first(headP, tailP, carry) == FAILURE)
        {
            delete_list(headP, tailP);
            return FAILURE;
        }
    }

    // The complete single-digit multiplication succeeded.
    return SUCCESS;
}

// Perform multiplication using long multiplication
// headR -> final result

// We multiply the first operand by each digit of the
// second operand, starting from its rightmost digit.
void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    // y bcz tail2 is not modified
    node *temp2 = tail2;

    node *headP = NULL, *tailP = NULL; // Store the current partial product
    node *headS = NULL, *tailS = NULL; // store the sum of the previous result and the current partial product

    // zero_count represents the place value of the
    // current digit being processed from the second operand.
    int zero_count = 0;
    int i;

    // Check whether both operand lists are valid.
    if (tail1 == NULL || tail2 == NULL)
    {
        printf("Error: Invalid operand lists\n");
        return;
    }

    // Traverse second operand from right to left
    while (temp2 != NULL)
    {
        // Multiply first operand by current digit of the second operand
        if (multiply_digit(tail1, temp2->data, &headP, &tailP) == FAILURE)
        {
            // Clean up allocated memory if multiplication fails.
            delete_list(&headP, &tailP);
            delete_list(headR, tailR);
            return;
        }

        // Add zeros according to place value
        for (i = 0; i < zero_count; i++)
        {
            // Zeros are inserted at the end because they
            // represent additional positions on the right.
            if (insert_last(&headP, &tailP, 0) == FAILURE)
            {
                delete_list(&headP, &tailP);
                delete_list(headR, tailR);
                return;
            }
        }

        // Check whether this is the first partial product

        // If the result list is empty, directly transfer
        // ownership of the partial product list to the result.
        if (*headR == NULL)
        {
            *headR = headP;
            *tailR = tailP;

            // Reset temporary pointers because their nodes
            // now belong to the result list.
            // This prevents accidental deletion of the result.

            headP = NULL;
            tailP = NULL;
        }
        else
        {
            // Add partial product to previously accumulated sum

            // This reuses the addition() function from add.c.
            // Both arguments are tails because addition
            // processes digits from right to left.
            addition(*tailR, tailP, &headS, &tailS);

            // Check whether addition produced a result
            // If headS is NULL, treat it as a failure.
            if (headS == NULL)
            {
                delete_list(&headP, &tailP);
                delete_list(headR, tailR);
                return;
            }
            // Delete the old result and the current
            // partial product because their sum is ready
            delete_list(&headP, &tailP);
            delete_list(headR, tailR);

            // Step 8: Make the new sum the accumulated result.
            // The previous result is replaced by headS/tailS.
            *headR = headS;
            *tailR = tailS;

            // Reset temporary pointers.
            // The sum nodes now belong to the result list.
            headS = NULL;
            tailS = NULL;
        }

        // Move to previous digit of the second operand
        temp2 = temp2->prev;

        // Increase place value
        zero_count++;
    }

    // Step 8: Remove leading zeros from the beginning of the final result
    remove_pre_zeros(headR);
}
