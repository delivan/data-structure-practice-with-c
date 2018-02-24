#include <stdlib.h>

#define STR_SIZE 100

/* 입력받은 문자들을 읽어 문자 앞뒤의 공백을 제외한 
 * 나머지 공백들을 제거하고 문자들의 총 갯수를 출력하는 프로그램
 * 배열로 받아 압축하는 함수와 포인터로 받아 압축하는 함수가 따로 있다*/

void read_line_with_compression(char str[]);
void compress(char *str);
void compress_with_additional_array(char str[]);

int main(int argc, char *argv[]) {
    char str[STR_SIZE];

    while (1) {
        printf("$ ");
        read_line_with_compression(str);
        printf("%s:%lu\n", str, strlen(str));
    }

    return 0;
}

void read_line_with_compression(char str[]) {
    int ch, i = 0;

    while ((ch = getchar()) != '\n')
        if (i < STR_SIZE-1)
            str[i++] = ch;

    str[i] = '\0';
    compress_with_additional_array(str);
}

void compress(char *str) {
    int i = 0, j = 0, ch;
    
    while (str[i] == ' ')
        i++;

    while (str[i] != '\0') {
        if ((str[i] != ' ') || ((str[i] == ' ') && (str[i-1] != ' '))) {
            str[j++] = str[i];
        }
        i++;
    }
    if (str[j-1] == ' ') 
        str[j-1] = '\0';
    else 
        str[j] = '\0';    
}

void compress_with_additional_array(char str[]) {
    char buf[STR_SIZE];
    int i = 0, j = 0, ch;
    
    while (str[i] == ' ')
        i++;

    while (str[i] != '\0') {
        if ((str[i] != ' ') || ((str[i] == ' ') && (str[i-1] != ' '))) {
            buf[j++] = str[i];
        }
        i++;
    }
    if (buf[j-1] == ' ') 
        buf[j-1] = '\0';
    else 
        buf[j] = '\0';
    
    strcpy(str, buf);
}

