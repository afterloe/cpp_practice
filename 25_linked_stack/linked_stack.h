
#ifndef __LINKED_STACK_H
#define __LINKED_STACK_H

typedef void *LinkedStack;

extern LinkedStack init();
extern void push(LinkedStack, void *);
extern void pop(LinkedStack);
extern void *top_linked_stack(LinkedStack);
extern int size(LinkedStack);
extern int is_empty(LinkedStack);
extern void empty(LinkedStack);
extern void destroy(LinkedStack);

#endif