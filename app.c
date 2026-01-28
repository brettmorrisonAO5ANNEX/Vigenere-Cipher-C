#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//global array for mapping [A-Z] -> [0-25]
char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                     'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

char *read_input(int mode);
int *map_to_int(char *message);
int char_to_int(char input);
char *map_to_char(int *message);
int *cipher(int *message, int *key, int mode);

int main() {
    //get raw message and key
    char *message = read_input(0);
    char *key = read_input(1);

    //map message and key -> [0-25]
    int *mapped_message = map_to_int(message);
    int *mapped_key = map_to_int(key);

    //encrypt
    int *encrypted_map = cipher(mapped_message, mapped_key, 0);
    char *encrypted_message = map_to_char(encrypted_map);

    printf("%s", encrypted_message);
    

    //free resources
    free(message);
    free(mapped_message);
    return 0;
};

char *read_input(int mode) {
    char *message = NULL;
    size_t buffer_size = 0;
    ssize_t chars_read;

    if (mode == 0) {
        printf("enter message: ");
    } else {
        printf("enter key: ");
    }

    chars_read = getline(&message, &buffer_size, stdin);
    if (chars_read == -1) {
        printf("error reading input");
        free(message);
        exit(1);
    }

    return message;
}

int *map_to_int(char *message) {
    size_t len = strlen(message);
    char c;
    int val;
    int *mapped_message = (int*)malloc(len * sizeof(int));

    for (int i = 0; i < len; i++) {
        c = (char)message[i];

        //c must not be end of string
        if (c != '\n' && c != '\0') {
            val = char_to_int(c);
        }
        //c must be a character in the alphabet
        if (val < 0) {
            printf("invalid character: %c\n", c);
            free(message);
            free(mapped_message);
            exit(1);
        }
        mapped_message[i] = val;
    }

    return mapped_message;
};

//maps [A-Z] -> [0-25]
int char_to_int(char input) {
    for (int i = 0; i < sizeof(alphabet); i++) {
        if (input == alphabet[i]){
            return i;
        }
    }

    //otherwise character is not in the allowed alphabet
    return -1;
};

char *map_to_char(int *message) {
    int len = sizeof(message);
    int val;
    char *mapped_to_char = (char*)malloc(len * sizeof(char));

    for (int i = 0; i < len; i++) {
        val = message[i];
        mapped_to_char[i] = alphabet[val];
    }

    return mapped_to_char;
}

//Vigenere Cipher
int *cipher(int *message, int *key, int mode) {
    int message_len = sizeof(message);
    int key_len = sizeof(key);
    int t;
    int k;
    int* processed_message = (int*)malloc(message_len * sizeof(int));

    for (int i = 0; i < message_len; i++) {
        t = message[i];
        k = key[i % key_len];

        //encryption
        if (mode == 0) {
            processed_message[i] = (t + k) % 26;
        } 
        //decryption
        else {
            processed_message[i] = (t - k) % 26;
        }
    }

    return processed_message;
};

