#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define FLAG_SIZE 64

char *initialize(void);

void main(void) {
    char *flag = initialize();
    
    FILE *file;
    file = fopen("riddle.txt", "r");
    if (file == NULL) {
        puts("Error: could not open the riddle\r");
        exit(0);
    }
    
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    char *riddle = malloc(fsize + 1);
    fread(riddle, fsize, 1, file);
    fclose(file);
    riddle[fsize] = 0;
    
    unsigned char *key = malloc(6);
    uint64_t key_int = 0;
    
    srand(time(0));
    
    for (int i = 0; i < 6; i++) {
        key[i] = rand();
        key_int += ((uint64_t) key[i] << (8*(5-i)));
    }

    printf("Here's an encrypted, hex-encoded riddle for you.\n");
    for (int i = 0; i < fsize; i++) {
        printf("%02x", riddle[i] ^ key[i % 6]);
    }
    printf("\n");
    
    free(riddle);
    
    uint64_t answer = 0;

    puts("Enter your solution:\r");
    if (!scanf("%llu", &answer)) {
        puts("Sorry, that's not quite right.\r");
        puts("Error: unrecognized input\r");
        exit(1);
    }
    
    if (answer != key_int) {
        puts("Sorry, that's not quite right.\r");
        exit(1);
    }

    printf("%s\r\n", flag);

    exit(0);
}

char *initialize(void) {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    char *flag = malloc(FLAG_SIZE);
    FILE *file;
    file = fopen(FLAG_FILE, "r");
    if (file == NULL) {
        puts("Error: could not open the flag\r");
        exit(0);
    }
    fgets(flag, FLAG_SIZE, file);
    fclose(file);
    return flag;
}
