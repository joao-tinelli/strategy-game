#include "libraries.h"

typedef struct _Dimension
{
    int n, m;
} Dimension;

Dimension *map_reads_dimension(const char *file_name)
{
    FILE *file = fopen(file_name, "r");
    Dimension *d = (Dimension*)malloc(sizeof(Dimension));

    if (!file)
    {
        msg_error("Could not open the file.", "map_reads_dimension");
        free(d);  
        return NULL;
    }

    int n, m;
    if (fscanf(file, "%d %d", &n, &m) != 2){
        msg_error("Could not read the map's dimension", "map_reads_dimension");
        fclose(file);
        free(d); 
        return NULL;
    }
    fclose(file);
    d->n = n;
    d->m = m;
    return d;
}

Dimension *sets_dimension(const int n, const int m)
{
    Dimension *aux = (Dimension*)malloc(sizeof(Dimension));
    aux->n = n;
    aux->m = m;
    return aux;
}

char **map_allocates(Dimension *d)
{
    char **map = (char **)malloc(d->n * sizeof(char*));
    if (map == NULL){
        msg_error("Failed to allocate the map", "map_allocates");
        return NULL;
    }
    
    for (int i = 0; i < d->n; i++) {
        map[i] = (char*)malloc(d->m * sizeof(char));
        if (map[i] == NULL){
            msg_error("Failed to allocate the map", "map_allocates");

            for (int j = 0; j < i; j++) {
                free(map[j]);
            }
            free(map);
            return NULL;
        }
    }
    return map;
}

void map_generates(char **map, Dimension *d)
{
    srand(time(NULL));
   
    for (int i = 0; i < d->n; i++){
        for (int j = 0; j < d->m; j++){
            int type = 1 + (rand() % 3);
            switch (type){
            case 1:
                map[i][j] = 'P';
                break;
            case 2:
                map[i][j] = 'F';
                break;
            case 3:
                map[i][j] = 'M';
                break;;            
            default:
                break;
            }            
        }
    }
}

void map_deallocates(char ***map, Dimension *d)
{
    int i;
    for (i = 0; i < d->n; i++)
        free((*map)[i]);
    free(*map);
    *map = NULL;
}

void map_dimension_deallocates(Dimension **d)
{
    free(*d);
    *d = NULL;
}

int is_map_empty(char **map, Dimension *dimension)
{
    if (map == NULL) {
        return 1; 
    }
    if (dimension->n == 0 || dimension->m == 0) {
        return 1; 
    }
    for (int i = 0; i < dimension->n; i++) {
        if (map[i] == NULL) {
            return 1; 
        }
        for (int j = 0; j < dimension->m; j++) {
            if (map[i][j] != 0) {
                return 0; 
            }
        }
    }
    return 1; 
}

void map_display(char **map, Dimension *d)
{
    if(is_map_empty(map, d))
    {
        msg_error("Empty map.", "map_display");
        return;
    }

    for (int i = 0; i < d->n; i++){
        for (int j = 0; j < d->m; j++){
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

void map_replicates(char **official_map, char **copied_map, Dimension *d)
{
    int i, j;
    for (i = 0; i < d->n; i++){
        for (j = 0; j < d->m; j++){
            copied_map[i][j] = official_map[i][j];
        }
    }
}

void map_makes(char ***official_map, char ***faction_map, char ***building_map, char ***unity_map, Dimension *dimension)
{
    *official_map = map_allocates(dimension);    
    map_generates(*official_map, dimension);

    *faction_map = map_allocates(dimension);
    map_replicates(*official_map, *faction_map, dimension);

    *building_map = map_allocates(dimension);
    map_replicates(*official_map, *building_map, dimension);

    *unity_map = map_allocates(dimension);
    map_replicates(*official_map, *unity_map, dimension);
}

char map_type_terrain(char **map, Dimension *dimension, const int x, const int y)
{
    if (is_map_empty(map, dimension))
    {
        msg_error("Empty map.", "map_type_terrain");
        return '\0';
    }

    return map[x][y];
}

