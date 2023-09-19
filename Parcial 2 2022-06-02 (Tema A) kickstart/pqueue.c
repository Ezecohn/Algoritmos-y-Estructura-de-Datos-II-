#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    unsigned int size;
    struct s_node *front;
};

struct s_node {
    unsigned int priority;
    pqueue_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node)); 
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node->next);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pqueue q) {
    bool inv = true;
    if(q==NULL){
        inv = false;
    }
    else if(q->front == NULL){ //cola vacia
        inv = true;
    }
    else if(q->front->next == NULL){ //cola con un solo elemento
        inv = true;
    }
    else{ //cola con mas de 1 elementos
        struct s_node *pointer = q->front;
        while(pointer->next != NULL){
            inv = inv && (pointer->priority <= pointer->next->priority);
            pointer = pointer->next;
        }
    }
    return inv;
}

pqueue pqueue_empty(void) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->size = 0;
    ////////////////////
    q->front = NULL;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    if(q->front == NULL){
        //q->front = malloc(sizeof(struct s_node));
        q->front = new_node;
    }
    else if(q->front->next == NULL){
        if(q->front->priority<=new_node->priority){
            q->front->next = new_node;
        }else{
            new_node->next = q->front;
            q->front = new_node;
        }
    }
    else if(q->front != NULL){
        struct s_node *pointer = q->front;
        struct s_node *previous = NULL;
        unsigned int j=0;
        while(j == 0 && pointer!= NULL ){
            if(new_node->priority >= pointer->priority){
            previous = pointer;
            pointer = pointer->next;}
            else{
                j = 1;
            }
        }

        if(previous == NULL){
            new_node->next = q->front;
            q->front = new_node;
        }
        else{
            previous->next = new_node;
            new_node->next = pointer;
        }

    }
    q->size++;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    
    return q->size == 0;
}

pqueue_elem pqueue_peek(pqueue q) {
    return q->front->elem;
}

unsigned int pqueue_peek_priority(pqueue q) {
    return q->front->priority;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    unsigned int size=0;
    size = q->size;
    return size;
}

pqueue pqueue_dequeue(pqueue q) {
    struct s_node *pointer = q->front;
    q->front = q->front->next;
    q->size--;
    free(pointer);
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *pointer = q->front;
    while(q->front != NULL){
        q->front = q->front->next;
        destroy_node(pointer);
        free(pointer);
        pointer = q->front;
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
