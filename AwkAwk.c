#include <stdio.h>
#include <string.h>

int main() {
  char input[500];

  fgets(input, 499, stdin);

  printf("Input: %s\n", input);

  if (strlen(input) == 0) {
    printf("Invalid input: File is empty.\n");
  } else if (!strstr(input, "CPU")) {
    printf("Invalid input: No reference to CPU\n");
  } else {

    int count = 0;
    int i = 0;
    while (i < strlen(input)) {
      if (strstr(input, "CPU")) {
        count++;
        *strstr(input, "CPU") = 'x';
      }

      i = i + 3;
    }

    printf("CPU count: %d\n", count);
  }

  return 0;
}
