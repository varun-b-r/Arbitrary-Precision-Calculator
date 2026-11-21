# Arbitrary Precision Calculator (APC)

A command-line calculator implemented in **C** that performs arithmetic operations on large integer values beyond the limits of standard built-in integer data types using **Doubly Linked Lists**.

## Overview

The Arbitrary Precision Calculator (APC) is designed to perform arithmetic operations on large integers without relying on fixed-size integer data types such as `int` or `long`.

Each digit of an operand is stored separately in a node of a doubly linked list. This allows the calculator to process large numbers digit by digit while managing memory dynamically.

The project implements addition, subtraction, multiplication, and integer division, including support for positive and negative operands.

## Features

-> Performs arithmetic operations on large integers.
-> Supports addition, subtraction, multiplication, and integer division.
-> Handles positive and negative operands.
-> Uses doubly linked lists for digit-wise number representation.
-> Supports quotient and remainder calculation during division.
-> Handles carry and borrow operations.
-> Validates command-line arguments and numeric operands.
-> Removes unnecessary leading zeros while preserving zero correctly.
-> Dynamically allocates and releases memory for linked-list nodes.
-> Provides formatted terminal output with colour and status messages.
-> Uses a Makefile to simplify compilation and project management.

## Key Implementation Details

### 1. Doubly Linked List Representation

Each digit of a number is stored in an individual node containing:

- `prev` – Pointer to the previous digit.
- `data` – Stores the digit.
- `next` – Pointer to the next digit.

The `head` pointer refers to the most significant digit, while the `tail` pointer refers to the least significant digit.

This representation allows arithmetic operations to traverse digits in both directions.

### 2. Addition

- Traverses both operands from right to left.
- Adds corresponding digits along with the carry.
- Stores each resulting digit in a new linked list.
- Continues until all digits and the final carry are processed.

### 3. Subtraction

- Performs digit-wise subtraction from right to left.
- Handles borrowing when the first digit is smaller than the second.
- Removes unnecessary leading zeros from the result.
- Uses magnitude comparison to determine the correct subtraction order.

### 4. Multiplication

- Implements the traditional long multiplication technique.
- Multiplies one operand by individual digits of the other operand.
- Generates intermediate partial products.
- Adjusts partial products according to their place values.
- Adds the partial products to obtain the final result.

### 5. Division

- Implements integer long division using repeated subtraction.
- Processes the dividend digit by digit.
- Compares the intermediate remainder with the divisor.
- Determines each quotient digit through repeated subtraction.
- Maintains separate linked lists for the quotient and remainder.
- Checks for division by zero.

### 6. Sign Handling

- Supports positive and negative integer operands.
- Determines the result sign based on the arithmetic operation.
- Handles different operand signs during addition and subtraction.
- Applies the appropriate sign to the quotient and remainder.
- Prevents negative zero in the displayed result.

### 7. Memory Management

- Allocates memory dynamically for each linked-list node.
- Uses insertion functions to construct operand and result lists.
- Releases allocated memory after calculations.
- Includes cleanup operations when intermediate calculations fail.

### 8. Terminal Display

- Displays the calculator heading and input details.
- Presents arithmetic results in a formatted layout.
- Displays quotient and remainder separately for division.
- Uses terminal colours, borders, and status messages for readability.

## Project Structure

```text
APC/
│
├── main.c       # Main program and operation selection
├── apc.c        # Validation and linked-list operations
├── apc.h        # Header file, structure and declarations
├── add.c        # Addition implementation
├── sub.c        # Subtraction implementation
├── mul.c        # Multiplication implementation
├── div.c        # Division implementation
├── display.c    # Terminal output and formatting
├── Makefile     # Automated compilation
└── README.md    # Project documentation
```

## Technologies Used

- **Programming Language:** C
- **Data Structure:** Doubly Linked List
- **Compiler:** GCC
- **Build Automation:** Makefile
- **Development Environment:** Linux / Ubuntu / WSL

## Compilation and Execution

### Prerequisites

Make sure GCC and Make are installed.

For Ubuntu / WSL:

````bash
sudo apt update
sudo apt install gcc make

### 1. Clone the Repository

```bash
git clone <your-repository-url>
````

Navigate into the project directory:

```bash
cd APC
```

### 2. Compile the Project

The project uses a Makefile to automate compilation.

Run:

```bash
make
```

This command:

- Compiles the source files.
- Generates the required object files.
- Links the object files.
- Creates the executable named `apc`.

### 3. Run the Calculator

**General syntax:**

```bash
./apc <operand1> <operator> <operand2>
```

**Example**:

Addition:

```bash
./apc 12345678901234567890 + 98765432109876543210
```

Subtraction:

```bash
./apc 98765432109876543210 - 12345678901234567890
```

Multiplication:

```bash
./apc 12345678901234567890 '*' 12345
```

Division:

```bash
./apc 10000000000000000000 / 25
```

Negative operands:

```bash
./apc -500 + 250
```

The calculator accepts `*`, `x`, and `X` as multiplication operators.

### 4. Clean Generated Files

To remove object files and the executable:

```bash
make clean
```

### 5. Rebuild the Project

To clean and compile the project again:

```bash
make rebuild
```

## Sample Output

Example: Addition

```text
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
```

Example: Division

```text
==============================================
       ARBITRARY PRECISION CALCULATOR
==============================================

Operation : DIVISION
Operand 1 : 125
Operand 2 : 12
==============================================
Quotient  : 10
Remainder : 5

Calculation completed successfully!
==============================================
```

## Concepts Demonstrated

This project provides practical implementation experience in:

- C programming and modular programming.
- Doubly linked list operations.
- Dynamic memory allocation and deallocation.
- Pointers and pointer-to-pointer concepts.
- Arithmetic algorithms and digit manipulation.
- Command-line argument handling.
- Input validation and error handling.
- Makefile-based compilation and build automation.

## Limitations

- The practical size of supported numbers depends on available system memory.
- Division uses repeated subtraction, so calculations with very large quotient values may take longer.
- The calculator supports integer arithmetic only; floating-point operations are not implemented.

## Conclusion

The Arbitrary Precision Calculator demonstrates how large integer arithmetic can be implemented in C using dynamically allocated doubly linked lists.

By implementing arithmetic operations at the digit level, the project provides a practical understanding of data structures, pointer manipulation, memory management, and fundamental arithmetic algorithms.

It brings together core C programming concepts in a modular, command-line application.
