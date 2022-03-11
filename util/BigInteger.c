//
// Created by Matvey on 19.10.2020.
//
#include "BigInteger.h"

BigInteger bigint_new() {
    return bigint_new_cap(1);
}

BigInteger bigint_new_cap(size_t capacity) {
    BigInteger bi;
    bi.capacity = capacity;
    bi.data = malloc(sizeof(buff) * capacity);
    bigint_setZero(&bi);
    return bi;
}

BigInteger bigint_new_cpy(BigInteger other) {
    BigInteger bi = bigint_new_cap(other.capacity);
    bigint_set(&bi, other);
    return bi;
}
void toInt(char* c){
    if (*c + 1 > '0' && *c - 1 < '9') {
        *c -= '0';
    } else if (*c + 1 > 'a' && *c - 1 < 'z') {
        *c -= 'a' - 10;
    } else if (*c + 1 > 'A' && *c - 1 < 'Z') {
        *c -= 'A' - 10;
    }
}
void fromInt(int* c){
    if(*c < 10){
        *c += '0';
    }else{
        *c += 'A' - 10;
    }
}
BigInteger bigint_new_hex(char *str, size_t len) {
    size_t k = sizeof(buff) * 2;
    size_t cap = len / k + 1;
    BigInteger bi = bigint_new_cap(cap);
    size_t i;
    bi.sign = 1;
    size_t pos = 0;
    char c;
    for (i = 0; i < len; ++i) {
        c = str[len - i - 1];
        if (c == '-') {
            bi.sign = -bi.sign;
            continue;
        }
        toInt(&c);
        bi.data[pos / k] |= c << (4 * (pos % k));
        ++pos;
    }
    pos = 1;
    for (i = 0; i < cap; ++i) {
        if (bi.data[i] != 0) {
            pos = 0;
            break;
        }
    }
    if (pos)
        bi.sign = 0;
    return bi;
}
BigInteger bigint_new_sys(char* str, size_t len, unsigned char system){
    if(system == 16){
        return bigint_new_hex(str, len);
    }
    if(system < 2){
        system = 2;
    }
    BigInteger tmp = bigint_new();
    BigInteger tmp2 = bigint_new();
    BigInteger bi = bigint_new();
    tmp.sign = 1;
    bi.sign = 1;
    int isZero = 1;
    size_t i;
    for(i = 0; i < len; ++i){
        char c = str[i];
        if (c == '-') {
            bi.sign = -bi.sign;
            continue;
        }
        toInt(&c);
        tmp.data[0] = system;
        bigint_mul_tmp(&bi, tmp, &tmp2);
        if(c) {
            tmp.data[0] = c;
            bigint_addData(&bi, tmp);
            isZero = 0;
        }
    }
    if(isZero){
        bi.sign = 0;
    }
    bigint_free(tmp);
    bigint_free(tmp2);
    return bi;
}
BigInteger bigint_new_dec(char* str, size_t len){
    return bigint_new_sys(str, len, 10);
}
size_t divUp(size_t a, size_t b){
    return (a % b)?(a / b + 1):(a / b);
}
void bigint_setBitTrue(BigInteger* a, size_t pos){
    size_t bits = sizeof(buff) * 8;
    a->data[pos / bits] |= 1 << (pos % bits);
}
int bigint_getBit(BigInteger a, size_t pos){
    size_t bits = sizeof(buff) * 8;
    buff v = a.data[pos / bits];
    return (v >> (pos % bits)) & 0b1;
}
void bigint_free(BigInteger a) {
    free(a.data);
}
int compare_data(const BigInteger a, const BigInteger b) {
    int cap = a.capacity > b.capacity;
    size_t mincap = cap ? b.capacity : a.capacity;
    size_t maxcap = cap ? a.capacity : b.capacity;
    BigInteger c = cap ? a : b;
    size_t i;
    for (i = maxcap - 1; i > mincap; --i) {
        if (c.data[i] != 0) {
            return cap ? 1 : -1;
        }
    }
    for (i = 0; i < mincap; ++i) {
        maxcap = mincap - i - 1;
        if (a.data[maxcap] > b.data[maxcap]) {
            return 1;
        }
        if (a.data[maxcap] < b.data[maxcap])
            return -1;

    }
    return 0;
}

int bigint_compare(const BigInteger a, const BigInteger b) {
    if (a.sign < b.sign)
        return -1;
    if (a.sign > b.sign)
        return 1;
    if (a.sign == 0 && b.sign == 0)
        return 0;
    return compare_data(a, b) * a.sign;
}

int bigint_ensureCapacity(BigInteger *a, size_t cap) {
    if (a->capacity >= cap) {
        return BIGINT_SUCCESS;
    }
    buff *data = malloc(sizeof(buff) * cap);
    if (data == NULL) {
        return BIGINT_ERROR_MEMORY;
    }
    size_t i;
    for (i = 0; i < a->capacity; ++i) {
        data[i] = a->data[i];
    }
    for (; i < cap; ++i) {
        data[i] = 0;
    }
    a->capacity = cap;
    free(a->data);
    a->data = data;
    return BIGINT_SUCCESS;
}

char *bigint_toHexString(BigInteger a) {
    size_t k = sizeof(buff) * 2;
    char *str = malloc(a.capacity * k + 2);
    size_t i, j;
    size_t str_len = 0;
    size_t v;
    int started = 0;
    if (a.sign == 0) {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
    if (a.sign < 0) {
        str[str_len++] = '-';
    }
    int p;
    for (i = 0; i < a.capacity; ++i) {
        v = a.data[a.capacity - i - 1];
        for (j = 0; j < k; ++j) {
            p = (v >> (4 * (k - j - 1))) & 0xf;
            if (p != 0) {
                started = 1;
            } else {
                if (!started)
                    continue;
            }
            fromInt(&p);
            str[str_len++] = p;
        }
    }
    str[str_len] = '\0';
    return str;
}
char* bigint_toString(BigInteger a, unsigned char system){
    if(system < 2)
        system = 2;
    if(system == 16)
        return bigint_toHexString(a);
    size_t cap;
    if(system > 16)
        cap = a.capacity * sizeof(buff) * 2 + 2;
    else
        cap = a.capacity * sizeof(buff) * 8 + 2;
    char* str = malloc(sizeof(char) * cap);
    size_t str_len = 0;
    if (a.sign == 0) {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
    str[str_len++] = '\0';
    int sign = a.sign;
    a.sign = 1;
    BigInteger tmp = bigint_new_cpy(a);
    BigInteger tmp2 = bigint_new_cpy(a);
    BigInteger tmp3 = bigint_new();
    BigInteger tmp4 = bigint_new();
    BigInteger tmp5 = bigint_new();
    tmp5.data[0] = system;
    tmp5.sign = 1;
    while(tmp.sign != 0){
        bigint_set(&tmp2, tmp);
        bigint_div_tmp(&tmp2, tmp5, &tmp3, &tmp4);
        bigint_set(&tmp3, tmp2);
        bigint_mul_tmp(&tmp2, tmp5, &tmp4);
        bigint_subData(&tmp, tmp2);
        int v = tmp.data[0];
        bigint_set(&tmp, tmp3);
        fromInt(&v);
        str[str_len++] = v;
    }
    bigint_free(tmp);
    bigint_free(tmp2);
    bigint_free(tmp3);
    bigint_free(tmp4);
    bigint_free(tmp5);
    size_t i;
    if(sign == -1){
        str[str_len++] = '-';
    }
    for(i = 0; i < str_len / 2; ++i){
        char c = str[i];
        str[i] = str[str_len - i - 1];
        str[str_len - i - 1] = c;
    }
    return str;
}
char* bigint_toDecString(BigInteger a){
    return bigint_toString(a, 10);
}
void bigint_setZero(BigInteger *a) {
    size_t i;
    for (i = 0; i < a->capacity; ++i) {
        a->data[i] = 0;
    }
    a->sign = 0;
}

int bigint_set(BigInteger *a, BigInteger b) {
    if (bigint_ensureCapacity(a, b.capacity) == BIGINT_ERROR_MEMORY)
        return BIGINT_ERROR_MEMORY;
    size_t i;
    for (i = 0; i < b.capacity; ++i) {
        a->data[i] = b.data[i];
    }
    for (; i < a->capacity; ++i) {
        a->data[i] = 0;
    }
    a->sign = b.sign;
    return BIGINT_SUCCESS;
}

buff mid(buff a, buff b) {
    buff max = (a > b) ? a : b;
    buff min = (a > b) ? b : a;
    return (max - min) / 2 + min;
}

int addElement(buff *a, buff b) {
    buff tmp1 = *a;
    buff tmp = mid(tmp1, b);
    if (tmp < BIGINT_MAX_BUFF2) {
        *a += b;
        return 0;
    } else {
        if (tmp1 > b)
            tmp1 -= BIGINT_MAX_BUFF2;
        else
            b -= BIGINT_MAX_BUFF2;
        tmp = mid(tmp1, b);
        if (tmp < BIGINT_MAX_BUFF2) {
            *a = tmp1 + b - BIGINT_MAX_BUFF2;
        } else {
            if (tmp1 > b)
                tmp1 -= BIGINT_MAX_BUFF2;
            else
                b -= BIGINT_MAX_BUFF2;
            *a = tmp1 + b;
        }
        return 1;
    }
}

int subElement(buff *a, buff b) {
    buff tmp1 = *a;
    if (tmp1 < b) {
        b = BIGINT_MAX_BUFF2 - 1 + BIGINT_MAX_BUFF2 - b + 1;
        *a = b + tmp1;
        return 1;
    } else {
        *a -= b;
        return 0;
    }
}

size_t bigint_log2(BigInteger a) {
    size_t i;
    if (a.sign == 0)
        return 0;
    for (i = 0; i < a.capacity; ++i) {
        if (a.data[a.capacity - i - 1]) {
            i = a.capacity - i - 1;
            break;
        }
    }
    size_t j;
    for (j = 0; j < sizeof(buff) * 8; ++j) {
        if ((a.data[i] >> (8 * sizeof(buff) - j - 1)) & 0b1) {
            break;
        }
    }
    return sizeof(buff) * 8 * i + (sizeof(buff) * 8 - j - 1);
}

int bigint_addData(BigInteger *a, const BigInteger b) {
    size_t i;
    size_t loga = bigint_log2(*a), logb = bigint_log2(b);
    size_t max = (loga > logb) ? loga : logb;
    max += 2;
    if (bigint_ensureCapacity(a, divUp(max, 8*sizeof(buff))) == BIGINT_ERROR_MEMORY) {
        return BIGINT_ERROR_MEMORY;
    }
    size_t mincap = (a->capacity > b.capacity) ? b.capacity : a->capacity;
    int t = 0;
    for (i = 0; i < mincap; ++i) {
        if (t) t = addElement(&a->data[i], 1);
        t |= addElement(&a->data[i], b.data[i]);
    }
    while (t) {
        t = addElement(&a->data[i], 1);
        ++i;
    }
    return BIGINT_SUCCESS;
}

void bigint_subData(BigInteger *big, BigInteger small) {
    size_t i;
    int t = 0;
    for (i = 0; i < small.capacity; ++i) {
        if (t) t = subElement(&big->data[i], 1);
        t |= subElement(&big->data[i], small.data[i]);
    }
    while (t) {
        t = subElement(&big->data[i], 1);
        ++i;
    }
}

int bigint_add(BigInteger *a, BigInteger b) {
    if (b.sign == 0)
        return BIGINT_SUCCESS;
    if (a->sign == 0) {
        return bigint_set(a, b);
    }
    if (a->sign == b.sign) {
        return bigint_addData(a, b);
    }
    int c = compare_data(*a, b);
    if (c < 0) {
        BigInteger tmp = bigint_new_cpy(b);
        bigint_subData(&tmp, *a);
        c = bigint_set(a, tmp);
        a->sign = b.sign;
        bigint_free(tmp);
        return c;
    } else {
        bigint_subData(a, b);
        if (c == 0)
            a->sign = 0;
        return BIGINT_SUCCESS;
    }
}

int big_add(BigInteger *a, BigInteger b, BigInteger *tmp) {
    if (b.sign == 0)
        return BIGINT_SUCCESS;
    if (a->sign == 0) {
        return bigint_set(a, b);
    }
    if (a->sign == b.sign) {
        return bigint_addData(a, b);
    }
    int c = compare_data(*a, b);
    if (c < 0) {
        bigint_set(tmp, b);
        bigint_subData(tmp, *a);
        c = bigint_set(a, *tmp);
        a->sign = b.sign;
        return c;
    } else {
        bigint_subData(a, b);
        if (c == 0)
            a->sign = 0;
        return BIGINT_SUCCESS;
    }
}

int big_sub(BigInteger *a, BigInteger b, BigInteger *tmp) {
    b.sign = -b.sign;
    return big_add(a, b, tmp);
}

int bigint_sub(BigInteger *a, BigInteger b) {
    b.sign = -b.sign;
    return bigint_add(a, b);
}

int bigint_moveLeft(BigInteger *a, long len) {
    if(len == 0)
        return BIGINT_SUCCESS;
    size_t log2 = bigint_log2(*a);
    if (len < 0 && log2 < -len) {
        bigint_setZero(a);
        return BIGINT_SUCCESS;
    }
    size_t bits = 8 * sizeof(buff);
    size_t i;
    size_t size = divUp(log2 + 1, bits);
    if (len < 0) {
        len = -len;
        size_t buffs = len / bits;
        size_t delta = len % bits;
        if(buffs) {
            for (i = 0; i < size - buffs; ++i) {
                a->data[i] = a->data[i + buffs];
            }
            for (; i < size; ++i) {
                a->data[i] = 0;
            }
        }
        if(delta == 0)
            return BIGINT_SUCCESS;
        size -= buffs;
        for (i = 0; i < size - 1; ++i) {
            a->data[i] = (a->data[i] >> delta) | (a->data[i + 1] << (bits - delta));
        }
        a->data[i] = a->data[i] >> delta;
    }else{
        if(bigint_ensureCapacity(a, divUp(log2 + len + 1, bits)) == BIGINT_ERROR_MEMORY){
            return BIGINT_ERROR_MEMORY;
        }
        size_t buffs = len / bits;
        size_t delta = len % bits;
        if(buffs){
            for(i = 0; i < size; ++i){
                a->data[size + buffs - i - 1] = a->data[size - i - 1];
            }
            for(i = 0; i < buffs; ++i){
                a->data[i] = 0;
            }
        }
        if(delta == 0)
            return BIGINT_SUCCESS;
        for(i = 0; i < size; ++i){
            a->data[size + buffs - i] = (a->data[size + buffs - i] << delta) | (a->data[size + buffs - i - 1] >> (bits - delta));
        }
        a->data[buffs] = a->data[buffs] << delta;
    }
    return BIGINT_SUCCESS;
}
void bigint_and(BigInteger* a, BigInteger b){
    size_t i;
    if(a->capacity > b.capacity){
        for(i = b.capacity; i < a->capacity; ++i){
            a->data[i] = 0;
        }
    }
    size_t minCap = (b.capacity < a->capacity)?b.capacity:a->capacity;
    for(i = 0; i < minCap; ++i){
        a->data[i] &= b.data[i];
    }
}
int bigint_or(BigInteger* a, BigInteger b){
    if(bigint_ensureCapacity(a, b.capacity) == BIGINT_ERROR_MEMORY){
        return BIGINT_ERROR_MEMORY;
    }
    size_t i;
    for(i = 0; i < b.capacity; ++i){
        a->data[i] |= b.data[i];
    }
    return BIGINT_SUCCESS;
}
int bigint_xor(BigInteger* a, BigInteger b){
    if(bigint_ensureCapacity(a, b.capacity) == BIGINT_ERROR_MEMORY){
        return BIGINT_ERROR_MEMORY;
    }
    size_t i;
    for(i = 0; i < b.capacity; ++i){
        a->data[i] ^= b.data[i];
    }
    return BIGINT_SUCCESS;
}
int bigint_mul_notZero(BigInteger* a, BigInteger b, BigInteger* tmp){
    size_t bits = sizeof(buff) * 8;
    size_t loga = bigint_log2(*a);
    size_t logb = bigint_log2(b);
    int sign = a->sign * b.sign;
    size_t cap = divUp(loga + logb + 2, bits);
    if(bigint_ensureCapacity(a, cap) == BIGINT_ERROR_MEMORY || bigint_ensureCapacity(tmp, cap) == BIGINT_ERROR_MEMORY){
        return BIGINT_ERROR_MEMORY;
    }
    bigint_set(tmp, *a);
    bigint_setZero(a);
    size_t i;
    size_t delta = 0;
    for(i = 0; i < logb + 1; ++i){
        int t = bigint_getBit(b, i);
        if(t){
            bigint_moveLeft(tmp, delta);
            bigint_addData(a, *tmp);
            delta = 0;
        }
        ++delta;
    }
    a->sign = sign;
    return BIGINT_SUCCESS;
}
int bigint_mul_tmp(BigInteger* a, BigInteger b, BigInteger* tmp){
    if(a->sign == 0){
        return BIGINT_SUCCESS;
    }else if(b.sign == 0){
        bigint_setZero(a);
        return BIGINT_SUCCESS;
    }
    int ret =  bigint_mul_notZero(a, b, tmp);
    return ret;
}
int bigint_mul(BigInteger* a, BigInteger b){
    if(a->sign == 0){
        return BIGINT_SUCCESS;
    }else if(b.sign == 0){
        bigint_setZero(a);
        return BIGINT_SUCCESS;
    }
    BigInteger tmp = bigint_new_cap(1);
    int ret =  bigint_mul_notZero(a, b, &tmp);
    bigint_free(tmp);
    return ret;
}
int bigint_div_notZero(BigInteger* a, BigInteger b, BigInteger* tmp, BigInteger* tmp2, size_t loga, size_t logb){
    int sign = a->sign * b.sign;
    a->sign = 1;
    b .sign = 1;
    bigint_set(tmp, b);
    bigint_set(tmp2, *a);
    bigint_setZero(a);
    size_t mv = loga - logb + 1;
    bigint_moveLeft(tmp, mv - 1);
    size_t i;
    int isZero = 1;
    for(i = 0; i < mv; ++i){
        int c = compare_data(*tmp2, *tmp);
        if(c >= 0){
            isZero = 0;
            bigint_setBitTrue(a, mv - i - 1);
            if(c == 0){
                break;
            }else {
                bigint_subData(tmp2, *tmp);
            }
        }
        bigint_moveLeft(tmp, -1);
    }
    if(isZero){
        a->sign = 0;
    }else{
        a->sign = sign;
    }
    return BIGINT_SUCCESS;
}
int bigint_div_tmp(BigInteger* a, BigInteger b, BigInteger* tmp1, BigInteger* tmp2){
    if(b.sign == 0)
        return BIGINT_ERROR_DIVIDE_BY_ZERO;
    if(a->sign == 0)
        return BIGINT_SUCCESS;
    size_t loga = bigint_log2(*a);
    size_t logb = bigint_log2(b);
    if(loga < logb){
        bigint_setZero(a);
        return BIGINT_SUCCESS;
    }
    int ret = bigint_div_notZero(a, b, tmp1, tmp2, loga, logb);
    return ret;
}
int bigint_div(BigInteger* a, BigInteger b){
    if(b.sign == 0)
        return BIGINT_ERROR_DIVIDE_BY_ZERO;
    if(a->sign == 0)
        return BIGINT_SUCCESS;
    size_t loga = bigint_log2(*a);
    size_t logb = bigint_log2(b);
    if(loga < logb){
        bigint_setZero(a);
        return BIGINT_SUCCESS;
    }
    BigInteger tmp = bigint_new_cap(divUp(loga+1, sizeof(buff) * 8));
    BigInteger tmp2 = bigint_new_cap(tmp.capacity);
    int ret = bigint_div_notZero(a, b, &tmp, &tmp2, loga, logb);
    bigint_free(tmp);
    bigint_free(tmp2);
    return ret;
}
int bigint_mod_notZero(BigInteger*a, BigInteger b, BigInteger* tmp1, BigInteger* tmp2, BigInteger* tmp3){
    bigint_set(tmp1, *a);
    int ret = bigint_div_tmp(tmp1, b, tmp2, tmp3);
    if(ret != BIGINT_SUCCESS){
        return ret;
    }
    ret = bigint_mul_tmp(tmp1, b, tmp2);
    if(ret != BIGINT_SUCCESS){
        return ret;
    }
    bigint_sub(a, *tmp1);
    return BIGINT_SUCCESS;
}
int bigint_mod(BigInteger* a, BigInteger b){
    if(b.sign == 0){
        return BIGINT_ERROR_DIVIDE_BY_ZERO;
    }
    if(a->sign == 0){
        return BIGINT_SUCCESS;
    }
    size_t loga = bigint_log2(*a);
    size_t logb = bigint_log2(b);
    if(loga < logb){
        return BIGINT_SUCCESS;
    }
    BigInteger tmp = bigint_new_cap(divUp(loga+1, sizeof(buff) * 8));
    BigInteger tmp2 = bigint_new_cap(tmp.capacity);
    BigInteger tmp3 = bigint_new_cap(tmp.capacity);
    int ret = bigint_mod_notZero(a, b, &tmp, &tmp2, &tmp3);
    bigint_free(tmp);
    bigint_free(tmp2);
    bigint_free(tmp3);
    return ret;
}
int bigint_mod_tmp(BigInteger* a, BigInteger b, BigInteger* tmp1, BigInteger* tmp2, BigInteger* tmp3){
    if(b.sign == 0){
        return BIGINT_ERROR_DIVIDE_BY_ZERO;
    }
    if(a->sign == 0){
        return BIGINT_SUCCESS;
    }
    size_t loga = bigint_log2(*a);
    size_t logb = bigint_log2(b);
    if(loga < logb){
        return BIGINT_SUCCESS;
    }
    int ret = bigint_mod_notZero(a, b, tmp1, tmp2, tmp3);
    return ret;
}
