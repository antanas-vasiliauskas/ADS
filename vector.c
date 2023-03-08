// Antanas Vasiliauskas 3 grupe 1 uzd.
// 5. ADT - Vektorius (vienmatis duomenų rinkinys = dinaminis masyvas)

#include <stdlib.h>
#include <stdio.h>

struct Vector{
    int *arr;
    int size;
    int capacity;
    int id;
} typedef Vector;

Vector *create_vector(int id);
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


Vector *create_vector(int id){
    Vector *v = malloc(sizeof(Vector));
    v->arr = malloc(0);
    v->size = 0;
    v->capacity = 0;
    v->id = id;
    return v;
}

char is_empty(Vector *v, int *error_code){
    if(v == NULL){
        *error_code = 2;
        return -1;
    }
    return v->size == 0;
}

void remove_all_elements(Vector *v, int *error_code){
    if(v == NULL){
        *error_code = 2;
        return;
    }
    v->size = 0;
}

void remove_element_at(Vector *v, int index, int *error_code){
    if(v == NULL){
        *error_code = 2;
        return;
    }
    if(v->size <= index){
        *error_code = 1;
        return;
    }
    *error_code = 0;
    for(int i = index; i < v->size - 1; i++){
        set_element_at(v, get_element_at(v, i+1, error_code), i, error_code);
    }
    v->size--;
}


void insert_element_at(Vector *v, int element, int index, int *error_code){
    if(v == NULL){
        *error_code = 2;
        return;
    }
    if(v->size < index || index < 0){
        *error_code = 1;
        return;
    }
    v->size++;
    if(v->size > v->capacity){
        realloc(v->arr, v->size * sizeof(int));
        v->capacity = v->size;
    }
    for(int i = v->size - 1; i > index; i--){
        set_element_at(v, get_element_at(v, i - 1, error_code), i, error_code);
    }
    set_element_at(v, element, index, error_code);
}

void add_element(Vector *v, int element, int *error_code){
    if(v == NULL){
        *error_code = 2;
        return;
    }
    insert_element_at(v, element, get_size(v, error_code), error_code);
}

void set_element_at(Vector *v, int element, int index, int *error_code){
    if(v == NULL){
        *error_code = 2;
        return;
    }
    if(v->size <= index){
        *error_code = 1;
        return;
    }
    v->arr[index] = element;
}

int get_element_at(Vector *v, int index, int *error_code){
    if(v == NULL){
        *error_code = 2;
        return -1;
    }
    if(v->size <= index){
        *error_code = 1;
        return -1;
    }
    return v->arr[index];
}

int get_size(Vector *v, int *error_code){
    if(v == NULL){
        *error_code = 2;
        return -1;
    }
    return v->size;
}
int get_capacity(Vector *v, int *error_code){
    return v->capacity;
}

void reserve(Vector *v, int capacity, int *error_code){
    if(v == NULL){
        *error_code = 2;
        return;
    }
    if(capacity <= v->capacity){
        *error_code = 2;
        return;
    }
    v->capacity = capacity;
    realloc(v->arr, capacity * sizeof(int));
}
void print_vector(Vector *v, int *error_code){
    if(v == NULL){
        *error_code = 2;
        return;
    }
    printf("[");
    for(int i = 0; i < v->size-1; i++){
        printf("%d, ", v->arr[i]);
    }
    if(v->size != 0)
        printf("%d", v->arr[v->size-1]);
    printf("]");
}

void delete_vector(Vector **v, int *error_code){
    if(*v == NULL){
        *error_code = 2;
        return;
    }
    free((*v)->arr);
    free(*v);
    *v = NULL;
}

