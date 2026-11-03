#ifndef DYNARRAY
#define DYNARRAY

struct IntDynArray {
  int* buffer;
  int length;
  int capacity;
};

typedef struct IntDynArray intDynArray;

intDynArray* new_intDynArray(void);
void resize_intDynArray(intDynArray* array);
void push_to_intDynArray(intDynArray* array, int element);
int pop_intDynArray(intDynArray* array);
void print_intDynArray(intDynArray* array);
void free_intDynArray(intDynArray* array);
#endif
