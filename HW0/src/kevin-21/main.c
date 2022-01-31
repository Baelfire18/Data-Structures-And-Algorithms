#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../structs/worlds.h"

/* Retorn true if both are equal */
bool string_equals(char *string1, char *string2) {
  return !strcmp(string1, string2);
}

/* Checks vadility of the programs parameters */
bool check_arguments(int argc, char **argv) {
  if (argc != 3) {
    printf("Mode of use: %s INPUT OUTPUT\n", argv[0]);
    printf("Where:\n");
    printf("\tINPUT is the input's file route\n");
    printf("\tOUTPUT is the output's file route\n");
    return false;
  }
  return true;
}

int main(int argc, char **argv) {
  /* If programs parameters are not valid */
  if (!check_arguments(argc, argv)) {
    /* We exit de program with an error */
    return 1;
  }

  /* We open the input file */
  FILE *input_file = fopen(argv[1], "r");

  /* We open the output file */
  FILE *output_file = fopen(argv[2], "w");

  char command[32];
  
  /* We read the total of countries */
  int n_countries;
  fscanf(input_file, "%d", &n_countries);

  /* We generate our world */
  World* world = world_init(n_countries);

  /* We read the number of regiosn per country */
  int n_regions;
  for (int cty = 0; cty < n_countries; cty ++) {
    fscanf(input_file, "%d", &n_regions);
    /* We populate the country with regions */
    world_create_region(world, cty, n_regions);
  }

  /* Number of events */
  int n_lines;
  fscanf(input_file, "%d", &n_lines);

  /* We declare variables to save: 
    - Country ID.
    - Region ID. 
    - Depth.
    - Contact ID for routes.
    - Number of contacts.
  */
  int country_id;
  int region_id;
  int depth;
  int depth_2;
  int contact_id;
  int n_contacts;

  while (n_lines) {
    /* We decrease by 1 the number of lines to read */
    n_lines--;

    /* We read the instructions */
    fscanf(input_file, "%s", command);

    /* We get the country, region, and depth */
    fscanf(input_file, "%d", &country_id);
    fscanf(input_file, "%d", &region_id);
    
    /* POSITIVE */
    if (string_equals(command, "ADD_CONTACTS")) {
      fscanf(input_file, "%d", &depth);
      // Get routes from file
      int route[depth];
      for (int r = 0; r < depth; r++) {
        fscanf(input_file, "%d", &contact_id);
        route[r] = contact_id;
      }
      /* Get number of contacts */
      fscanf(input_file, "%d", &n_contacts);
      world_add_contacts(world, country_id, region_id, depth, route, n_contacts);

    }
    else if (string_equals(command, "POSITIVE")) {
      fscanf(input_file, "%d", &depth);
      // Get routes from file
      int route[depth];
      for (int r = 0; r < depth; r++) {
        fscanf(input_file, "%d", &contact_id);
        route[r] = contact_id;
      }
      positive(world, country_id, region_id, depth, route);

    }
    else if (string_equals(command, "NEGATIVE")) {
      fscanf(input_file, "%d", &depth);
      // Get routes from file
      int route[depth];
      for (int r = 0; r < depth; r++) {
        fscanf(input_file, "%d", &contact_id);
        route[r] = contact_id;
      }
      negative(world, country_id, region_id, depth, route);

    }
    else if (string_equals(command, "RECOVERED")) {
      fscanf(input_file, "%d", &depth);
      // Get routes from file
      int route[depth];
      for (int r = 0; r < depth; r++) {
        fscanf(input_file, "%d", &contact_id);
        route[r] = contact_id;
      }
      recovered(world, country_id, region_id, depth, route);
    }
    else if (string_equals(command, "CORRECT")) {
      fscanf(input_file, "%d", &depth);
      // Get first route from file
      int route_1[depth];
      for (int r = 0; r < depth; r++) {
        fscanf(input_file, "%d", &contact_id);
        route_1[r] = contact_id;
      }
      // Get second route from file
      fscanf(input_file, "%d", &depth_2);
      int route_2[depth_2];
      for (int r = 0; r < depth_2; r++) {
        fscanf(input_file, "%d", &contact_id);
        route_2[r] = contact_id;
      }  
      correct(world, country_id, region_id, depth, route_1, depth_2, route_2);
    }
    else if (string_equals(command, "INFORM")) {
      fprintf(output_file, "INFORM %d %d\n", country_id, region_id);
      world_inform(world, country_id, region_id, output_file); 
    }
    else if (string_equals(command, "STATISTICS")) {
      fprintf(output_file, "STATISTICS %d %d\n", country_id, region_id);
      int master[4] = {0, 0, 0, 0};
      statistics(world->countries[country_id][region_id], output_file, master);
    }
  }

  int count = 0;
  for (int i = 0; i < world->n_countries; i ++) {
    for (int j = 0; j < world->n_regions_countries[i]; j ++) {
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
  return 0;
}
