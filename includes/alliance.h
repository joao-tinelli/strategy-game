#ifndef ALLIANCE_H
#define ALLIANCE_H

/**
 * @brief List's node;
 * @typedef TAlliance;
*/
typedef struct _alliance TAlliance;

/**
 * @brief List's head;
 * @typedef HAlliance;
*/
typedef struct _halliance HAlliance;

/**
 * @brief Allocates a struct of TAliance's type;
 * @param name;
 * @return TAlliance;
*/
TAlliance *alliance_allocates(const char *name);

/**
 * @brief Creates the list's head;
 * @param void;
 * @return HAlliance;
*/
HAlliance *halliance_creates(void);

/**
 * @brief Deallocate the list;
 * @param head;
 * @return void;
*/
void halliance_deallocates(HAlliance **head);

/**
 * @brief Verifies if an alliance is empty;
 * @param head;
 * @return 0 or 1;
*/
int is_halliance_empty(const HAlliance *head);

/**
 * @brief Inserts a new alliance on the list;
 * @param head, name;
 * @return void;
*/
void halliance_insert(HAlliance *head, const char *name);
/**
 * @brief Prints the list's content, if it's not empty;
 * @param head;
 * @return void;
*/
void alliance_allies(const HAlliance *head);

#endif 

