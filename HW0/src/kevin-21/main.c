#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../structs/worlds.h"



/* Retorna true si ambos strings son iguales */
bool string_equals(char *string1, char *string2) {
  return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
bool check_arguments(int argc, char **argv) {
  if (argc != 3) {
    printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta del archivo de input\n");
    printf("\tOUTPUT es la ruta del archivo de output\n");
    return false;
  }
  return true;
}

int main(int argc, char **argv) {
  /* Si los parámetros del programa son inválidos */
  if (!check_arguments(argc, argv)) {
    /* Salimos del programa indicando que no terminó correctamente */
    return 1;
  }

  /* Abrimos el archivo de input */
  FILE *input_file = fopen(argv[1], "r");

  /* Abrimos el archivo de output */
  FILE *output_file = fopen(argv[2], "w");

  char command[32];
  
  /* Leemos la cantidad de países */
  int n_countries;
  fscanf(input_file, "%d", &n_countries);

  /* [Por implementar] Generamos nuestro mundo */
  World* world = world_init(n_countries);
  /* Leemos la cantidad de regiones de cada país */
  int n_regions;
  for (int cty = 0; cty < n_countries; cty++) {
    fscanf(input_file, "%d", &n_regions);
    
    /* [Por implementar] Poblamos el país con regiones */
    world_create_region(world, cty, n_regions);
  }

  /* Número de eventos/líneas */
  int n_lines;
  fscanf(input_file, "%d", &n_lines);

  /* Declaramos variables para guardar: 
    - Id de país.
    - Id de región. 
    - Profundidad.
    - Id de contacto para las rutas
    - Número de contactos.
  */
  int country_id;
  int region_id;
  int depth;
  int depth_2;
  int contact_id;
  int n_contacts;

  while (n_lines) {
    /* Disminuimos en 1 el número de líneas por leer */
    n_lines--;

    /* Leemos la instrucción */
    fscanf(input_file, "%s", command);

    /* Obtenemos país, región, y profundidad */
    fscanf(input_file, "%d", &country_id);
    fscanf(input_file, "%d", &region_id);
    
    /* POSITIVE */
    if (string_equals(command, "ADD_CONTACTS")) {
      fscanf(input_file, "%d", &depth);
      // printf("ADD_CONTACTS %d %d %d ", country_id, region_id, depth);
      /* Obtenemos la ruta desde el archivo*/
      int route[depth];
      for (int r = 0; r < depth; r++) {
        fscanf(input_file, "%d", &contact_id);
        // printf("%d ", contact_id);
        route[r] = contact_id;
      }
      /* Obtenemos el numero de contactos */
      fscanf(input_file, "%d", &n_contacts);
      // printf("%d\n", n_contacts);
      world_add_contacts(world, country_id, region_id, depth, route, n_contacts);
    } 
    else if (string_equals(command, "POSITIVE")) {
      fscanf(input_file, "%d", &depth);
      // printf("POSITIVE %d %d %d ", country_id, region_id, depth);
      /* Obtenemos la ruta desde el archivo*/
      int route[depth];
      for (int r = 0; r < depth; r++) {
        fscanf(input_file, "%d", &contact_id);
        // printf("%d ", contact_id);
        route[r] = contact_id;
      }
      positive(world, country_id, region_id, depth, route);
      // printf("\n");

    } 
    else if (string_equals(command, "NEGATIVE")) {
      
      fscanf(input_file, "%d", &depth);
      // printf("NEGATIVE %d %d %d ", country_id, region_id, depth);
      /* Obtenemos la ruta desde el archivo*/
      int route[depth];
      for (int r = 0; r < depth; r++) {
        fscanf(input_file, "%d", &contact_id);
        // printf("%d ", contact_id);
        route[r] = contact_id;
      }
      negative(world, country_id, region_id, depth, route);
      // printf("\n");

    } 
    else if (string_equals(command, "RECOVERED")) {
      
      fscanf(input_file, "%d", &depth);
      // printf("RECOVERED %d %d %d ", country_id, region_id, depth);
      /* Obtenemos la ruta desde el archivo*/
      int route[depth];
      for (int r = 0; r < depth; r++) {
        fscanf(input_file, "%d", &contact_id);
        // printf("%d ", contact_id);
        route[r] = contact_id;
      }
      // printf("\n");

      /* [Por implementar] */
      recovered(world, country_id, region_id, depth, route);

    } 
    else if (string_equals(command, "CORRECT")) {
      fscanf(input_file, "%d", &depth);
      // printf("CORRECT %d %d %d ", country_id, region_id, depth);
      /* Obtenemos la primera ruta desde el archivo*/
      int route_1[depth];
      for (int r = 0; r < depth; r++) {
        fscanf(input_file, "%d", &contact_id);
        // printf("%d ", contact_id);
        route_1[r] = contact_id;
      }
      /* Obtenemos la segunda ruta desde el archivo*/
      fscanf(input_file, "%d", &depth_2);
      // printf("%d ", depth_2);
      int route_2[depth_2];
      for (int r = 0; r < depth_2; r++) {
        fscanf(input_file, "%d", &contact_id);
        // printf("%d ", contact_id);
        route_2[r] = contact_id;
      }
      // printf("\n");

      /* [Por implementar] */
      correct(world, country_id, region_id, depth, route_1, depth_2, route_2);
    } 
    else if (string_equals(command, "INFORM")) {
      fprintf(output_file, "INFORM %d %d\n", country_id, region_id);
      /* [Por implementar] */
      world_inform(world, country_id, region_id, output_file);
    } 
    else if (string_equals(command, "STATISTICS")) {
      fprintf(output_file, "STATISTICS %d %d\n", country_id, region_id);
      /* [Por implementar] */
      int master[4] = {0, 0, 0, 0};
      statistics(world->countries[country_id][region_id], output_file, master);
    }
  }
  int count = 0;
  // printf("Si llego hasta acá hice todo!\n");
  /*  [Por implementar] Liberamos nuestra estructura */
  for (int i = 0; i < world->n_countries; i += 1) {
    // // printf("fuck me %i\n", world->n_regions_countries[i]);
    for (int j = 0; j < world->n_regions_countries[i]; j += 1) {
      // // printf("%i %i\n", i, j);
      count += 1;
      person_delete(world->countries[i][j]);
    }
    free(world->countries[i]);
    free(world->people_count[i]);
  }
  free(world->countries);
  free(world->people_count);
  free(world->n_regions_countries);
  free(world);

  fclose(input_file);
  fclose(output_file);
  // printf("Borre %i regiones\n", count);
  return 0;
}
