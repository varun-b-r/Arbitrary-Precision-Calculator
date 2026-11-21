
/*
Documentation

Name        : Varun B R
Student id  : 26018_040
Batch id    : 26018D
Start Date  :
End date    :

Description: The following main functions are implemented in the Arbitrary Precision Calculator(APC) project to perform arithmetic operations on large numbers
beyond the standard data type limits.

main()              :-> Handles command line arguments and selects the required arithmetic operation such as addition, subtraction, multiplication or division.
                     -> Validates the input operands and operator, identifies the signs of operands and calls the appropriate arithmetic function.
                     -> Displays the final result and handles the operation status.

addition()          :-> Performs addition of two large numbers using linked lists.
                     -> Adds corresponding digits from right to left while handling carry values.

subtraction()       :-> Performs subtraction of two large numbers using linked lists.
                     -> Subtracts corresponding digits while handling borrow values and maintains the correct sign of the result.

multiplication()    :-> Performs multiplication of two large numbers using linked lists.
                     -> Multiplies individual digits and handles carry values to generate the final product.

division()          :-> Performs division of two large numbers using the long division method.
                     -> Calculates the quotient and remainder while handling division by zero.

insert_first()      :-> Inserts a new digit at the beginning of the linked list.
                     -> Used to construct the result by storing digits in the required order.

insert_last()       :-> Inserts a new digit at the end of the linked list.
                     -> Used to build linked lists containing input numbers and intermediate results.

delete_list()       :-> Deletes all nodes from the linked list.
                     -> Frees the dynamically allocated memory used by the linked list.

print_list()        :-> Traverses and displays the digits stored in the linked list.

compare_lists()     :-> Compares two linked lists representing numbers.
                     -> Determines whether the first number is greater than, smaller than or equal to the second number.

remove_pre_zeros()  :-> Removes unnecessary leading zeros from a linked list.
                     -> Maintains the correct representation of the number.

cla_validation()    :-> Validates the command line arguments.
                     -> Checks the number of arguments and verifies whether the given arithmetic operator is valid.

display.c           :-> Handles the overall presentation and formatting of the Arbitrary Precision Calculator output.
                     -> Displays the calculator heading, operation details, input operands, and calculation results.
                     -> Displays the quotient and remainder separately for division operations.
                     -> Provides error messages and calculation completion status.
                     -> Uses terminal colour formatting and borders to improve the readability and appearance of the output.
==============================================
       ARBITRARY PRECISION CALCULATOR
==============================================

Operation : ADDITION
Operand 1 : 12345678901234567890
Operand 2 : 98765432109876543210
==============================================

Result    : 111111111011111111100

Calculation completed successfully!
==============================================
*/
#include "apc.h"

int main(int argc, char *argv[])
{
    // Pointers for the first and second operand's doubly linked list.
    node *head1 = NULL, *tail1 = NULL;
    node *head2 = NULL, *tail2 = NULL;

    // Pointers for storing the final arithmetic result.
    node *headR = NULL, *tailR = NULL;

    // Separate pointers for storing the remainder during division.
    node *headRem = NULL, *tailRem = NULL;

    // Store the signs of the two operands and final result sign.
    int sign1 = 1, sign2 = 1;
    int result_sign = 1;
    int cmp;

    char oper;             // Store the arithmatic operator entered by the user
    const char *operation; // Stores the name of the selected arithmetic operation.

    // Validate the number of command-line arguments,
    // operator and operand values.
    if (cla_validation(argc, argv) == FAILURE)
    {
        return FAILURE;
    }

    // Extract the arithmetic operator.
    oper = argv[2][0];

    // Identify the sign of the first operand.
    // If the first operand starts with '-', mark it as negative.
    if (argv[1][0] == '-')
        sign1 = -1;

    // Identify the sign of the second operand.
    if (argv[3][0] == '-')
        sign2 = -1;

    // Convert the first and second operands into a seperate doubly linked list.
    // Each decimal digit is stored in a separate node.
    create_list(argv[1], &head1, &tail1);
    create_list(argv[3], &head2, &tail2);

    // Check whether both operand lists were created successfully.
    if (head1 == NULL || head2 == NULL)
    {
        display_header();
        display_error("Unable to create operand lists");
        display_footer();

        // Release any nodes allocated before the failure.
        delete_list(&head1, &tail1);
        delete_list(&head2, &tail2);

        // Stop execution because the operands are unavailable.
        return FAILURE;
    }

    // Remove unnecessary leading zeros from the first and second operands.
    remove_pre_zeros(&head1);
    remove_pre_zeros(&head2);

    // Handle negative zero.
    // Zero should always be treated as positive.
    if (head1->data == 0 && head1->next == NULL)
        sign1 = 1;

    if (head2->data == 0 && head2->next == NULL)
        sign2 = 1;

    // Identify the operation name for terminal display.
    // The operator symbol is converted into a readable operation name.
    switch (oper)
    {
    case '+':
        operation = "ADDITION";
        break;

    case '-':
        operation = "SUBTRACTION";
        break;

    case 'x':
    case 'X':
    case '*':
        operation = "MULTIPLICATION";
        break;

    case '/':
        operation = "DIVISION";
        break;

    default:
        operation = "UNKNOWN";
        break;
    }

    // Display calculator heading.
    display_header();

    // Display the selected operation and original input operands.
    display_operation(operation, argv[1], argv[3]);

    // Perform the requested operation
    switch (oper)
    {
        // Addition and subtraction are handled together
        // because both operations depend on operand signs.
    case '+':
    case '-':
    {
        // For subtraction, reverse the sign of the second operand.
        // This allows subtraction to be handled as signed addition.
        if (oper == '-')
            sign2 = -sign2;

        // If both operands have the same sign -> add their magnitudes.
        if (sign1 == sign2)
        {
            // Addition starts from the tail (least significant digit) of both operand lists.
            addition(tail1, tail2, &headR, &tailR);

            // The result takes the common operand sign.
            result_sign = sign1;
        }
        else
        {
            // If signs are different, compare operand magnitudes.
            cmp = compare_list(head1, head2);

            // If both magnitudes are equal, the result is zero.
            if (cmp == SAME)
            {
                // Create a single node containing zero.
                insert_first(&headR, &tailR, 0);

                // Zero is always positive.
                result_sign = 1;
            }
            // If the first operand magnitude is greater,
            // subtract the second operand from the first.
            else if (cmp == OPERAND1)
            {
                subtraction(tail1, tail2, &headR, &tailR);

                // The result takes the first operand's sign.
                result_sign = sign1;
            }

            // If the second operand magnitude is greater,
            // subtract the first operand from the second.
            else
            {
                subtraction(tail2, tail1, &headR, &tailR);

                // The result takes the second operand's sign.
                result_sign = sign2;
            }
        }

        // Check whether the result list was created successfully.
        if (headR != NULL)
        {
            // Display the result with its appropriate sign.
            display_result(headR, result_sign);

            // Display the successful calculation message.
            display_success();
        }
        else
        {
            // Display an error if the result could not be generated.
            display_error("Unable to calculate result");
        }

        break;
    }

        // Multiplication can be represented using x, X or *.
    case 'x':
    case 'X':
    case '*':
    {
        // Perform multiplication using the long multiplication method.
        // The multiplication function internally uses addition
        // to accumulate the partial products.
        multiplication(tail1, tail2, &headR, &tailR);

        // Calculate the result sign.
        // Equal signs produce positive; different signs produce negative.
        result_sign = sign1 * sign2;

        // Check whether multiplication generated a result.
        if (headR != NULL)
        {
            // Display the multiplication result with its sign.
            display_result(headR, result_sign);

            // Display successful completion message.
            display_success();
        }
        else
        {
            // Display an error if multiplication failed.
            display_error("Unable to calculate result");
        }

        break;
    }

    // Division
    case '/':
    {
        // Perform integer division.
        // headR and tailR store the quotient.
        // headRem and tailRem store the remainder.
        division(head1, head2, tail2, &headR, &tailR, &headRem, &tailRem);

        // Check whether both quotient and remainder lists exist.
        if (headR != NULL && headRem != NULL)
        {
            // Quotient sign is the product of operand signs.
            result_sign = sign1 * sign2;

            // Display quotient and remainder separately.
            // The quotient uses result_sign.
            // The remainder uses the dividend sign (sign1)
            display_division_result(headR, result_sign, headRem, sign1);

            display_success();
        }

        break;
    }

        // Handle an unsupported operator.
    default:
        display_error("Invalid operator");
        break;
    }

    // Display footer
    display_footer();

    // Free allocated memory
    delete_list(&head1, &tail1);
    delete_list(&head2, &tail2);

    delete_list(&headR, &tailR);
    delete_list(&headRem, &tailRem);

    return SUCCESS;
}
