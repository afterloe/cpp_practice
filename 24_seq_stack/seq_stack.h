#ifndef __STACK
#define __STACK

typedef void *Seq_Stack;

extern Seq_Stack init();
extern void push(Seq_Stack, void *);
extern void pop(Seq_Stack);
extern void *top_seq_stack(Seq_Stack);
extern int size(Seq_Stack);
extern int is_empty(Seq_Stack);
extern void empty(Seq_Stack);
extern void destroy(Seq_Stack);

#endif
