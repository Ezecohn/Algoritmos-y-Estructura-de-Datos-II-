#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "unogame.h"
#include "card.h"

#define NO_PLAYER -1

struct s_card {
    unsigned int num;
    color_t color;
    type_t type;
};

struct s_ugame {
   struct s_card *card;
   int player;
   struct s_ugame *next;
};


unogame_t
uno_newgame(card_t card) {
    unogame_t game = NULL;
    game = malloc(sizeof(struct s_ugame));
    game->card = card;
    game->player = NO_PLAYER;
    game->next = NULL;
    return game;
}

card_t
uno_topcard(unogame_t uno) {
    return uno->card;
}

unogame_t
uno_addcard(unogame_t uno, card_t c) {
    unogame_t aux = malloc(sizeof(struct s_ugame));
    aux->card = c;
    aux->player = uno_nextplayer(uno);
    aux->next = uno;
    uno = aux;
    return uno;
    
}

unsigned int
uno_count(unogame_t uno) {
    unogame_t pointer = uno;
    unsigned int counter = 0;
    while(pointer != NULL){
        pointer = pointer->next;
        counter++;
    }
    return counter;
}

bool
uno_validpile(unogame_t uno) {
    unogame_t pointer = uno;
    bool valid = true;
    
    for(unsigned int i=0; i<uno_count(uno)-1; i++){
        valid = valid && card_compatible(pointer->card, pointer->next->card);
        pointer = pointer->next;
    }
    pointer = uno;
    while(pointer->next != NULL){
        pointer = pointer->next;
    }
    if(pointer->card->type == 1){
        valid = false;
    }
    return valid;
}

color_t
uno_currentcolor(unogame_t uno) {
    return uno->card->color;
}

player_t
uno_nextplayer(unogame_t uno) {
    player_t siguiente;
    if(uno->card->type != 2){
        if(uno->player == -1){
            siguiente = 0;
        }
        if(uno->player == 0){
            siguiente = 1;
        }
        if(uno->player == 1){
            siguiente = 2;
        }
        if(uno->player == 2){
            siguiente = 0;
        }
    }
    else if(uno->card->type == 2){
        if(uno->player == -1){
            siguiente = 1;
        }
        if(uno->player == 0){
            siguiente = 2;
        }
        if(uno->player == 1){
            siguiente = 0;
        }
        if(uno->player == 2){
            siguiente = 1;
        }
    }
    return siguiente;
}



card_t *
uno_pile_to_array(unogame_t uno) {
    unogame_t aux = uno;
    card_t *array = malloc(uno_count(uno)*sizeof(struct s_card*));
    for(int i=uno_count(uno)-1; i>=0; i--){
        array[i] = aux->card;
        aux = aux->next;
    }
    return array;
}

unogame_t
uno_destroy(unogame_t uno) {
    unogame_t killme = uno;
    while(uno != NULL){
        uno = uno->next;
        free(killme->card);
        free(killme);
        killme = uno;
        
    }
    free(uno);
    uno = NULL;
    return uno;
}

