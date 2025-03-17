// @Duren Gouda

#include <stdio.h>

long min_bits(long x, long y) {
    long result;
    /* Determine which x or y has fewer bits.
     * Use the popcnt instruction to count the number of bits in a long
     * This instruction calculates the number of bits set to 1 in the source operand and
     * returns the count in the destination operand (must be a register).
     */
    asm ("popcntq %1, %%rax;"    // count bits in x, store in rax 
        "popcntq %2, %%rcx;"    // count bits in y, store in rcx
        "cmpq %%rcx, %%rax;"    // compare
        "jle fewer_in_x;"       /* if x has fewer or equal bits, jump */
        "movq %2, %0;"          /* y has fewer bits, move y to result */
        "jmp end;"             // jump to end
        "fewer_in_x:"
        "movq %1, %0;"          // x has fewer bits, move x to result
        "end:"
        : "=r" (result)         // output
        : "r" (x), "r" (y)      // input
        : "rax", "rcx", "cc"    
   );

    return result;
}

int call_min_bits(long x, long y) {
    long n;
    /* Call the min_bits function above
     */
    asm ("movq %1, %%rdi;"      // x
        "movq %2, %%rsi;"       // y
        "call min_bits;"        // call min_bits function 
        "movq %%rax, %0;"       // store return value in n 
        : "=r" (n)              // output
        : "r" (x), "r" (y)      // input
        : "rdi", "rsi", "rax", "rcx", "cc" 
   );

    return (int)n;
}

unsigned int sum(unsigned int *data, long size) {
    unsigned int result = 0;
    /* Computes the sum of the integers in data array
     */
    asm ("xorl %%eax, %%eax;"    // initialize sum to 0
         "testq %2, %2;"         //  if size is 0 
         "jle done_sum;"         // if size <= 0, skip loop 
         "movq %1, %%rcx;"       // store pointer in rcx 
         "movq %2, %%rdx;"       // store size in rdx 
         "loop_start:"
         "addl (%%rcx), %%eax;"  // add current element to sum 
         "addq $4, %%rcx;"       // move to next element (4 bytes) 
         "decq %%rdx;"           // decrement counter
         "jnz loop_start;"       // continue if not zero 
         "done_sum:"
         "movl %%eax, %0;"       // store final sum in result 
         : "=r" (result)         // output 
         : "r" (data), "r" (size) // input
         : "rax", "rcx", "rdx", "cc"
        );

    return result;
}

int main() {
    int n;
    int data[5] = {1, 2, 3, 4, 5};

    scanf("%d", &n);  /* read in the test to perform */
    switch(n) {
        case 0:
            printf("%ld = min_bits(%d, %d)\n", min_bits(8,7), 7, 8);
            break;

        case 1:
            printf("%d = call(%d, %d)\n", call_min_bits(15,16),15, 16);
            break;

        case 2:
            printf("%d = sum(data)\n", sum(data, 5));
            break;

        default:
            break;
    }
    return 0;
}


