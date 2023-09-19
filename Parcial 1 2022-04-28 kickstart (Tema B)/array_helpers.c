/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

/**
* @brief returns true when reach last entry in flight table
* @return True when is the last entre of the flight table, False otherwise
*/
static bool is_last_line(unsigned int hour, unsigned int type) {
  return  hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(DeliveryTable a) {
  for (unsigned int type = 0u; type < TYPE; ++type) {
    for (unsigned int hour = 0u; hour < HOURS; ++hour) {
      Flight f = a[type][hour];
      fprintf(stdout, "%c: flight with %u %s arrived at %u:00", f.code, f.items_amount, f.type == 0 ? "boxes" : "letters", f.hour - 1);
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}

unsigned int extra_space_fee_cost (DeliveryTable a) {

  int cajas= 0;
  int cartas= 0;
  int penalty_cajas = 0;
  int penalty_cartas = 0;
  int penalidad_total = 0;

  for(unsigned int i = 0; i <= 23; i++){
    if(a[0][i].hour <= 19){
      cajas = cajas + a[0][i].items_amount;
    }

    if(a[1][i].hour <= 19){
      cartas = cartas + a[1][i].items_amount;
    }

    if(cajas > MAX_ALLOWED_BOXES){
      penalty_cajas = (cajas - MAX_ALLOWED_BOXES) * BOX_PENALTY;
    }
    else {penalty_cajas = 0;}

    if(cartas > MAX_ALLOWED_LETTERS){
      penalty_cartas = (cartas - MAX_ALLOWED_LETTERS) * LETTER_PENALTY;
    }
    else {penalty_cartas = 0;}

    penalidad_total = penalty_cajas + penalty_cartas;

  }
  return penalidad_total;
}


void array_from_file(DeliveryTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  int i = 0;
  while (i < HOURS &&!feof(file)) {
    int res = fscanf(file, "_%c_", &code);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    /* COMPLETAR: Generar y guardar ambos Flight en el array multidimensional */
    array[0][i] = flight_from_file(file, code, 0);
    array[1][i] = flight_from_file(file, code, 1);
    fscanf(file, "\n");
    i++;
  }
  fclose(file);
}
