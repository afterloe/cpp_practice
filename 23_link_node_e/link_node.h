#ifndef __link_node_h
#define __link_node_h

typedef void *LinkedList;

extern LinkedList init();
extern void insert(LinkedList, void *, int);
extern void info(LinkedList, void (*)(void *));
extern void remove_by_pos(LinkedList, int);
extern void remove_by_value(LinkedList, void *, int (*)(void *, void *));
extern void empty(LinkedList);
extern void destroy(LinkedList);

#endif