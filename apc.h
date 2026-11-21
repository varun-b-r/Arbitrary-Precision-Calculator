#ifndef APC_H
#define APC_H

// Standard header files
#include <stdio.h>  // -> printf(), scanf() and other input/output functions
#include <string.h> // -> strlen() and string-related functions
#include <stdlib.h> // -> malloc(), free() and memory management functions

// Return status constants
#define SUCCESS 1
#define FAILURE 0

// Constants used by compare_list()
#define SAME 0
#define OPERAND1 1
#define OPERAND2 2

// Terminal colour definitions
#define RESET "\033[0m"
#define CYAN "\033[1;96m"
#define WHITE "\033[1;97m"
#define GREEN "\033[1;92m"
#define RED "\033[1;91m"
#define GREY "\033[1;90m"

// Border decoration
#define BORDER "=============================================="

// Structure definition for a doubly linked list node.
typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
} node;

// Arithmetic operation function declarations
// These functions receive the tail pointers because arithmetic
// operations process digits from right to left.
void addition(node *tail1, node *tail2, node **headR, node **tailR);
void subtraction(node *tail1, node *tail2, node **headR, node **tailR);
void multiplication(node *tail1, node *tail2, node **headR, node **tailR);

// Division receives the heads of both operands to process
// digits from left to right.
// It also receives the divisor's tail for subtraction.
// Quotient and remainder are stored in separate linked lists.

void division(node *head1, node *head2, node *tail2, node **headQ, node **tailQ, node **headRem, node **tailRem);

// Checks whether the user entered valid operands and an operator.
int cla_validation(int argc, char *argv[]);

// Converts an operand string into a doubly linked list.
// Each decimal digit is stored in a separate node.
void create_list(char *opr, node **head, node **tail);

// Linked list insertion and deletion functions
int insert_first(node **head, node **tail, int data);
int insert_last(node **head, node **tail, int data);
int delete_list(node **head, node **tail); // releases their allocated memory
void print_list(node *head);

// linked lists utility functions

// Compares two numbers based on their lengths and digits.
// Returns SAME, OPERAND1 or OPERAND2.
int compare_list(node *head1, node *head2);

//// Counts the number of nodes in a linked list.
int list_len(node *head);

// Removes unnecessary zeros from the beginning of a number.
// Example: 000123 becomes 123.
void remove_pre_zeros(node **head);

// Display function declarations
// functions that handle the calculator's user interface.
void display_header(void);
void display_operation(const char *operation, const char *operand1, const char *operand2); // Displays the operation name and input operands.
void display_result(node *head, int sign);                                                 // Displays the arithmetic result with its sign.
void display_division_result(node *headQ, int quotient_sign, node *headRem, int remainder_sign);
void display_error(const char *message);
void display_success(void);
void display_footer(void);
// usage message
void display_usage(const char *program_name);
#endif

/*
1. #ifndef APC_H and #define APC_H – These are called header guards. They prevent the same header file from being included multiple times during compilation.

2. typedef struct node – Defines the linked-list node structure. Because of typedef, we can write node instead of struct node whenever we declare a node pointer.

3. Function prototypes – These tell the compiler the function name, its parameters and its return type before the function is used.

4. Why node ** for some parameters? – Functions such as insert_first() and insert_last() may change the actual head and tail pointers.
                                      Passing their addresses allows those changes to reach the calling function.
*/