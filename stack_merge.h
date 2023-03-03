#ifndef STACKMERGE_H_
#define STACKMERGE_H_

#include <stdio.h>
#include "stack.h"
#include "types.h"
#include "file_utils.h"


Status mergeStacks(Stack * sin1, Stack * sin2, Stack * sout);

int stack_cmp(Stack *s1, Stack *s2);

#endif /* STACKMERGE_H_ */