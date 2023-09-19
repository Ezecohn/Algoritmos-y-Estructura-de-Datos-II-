#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "domino.h"
#include "domino_line.h"


struct _s_line {
    domino_line previous;
    domino tile;
    domino_line next;
};

domino_line line_new(domino first) {
    assert(domino_is_double(first));
    domino_line l = malloc(sizeof(struct _s_line));
    l->previous = NULL;
    l->next = NULL;
    l->tile = first;
    return l;
}

domino_line line_add(domino_line line, domino t) {
    domino_line l = malloc(sizeof(struct _s_line));
    l->previous = NULL;
    l->tile = t;
    l->next = NULL;
    if (line == NULL){
        line = l;
    }
    else{
        domino_line pointer = NULL;
        pointer = line;
        while(pointer->next != NULL){
            pointer = pointer->next;
        }
        l->previous = pointer;
        pointer->next = l;
    }
    return line;
}

unsigned int line_length(domino_line line) {
    assert(line != NULL);
    unsigned int length = 0;
    domino_line pointer = line;
    while(pointer != NULL){
        length ++;
        pointer = pointer->next;
    }
    assert(length > 0);
    return length;
}

bool line_n_correct(domino_line line, unsigned int n) {
    assert(n < line_length(line));
    bool correct = false;
    domino_line pointer = line;
    if(line_length(line) == 1){
        correct = true;
    }
    else{
    if(n == 0){
        correct = (line->tile->down == line->next->tile->up);
    }
    else if (n == line_length(line)-1){
        while(pointer->next != NULL){
            pointer = pointer->next;
        }
        correct = (pointer->tile->up == pointer->previous->tile->down);}
    else{
        for (unsigned int i = 0; i < n; i++){
            pointer = pointer->next;
        }
        correct = (pointer->tile->up == pointer->previous->tile->down);
        correct = (correct && (pointer->tile->down == pointer->next->tile->up));
    }}
    return correct;
}   

int line_total_points(domino_line line) {
    assert(line != NULL);
    int total = 0;
    domino_line pointer = line;
    while(pointer != NULL){
        total += pointer->tile->up + pointer->tile->down;
        pointer = pointer->next;
    }
    assert(total >= 0);
    return total;
}

domino * line_to_array(domino_line line) {
    assert(line != NULL);
    domino_line pointer = line;
    domino *array = malloc(line_length(line) * sizeof(domino));
    for (unsigned int i = 0; i < line_length(line); i++){
        array[i] = pointer->tile;
        pointer = pointer->next;
    }
    assert(array != NULL);
    return array;
}

void line_dump(domino_line line) {
    domino *array=line_to_array(line);
    for (unsigned int i=0u; i < line_length(line); i++) {
        domino_dump(array[i]);
    }
    free(array);
}

domino_line line_destroy(domino_line line) {
    assert(line != NULL);
    domino_line destroyer = line;
    while (line != NULL){
        line = line->next;
        free(destroyer->tile);
        free(destroyer);
        destroyer = line;
    
    }
    line = NULL;
    assert(line == NULL);
    return  line;
}

