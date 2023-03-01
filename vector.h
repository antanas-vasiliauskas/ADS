// Antanas Vasiliauskas 3 grupe 1 uzd.
// 5. ADT - Vektorius (vienmatis duomenų rinkinys = dinaminis masyvas)
#ifndef VECTOR
#define VECTOR

struct Vector{
    int *arr;
    int size;
    int capacity;
} typedef Vector;

Vector *create_vector();
char is_empty(Vector *v, int *error_code);
void remove_all_elements(Vector *v, int *error_code);
void remove_element_at(Vector *v, int index, int *error_code);
void insert_element_at(Vector *v, int element, int index, int *error_code);
void add_element(Vector *v, int element, int *error_code);
void set_element_at(Vector *v, int element, int index, int *error_code);
int get_element_at(Vector *v, int index, int *error_code);

int get_size(Vector *v, int *error_code);
int get_capacity(Vector *v, int *error_code);

void reserve(Vector *v, int capacity, int *error_code);
void print_vector(Vector *v, int *error_code);
void delete_vector(Vector **v, int *error_code);

#endif
