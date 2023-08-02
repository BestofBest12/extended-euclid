#include <stdio.h>
#include <stdlib.h>
#include <openssl/bn.h>

// Helper function to initialize a BIGNUM variable with a value
void initBignum(BIGNUM **bn, const char *value) {
    if (*bn == NULL) {
        *bn = BN_new();
    }
    BN_dec2bn(bn, value);
}

// Helper function to print a BIGNUM variable
void printBN(const char *label, const BIGNUM *bn) {
    char *str = BN_bn2dec(bn);
    printf("%s%s\n", label, str);
    OPENSSL_free(str);
}

BIGNUM *XEuclid(BIGNUM *x, BIGNUM *y, const BIGNUM *a, const BIGNUM *b) {
    BIGNUM *gcd = BN_new();
    BIGNUM *x0 = BN_new();
    BIGNUM *x1 = BN_new();
    BIGNUM *y0 = BN_new();
    BIGNUM *y1 = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *r = BN_new();
    BIGNUM *temp = BN_new();

    BN_set_word(x0, 1);
    BN_set_word(y1, 1);

    BN_copy(x1, BN_value_one());
    BN_copy(y0, BN_value_one());

    BN_copy(x, BN_value_one());
    BN_copy(y, BN_value_one());

    BN_copy(gcd, a);

    while (!BN_is_zero(b)) {
        BN_div(q, r, gcd, b, BN_CTX_new());
        BN_copy(gcd, b);
        BN_copy(b, r);

        // Update x and y values
        BN_mul(temp, q, x1, BN_CTX_new());
        BN_sub(x, x0, temp);

        BN_mul(temp, q, y1, BN_CTX_new());
        BN_sub(y, y0, temp);

        // Update x0, x1, y0, y1 for the next iteration
        BN_copy(x0, x1);
        BN_copy(x1, x);

        BN_copy(y0, y1);
        BN_copy(y1, y);
    }


    // Make sure x is positive
    if (BN_is_negative(x)) {
        BN_add(x, x, a);
    }

    BN_free(x0);
    BN_free(x1);
    BN_free(y0);
    BN_free(y1);
    BN_free(q);
    BN_free(r);
    BN_free(temp);

    return gcd;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("usage: xeuclid num1 num2\n");
        return -1;
    }

    BIGNUM *a = NULL;
    BIGNUM *b = NULL;
    BIGNUM *x = BN_new();
    BIGNUM *y = BN_new();
    BIGNUM *gcd = NULL;

    initBignum(&a, argv[1]);
    initBignum(&b, argv[2]);
    gcd = XEuclid(x, y, a, b);

    printBN("(a, b) = ", gcd);
    printBN("a = ", a);
    printBN("b = ", b);
    printBN("x = ", x);
    printBN("y = ", y);
    printf("%s*(%s) + %s*(%s) = %s\n", BN_bn2dec(a), BN_bn2dec(x), BN_bn2dec(b), BN_bn2dec(y), BN_bn2dec(gcd));

    BN_free(a);
    BN_free(b);
    BN_free(x);
    BN_free(y);
    BN_free(gcd);

    return 0;
}
