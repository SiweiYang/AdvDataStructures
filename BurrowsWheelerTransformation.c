#include "BurrowsWheelerTransformation.h"
#include <cstdio>


int main() {
  char *a = "banana$";
  char *b = "$banana";
  char* *array = populateRotationArray("banana$", 7);
  for (int i = 0; i < 7; i++) {
    printf("%s\n", array[i]);
  }
  sortByLexOrder("abn", array, 7);
  for (int i = 0; i < 7; i++) {
    printf("%s\n", array[i]);
  }
  
  char *t = absorbRotationArray(array, 7);
  printf("%s\n", t);
  
  printf("%s\n", recoverRotationArray("abn", t, 7));
}
