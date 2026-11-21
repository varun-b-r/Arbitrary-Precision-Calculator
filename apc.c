#include "apc.h"

// This function is declared static because it is used only
// inside this apc.c file. Other files cannot call it directly.
static int is_valid_number(const char *str);

// Function definitions

// Validate command-line arguments before calculation.
int cla_validation(int argc, char *argv[])
{
    // Check whether exactly 4 user arguments are provided.
    if (argc != 4)
    {
        display_usage(argv[0]);
        return FAILURE;
    }

    // Check whether the operator contains only one character.
    if (strlen(argv[2]) != 1)
    {
        printf(RED "INVALID OPERATOR\n" RESET);
        return FAILURE;
    }

    // Check whether the entered operator is supported.
    if (argv[2][0] != '+' &&
        argv[2][0] != '-' &&
        argv[2][0] != 'x' &&
        argv[2][0] != 'X' &&
        argv[2][0] != '*' &&
        argv[2][0] != '/')
    {
        printf(RED "Invalid operator\n" RESET);
        return FAILURE;
    }
    // The operand must contain an optional sign followed by digits.
    if (is_valid_number(argv[1]) == FAILURE)
    {
        printf(RED "Invalid First operand\n" RESET);
        return FAILURE;
    }

    // Validate Second operand
    if (is_valid_number(argv[3]) == FAILURE)
    {
        printf(RED "Invalid Second operand\n" RESET);
        return FAILURE;
    }
    return SUCCESS; // All command-line aeguments are valid
}
// Check whether a string represents a valid integer.
static int is_valid_number(const char *str) //
// static means this helper function is private to apc.c.
{
    int i = 0;

    // Check whether the string is empty.
    if (str[0] == '\0')
    {
        return FAILURE;
    }

    // Skip optional sign
    // Allow an optional positive or negative sign.
    // Examples:
    // +123 -> skip '+'
    // -123 -> skip '-'
    if (str[i] == '+' || str[i] == '-')
    {
        i++;
    }

    // Check whether the string contains only a sign.
    if (str[i] == '\0')
    {
        return FAILURE;
    }

    // Check each character
    while (str[i] != '\0')
    {
        // If the character is not a decimal digit,
        // the operand is invalid.
        if (str[i] < '0' || str[i] > '9')
        {
            return FAILURE;
        }
        i++;
    }

    return SUCCESS;
}

// Convert a number string into a doubly linked list.
void create_list(char *opr, node **head, node **tail)
{
    int i = 0;
    int digit;

    // Step 1: Skip the optional sign.
    // The sign is handled separately in main.c.
    // Only the numeric digits are stored in the list.
    if (opr[i] == '+' || opr[i] == '-')
    {
        i++;
    }

    // Traverse the string until its end.
    while (opr[i] != '\0')
    {
        // Convert a character digit into its integer value.
        //
        // Example:
        // '5' - '0' = 5
        digit = opr[i] - '0';

        // Insert each digit at the end of the list.
        if (insert_last(head, tail, digit) == FAILURE)
        {
            printf(RED "Failed to insert digit %d into the list\n" RESET, digit);
            return;
        }
        i++;
    }
}

// Insert a new node at the beginning of the list.
int insert_first(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));

    if (new == NULL)
    {
        printf(RED "memory allocation failed\n" RESET);
        return FAILURE;
    }

    // Store the digit in the new node.
    new->data = data;

    // The new node becomes the first node,
    // so its previous pointer must be NULL.
    new->prev = NULL;

    // Connect the new node to the current first node.
    new->next = *head;

    if (*head == NULL)
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }

    (*head)->prev = new;
    *head = new;

    return SUCCESS;
}

// Insert a new node at the end of the list.
int insert_last(node **head, node **tail, int data)
{
    // create node
    node *new = malloc(sizeof(node));

    if (new == NULL)
    {
        printf(RED "memory allocation failed\n" RESET);
        return FAILURE;
    }

    new->data = data;
    new->next = NULL;
    new->prev = *tail;

    // list empty
    if (*head == NULL)
    {
        *tail = new;
        *head = new;
        return SUCCESS;
    }
    (*tail)->next = new;
    *tail = new;
    return SUCCESS;
}

// Delete all nodes and free allocated memory.
int delete_list(node **head, node **tail)
{
    node *temp;

    // Check whether the list is already empty.
    if (*head == NULL)
    {
        return SUCCESS;
    }

    while (*head != NULL)
    {
        // Keep the current first node in temp.
        // We need its address to free its memory.
        temp = *head;

        // Move head to the next node before freeing temp.
        *head = (*head)->next;

        // Release the memory occupied by the old first node.
        free(temp);
    }
    // After deleting every node,
    //  reset tail because the list is now empty.
    *tail = NULL;
    return SUCCESS;
}

// Display all digits stored in the linked list.
void print_list(node *head)
{
    // Use a temporary pointer to traverse the list.
    // The original head pointer is not modified.
    node *temp = head;

    if (head == NULL)
    {
        printf(RED "List is empty\n" RESET);
        return;
    }

    while (temp != NULL)
    {
        // Print the digit stored in the current node.
        printf("%d", temp->data);

        // Move to the next node.
        temp = temp->next;
    }

    printf("\n");
}

// Count the number of nodes in a linked list.
int list_len(node *head)
{
    // Temporary pointer for traversal.
    node *temp = head;

    // Initially, the list contains zero counted nodes.
    int count = 0;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

// Compare the magnitudes of two positive numbers.

// We only read and traverse the lists here.
// We do not change the original head pointers.
// Therefore, node * is sufficient; node ** is not required.
int compare_list(node *head1, node *head2)
{
    int len1, len2;

    // Find the number of digits in both operands.
    len1 = list_len(head1);
    len2 = list_len(head2);

    // Create temporary pointers for traversal.
    //  These allow us to move through the lists
    //  without changing the original head pointers.
    node *temp1 = head1;
    node *temp2 = head2;

    // Compare the number of digits.
    //  A number with more digits has a greater magnitude.
    if (len1 > len2)
    {
        return OPERAND1;
    }
    if (len1 < len2)
    {
        return OPERAND2;
    }

    // If both numbers have the same length,
    // compare digits from left to right.
    while (temp1 != NULL && temp2 != NULL)
    {
        // First number has a greater digit at this position.
        if (temp1->data > temp2->data)
        {
            return OPERAND1;
        }

        // Second number has a greater digit at this position.
        if (temp1->data < temp2->data)
        {
            return OPERAND2;
        }

        // Current digits are equal.
        // Move to the next pair of digits.
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    // If all digits are equal, both numbers have the same value.
    return SAME;
}

// Remove unnecessary zeros from the beginning.
void remove_pre_zeros(node **head)
{
    node *temp;

    // If the list is empty, nothing can be removed.
    if (*head == NULL)
    {
        return;
    }

    //  Remove leading zeros one by one.
    while ((*head)->data == 0 && (*head)->next != NULL) // Remove leading zeros,but leave at least one zero bcz  0000 is still 0
    // if we remove all zeros then the head and tail points to null and we will not able to perform any operation on it
    {
        // Store the current first node before deleting it.
        temp = *head;

        // Move head to the next node.
        *head = (*head)->next;

        // The new first node must not point backwards.
        (*head)->prev = NULL;

        // Free the memory of the removed leading-zero node.
        free(temp);
    }
}