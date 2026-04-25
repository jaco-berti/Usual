#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
#else
    #include <sys/stat.h>
    #define MKDIR(path) mkdir(path, 0777)
#endif

#define DIR_USUAL "C:/Usual"
#define DIR_KEY "C:/Usual/key"
#define DIR_SAVED "C:/Usual/saved"
#define SPECIAL_SYMBOLS 0
#define NUMBER_SYMBOLS 1
#define CHARS_MAIUSC_SYMBOLS 2
#define CHARS_MINUSC_SYMBOLS 3
#define MAX_EXCLUDED_SYMBOLS_SIZE 32
#define TOTAL_SYMBOLS 93
#define MIN_ASCII_SYMBOL 33
#define MAX_ASCII_SYMBOL 126
#define HASH_SIZE 64
#define SEPARATOR_HASH_SPACE 16

int create_folder(const char *dirname);
int create_key_file(const char *key);
char* join_all_strings(const int count, const char **crs);
int* get_symbols_group_ascii(const int symbols_group);
char* random_hash_seed(unsigned int seed, const int *exclude_symbols, int exclude_symbols_size);
void fill_integer_array(int *array, int size);
int set_exluded_size(int **array);
char* get_symbol_array();

int main() {
    int result = 0, i = 0, k = 0;

    // create folder if not exist
    result = create_folder(DIR_USUAL);
    if(result == 0) printf("[*] Folder %s successfully created!\n", DIR_USUAL);

    result = create_folder(DIR_SAVED);
    if(result == 0) printf("[*] Folder %s successfully created!\n", DIR_SAVED);

    // create key file
    result = create_folder(DIR_KEY);
    if(result == 0) printf("[*] Folder %s successfully created!\n", DIR_KEY);
    int *ascii_symbols = get_symbols_group_ascii(SPECIAL_SYMBOLS);
    int size = set_exluded_size(&ascii_symbols);
    char* fileName = random_hash_seed(time(NULL), ascii_symbols, size);
    printf("[*] File name hashed successfully with hash: %s\n", fileName);

    const char *key_path_char[] = {DIR_KEY, "/", fileName};
    char *key_path = join_all_strings(3, key_path_char);
    result = create_key_file(key_path);
    if(result == 0) printf("[*] Key added to your device\n");

    return 0;
}

int create_folder(const char *dirname) {
    if (MKDIR(dirname) == 0) {
        return 0; // success
    } else {
        if (errno == EEXIST) {
            return 1; // already exist
        } else {
            return 2; // creation error
        }
    }
}

int create_key_file(const char *key) {
    FILE *fptr;
    fptr = fopen(key, "w");
    fclose(fptr);
    return 0;
}

char* join_all_strings(int count, const char **crs) {
    size_t totale_len = 0;

    for (int i = 0; i < count; i++) {
        totale_len += strlen(crs[i]);
    }

    char *risultato = malloc(totale_len + 1);
    if (risultato == NULL) return NULL;

    risultato[0] = '\0'; 

    for (int i = 0; i < count; i++) {
        strcat(risultato, crs[i]);
    }

    return risultato;
}

char* random_hash_seed(unsigned int seed, const int *exclude_symbols, const int exclude_symbols_size) {
    // hash example: e3b0c44298fc1c14-9afbf4c8996fb924-27ae41e4649b934c-a495991b7852b855
    srand(seed);
    int i = 0, k = 0, j = 0, count = 0, excluded = 0, selected_count = (TOTAL_SYMBOLS - exclude_symbols_size);
    char *hash = malloc(HASH_SIZE * sizeof(char));
    char *symbols = get_symbol_array();
    char *selected_symbols = malloc(selected_count * sizeof(char));

    j = 0;
    for(i = 0; i < TOTAL_SYMBOLS; i++) {
        excluded = 0;
        for(k = 0; k < exclude_symbols_size; k++) {
            if(symbols[i] == exclude_symbols[k]) {
                excluded = 1;
                k = exclude_symbols_size;
            }
        }
        if(excluded == 0) {
            selected_symbols[j] = symbols[i];
            j++;
        }
    }

    for(i = 0; i < HASH_SIZE; i++) {
        char symbol_index = (rand() % selected_count);
        hash[i] = selected_symbols[symbol_index];
    }

    return hash;
}

int* get_symbols_group_ascii(const int symbols_group) {
    int *result = malloc(MAX_EXCLUDED_SYMBOLS_SIZE * sizeof(int));
    fill_integer_array(result, MAX_EXCLUDED_SYMBOLS_SIZE);
    int i = 0, k;
    switch (symbols_group) {
    case NUMBER_SYMBOLS:
        k = 0;
        for(i = 48; i <= 57; i++, k++) {
            result[k] = i;
        }
        break;
    case SPECIAL_SYMBOLS:
        k = 0;
        for(i = 33; i <= 47; i++, k++) {
            result[k] = i;
        }
        for(i = 58; i <= 64; i++, k++) {
            result[k] = i;
        }
        for(i = 91; i <= 96; i++, k++) {
            result[k] = i;
        }
        for(i = 123; i <= 126; i++, k++) {
            result[k] = i;
        }
        break;
    case CHARS_MAIUSC_SYMBOLS:
        k = 0;
        for(i = 65; i <= 90; i++, k++) {
            result[k] = i;
        }
        break;
    case CHARS_MINUSC_SYMBOLS:
        k = 0;
        for(i = 97; i <= 122; i++, k++) {
            result[k] = i;
        }
        break;
    }

    return result;
}

void fill_integer_array(int *array, int size) {
    int i = 0;
    for(i = 0; i < size; i++) {
        array[i] = 0;
    }
}

char* get_symbol_array() {
    int i, k = MIN_ASCII_SYMBOL;
    char *array = malloc(TOTAL_SYMBOLS * sizeof(int));
    for(i = 0; i < TOTAL_SYMBOLS; i++, k++) {
        array[i] = k;
    }
    return array;
}

int set_exluded_size(int **array) {
    int i, k, count = 0;

    for(i = 0; i < MAX_EXCLUDED_SYMBOLS_SIZE; i++) {
        if((*array)[i] != 0) {
            count++;
        }
    }

    int *temp = malloc(count * sizeof(int));

    k = 0;
    for(i = 0; i < MAX_EXCLUDED_SYMBOLS_SIZE; i++) {
        if((*array)[i] != 0) {
            temp[k++] = (*array)[i];
        }
    }

    free(*array);        // libera quello originale
    *array = temp;       // aggiorna il puntatore originale

    return count;
}