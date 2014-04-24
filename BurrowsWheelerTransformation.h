#ifndef	BURROWS_WHEELER
#define	BURROWS_WHEELER

#define	TERMINAL	'$'
#define	EOL		'\0'

unsigned int lexOrder(char *alphabet, char ch) {
  int counter = 1;
  if (ch == TERMINAL)return 0;

  while(*(alphabet+counter-1) != ch)counter++;

  return counter;
}

bool lexOrdered(char *alphabet, char *less, char *greater) {
  char left = *less, right = *greater;
  if (left == EOL && right == EOL)return true;
  if (left == EOL)return true;
  if (right == EOL)return false;

  unsigned int leftOrder = lexOrder(alphabet, left), rightOrder = lexOrder(alphabet, right);
  if (leftOrder == rightOrder)return lexOrdered(alphabet, less + 1, greater + 1);
  return leftOrder < rightOrder;
}

void sortByLexOrder(char *alphabet, char* *texts, int size, int offset = 0) {
  if (size < 2)return;

  unsigned int startPos = 1, endPos = size - 1;
  bool step;
  char *swap;
  while (startPos <= endPos) {
    step = lexOrdered(alphabet, *texts + offset, *(texts+startPos) + offset);
    if (step) {
      startPos++;
    } else {
      swap = *(texts + endPos);
      *(texts + endPos) = *(texts + startPos);
      *(texts + startPos) = swap;
      endPos--;
    }
  }
  swap = *(texts + startPos - 1);
  *(texts + startPos - 1) = *texts;
  *texts = swap; 

  sortByLexOrder(alphabet, texts, startPos - 1, offset);
  sortByLexOrder(alphabet, texts + startPos, size - startPos, offset);
}

char* *populateRotationArray(char *text, int size) {
  char* *array = new char*[size + 1];
  array[size] = 0;
  for (int i = 0; i < size; i ++) {
    array[i] = new char[size + 1];
    array[i][size] = 0;
    for (int j = 0; j < size; j++) {
      array[i][j] = text[(i + j) % size];
    }
  }
  
  return array;
}

char *absorbRotationArray(char* *texts, int size) {
  char *array = new char[size + 1];
  array[size] = 0;
  for (int i = 0; i < size; i ++) {
    array[i] = texts[i][size - 1];
  }
  
  return array;
}

char *recoverRotationArray(char* alphabet, char* text, int size) {
  char* *array = populateRotationArray(text, size);
  
  for (int i = 1; i < size; i++) {
    sortByLexOrder(alphabet, array, size, size - i);
    for ( int j = 0; j < size; j++) {
      array[j][size - i - 1] = text[j];
    }
  }
  
  char *t = 0;
  for (int i = 0; i < size; i++) {
    if (array[i][size - 1] == TERMINAL) {
      t = array[i];
    } else {
      delete array[i];
    }
  }
  delete array;
  
  return t;
}

#endif
