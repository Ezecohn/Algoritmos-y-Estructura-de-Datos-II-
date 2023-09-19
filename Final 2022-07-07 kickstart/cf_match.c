#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#include "card.h"
#include "cf_match.h"



struct _s_match {
    cf_match previous;
    card c;
    cf_match next;
};

struct _s_card {
    unsigned int number;
    char suit;
    unsigned int player;
};

cf_match match_new(void)
{
    cf_match new = malloc(sizeof(struct _s_match));
    new->previous = NULL;
    new->next = NULL;
    new->c = NULL;
    return new;
}

cf_match match_add(cf_match match, card c)
{   
    cf_match new = malloc(sizeof(struct _s_match));
    new->previous = NULL;
    new->c = c;
    new->next = NULL;
    if(match->c == NULL){
        match->previous=NULL;
        match->c = c;
        match->next=NULL;
        free(new);
    }
    else{  
        cf_match pointer = match;
        while(pointer->next != NULL){
            pointer = pointer->next;
        }
        pointer->next = new;
        new->previous = pointer; 
    }
    return match;
}

unsigned int match_size(cf_match match)
{   
    unsigned int counter = 0;
    if(match == NULL){
        counter = 0;
    }
    else{
        while(match != NULL){
            counter++;
            match = match->next;
        }
    }
    return counter;
}

bool is_match_correct(cf_match match)
{
    bool correct = true;
    bool aux = true;
    correct = match->c->player == 1;
    correct = correct &&  (match_size(match) % 2) == 0;
    if(match_size(match)==1){
        correct = false;
    }
    else{
    for(unsigned int i=0; i<match_size(match); i++){
        if(match->c->player == 1){
            aux = aux && (match->previous == NULL || match->previous->c->player == 2) &&
            (match->next->c->player == 2);
        }
        match = match->next;
    } 
    correct = correct && aux;
    for(unsigned int i=0; i<match_size(match); i++){
        if(match->c->player == 2){
            aux = aux && (match->next == NULL || match->next->c->player == 1) &&
            (match->previous->c->player == 1);
        }
        match = match->next;
    } 
    correct = correct && aux;
    for(unsigned int i=0; i<match_size(match); i++){
        if(match->c->suit == 'd'){
            aux = aux && (match->previous == NULL || match->previous->c->suit == 'p' ||
            match->previous->c->suit == 't') &&
            (match->next == NULL || match->next->c->suit == 'p' ||
            match->next->c->suit == 't');
        }
        match = match->next;
    }  
    correct = correct && aux;
    for(unsigned int i=0; i<match_size(match); i++){
        if(match->c->suit == 'c'){
            aux = aux && (match->previous == NULL || match->previous->c->suit == 'p' ||
            match->previous->c->suit == 't') &&
            (match->next == NULL || match->next->c->suit == 'p' ||
            match->next->c->suit == 't');
        }
        match = match->next;
    }  
    correct = correct && aux;
    for(unsigned int i=0; i<match_size(match); i++){
        if(match->c->suit == 'p'){
            aux = aux && (match->previous == NULL || match->previous->c->suit == 'c' ||
            match->previous->c->suit == 'd') &&
            (match->next == NULL || match->next->c->suit == 'd' ||
            match->next->c->suit == 'c');
        }
        match = match->next;
    }  
    correct = correct && aux;
    for(unsigned int i=0; i<match_size(match); i++){
        if(match->c->suit == 't'){
            aux = aux && (match->previous == NULL || match->previous->c->suit == 'c' ||
            match->previous->c->suit == 'd') &&
            (match->next == NULL || match->next->c->suit == 'd' ||
            match->next->c->suit == 'c');
        }
        match = match->next;
    }  
    correct = correct && aux;}
    return correct;
}

static int player_score(cf_match match, unsigned int player)
{   
    assert(is_match_correct(match));
    int score = 0;
    cf_match pointer = match;
    while (pointer != NULL){
        //chequea primera carta
        if(pointer->c->player == player){
           if(pointer->previous == NULL){
                score = score + 0;
           } 
           //chquear la segunda carta
           else if(pointer->previous->previous == NULL){
                if(pointer->previous->c->number + 1 == pointer->c->number){
                    score = score + 5;
                }
                else if(pointer->previous->c->number - 1 == pointer->c->number){
                    score = score + 5;
                }
               }
           // anterior menor por 1
           else if(pointer->previous->c->number + 1 == pointer->c->number){
                // si ya venia la escalera y agrega para el mismo lado
                if(pointer->previous->previous->c->number + 1 == pointer->previous->c->number){
                score = score + 3;
           }    // si ya venia la escalera y agrega para el otro lado
                else if (pointer->previous->previous->c->number - 1 == pointer->previous->c->number) {
                    score = score + 5;
                }
                else if(pointer->previous->previous->c->number == pointer->previous->c->number){
                    score = score + 5;
                }
           }
           // anterior mayor por 1
           else if(pointer->previous->c->number - 1 == pointer->c->number){
           // si ya venia la escalera y agrega para el mismo lado
                if(pointer->previous->previous->c->number - 1 == pointer->previous->c->number){
                score = score + 3;
           }    // si ya venia la escalera y agrega para el otro lado
                else if (pointer->previous->previous->c->number + 1 == pointer->previous->c->number) {
                    score = score + 5;
                }
        }
        // si la carta tiene el mismo numero que la anterior
        else if (pointer->previous->c->number == pointer->c->number){
            if(pointer->previous->previous->c->number + 1 == pointer->previous->c->number){
            score = score + 7;}
            else if(pointer->previous->previous->c->number - 1 == pointer->previous->c->number){
            score = score + 7;}
            else{
                score = score;
            }
        }
        // si rompoe una escalera
        else if((pointer->previous->previous->c->number - 1 == pointer->previous->c->number) ||(
        (pointer->previous->previous->c->number + 1 == pointer->previous->c->number) &&
        (pointer->previous->c->number + 1 != pointer->c->number) && 
        (pointer->previous->c->number - 1 != pointer->c->number))){
            score = score - 3;
        }

        
    }
    pointer = pointer->next;
}return score;
}

unsigned int match_winner(cf_match match)
{   
    unsigned int resultado = 0;
    if (!is_match_correct(match)){
        resultado = -1;
    }
    else{
        if (player_score(match, 1) == player_score(match, 2)){
            resultado = 0;
        }
        else if(player_score(match, 1) > player_score(match, 2)){
            resultado = 1;
        }
        else{
            resultado = 2;
        }
    }
    return resultado;
}

unsigned int winner_total_points(cf_match match)
{
    if (!is_match_correct(match)) {
        return -1;
    }

    int playerOneScore = player_score(match, 1);
    int playerTwoScore = player_score(match, 2);

    if (playerOneScore == playerTwoScore) {
        return 0;
    }
    return playerOneScore > playerTwoScore ? playerOneScore : playerTwoScore;
}

card* match_to_array(cf_match match)
{   
    cf_match pointer = match;
    card *array = malloc(sizeof(card) * match_size(match));
    for (unsigned int i = 0; i<match_size(match); i++){
        array[i] = pointer->c;
        pointer = pointer->next;
    } 
    return array;
}

void match_dump(cf_match match)
{
    card* array = match_to_array(match);
    for (unsigned int i = 0u; i < match_size(match); i++) {
        card_dump(array[i]);
    }
    free(array);
}

cf_match match_destroy(cf_match match)
{
    cf_match destroyer = match;
    while(match != NULL){
        match = match->next;
        free(destroyer->c);
        free(destroyer);
        destroyer = match;
    }
    free(match);
    match = NULL;
    return match;
}
