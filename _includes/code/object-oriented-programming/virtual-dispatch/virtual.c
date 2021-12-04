#include <stdio.h>

typedef struct Animal {
  const char *name;
  void (*move)(const struct Animal *);
} Animal_t;

void fly(const Animal_t *a) { printf("fly %s\n", a->name); }
void walk(const Animal_t *a) { printf("walk %s\n", a->name); }
void animal_move(const Animal_t *a) { a->move ? a->move(a) : walk(a); }

int main(void) {
  const Animal_t animals[] = {
      {.name = "Animal"}, {.name = "Bird", .move = fly}, {.name = "Elephant"}};
  const size_t animals_len = sizeof(animals) / sizeof(Animal_t);

  for (int i = 0; i < animals_len; i++) {
    const Animal_t animal = animals[i];
    animal_move(&animal);
  }
}
