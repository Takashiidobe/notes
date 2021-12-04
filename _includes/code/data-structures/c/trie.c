#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint8_t ALPHABET_SIZE = 26;
const uint8_t CHAR_CODE_A = 97;

struct letter {
  struct letter *next[ALPHABET_SIZE];
  bool end;
};

struct trie {
  struct letter *dummy;
};

struct letter *ltr_ctor() {
  struct letter *l = (struct letter *)malloc(sizeof(struct letter));
  l->end = false;
  return l;
}

void ltr_free(struct letter *l) {
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (l->next[i]) {
      ltr_free(l->next[i]);
    }
  }
  free(l);
}

struct trie *trie_ctor() {
  struct trie *t = (struct trie *)malloc(sizeof(struct trie));
  struct letter *d = (struct letter *)malloc(sizeof(struct letter));
  t->dummy = d;
  return t;
}

void free_trie(struct trie *t) {
  ltr_free(t->dummy);
  free(t);
}

void add_letter(struct letter *l, const char c) {
  if (!l->next[c - CHAR_CODE_A]) {
    struct letter *new_ltr = (struct letter *)malloc(sizeof(struct letter));
    l->next[c - CHAR_CODE_A] = new_ltr;
    l->end = true;
  }
}

void add_word(struct letter *l, const char *word) {
  struct letter *ptr = l;
  for (size_t i = 0; i < strlen(word); i++) {
    add_letter(ptr, word[i]);
    ptr = ptr->next[word[i] - CHAR_CODE_A];
  }
}

bool has_word(struct letter *l, const char *word) {
  struct letter *ptr = l;
  for (size_t i = 0; i < strlen(word); i++) {
    if (ptr->next[word[i] - CHAR_CODE_A])
      ptr = ptr->next[word[i] - CHAR_CODE_A];
    else
      return false;
  }
  return ptr->end == true;
}

int main() {
  struct trie *t = trie_ctor();
  add_word(t->dummy, "spongebob");
  add_word(t->dummy, "patrick");
  add_word(t->dummy, "squidward");
  add_word(t->dummy, "plankton");
  bool has_word_t = has_word(t->dummy, "spo");
  if (has_word_t) {
    puts("The word was found");
  } else {
    puts("The word was not found");
  }
  free_trie(t);
}
