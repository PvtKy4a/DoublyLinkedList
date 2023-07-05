#include "DoublyLinkedList.h"
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char * key;
  void * data;
  struct Node * next;
  struct Node * prev;
} Node_t;

typedef struct {
  Node_t * head;
  Node_t * tail;
  uint16_t size;
} DoublyLinkedList_t;

DoublyLinkedList_t doubly_linked_list = {0};

Node_t * create_node(const char * key, void * data) {
  uint8_t key_size = strlen(key);
  Node_t * new_node = (Node_t *)malloc(sizeof(*new_node));
  if (new_node == NULL) {
    return NULL;
  }
  new_node->key = (char *)malloc(key_size + 1);
  if (new_node->key == NULL) {
    free(new_node);
    return NULL;
  }
  new_node->key = strcpy(new_node->key, key);
  new_node->key[key_size] = '\0';
  new_node->data = data;
  new_node->next = NULL;
  new_node->prev = NULL;
  return new_node;
}

void delete_node(Node_t * node) {
  free(node->key);
  free(node);
}

dbll_return_status_t dbll_push_at_tail(const char * key, void * data) {
  Node_t * new_node = create_node(key, data);
  if (new_node == NULL) {
    return DBLL_MALLOC_FAILED;
  }
  if (doubly_linked_list.tail == NULL) {
    doubly_linked_list.tail = new_node;
    doubly_linked_list.head = new_node;
    doubly_linked_list.size++;
    return DBLL_DATA_PUSHED;
  }
  if (doubly_linked_list.tail == doubly_linked_list.head) {
    doubly_linked_list.tail = new_node;
    doubly_linked_list.tail->prev = doubly_linked_list.head;
    doubly_linked_list.head->next = doubly_linked_list.tail;
    doubly_linked_list.size++;
    return DBLL_DATA_PUSHED;
  }
  doubly_linked_list.tail->next = new_node;
  new_node->prev = doubly_linked_list.tail;
  doubly_linked_list.tail = new_node;
  doubly_linked_list.size++;
  return DBLL_DATA_PUSHED;
}

dbll_return_status_t dbll_push_at_head(const char * key, void * data) {
  Node_t * new_node = create_node(key, data);
  if (new_node == NULL) {
    return DBLL_MALLOC_FAILED;
  }
  if (doubly_linked_list.head == NULL) {
    doubly_linked_list.head = new_node;
    doubly_linked_list.tail = new_node;
    doubly_linked_list.size++;
    return DBLL_DATA_PUSHED;
  }
  if (doubly_linked_list.head == doubly_linked_list.tail) {
    doubly_linked_list.head = new_node;
    doubly_linked_list.head->next = doubly_linked_list.tail;
    doubly_linked_list.tail->prev = doubly_linked_list.head;
    doubly_linked_list.size++;
    return DBLL_DATA_PUSHED;
  }
  doubly_linked_list.head->prev = new_node;
  new_node->next = doubly_linked_list.head;
  doubly_linked_list.head = new_node;
  doubly_linked_list.size++;
  return DBLL_DATA_PUSHED;
}

uint16_t get_list_size(void) {
  return doubly_linked_list.size;
}

void * dbll_search_from_tail(const char * key) {
  if (doubly_linked_list.tail == NULL) {
    return NULL;
  }
  Node_t * node = doubly_linked_list.tail;
  while (node != NULL) {
    if (strcmp(node->key, key) == 0) {
      return node->data;
    }
    node = node->prev;
  }
  return NULL;
}

void * dbll_search_from_head(const char * key) {
  if (doubly_linked_list.head == NULL) {
    return NULL;
  }
  Node_t * node = doubly_linked_list.head;
  while (node != NULL) {
    if (strcmp(node->key, key) == 0) {
      return node->data;
    }
    node = node->next;
  }
  return NULL;
}

Node_t * get_node(const char * key) {
  if (doubly_linked_list.head == NULL) {
    return NULL;
  }
  Node_t * node = doubly_linked_list.head;
  while (node != NULL) {
    if (strcmp(node->key, key) == 0) {
      return node;
    }
    node = node->next;
  }
  return NULL;
}

dbll_return_status_t dbll_update_data(const char * key, void * data) {
  Node_t * node = get_node(key);
  if (node == NULL) {
    return DBLL_KEY_NOT_FOUND;
  }
  node->data = data;
  return DBLL_DATA_UPDATED;
}

dbll_return_status_t dbll_delete(const char * key) {
  void * data = dbll_pop(key);
  if (data == NULL) {
    return DBLL_KEY_NOT_FOUND;
  }
  return DBLL_DATA_DELETED;
}

void * dbll_pop(const char * key) {
  Node_t * poped_node = get_node(key);
  Node_t * temp_node = NULL;
  void * data = NULL;
  if (poped_node == NULL) {
    return NULL;
  }
  if (doubly_linked_list.head == doubly_linked_list.tail) {
    data = poped_node->data;
    delete_node(poped_node);
    doubly_linked_list.head = NULL;
    doubly_linked_list.tail = NULL;
    doubly_linked_list.size = 0;
    return data;
  }
  if (poped_node == doubly_linked_list.head) {
    doubly_linked_list.head = doubly_linked_list.head->next;
    doubly_linked_list.head->prev = NULL;
    data = poped_node->data;
    delete_node(poped_node);
    doubly_linked_list.size--;
    return data;
  }
  if (poped_node == doubly_linked_list.tail) {
    doubly_linked_list.tail = doubly_linked_list.tail->prev;
    doubly_linked_list.tail->next = NULL;
    data = poped_node->data;
    delete_node(poped_node);
    doubly_linked_list.size--;
    return data;
  }
  temp_node = poped_node->prev;
  temp_node->next = poped_node->next;
  temp_node = poped_node->next;
  temp_node->prev = poped_node->prev;
  data = poped_node->data;
  delete_node(poped_node);
  doubly_linked_list.size--;
  return data;
}

void * dbll_pop_from_tail(void) {
  if (doubly_linked_list.tail == NULL) {
    return NULL;
  }
  Node_t * popped_node = NULL;
  void * data = doubly_linked_list.tail->data;
  if (doubly_linked_list.tail == doubly_linked_list.head) {
    delete_node(doubly_linked_list.tail);
    doubly_linked_list.tail = NULL;
    doubly_linked_list.head = NULL;
    doubly_linked_list.size = 0;
    return data;
  }
  popped_node = doubly_linked_list.tail;
  doubly_linked_list.tail = doubly_linked_list.tail->prev;
  doubly_linked_list.tail->next = NULL;
  delete_node(popped_node);
  doubly_linked_list.size--;
  return data;
}

void * dbll_pop_from_head(void) {
  if (doubly_linked_list.head == NULL) {
    return NULL;
  }
  Node_t * popped_node = NULL;
  void * data = doubly_linked_list.head->data;
  if (doubly_linked_list.head == doubly_linked_list.tail) {
    delete_node(doubly_linked_list.head);
    doubly_linked_list.tail = NULL;
    doubly_linked_list.head = NULL;
    doubly_linked_list.size = 0;
    return data;
  }
  popped_node = doubly_linked_list.head;
  doubly_linked_list.head = doubly_linked_list.head->next;
  doubly_linked_list.head->prev = NULL;
  delete_node(popped_node);
  doubly_linked_list.size--;
  return data;
}

void * dbll_get(const char * key) {
  void * data = dbll_search_from_head(key);
  return data;
}

void * dbll_get_from_tail(const char * key) {
  if (doubly_linked_list.tail == NULL) {
    return NULL;
  }
  return doubly_linked_list.tail->data;
}

void * dbll_get_from_head(const char * key) {
  if (doubly_linked_list.head == NULL) {
    return NULL;
  }
  return doubly_linked_list.head->data;
}
