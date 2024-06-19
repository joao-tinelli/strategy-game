#ifndef MAP_H
#define MAP_H

/**
 * @brief Map's dimension;
 * @typedef Dimension;
*/
typedef struct _Dimension Dimension;

/**
 * @brief Read map's dimension;
 * @param file_name;
 * @return Dimension;
*/
Dimension *map_reads_dimension(const char *file_name);
/**
 * @brief Sets rows and columns;
 * @param n, m;
 * @return Dimension;
*/
Dimension *sets_dimension(const int n, const int m);

/**
 * @brief Allocates a map of dimension d;
 * @param d;
 * @return char **;
*/
char **map_allocates(Dimension *d);

/**
 * @brief Generates a map with random terrains;
 * @param map, d;
 * @return void;
*/
void map_generates(char **map, Dimension *d);

/**
 * @brief Deallocates a map;
 * @param map, d;
 * @return void;
*/
void map_deallocates(char ***map, Dimension *d);
/**
 * @brief Deallocates a map's dimension;
 * @param d;
 * @return void;
*/
void map_dimension_deallocates(Dimension **d);

/**
 * @brief Verifies if a map is empty;
 * @param map, dimension;
 * @return 0 or 1;
*/
int is_map_empty(char **map, Dimension *dimension);

/**
 * @brief Prints a map;
 * @param map, d;
 * @return void;
*/
void map_display(char **map, Dimension *d);

/**
 * @brief Replicates a map;
 * @param official_map, copied_map, d;
 * @return void;
*/
void map_replicates(char **official_map, char **copied_map, Dimension *d);

/**
 * @brief Makes all maps;
 * @param official_map, faction_map, building_map, unity_map, dimension;
 * @return void;
*/
void map_makes(char ***official_map, char ***faction_map, char ***building_map, char ***unity_map, Dimension *dimension);

/**
 * @brief Verifies the type of terrain on the map;
 * @param map, dimension, x, y;
 * @return char;
*/
char map_type_terrain(char **map, Dimension *dimension, const int x, const int y);

#endif 