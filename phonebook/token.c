#include <stdio.h>
#include <string.h>

int main() {
    /* str[]은 char array로 문자열을 저장해서 수정이 가능하지만
     * *str은 string literal로 문자열을 저장하기 때문에 수정이 불가능하다.
     * 따라서 strtok는 문자열이 저장된 곳을 수정하기 때문에 *str을 수정하지 못한다*/
    char str[] = "now # is the time # to start preparing ### for the exam#";
//  char *str = "now # is the time # to start preparing ### for the exam#"; 
    char delim[] = "#";
    char *token;

    token = strtok(str, delim);
    while (token != NULL) {
        printf("next token is: %s:%lu\n", token, strlen(token)); 
        token = strtok(NULL, delim);
        printf("NULL token?%s\n", token);
    }

    return 0;
}
