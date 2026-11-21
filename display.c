
#include "apc.h"

// Display calculator heading
void display_header(void)
{
    printf("\n");

    // Print the top border in grey colour.
    printf("%s%s%s\n", GREY, BORDER, RESET);

    // Display the calculator title in cyan.
    printf("%s       ARBITRARY PRECISION CALCULATOR       %s\n", CYAN, RESET);

    // Print the bottom border in grey colour.
    printf("%s%s%s\n\n", GREY, BORDER, RESET);
}

// Display the selected operation and operands.
void display_operation(const char *operation,
                       const char *operand1,
                       const char *operand2)
{
    printf("%sOperation : %s%s\n", WHITE, operation, RESET);
    printf("%sOperand 1 : %s%s\n", WHITE, operand1, RESET);
    printf("%sOperand 2 : %s%s\n", WHITE, operand2, RESET);

    printf("%s%s%s\n", GREY, BORDER, RESET);
}

// Display the result of normal arithmetic operations.
void display_result(node *head, int sign)
{
    printf("%sResult    : %s", GREEN, RESET);

    if (head == NULL)
    {
        printf("%sUnavailable%s\n", RED, RESET);
        return;
    }

    // Print the negative sign only when the result is
    // negative and the result is not zero.
    if (sign == -1 &&
        !(head->data == 0 && head->next == NULL))
    {
        printf("-");
    }

    printf("%s", GREEN);
    print_list(head);
    printf("%s", RESET);
}

// Display quotient and remainder after division.
void display_division_result(node *headQ, int quotient_sign, node *headRem, int remainder_sign)
{
    printf("%sQuotient  : %s", GREEN, RESET);

    // Check whether the quotient list exists.
    if (headQ != NULL)
    {
        // Print minus sign if quotient is negative
        // and its value is not zero.
        if (quotient_sign == -1 &&
            !(headQ->data == 0 && headQ->next == NULL))
        {
            printf("-");
        }

        printf("%s", GREEN);
        print_list(headQ);
        printf("%s", RESET);
    }

    printf("%sRemainder : %s", GREEN, RESET);

    // Check whether the remainder list exists.
    if (headRem != NULL)
    {
        // Print minus sign if remainder is negative
        // and its value is not zero.
        if (remainder_sign == -1 &&
            !(headRem->data == 0 && headRem->next == NULL))
        {
            printf("-");
        }

        printf("%s", GREEN);
        print_list(headRem);
        printf("%s", RESET);
    }
}

// Display error message
void display_error(const char *message)
{
    printf("\n%sERROR: %s%s\n", RED, message, RESET);
}

// Display successful completion message
void display_success(void)
{
    printf("\n%sCalculation completed successfully!%s",
           GREEN, RESET);
}

// Display the bottom footer
void display_footer(void)
{
    printf("\n%s%s%s\n", GREY, BORDER, RESET);
}

// Display usage instructions
void display_usage(const char *program_name)
{
    printf("\n");
    printf("%s%s%s\n", GREY, BORDER, RESET);
    printf("%s       ARBITRARY PRECISION CALCULATOR       %s\n",
           CYAN, RESET);
    printf("%s%s%s\n\n", GREY, BORDER, RESET);

    printf("%sUSAGE:%s\n", WHITE, RESET);
    printf("%s%s <operand1> <operator> <operand2>%s\n\n",
           GREEN, program_name, RESET);

    printf("%sSUPPORTED OPERATORS:%s\n", WHITE, RESET);
    printf("  +       Addition\n");
    printf("  -       Subtraction\n");
    printf("  '*' x X Multiplication\n");
    printf("  /      Division\n\n");

    printf("%sEXAMPLES:%s\n", WHITE, RESET);
    printf("  %s 123456789 + 987654321\n", program_name);
    printf("  %s -500 - 250\n", program_name);
    printf("  %s 987654321 * 12345\n", program_name);
    printf("  %s 1000 / 25\n\n", program_name);

    printf("%sNOTE: Enter integer operands only.%s\n",
           GREY, RESET);

    printf("%s%s%s\n", GREY, BORDER, RESET);
}
