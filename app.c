#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//global array for mapping [A-Z] -> [0-25]
char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                     'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

char *read_input(int mode);
int *map_to_int(char *message, int len);
int char_to_int(char input);
char *map_to_char(int *message, int len);
int *cipher(int *message, int message_len, int *key, int key_len, int mode);

int main() {
    //get raw message and key
    char *message = read_input(0);
    char *key = read_input(1);
    //lengths not including '\n
    int message_len = strlen(message) - 1;
    int key_len = strlen(key) - 1;

    //map message and key -> [0-25]
    int *mapped_message = map_to_int(message, message_len);
    int *mapped_key = map_to_int(key, key_len);

    //encrypt
    int *encrypted_map = cipher(mapped_message, message_len, mapped_key, key_len, 0);
    char *encrypted_message = map_to_char(encrypted_map, message_len);
    printf("%s", encrypted_message);
    
    //free resources
    free(message);
    free(mapped_message);
    free(mapped_key);
    free(encrypted_map);
    free(encrypted_message);
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

int *map_to_int(char *message, int len) {
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

char *map_to_char(int *message, int len) {
    int val;
    // + 2 for null terminator and newline
    char *mapped_to_char = (char*)malloc((len + 2) * sizeof(char)); 

    for (int i = 0; i < len; i++) {
        val = message[i];
        mapped_to_char[i] = alphabet[val];
    }
    // null terminate the string
    mapped_to_char[len] = '\n'; 
    mapped_to_char[len + 1] = '\0';

    return mapped_to_char;
}

//Vigenere Cipher
int *cipher(int *message, int message_len, int *key, int key_len, int mode) {
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

