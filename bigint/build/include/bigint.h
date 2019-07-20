/*
 * bigint.h -- big integer library
 */


#ifndef _BIGINT_H_
#define _BIGINT_H_


#include <stdio.h>

#include "support.h"


/* big integer processor registers */

typedef struct {
  ObjRef op1;			/* first (or single) operand */
  ObjRef op2;			/* second operand (if present) */
  ObjRef res;			/* result of operation */
  ObjRef rem;			/* remainder in case of division */
} BIP;

extern BIP bip;			/* registers of the processor */


/* big integer processor functions */

int bigSgn(void);			/* sign */
int bigCmp(void);			/* comparison */
void bigNeg(void);			/* negation */
void bigAdd(void);			/* addition */
void bigSub(void);			/* subtraction */
void bigMul(void);			/* multiplication */
void bigDiv(void);			/* division */

void bigFromInt(int n);			/* conversion int --> big */
int bigToInt(void);			/* conversion big --> int */

void bigRead(FILE *in);			/* read a big integer */
void bigPrint(FILE *out);		/* print a big integer */

void bigDump(FILE *out, ObjRef objRef);	/* dump a big integer object */


#endif /* _BIGINT_H_ */
