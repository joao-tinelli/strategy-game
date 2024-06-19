#ifndef BUILDING_H
#define BUILDING_H

#include "map.h"

/**
 * @brief List's node;
 * @typedef TBuilding;
*/
typedef struct building TBuilding;

/**
 * @brief List's head;
 * @typedef Hbuilding;
*/
typedef struct _hbuilding Hbuilding;

/**
 * @brief Creates a building;
 * @param key, amount, type, x, y;
 * @return TBuilding;
*/
TBuilding *tbuilding_allocates(const char key, const int amount, const int type, const int x, const int y);

/**
 * @brief Creates the buildings list;
 * @param void;
 * @return Hbuilding;
*/
Hbuilding *hbuilding_creates(void);

/**
 * @brief Deallocate the list;
 * @param head;
 * @return void;
*/
void hbuilding_deallocates(Hbuilding **head);

/**
 * @brief Verifies if the list is empty;
 * @param head;
 * @return 0 or 1;
*/
int is_hbuilding_empty(const Hbuilding *head);

/**
 * @brief Inserts a building on the list;
 * @param head, new;
 * @return void;
*/
void building_insert(Hbuilding *head, TBuilding *new);

/**
 * @brief Creates and makes a building;
 * @param head, identifier, amount, type, x, y;
 * @return void;
*/
void building_makes(Hbuilding *head, char *identifier, int amount, int type, int x, int y);

/**
 * @brief Merges two buildings lists;
 * @param cabeca_1, cabeca_2;
 * @return void;
*/
void building_merge(Hbuilding *head_1, Hbuilding *head_2);

#endif

