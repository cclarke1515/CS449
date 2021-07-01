/*
 * CS:APP Data Lab
 *
 * <Connor Clarke    cmc240>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#ifndef COMMON_H
#include "common.h"
#endif

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
     not allowed to use big constants such as 0xffffffff.
     However, you are allowed to combine constants to values greater
     than 255 or less than 0. e.g. 250 + 250 = 500, so long as
     the operator you are using to combine the constants is listed as
     "legal" at the top of the method you are writing.
  2. Function arguments and local variables (no global variables).
  3. Any operators listed as "legal" at the top of the method you are writing.
  4. Shorthand versions of "legal" operators (ex. you can use ++ and += if + is legal)

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
  5. Write comments for your functions! These won't be graded, but it's good
     practice to write comments and may help you debug your code. See the
     above example to see what the comments should look like.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 */
#endif

/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~x & ~y) & ~(x & y);
  /* XOR = OR + NAND
  OR can be written as (~x & ~y) using DeMorgan's Law */
}

/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  int mask = 0x55;
  mask = (mask << 8) | mask;
  mask = (mask << 16) | mask;  
  return !((x & mask) ^ mask);
  /* Create mask of 0x55555555 or 1010 repeating (mask had to be created in parts for this function)
     AND x & mask then XOR to see if they match up with mask or not
     if so then all even bits are 1
     if not then one or more even bits are 0
     ! the entire phrase to give you a 0 or 1 */
}

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  int one = ~(((1 << 31) >> n) << 1);  
  return (x >> n) & one;
  /* Logical shift leads with 0's
     Create an int that shifts a 1 to the MSB
     Then shift it to the right by n-1 creating leading 1's
     NOT the statement to flips the bits from 1 to 0
     Shift x over by n then AND with int one to mask the leading 1's with 0's */
}

/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  int neg = x | (~x + 1);  
  return ~(neg >> 31) & 1;
  /* Set x = its current value OR it's two's complement value
     Either will give you a 1 in the msb unless x = 0
     Shift x over to the lsb and negate it to get 1 if x was 0
     AND the negated lsb to see if it was 1 or not
     If 1 was returned then the number was 0 */
}

/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  return ~(1 << 31);
  /* 0x7FFFFFFF is the largest two's complement number
     1 is left-shifted by 31 to create 100000000...
     NOT operator flips it to 011111111111... */ 
}

/* 
 * twosBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: twosBits(5,3) = 0, twosBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int twosBits(int x, int n) {
  int truncate = 32 + (~n + 1);
  truncate = (x << truncate) >> truncate;
  return !(truncate ^ x);
  /* THIS FUNCTION IS JUST ASKING IF THERE IS A SIGN CHANGE!!!!!!!
     Truncate by the full 32 bits - the amound of bits specified by n
     Must use + two's complement to create subtraction of n-bit amount
     Shift x right by truncation amount and then left by truncation amount to create the actual truncation aka sign extention
     XOR with the new truncate value to check if there exists a sign shift
     NOT the answer so that when XOR returns 1 we return 0 */
}

/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int s = uf >> 31; // sign value
  int exp = (uf >> 23) & 0xFF; // AND with 0xFF to create a mask only retaining the bits we need and cutting off the sign
  int frac = uf & 0x7FFFFF; // 0x7FFFFF is a 24-bit mask that will grab the last 23 bits or the f bits
  int E = exp - 127; // single precision bias is 127
  int res = 0;

  if ( exp == 0xFF || E > 31 ) // Base Case: NaN or Infinity or exp greater than number of bits allowed (overflow)
	return 0x80000000u;

  if ( exp < 127 ) // Base Case: Denormalized 
	return 0;

  frac = frac | 0x800000; // append 1 to the front of frac

  if ( E < 23 ) // If exponent is smaller than frac move left
	res = frac >> (23 - E);
  else // Else if exponent is larger or equal move right to create leading zeroes
	res = frac << (E - 23);

  if ( s == 1 ) // If the sign bit was 1 make number negative
	return -res; // negative

  return res;
}
