//27 OPCODE ERROR IN GIVEN JOB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isValidOperand(char *operand) {
    // Check if operand is a valid integer or register name
    if (isdigit(operand[0])) {  // Check if operand is a valid integer
        for (int i = 0; i < strlen(operand); i++) {
            if (!isdigit(operand[i])) return 0;
        }
        return 1;
    } else {  // Check if operand is a valid register (e.g., "R1", "AX")
        return (isalpha(operand[0]) && strlen(operand) <= 3);
    }
}

void checkOperandError(char *job[], int n) {
    int error_found = 0;
    printf("\nInstruction\tOperand Validity\n");
    for (int i = 0; i < n; i++) {
        if (!isValidOperand(job[i])) {
            printf("%s\t\tInvalid (Interrupt Raised)\n", job[i]);
            error_found = 1;
        } else {
            printf("%s\t\tValid\n", job[i]);
        }
    }
    if (error_found) printf("\nInterrupt: Invalid operand(s) detected!\n");
}

int main() {
    int n;
    printf("Enter number of instructions: ");
    scanf("%d", &n);
    getchar(); // Clear newline character from input buffer

    char *job[n];
    printf("Enter operands (one per instruction):\n");
    for (int i = 0; i < n; i++) {
        job[i] = (char*) malloc(10); // Cast malloc to (char*)
        if (job[i] == NULL) { // Check if malloc was successful
            printf("Memory allocation failed\n");
            return 1;
        }
        fgets(job[i], 10, stdin); // Use fgets to avoid buffer overflow
        job[i][strcspn(job[i], "\n")] = '\0'; // Remove newline character
    }

    checkOperandError(job, n);
    
    for (int i = 0; i < n; i++) free(job[i]); // Free allocated memory

    return 0;
}

// INPUT:- 
// 123
// AX
// 45B
// 500