#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdint.h>

typedef enum {
  DBLL_DATA_PUSHED,
  DBLL_DATA_UPDATED,
  DBLL_DATA_DELETED,
  DBLL_MALLOC_FAILED,
  DBLL_KEY_NOT_FOUND
} dbll_return_status_t;

dbll_return_status_t dbll_push_at_tail(const char * key, void * data);
dbll_return_status_t dbll_push_at_head(const char * key, void * data);

uint16_t get_list_size(void);

void * dbll_search_from_tail(const char * key);
void * dbll_search_from_head(const char * key);

dbll_return_status_t dbll_update_data(const char * key, void * data);

dbll_return_status_t dbll_delete(const char * key);

void * dbll_pop(const char * key);
void * dbll_pop_from_tail(void);
void * dbll_pop_from_head(void);

void * dbll_get(const char * key);
void * dbll_get_from_tail(const char * key);
void * dbll_get_from_head(const char * key);

#endif