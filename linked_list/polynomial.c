#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POLYS 10
#define BUFFER_LENGTH 50

/* global variables here */

typedef struct term {
    int coef;
    int expo;
    struct term *next;
} Term;

typedef struct polynomial {
    char name;
    Term *first;
    int size;
} Polynomial;

Polynomial *polys[MAX_POLYS];
int n = 0;                      // number of polynomial

/* function prototype here */

Term *create_term_instance();
Polynomial *create_polynomial_instance(char name);
void add_term(int c, int e, Polynomial *poly);
int eval_poly(Polynomial *poly, int x);
int eval_term(Term *term, int x);
void print_poly(Polynomial *poly); 
void print_term(Term *term);
int read_line(FILE *fp, char line[], int buf_len);
void process_command();
void handle_print(char name); 
void handle_calc(char name, char *x_str); 
void handle_definition(char *expression);
void erase_blanks(char *expression);
Polynomial *create_by_parse_polynomial(char name, char *body);
int parse_and_add_term(char *expr, int begin, int end, Polynomial *p_poly);
void insert_polynomial(Polynomial *ptr_poly);
void destroy_polynomial(Polynomial *ptr_poly);
Polynomial *create_by_add_two_polynomials(char f_name, char left, char right);

Term *create_term_instance() {
    Term *t = (Term *)malloc(sizeof(Term));
    t->coef = 0;
    t->expo = 0;
    t->next = NULL;
   
    return t;
}

Polynomial *create_polynomial_instance(char name) {
    Polynomial *p = (Polynomial *)malloc(sizeof(Polynomial));
    p->name = name;
    p->first = NULL;
    p->size = 0;

    return p;
}

void add_term(int c, int e, Polynomial *poly) {
    if (c == 0)
        return;
    Term *p = poly->first;
    Term *q = NULL;
    while (p!= NULL && p->expo > e) {
        q = p;
        p = p->next;
    }
    if (p != NULL && p->expo == e) {
        p->coef += c;
        if (p->coef == 0) {
            if (q == NULL)
                poly->first = p->next;
            else
                q->next = p->next;
            poly->size--;
            free(p);
        }
        return;
    }
    Term *new = create_term_instance();
    new->coef = c;
    new->expo = e;
    if (q == NULL) {
        new->next = poly->first;
        poly->first = new;
    } else {
        new->next = p;
        q->next = new;
    }
    poly->size++;
}

int eval_poly(Polynomial *poly, int x) {
    int result;
    Term *term = poly->first;

    for (int i = 0; i < poly->size; i++) {
        result += eval_term(term, x);
        term = term->next;
    }

    return result;
}

int eval_term(Term *term, int x) {
    int result = term->coef;
    for (int i = 0; i < term->expo; i++) 
        result *= x;

    return result;
}

void print_poly(Polynomial *poly) { 
    Term *term = poly->first;
    if (term == NULL)
        return;
    
    printf("%c = ", poly->name);
    for (int i = 0; i < poly->size; i++) {
        print_term(term);
        term = term->next;
    }
    fputc('\n', stdout);
}
// +x, -x, 4x, -4x, +4x^2, -20
void print_term(Term *term) {
    if (term->coef > 0) {
        if (term->coef == 1) {
            if (term->expo == 0) {
                printf("+%d", term->coef);
            } else if (term->expo == 1) {
                printf("+x");
            } else {
                printf("+x^%d", term->expo);
            }
        } else {
            if (term->expo == 0) {
                printf("+%d", term->coef);
            } else if (term->expo == 1) {
                printf("+%dx", term->coef);
            } else {
                printf("+%dx^%d", term->coef, term->expo);
            }
        }
    } else {
        if (term->coef == -1) {
            if (term->expo == 0) {
                printf("%d", term->coef);
            } else if (term->expo == 1) {
                printf("-x");
            } else {
                printf("-x^%d", term->expo);
            }
        } else {
            if (term->expo == 0) {
                printf("%d", term->coef);
            } else if (term->expo == 1) {
                printf("%dx", term->coef);
            } else {
                printf("%dx^%d", term->coef, term->expo);
            }
        }
    }
}

int read_line(FILE *fp, char line[], int buf_len) {
    int ch, i = 0;
    
    while ((ch = fgetc(fp)) != '\n' && ch != EOF)
        if (i < buf_len - 1)
            line[i++] = ch;

    line[i] = '\0';

    return i;
}

void process_command() {
    char command_line[BUFFER_LENGTH];
    char copied[BUFFER_LENGTH];
    char *command, *arg1, *arg2;

    while (1) {
        printf("$ ");
        if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
            continue;
        strcpy(copied, command_line);
        command = strtok(command_line, " ");
        if (strcmp(command, "print") == 0) {
            arg1 = strtok(NULL, " ");
            if (arg1 == NULL) {
                printf("Invalid argument.\n");
                continue;
            }
            handle_print(arg1[0]);
        } else if (strcmp(command, "calc") == 0) {
            arg1 = strtok(NULL, " ");
            if (arg1 == NULL) {
                printf("Invalid argument.\n");
                continue;
            }
            arg2 = strtok(NULL, " ");
            if (arg2 == NULL) {
                printf("Invalid argument.\n");
                continue;
            }
            handle_calc(arg1[0], arg2);
        } else if (strcmp(command, "exit") == 0) 
            break;
        else
            handle_definition(copied);
    }
}

void handle_print(char name) {
    for (int i = 0; i < n; i++) {
        if (polys[i]->name == name) {
            print_poly(polys[i]);
            return;
        }
    }
}

void handle_calc(char name, char *x_str) {
    int x = atoi(x_str);
    for (int i = 0; i < n; i++) {
        if (polys[i]->name == name) {
            printf("%d\n", eval_poly(polys[i], x));
            return;
        }
    }
}

//f = g + h
//f = 2x^2+x+1
void handle_definition(char *expression) {
    erase_blanks(expression);
    printf("%s\n", expression);
    char *f_name, *exp_body;
    f_name = strtok(expression, "=");
    if (f_name == NULL || strlen(f_name) != 1) {
        printf("Invalid funtion name\n");
        return;
    }
    exp_body = strtok(NULL, "=");
    if (exp_body == NULL || strlen(exp_body) <= 0) {
        printf("Invalid expression\n");
        return;
    }
    if ((exp_body[0] >= 'a') && (exp_body[0] <= 'z') && (exp_body[0] != 'x')) {
        char *left_f_name = strtok(exp_body, "+");
        if (left_f_name == NULL || strlen(left_f_name) != 1) {
            printf("Invalid left function name\n");
            return;
        }
        char *right_f_name = strtok(NULL, "+");
        if (right_f_name == NULL || strlen(right_f_name) != 1) {
            printf("Invalid right function name\n");
            return;
        }
        Polynomial *poly = create_by_add_two_polynomials(f_name[0], left_f_name[0], right_f_name[0]);
        if (poly == NULL) {
            printf("create poly by adding error\n");
            return;
        }
        insert_polynomial(poly);
    } else {
        Polynomial *poly = create_by_parse_polynomial(f_name[0], exp_body);
        if (poly == NULL) {
            printf("create poly by parsing error\n");
            return;
        }
        insert_polynomial(poly);
    }
}

void erase_blanks(char expression[]) {
    char *buf1, buf2[BUFFER_LENGTH];
    int buf_len;

    buf1 = strtok(expression, " ");
    strcpy(buf2, buf1);
    buf_len = strlen(buf1);
    while ((buf1 = strtok(NULL, " ")) != NULL) {
        strcat(buf2, buf1);
        buf_len += strlen(buf1);
    }
    strcpy(expression, buf2);
    expression[buf_len] = '\0';
}

Polynomial *create_by_parse_polynomial(char name, char *body) {
    Polynomial *ptr_poly = create_polynomial_instance(name);
    int i = 0, begin_term = 0;

    while (i < strlen(body)) {
        if(body[i] == '+' || body[i] == '-') 
            i++;
        while (i < strlen(body) && body[i] != '+' && body[i] != '-')
            i++;
        int result = parse_and_add_term(body, begin_term, i, ptr_poly);
        if (result == 0) {
            destroy_polynomial(ptr_poly);
            return NULL;
        }
        begin_term = i;
    }
    
    return ptr_poly;
} 
// +x, -x, 4x^2, -4x, 5
int parse_and_add_term(char *expr, int begin, int end, Polynomial *p_poly) {
    int i = begin;
    int sign_coef = 1, coef = 0, expo = 0;
    if (expr[i] == '+')
        i++;
    else if (expr[i] == '-') {
        sign_coef = -1;
        i++;
    } 
    while (expr[i] >= '0' && expr[i] <= '9') {
        coef = (coef * 10) + atoi(&expr[i]);
        i++;
    }
    if (coef == 0) 
        coef = sign_coef;
    else 
        coef *= sign_coef;
    if (i == end) {
        add_term(coef, expo, p_poly);
        return 1;
    }
    if (expr[i] != 'x')
        return 0;
    i++;
    if (i == end) {
        expo = 1;
        add_term(coef, expo, p_poly);
        return 1;
    }
    if (expr[i] != '^')
        return 0;
    i++;
    while (expr[i] >= '0' && expr[i] <= '9') {
        expo = (expo * 10) + atoi(&expr[i]);
        i++;
    }
    add_term(coef, expo, p_poly);
    return 1;
}

void insert_polynomial(Polynomial *ptr_poly) {
    for (int i = 0; i < n; i++) {
        if (polys[i]->name == ptr_poly->name) {
            destroy_polynomial(polys[i]);
            polys[i] = ptr_poly;
            return;
        }
    }
    polys[n++] = ptr_poly;
}

void destroy_polynomial(Polynomial *ptr_poly) {
    if (ptr_poly == NULL)
        return;
    Term *t = ptr_poly->first, *tmp;
    while (t != NULL) {
        tmp = t;
        t = t->next;
        free(tmp);
    }
    free(ptr_poly);
}
// g, h, z 존재
// f = g + h
// g = g + h
// f = h + f
// g = z + h
// f = g + g
Polynomial *create_by_add_two_polynomials(char f_name, char left, char right) {
    Polynomial *poly = create_polynomial_instance(f_name);
    Term *adding_term;
    int result = 0;
    for (int i = 0; i < n; i++) {
        if (polys[i]->name == left || polys[i]->name == right) {
            adding_term = polys[i]->first;
            while (adding_term != NULL) {
                add_term(adding_term->coef, adding_term->expo, poly);
                adding_term = adding_term->next;
            }
            result++;
            if (polys[i]->name == left && polys[i]->name == right) {
                adding_term = polys[i]->first;
                while (adding_term != NULL) {
                    add_term(adding_term->coef, adding_term->expo, poly);
                    adding_term = adding_term->next;
                }
                result++;
            }
        }
    }
    if (result != 2)
        return NULL;

    return poly;
}

int main() {
    process_command();
    
    return 0;
}
