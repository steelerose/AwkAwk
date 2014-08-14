#include <stdio.h>
#include <string.h>

#define BUFF_LEN  500
#define TAG       "CPU"

int main() {
    char input[BUFF_LEN];
    char tempInput[BUFF_LEN];
    char line[BUFF_LEN];
    int numberOfCPUs = 0;
    int numberOfLines = 0;
    int interruptsCount = 0;
    int tempInt = 0;
    char *p;
    int i;
    char tempStr[50];
    FILE * file;

    file = fopen("/proc/interrupts", "r");

    if (fgets(input, sizeof(input), file) == NULL) {
        printf("Invalid input: File is empty.\n");
        fclose(file);
        return 0;
    }

    p = input;
    while ((p = strstr(p, TAG)) != NULL) {
        numberOfCPUs++;
        p += sizeof(TAG);
    }

    if (!numberOfCPUs) {
        printf("Invalid input: No reference to CPU\n");
        fclose(file);
        return 0;
    }

    int cpuCounts[numberOfCPUs];
    for (i = 0; i < numberOfCPUs; i++) {
        cpuCounts[i] = 0;
    }

    while (fscanf(file, "%s", tempStr) != EOF) {
        printf("Line: '");
        for (i = 0; i < numberOfCPUs; i++) {
            fscanf(file, "%d", &tempInt);

            cpuCounts[i] += tempInt;

            printf("%d", tempInt);
            if (i < numberOfCPUs - 1)
                printf(" ");
        }
        printf("'\nTotals: ");

        for (i = 0; i < numberOfCPUs; i++) {
            printf("CPU%d %d  ", i + 1, cpuCounts[i]);
        }
        printf("\n\n");

        numberOfLines++;
        fgets(tempInput, sizeof(tempInput), file);
    }

    for (i = 0; i < numberOfCPUs; i++) {
        cpuCounts[i] = cpuCounts[i] / numberOfLines;
    }

    printf("\n\nCPU count: %d\n\n", numberOfCPUs);
    printf("Average interrupt values:\n");
    for (i = 0; i < numberOfCPUs; i++) {
        printf("CPU%d\t\t", i + 1);
    }
    printf("\n");

    for (i = 0; i < numberOfCPUs; i++) {
        printf("%d\t\t", cpuCounts[i]);
    }
    printf("\n\n");
    
    fclose(file);
    return 0;
}