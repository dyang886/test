/* REMEMBER:
 * - This is the only file that you need to edit!
 * - Declare variables only at the beginning of a function (as in C89).
 * - Do not include <stdio.h> header (it confuses dlc)
 * - Check correctness with ./btest
 * - Check operator constraints with ./dlc bits.c
 * - Run ./grade before you commit/push your solution
 */

/*
 * TMax - return maximum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int tmax(void)
{
  // Minimum value: -2^31 -> 1000 0000 0000 0000 0000 0000 0000 0000
  // Maximum value: 2^31 - 1 -> 0111 1111 1111 1111 1111 1111 1111 1111
  return ~(1 << 31);
}

/*
 * bitOr - x|y using only ~ and &
 * (tip: always remember De Morgan's laws!)
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 4
 *   Rating: 1
 */
int bitOr(int x, int y)
{
  return ~(~x & ~y);
}

/*
 * negate - return -x
 * (tip: remember the definition of two's complement!)
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int negate(int x)
{
  return ~x + 1;
}

/*
 * isEqual - return 1 if x == y, and 0 otherwise
 * (tip: which bitwise op computes the difference?)
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 2
 */
int isEqual(int x, int y)
{
  return !(x ^ y);
}

/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 14
 *   Rating: 4
 */
int addOK(int x, int y)
{
  int sum = x + y;
  int signX = x >> 31;
  int signY = y >> 31;
  int signSum = sum >> 31;
  return !(~(signX ^ signY) & (signX ^ signSum));
}

/*
 * signMag2TwosComp - Convert from sign-magnitude to two's complement
 *   where the MSB is the sign bit
 *   Example: signMag2TwosComp(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int signMag2TwosComp(int x)
{
  int sign = x >> 31;
  int magnitude = x & ~(1 << 31);
  int twosComp = ~magnitude + 1;
  return (sign & twosComp) | (~sign & magnitude);
}

/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x80000001) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 14
 *   Rating: 4
 */
int satMul2(int x)
{
  int doubled = x << 1;
  int signX = x >> 31;
  int signMismatch = (x ^ doubled) >> 31;
  int tmax = ~(1 << 31);
  int saturateVal = tmax ^ signX;
  return (signMismatch & saturateVal) | (~signMismatch & doubled);
}

/*
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: dividePower2(15,1) = 7, dividePower2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int dividePower2(int x, int n)
{
  int bias = (x >> 31) & ((1 << n) + ~0);
  return (x + bias) >> n;
}

/*
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c)
{
  int mask = ~(0xFF << (n << 3));
  int newByte = c << (n << 3);
  return (x & mask) | newByte;
}

/*
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 5
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf)
{
  unsigned x = uf & 0x7FFFFFFF;
  if (x > 0x7F800000)
  {
    return uf;
  }

  return x;
}

/*
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 19
 *   Rating: 4
 */
int floatIsEqual(unsigned uf, unsigned ug)
{
  unsigned expFracMask = 0x7F800000; // bits 31..23 for exponent
  unsigned fracMask = 0x007FFFFF;    // bits 22..0 for fraction

  int ufIsNaN = ((uf & expFracMask) == expFracMask) && ((uf & fracMask) != 0);
  int ugIsNaN = ((ug & expFracMask) == expFracMask) && ((ug & fracMask) != 0);

  if (ufIsNaN || ugIsNaN)
  {
    return 0;
  }

  if (uf == ug)
  {
    return 1;
  }

  if (((uf & 0x7FFFFFFF) == 0) && ((ug & 0x7FFFFFFF) == 0))
  {
    return 1;
  }

  return 0;
}
