#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <math.h>

// error handeling functions
int is_in_bounds(int value);
int is_valid(char *num);

// converting functions
int convert_to_num(char c);
char convert_to_char(int num);
int find_len(unsigned long int dec_num, int to);

// error message printing functions
void print_error_message(uint8_t param);

int main() {
    printf("This converter does weird stuff when you input large numbers\nYOU'RE BETTER OFF USING SOMETHING ELSE!!!\n");

    char *num = NULL;
    size_t size = 0;
    size_t chars_read;
    int from;
    int to;

    // handle input
    printf("number: ");
    chars_read = getline(&num, &size, stdin);
    if (!is_valid(num)) {
        print_error_message(2);
        return 1;
    }
    printf("from: ");
    scanf("%d", &from);
    if (!is_in_bounds(from)) {
        print_error_message(0);
        return 1;
    }
    printf("to: ");
    scanf("%d", &to);
    if (!is_in_bounds(to)) {
        print_error_message(1);
        return 1;
    }

    // loop to convert the number into decimal
    unsigned long int dec_number = 0;
    unsigned int temp;
    for (int i = 0; i < chars_read - 1; i++) {
        temp = convert_to_num(num[i]);
        dec_number += (int)(temp * pow(from, chars_read - 2 - i));
    }
    
    // loop to convert the decimal number into whatever base the user entered as 'to'
    int tmp;
    int len = find_len(dec_number, to);
    char result[len + 1];
    for (int i = 0; i < len; i++) {
        tmp = dec_number % to;
        dec_number = (int)((dec_number - tmp) / to);
        result[len - 1 - i] = convert_to_char(tmp);
    }
    result[len] = '\0';

    // print the reuslt 
    printf("%s\n", result);

    // free the allocated memory
    free(num);

}

//=====================================~Functions~=====================================

int is_in_bounds(int value) {
    if (value < 2 || value > 36) {
        return 0;
    } else return 1;
}

int is_valid(char *num) {
    for (int i = 0; i < strlen(num); i++) {
        if (num[i] == '\n' || num[i] == '\0') {
            continue;
        }
        // if charcter is not a digit nor a alphabetic character (it is a special cahracter os something else)
        if (!(isdigit(num[i]) || isalpha(num[i]))) {
            return 0;
        }
    }
    return 1;
}

int convert_to_num(char c) {
    if (c == '\0' || c == '\n')
        return 0;
    if (isdigit(c))
        return c - '0';
    return (int)(tolower(c)) - 87; 
}

char convert_to_char(int num) {
    if (num > 9) {
        return (char)(num + 87);
    } else return (char)(num + 48);
}

int find_len(unsigned long int dec_num, int to) {
    unsigned int count = 0;
    while ((int)(dec_num / to) != 0) {
        dec_num = (dec_num - (dec_num % to)) / to;
        count++;
    }
    return count + 1;
}

void print_error_message(uint8_t param) {
    switch (param) {
        case 0:
            printf("value 'from' must be from range 2-36\n");
            break;
        case 1:
            printf("value 'to' must be from range 2-36\n");
            break;
        case 2:
            printf("Invalid number entered\n");
            break;
        default:
            printf("unknown error ");
            break;
    }
}