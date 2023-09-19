#include <stdlib.h>
#include "fence.h"

struct _fence_t {
    fence_t next;
    type_t type;
};

fence_t fence_P(){
    fence_t f = malloc(sizeof(struct _fence_t));
    f->next = NULL;
    f->type = P;
    return f;
}

fence_t fence_add_P(fence_t fence){
    fence_t p = fence_P();
    p->next = fence;
    fence = p;
    return fence;
}

fence_t fence_add_A(fence_t fence){
    fence_t a = malloc(sizeof(struct _fence_t));
    a->type = A;
    a->next = fence;
    fence = a;
    return fence;
}

fence_t fence_add_H(fence_t fence){
    fence_t a = malloc(sizeof(struct _fence_t));
    a->type = H;
    a->next = fence;
    fence = a;
    return fence;
}

fence_t fence_add_T(fence_t fence){
    fence_t a = malloc(sizeof(struct _fence_t));
    a->type = T;
    a->next = fence;
    fence = a;
    return fence;
}

bool fence_is_correct(fence_t fence){
    bool correct = true;
    bool exists_t = false;
    if(fence->type != P || fence->next == NULL ){
        correct = false;
    }
    else{
    fence_t pointer = fence;
    while(pointer->next != NULL){
        if(pointer->type != P){
            correct = correct && pointer->next->type == P; 
        }
        pointer = pointer->next;
        if(pointer->type == T){
            exists_t = true;
        }
    }
    correct = correct && pointer->type == P;
    }
    correct = correct && exists_t;
    return correct;
}

unsigned int fence_perimeter(fence_t fence){
    fence_t pointer = fence;
    unsigned int counter = 0;
    while(pointer != NULL){
        if(pointer->type != P){
        counter += 3;}
        pointer = pointer->next;
    }
    return counter;
}

unsigned int fence_size(fence_t fence){
    fence_t pointer = fence;
    unsigned int counter = 0;
    while(pointer != NULL){
        counter++;
        pointer = pointer->next;
    }
    return counter;
}

type_t *fence_to_array(fence_t fence){
    type_t *array = malloc(fence_size(fence) * sizeof(type_t));
    fence_t pointer = fence;
    for(unsigned int i=0; i<fence_size(fence); i++){
        array[i] = pointer->type;
        pointer = pointer->next;
    }
    return array;
}

fence_t fence_destroy(fence_t fence){
    fence_t killme = fence;
    fence = fence->next;
    while(fence != NULL){
        free(killme);
        killme = fence;
        fence = fence->next;
    }
    free(killme);
    free(fence);
    fence = NULL;
    return fence;
}