/*
 * testbip.c -- test the big integer processor
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigint.h"


/**************************************************************/


void dump(char *prefix, ObjRef x, char *suffix) {
  if (prefix != NULL && *prefix != '\0') {
    printf("%s", prefix);
  }
  bigDump(stdout, x);
  if (suffix != NULL && *suffix != '\0') {
    printf("%s", suffix);
  }
}


/**************************************************************/


void test00(void) {
  bigFromInt(0);
  dump("+0x00000000 = ", bip.res, "\n");

  bigFromInt(1);
  dump("+0x00000001 = ", bip.res, "\n");

  bigFromInt(2);
  dump("+0x00000002 = ", bip.res, "\n");

  bigFromInt(0x12);
  dump("+0x00000012 = ", bip.res, "\n");

  bigFromInt(0x123);
  dump("+0x00000123 = ", bip.res, "\n");

  bigFromInt(0x1234);
  dump("+0x00001234 = ", bip.res, "\n");

  bigFromInt(0x12345);
  dump("+0x00012345 = ", bip.res, "\n");

  bigFromInt(0x123456);
  dump("+0x00123456 = ", bip.res, "\n");

  bigFromInt(0x1234567);
  dump("+0x01234567 = ", bip.res, "\n");

  bigFromInt(0x12345678);
  dump("+0x12345678 = ", bip.res, "\n");

  bigFromInt(-0);
  dump("-0x00000000 = ", bip.res, "\n");

  bigFromInt(-1);
  dump("-0x00000001 = ", bip.res, "\n");

  bigFromInt(-2);
  dump("-0x00000002 = ", bip.res, "\n");

  bigFromInt(-0x12);
  dump("-0x00000012 = ", bip.res, "\n");

  bigFromInt(-0x123);
  dump("-0x00000123 = ", bip.res, "\n");

  bigFromInt(-0x1234);
  dump("-0x00001234 = ", bip.res, "\n");

  bigFromInt(-0x12345);
  dump("-0x00012345 = ", bip.res, "\n");

  bigFromInt(-0x123456);
  dump("-0x00123456 = ", bip.res, "\n");

  bigFromInt(-0x1234567);
  dump("-0x01234567 = ", bip.res, "\n");

  bigFromInt(-0x12345678);
  dump("-0x12345678 = ", bip.res, "\n");
}


/**************************************************************/


void test01(void) {
  bigFromInt(0);
  bip.op1 = bip.res;
  printf("sign(+0x00000000) = %d\n", bigSgn());

  bigFromInt(1);
  bip.op1 = bip.res;
  printf("sign(+0x00000001) = %d\n", bigSgn());

  bigFromInt(2);
  bip.op1 = bip.res;
  printf("sign(+0x00000002) = %d\n", bigSgn());

  bigFromInt(0x12);
  bip.op1 = bip.res;
  printf("sign(+0x00000012) = %d\n", bigSgn());

  bigFromInt(0x123);
  bip.op1 = bip.res;
  printf("sign(+0x00000123) = %d\n", bigSgn());

  bigFromInt(0x1234);
  bip.op1 = bip.res;
  printf("sign(+0x00001234) = %d\n", bigSgn());

  bigFromInt(0x12345);
  bip.op1 = bip.res;
  printf("sign(+0x00012345) = %d\n", bigSgn());

  bigFromInt(0x123456);
  bip.op1 = bip.res;
  printf("sign(+0x00123456) = %d\n", bigSgn());

  bigFromInt(0x1234567);
  bip.op1 = bip.res;
  printf("sign(+0x01234567) = %d\n", bigSgn());

  bigFromInt(0x12345678);
  bip.op1 = bip.res;
  printf("sign(+0x12345678) = %d\n", bigSgn());

  bigFromInt(-0);
  bip.op1 = bip.res;
  printf("sign(-0x00000000) = %d\n", bigSgn());

  bigFromInt(-1);
  bip.op1 = bip.res;
  printf("sign(-0x00000001) = %d\n", bigSgn());

  bigFromInt(-2);
  bip.op1 = bip.res;
  printf("sign(-0x00000002) = %d\n", bigSgn());

  bigFromInt(-0x12);
  bip.op1 = bip.res;
  printf("sign(-0x00000012) = %d\n", bigSgn());

  bigFromInt(-0x123);
  bip.op1 = bip.res;
  printf("sign(-0x00000123) = %d\n", bigSgn());

  bigFromInt(-0x1234);
  bip.op1 = bip.res;
  printf("sign(-0x00001234) = %d\n", bigSgn());

  bigFromInt(-0x12345);
  bip.op1 = bip.res;
  printf("sign(-0x00012345) = %d\n", bigSgn());

  bigFromInt(-0x123456);
  bip.op1 = bip.res;
  printf("sign(-0x00123456) = %d\n", bigSgn());

  bigFromInt(-0x1234567);
  bip.op1 = bip.res;
  printf("sign(-0x01234567) = %d\n", bigSgn());

  bigFromInt(-0x12345678);
  bip.op1 = bip.res;
  printf("sign(-0x12345678) = %d\n", bigSgn());
}


/**************************************************************/


void test02(void) {
  int m[7];
  ObjRef n[7];
  int i, j;
  int res;

  m[0] = 0;
  bigFromInt(m[0]);
  n[0] = bip.res;
  printf("n[0] = %d\n", m[0]);

  m[1] = 100;
  bigFromInt(m[1]);
  n[1] = bip.res;
  printf("n[1] = %d\n", m[1]);

  m[2] = -100;
  bigFromInt(m[2]);
  n[2] = bip.res;
  printf("n[2] = %d\n", m[2]);

  m[3] = 101;
  bigFromInt(m[3]);
  n[3] = bip.res;
  printf("n[3] = %d\n", m[3]);

  m[4] = -101;
  bigFromInt(m[4]);
  n[4] = bip.res;
  printf("n[4] = %d\n", m[4]);

  m[5] = 12345678;
  bigFromInt(m[5]);
  n[5] = bip.res;
  printf("n[5] = %d\n", m[5]);

  m[6] = -12345678;
  bigFromInt(m[6]);
  n[6] = bip.res;
  printf("n[6] = %d\n", m[6]);

  for (i = 0; i < 7; i++) {
    for (j = 0; j < 7; j++) {
      printf("%12d ", m[i]);
      bip.op1 = n[i];
      bip.op2 = n[j];
      res = bigCmp();
      if (res < 0) {
        printf("<");
      } else
      if (res > 0) {
        printf(">");
      } else {
        printf("=");
      }
      printf(" %12d", m[j]);
      printf("\n");
    }
  }
}


/**************************************************************/


void test03(void) {
  bigFromInt(0);
  bip.op1 = bip.res;
  bigNeg();
  dump("+n = ", bip.op1, "\n");
  dump("-n = ", bip.res, "\n");

  bigFromInt(1);
  bip.op1 = bip.res;
  bigNeg();
  dump("+n = ", bip.op1, "\n");
  dump("-n = ", bip.res, "\n");

  bigFromInt(-1);
  bip.op1 = bip.res;
  bigNeg();
  dump("+n = ", bip.op1, "\n");
  dump("-n = ", bip.res, "\n");

  bigFromInt(0x12345678);
  bip.op1 = bip.res;
  bigNeg();
  dump("+n = ", bip.op1, "\n");
  dump("-n = ", bip.res, "\n");

  bigFromInt(-0x12345678);
  bip.op1 = bip.res;
  bigNeg();
  dump("+n = ", bip.op1, "\n");
  dump("-n = ", bip.res, "\n");
}


/**************************************************************/


void test04(void) {
  int m[6];
  ObjRef n[6];
  int i, j;

  m[0] = +0x12345679;
  m[1] = +0x12345678;
  m[2] = +0x12345677;
  m[3] = -0x12345677;
  m[4] = -0x12345678;
  m[5] = -0x12345679;

  for (i = 0; i < 6; i++) {
    bigFromInt(m[i]);
    n[i] = bip.res;
  }

  for (i = 0; i < 6; i++) {
    for (j = 0; j < 6; j++) {
      bip.op1 = n[i];
      bip.op2 = n[j];
      bigAdd();
      printf("%12d + %12d = ", m[i], m[j]);
      dump("", bip.res, "\n");
    }
  }
}


/**************************************************************/


void test05(void) {
  int m[5];
  ObjRef n[5];
  int i, j;

  m[0] = +0x12345678;
  m[1] = +1;
  m[2] = 0;
  m[3] = -1;
  m[4] = -0x12345678;

  for (i = 0; i < 5; i++) {
    bigFromInt(m[i]);
    n[i] = bip.res;
  }

  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      bip.op1 = n[i];
      bip.op2 = n[j];
      bigAdd();
      printf("%12d + %12d = ", m[i], m[j]);
      dump("", bip.res, "\n");
    }
  }
}


/**************************************************************/


void test06(void) {
  int m[6];
  ObjRef n[6];
  int i, j;

  m[0] = +0x12345679;
  m[1] = +0x12345678;
  m[2] = +0x12345677;
  m[3] = -0x12345677;
  m[4] = -0x12345678;
  m[5] = -0x12345679;

  for (i = 0; i < 6; i++) {
    bigFromInt(m[i]);
    n[i] = bip.res;
  }

  for (i = 0; i < 6; i++) {
    for (j = 0; j < 6; j++) {
      bip.op1 = n[i];
      bip.op2 = n[j];
      bigSub();
      printf("%12d - %12d = ", m[i], m[j]);
      dump("", bip.res, "\n");
    }
  }
}


/**************************************************************/


void test07(void) {
  int m[5];
  ObjRef n[5];
  int i, j;

  m[0] = +0x12345678;
  m[1] = +1;
  m[2] = 0;
  m[3] = -1;
  m[4] = -0x12345678;

  for (i = 0; i < 5; i++) {
    bigFromInt(m[i]);
    n[i] = bip.res;
  }

  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      bip.op1 = n[i];
      bip.op2 = n[j];
      bigSub();
      printf("%12d - %12d = ", m[i], m[j]);
      dump("", bip.res, "\n");
    }
  }
}


/**************************************************************/


void test08(void) {
  int i;

  bigFromInt(1);
  for (i = 1; i < 100; i++) {
    bip.op1 = bip.res;
    bip.op2 = bip.res;
    bigAdd();
    printf("2 ^ %2d = ", i);
    dump("", bip.res, "\n");
  }
}


/**************************************************************/


void test09(void) {
  int i, j;

  bigFromInt(2);
  bip.op2 = bip.res;
  for (i = 1; i < 10; i++) {
    bip.res = bip.op2;
    for (j = 1; j < i * i; j++) {
      bip.op1 = bip.res;
      bigMul();
    }
    printf("2 ^ (%d ^ 2) = ", i);
    dump("", bip.res, "\n");
  }
}


/**************************************************************/


void factorial(int n) {
  bigFromInt(1);
  while (n > 0) {
    bip.op1 = bip.res;
    bigFromInt(n);
    bip.op2 = bip.res;
    bigMul();
    n--;
  }
}


void test10(void) {
  int i;

  for (i = 0; i < 100; i++) {
    factorial(i);
    printf("%2d! = ", i);
    dump("", bip.res, "\n");
  }
}


/**************************************************************/


void test11(void) {
  int n, m;

  n = 5;
  m = 0;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");
}


/**************************************************************/


void test12(void) {
  int n, m;

  n = 12;
  m = 12345678;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = 12345677;
  m = 12345678;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = -12;
  m = 12345678;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = -12345677;
  m = 12345678;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = 12;
  m = -12345678;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = 12345677;
  m = -12345678;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = -12;
  m = -12345678;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = -12345677;
  m = -12345678;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");
}


/**************************************************************/


void test13(void) {
  int n, m;

  n = 12345678;
  m = 1;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = 12345678;
  m = 17;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = 12345678;
  m = 255;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = -12345678;
  m = 1;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = -12345678;
  m = 17;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = -12345678;
  m = 255;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = 12345678;
  m = -1;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = 12345678;
  m = -17;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = 12345678;
  m = -255;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = -12345678;
  m = -1;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = -12345678;
  m = -17;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  n = -12345678;
  m = -255;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");
}


/**************************************************************/


void test14(void) {
  int n, m;
  ObjRef dividend;
  ObjRef divisor;
  int ok;

  printf("divisor");
  for (m = 0; m < 256; m++) {
    if (m % 8 == 0) {
      printf("\n%3d to %3d:   ", m, m + 7);
    }
    if (m == 0) {
      printf(" ");
      fflush(stdout);
      continue;
    }
    bigFromInt(m);
    divisor = bip.res;
    ok = 1;
    for (n = 0; n < (1 << 18); n++) {
      bigFromInt(n);
      dividend = bip.res;
      bip.op1 = dividend;
      bip.op2 = divisor;
      bigDiv();
      bip.op1 = bip.res;
      bigMul();
      free(bip.op1);
      bip.op1 = bip.res;
      bip.op2 = bip.rem;
      bigAdd();
      free(bip.op1);
      free(bip.op2);
      bip.op1 = bip.res;
      bip.op2 = dividend;
      if (bigCmp() != 0) {
        ok = 0;
      }
      free(bip.op1);
      free(dividend);
    }
    free(divisor);
    printf("%c", ok ? '.' : '?');
    fflush(stdout);
  }
  printf("\n");
}


/**************************************************************/


void test15(void) {
  int n, m;

  n = 123456789;
  m = (0xFF << 16) + 0x1234;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  printf("--------------------------------------------------\n");

  n = 123456789;
  m = (0x80 << 16) + 0x1234;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  printf("--------------------------------------------------\n");

  n = 123456789;
  m = (0x7F << 16) + 0x1234;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  printf("--------------------------------------------------\n");

  n = 123456789;
  m = (0x55 << 16) + 0x1234;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  printf("--------------------------------------------------\n");

  n = 123456789;
  m = (0x2F << 16) + 0x1234;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  printf("--------------------------------------------------\n");

  n = 123456789;
  m = (0x18 << 16) + 0x1234;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  printf("--------------------------------------------------\n");

  n = 123456789;
  m = (0x0A << 16) + 0x1234;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  printf("--------------------------------------------------\n");

  n = 123456789;
  m = (0x03 << 16) + 0x1234;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  printf("--------------------------------------------------\n");

  n = 123456789;
  m = (0x02 << 16) + 0x1234;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");

  printf("--------------------------------------------------\n");

  n = 123456789;
  m = (0x01 << 16) + 0x1234;
  bigFromInt(n);
  bip.op1 = bip.res;
  bigFromInt(m);
  bip.op2 = bip.res;
  bigDiv();
  printf("%12d / %12d = ", n, m);
  dump("", bip.res, "\n");
  printf("%12d %% %12d = ", n, m);
  dump("", bip.rem, "\n");
}


/**************************************************************/


void test16(void) {
  int n1, n2, n3, m;

  n1 = 0x12345678;
  n2 = 0x66554433;
  n3 = 12;
  bigFromInt(n1);
  bip.op1 = bip.res;
  bigFromInt(n2);
  bip.op2 = bip.res;
  bigMul();
  bip.op1 = bip.res;
  bigFromInt(n3);
  bip.op2 = bip.res;
  bigMul();
  bip.op1 = bip.res;
  m = 0x5764;
  bigFromInt(m);
  bip.op2 = bip.res;
  dump("", bip.op1, " / ");
  dump("", bip.op2, " =\n");
  bigDiv();
  dump("", bip.res, " R. ");
  dump("", bip.rem, "\n");
  bip.op1 = bip.res;
  bigMul();
  bip.op1 = bip.res;
  bip.op2 = bip.rem;
  bigAdd();
  dump("quotient * divisor + remainder =\n", bip.res, "\n");
}


/**************************************************************/


void test17(void) {
  /* prepare two big integers with 8 and 4 digits, respectively */
  bigFromInt(0x11111111);
  bip.op1 = bip.res;
  bip.op2 = bip.res;
  bigMul();
  bip.op1 = bip.res;
  /* set all 8 digits of dividend */
  bip.op1->data[5 + 0] = 0xF2;
  bip.op1->data[5 + 1] = 0xFB;
  bip.op1->data[5 + 2] = 0xE3;
  bip.op1->data[5 + 3] = 0x46;
  bip.op1->data[5 + 4] = 0x7C;
  bip.op1->data[5 + 5] = 0xC2;
  bip.op1->data[5 + 6] = 0x54;
  bip.op1->data[5 + 7] = 0xF8;
  /* set all 4 digits of divisor */
  bip.op2->data[5 + 0] = 0x1B;
  bip.op2->data[5 + 1] = 0xE8;
  bip.op2->data[5 + 2] = 0xE7;
  bip.op2->data[5 + 3] = 0x8D;
  /* divide */
  dump("", bip.op1, " / ");
  dump("", bip.op2, " =\n");
  bigDiv();
  dump("", bip.res, " R. ");
  dump("", bip.rem, "\n");
  /* verify */
  bip.op1 = bip.res;
  bigMul();
  bip.op1 = bip.res;
  bip.op2 = bip.rem;
  bigAdd();
  dump("quotient * divisor + remainder =\n", bip.res, "\n");
}


/**************************************************************/


void test18(void) {
  /* prepare two big integers with 8 and 4 digits, respectively */
  bigFromInt(0x11111111);
  bip.op1 = bip.res;
  bip.op2 = bip.res;
  bigMul();
  bip.op1 = bip.res;
  /* set all 8 digits of dividend */
  bip.op1->data[5 + 0] = 0x4D;
  bip.op1->data[5 + 1] = 0xCC;
  bip.op1->data[5 + 2] = 0x8C;
  bip.op1->data[5 + 3] = 0x18;
  bip.op1->data[5 + 4] = 0x34;
  bip.op1->data[5 + 5] = 0xDF;
  bip.op1->data[5 + 6] = 0x1D;
  bip.op1->data[5 + 7] = 0xFD;
  /* set all 4 digits of divisor */
  bip.op2->data[5 + 0] = 0x69;
  bip.op2->data[5 + 1] = 0xF4;
  bip.op2->data[5 + 2] = 0x94;
  bip.op2->data[5 + 3] = 0x37;
  /* divide */
  dump("", bip.op1, " / ");
  dump("", bip.op2, " =\n");
  bigDiv();
  dump("", bip.res, " R. ");
  dump("", bip.rem, "\n");
  /* verify */
  bip.op1 = bip.res;
  bigMul();
  bip.op1 = bip.res;
  bip.op2 = bip.rem;
  bigAdd();
  dump("quotient * divisor + remainder =\n", bip.res, "\n");
}


/**************************************************************/


void test19(void) {
  int n, m;

  n = 0x7FFFFFFF;
  bigFromInt(n);
  bip.op1 = bip.res;
  m = bigToInt();
  printf("%12d = %12d\n", n, m);

  n = 0x00000001;
  bigFromInt(n);
  bip.op1 = bip.res;
  m = bigToInt();
  printf("%12d = %12d\n", n, m);

  n = 0x00000000;
  bigFromInt(n);
  bip.op1 = bip.res;
  m = bigToInt();
  printf("%12d = %12d\n", n, m);

  n = -0x00000001;
  bigFromInt(n);
  bip.op1 = bip.res;
  m = bigToInt();
  printf("%12d = %12d\n", n, m);

  n = -0x7FFFFFFF;
  bigFromInt(n);
  bip.op1 = bip.res;
  m = bigToInt();
  printf("%12d = %12d\n", n, m);
}


/**************************************************************/


void test20(void) {
  printf("please enter a number: ");
  fflush(stdout);
  bigRead(stdin);
  dump("", bip.res, "\n");
}


/**************************************************************/


void test21(void) {
  bigFromInt(0);
  dump("", bip.res, " = ");
  bip.op1 = bip.res;
  bigPrint(stdout);
  printf("\n");

  bigFromInt(1);
  dump("", bip.res, " = ");
  bip.op1 = bip.res;
  bigPrint(stdout);
  printf("\n");

  bigFromInt(-1);
  dump("", bip.res, " = ");
  bip.op1 = bip.res;
  bigPrint(stdout);
  printf("\n");

  bigFromInt(0x1234);
  dump("", bip.res, " = ");
  bip.op1 = bip.res;
  bigPrint(stdout);
  printf("\n");

  bigFromInt(-0x1234);
  dump("", bip.res, " = ");
  bip.op1 = bip.res;
  bigPrint(stdout);
  printf("\n");

  bigFromInt(0x186A0);
  dump("", bip.res, " = ");
  bip.op1 = bip.res;
  bigPrint(stdout);
  printf("\n");

  bigFromInt(-0x186A0);
  dump("", bip.res, " = ");
  bip.op1 = bip.res;
  bigPrint(stdout);
  printf("\n");

  bigFromInt(0x12345678);
  dump("", bip.res, " = ");
  bip.op1 = bip.res;
  bigPrint(stdout);
  printf("\n");

  bigFromInt(-0x12345678);
  dump("", bip.res, " = ");
  bip.op1 = bip.res;
  bigPrint(stdout);
  printf("\n");

  bigFromInt(987654321);
  bip.op1 = bip.res;
  bip.op2 = bip.res;
  bigMul();
  bip.op1 = bip.res;
  bip.op2 = bip.res;
  bigMul();
  dump("", bip.res, " =\n");
  bip.op1 = bip.res;
  bigPrint(stdout);
  printf("\n");
}


/**************************************************************/


typedef struct {
  void (*func)(void);
  char *explanation;
} TestFunc;


TestFunc tests[] = {
  { test00, "representation" },
  { test01, "sign" },
  { test02, "comparison" },
  { test03, "negation" },
  { test04, "addition, equal sizes" },
  { test05, "addition, different sizes" },
  { test06, "subtraction, equal sizes" },
  { test07, "subtraction, different sizes" },
  { test08, "2^n by addition" },
  { test09, "2^(n^2) by multiplication" },
  { test10, "factorial" },
  { test11, "division by zero" },
  { test12, "division, small dividend" },
  { test13, "division, single digit divisor" },
  { test14, "division, systematic test of simple cases" },
  { test15, "division, general case, different scale factors" },
  { test16, "division, general case, qhat (first guess)" },
  { test17, "division, general case, qhat (decremented twice)" },
  { test18, "division, general case, qhat (final correction)" },
  { test19, "conversion big --> int" },
  { test20, "read from file" },
  { test21, "print to file" },
};

int numTests = sizeof(tests) / sizeof(tests[0]);


/**************************************************************/


void usage(char *myself) {
  int i;

  printf("Usage: %s <test number>\n", myself);
  printf("valid test numbers are:\n");
  for (i = 0; i < numTests; i++) {
    printf("    %2d: %s\n", i, tests[i].explanation);
  }
  exit(1);
}


int main(int argc, char *argv[]) {
  int testNumber;
  char *endp;

  if (argc != 2) {
    usage(argv[0]);
  }
  testNumber = strtol(argv[1], &endp, 0);
  if (*endp != '\0') {
    usage(argv[0]);
  }
  if (testNumber < 0 || testNumber >= numTests) {
    usage(argv[0]);
  }
  printf("Test %d: %s\n", testNumber, tests[testNumber].explanation);
  (*tests[testNumber].func)();
  return 0;
}
