//
// Created by Matvey on 19.10.2020.
//
#include <stdlib.h>
#include <limits.h>
#ifndef MATH_BIGINTEGER_H
#define MATH_BIGINTEGER_H

#endif //MATH_BIGINTEGER_H
#define BIGINT_ERROR_MEMORY 0
#define BIGINT_SUCCESS 1
#define BIGINT_ERROR_DIVIDE_BY_ZERO 2

#define BIGINT_MAX_BUFF2 ((UCHAR_MAX >> 1) + 1)
typedef unsigned char buff; // element of buffer, use only unsigned values here
typedef struct BigInteger{
    int sign;
    buff* data;
    size_t capacity;
} BigInteger;

BigInteger bigint_new(); // returns new zero BigInteger with capacity 1 (buffer size)
BigInteger bigint_new_cap(size_t capacity);// returns new zero BigInteger with given capacity
BigInteger bigint_new_cpy(BigInteger other);// returns copy of given BigInteger (with the same sign, value and capacity)

BigInteger bigint_new_hex(char* str, size_t len);// returns new BigInteger with value of числа в шестнадцатиричной системе
BigInteger bigint_new_sys(char* str, size_t len, unsigned char system); // returns new BigInteger with value of number in given number system
BigInteger bigint_new_dec(char* str, size_t len);// returns new BigInteger with value of given decimal number
int bigint_set(BigInteger* a, BigInteger b);// fully assigns value of b to a, doesn't decrease capacity of b
void bigint_setZero(BigInteger* a);//assigns 0 to a, doesn't decrease capacity

int bigint_ensureCapacity(BigInteger* a, size_t capacity);//makes capacity of a at least given capacity

int bigint_compare(const BigInteger a, const BigInteger b);//compares two big integers, 0 if equal, 1 if a > b, -1 if b > a

size_t bigint_log2(BigInteger a);//logarithm of a with basis 2, just position of first '1' in binary notation

int bigint_add(BigInteger* a, BigInteger b);//assigns a+b to a
int bigint_sub(BigInteger* a, BigInteger b);//assigns a-b to a
int bigint_mul(BigInteger* a, BigInteger b);//assigns a*b to a
int bigint_div(BigInteger* a, BigInteger b);//assigns a/b to a, b isn't 0
int bigint_mod(BigInteger* a, BigInteger b);//assigns a%b to a, b isn't 0

int bigint_addData(BigInteger* a, BigInteger b);//sum of a and b, but ignore signs, sign of a doesn't change
void bigint_subData(BigInteger* a, BigInteger b);//assigns difference between a and b to a, but ignore signs and a >= b, sign of a doesn't change (value can be 0, but sign 1)
int bigint_mul_tmp(BigInteger* a, BigInteger b, BigInteger* tmp);//assigns a*b to a, but for speed use the same tmp value for different operations
int bigint_div_tmp(BigInteger* a, BigInteger b, BigInteger* tmp1, BigInteger* tmp2);//logic is the same as in mul_tmp
int bigint_mod_tmp(BigInteger* a, BigInteger b, BigInteger* tmp1, BigInteger* tmp2, BigInteger* tmp3);// the same

void bigint_setBitTrue(BigInteger* a, size_t pos);//sets one bit '1' in given position
int bigint_getBit(BigInteger a, size_t pos);//returns bit in given position. Don't exit from allocated array!

void bigint_and(BigInteger* a, BigInteger b);//binary operation and - a & b
int bigint_or(BigInteger* a, BigInteger b);//binary operation or - a | b
int bigint_xor(BigInteger* a, BigInteger b);//binary operation or - a | b
int bigint_moveLeft(BigInteger* a, long len);//binary operation move - a << len, len can be < 0

char* bigint_toHexString(BigInteger a);//returns string in hex number system
char* bigint_toString(BigInteger a, unsigned char system);//returns string in given number system
char* bigint_toDecString(BigInteger a);//returns string in given number system

void bigint_free(BigInteger a);//disposes BigInteger