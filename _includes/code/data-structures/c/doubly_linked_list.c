#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  const char *str;
  struct Node *next;
  struct Node *prev;
};

struct Node *node_ctor(const char *_str) {
  struct Node *n = malloc(sizeof(struct Node));
  n->str = _str;
  n->next = NULL;
  n->prev = NULL;
  return n;
}

struct DoublyLinkedList {
  struct Node *head;
  struct Node *tail;
  size_t length;
};

struct DoublyLinkedList list_ctor(const char *_str) {
  struct Node *n = node_ctor(_str);
  struct DoublyLinkedList dll = {n, n, 1};
  return dll;
}

void insert(struct DoublyLinkedList *dll, const char *_str, size_t index) {
  assert(index <= dll->length);
  struct Node *n = node_ctor(_str);
  if (index == 0) {
    n->next = dll->head;
    dll->head->prev = n;
    dll->head = n;
  } else if (index == dll->length) {
    n->prev = dll->tail;
    dll->tail->next = n;
    dll->tail = n;
  } else {
    size_t i = 0;
    struct Node *head_ptr = dll->head;
    while (i < index) {
      head_ptr = head_ptr->next;
      i++;
    }
    struct Node *temp;
    temp = head_ptr->next;
    head_ptr->next = n;
    n->prev = head_ptr;
    n->next = temp;
    temp->prev = n;
  }
  dll->length++;
}

void print_list(struct DoublyLinkedList *l) {
  struct Node *head = l->head;

  while (head) {
    printf("%s\n", head->str);
    head = head->next;
  }
}

void print_head(struct DoublyLinkedList *l) {
  if (l->head)
    printf("The head is: %s\n", l->head->str);
}

void print_tail(struct DoublyLinkedList *l) {
  if (l->tail)
    printf("The tail is: %s\n", l->tail->str);
}

void free_list(struct DoublyLinkedList *l) {
  struct Node *head = l->head;
  struct Node *temp;

  while (head) {
    temp = head;
    head = head->next;
    free(temp);
  }
}

bool find(struct DoublyLinkedList *l, const char *str) {
  struct Node *n = l->head;
  while (n) {
    if (n->str == str)
      return true;
    n = n->next;
  }
  return false;
}

void find_and_delete(struct DoublyLinkedList *l, const char *str) {
  struct Node *n = l->head;
  size_t index = 0;
  while (n) {
    if (n->str == str) {
      if (index == 0) {
        l->head = l->head->next;
        l->head->prev = NULL;
      } else if (index == l->length) {
        l->tail = l->tail->prev;
        l->tail->next = NULL;
      } else {
        struct Node *next = n->next;
        struct Node *prev = n->prev;
        next->prev = prev;
        prev->next = next;
      }
      free(n);
      l->length--;
    } else {
      n = n->next;
      index++;
    }
  }
}

int main() {
  struct DoublyLinkedList l = list_ctor("Second");
  insert(&l, "Third", 1);
  insert(&l, "First", 0);
  insert(&l, "Fourth", 3);
  insert(&l, "inserted", 2);
  insert(&l, "random", 3);
  find_and_delete(&l, "inserted");
  print_list(&l);
  bool a = find(&l, "Third");
  bool b = find(&l, "garbage");
  if (a)
    printf("Found \"Third\"\n");
  if (b)
    printf("Found \"garbage\"\n");
  free_list(&l);
}
