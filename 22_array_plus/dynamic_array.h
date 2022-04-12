#ifndef __dynamic_array_h
#define __dynamic_array_h

typedef void *ArrayList;

extern ArrayList init(int);

extern void insert(ArrayList, void *, int);

extern void remove_by_pos(ArrayList, int);

extern void remove_by_data(ArrayList, void *, int (*compare)(void *, void *));

extern void info(ArrayList, void (*)(void *));

extern void emptry(ArrayList);

extern void destroy(ArrayList);

#endif