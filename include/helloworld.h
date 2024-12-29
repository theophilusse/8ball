#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include "8ball.h"

#define HELLO_EPSILON 	0.001000
#define HELLO_DECODE_EPSILON	1000

unsigned char *helloworld(uint *length);
void inject_helloworld(t_model *model, void *payload, uint size);
void read_helloworld(t_model *model, t_camdata *d);

#endif // HELLOWORLD_H
