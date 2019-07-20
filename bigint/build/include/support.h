/*
 * support.h -- object representation and support functions
 */


#ifndef _SUPPORT_H_
#define _SUPPORT_H_


/* object representation */

typedef struct {
  unsigned int size;			/* byte count of payload data */
  unsigned char data[1];		/* payload data, size as needed */
} *ObjRef;


/* support functions */

void fatalError(char *msg);		/* print a message and exit */
ObjRef newPrimObject(int dataSize);	/* create a new primitive object */


#endif /* _SUPPORT_H_ */
