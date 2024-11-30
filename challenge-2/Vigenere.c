#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#define FLAG_SIZE 64
#define KEY_LENGTH 7

char *initialize(void);

void main(void) {
    char *flag = initialize();
    
    // Read the key
    FILE *keyfile;
    keyfile = fopen("key", "r");
    if (keyfile == NULL) {
        puts("Error: could not open the key\r");
        exit(0);
    }
    fseek(keyfile, 0, SEEK_END);
    
    long keylength = ftell(keyfile);
    fclose(keyfile);

    unsigned char *key = malloc(keylength + 1);
    key[keylength] = '\0';
    srand(time(0));
    
    char key_string[2*keylength + 1];
    key_string[2*keylength] = '\0';
    
    for (int i = 0; i < keylength; i++) {
        key[i] = rand();
        snprintf(&key_string[2*i], 3, "%02x", key[i]);
    }
        
    // Read the riddle
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
    riddle[fsize] = '\0';
    
    // Encrypt the riddle
    printf("Here's an encrypted, hex-encoded riddle for you.\n");
    for (int i = 0; i < fsize; i++) {
        printf("%02x", riddle[i] ^ key[i % keylength]);
    }
    printf("\n");
    
    free(riddle);
    free(key);
    
    char answer[33];

    puts("Enter your solution:\r");
    if (!scanf("%32s", answer)) {
        puts("Sorry, that's not quite right.\r");
        puts("Error: unrecognized input\r");
        exit(1);
    }
    
    if (strcmp(answer, key_string)) {
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
