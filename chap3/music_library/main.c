#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_tools.h"
#include "library.h"

void process_command();
void handle_load();
void handle_add();
void handle_status(); 
void handle_search();
void handle_play();
void handle_save();
void handle_remove();

int main() {
    directory_initialize();
    handle_load();
    process_command();
}

void process_command() {
    char command_line[BUFFER_LENGTH];
    char *command;

    while (1) {    
        printf("$ ");       // prompt
        
        if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
            continue;           

        command = strtok(command_line, " ");
        if (strcmp(command, "add") == 0)
            handle_add();
        else if (strcmp(command, "status") == 0)
            handle_status(); 
        else if (strcmp(command, "search") == 0)
            handle_search();
        else if (strcmp(command, "play") == 0)
            handle_play();
        else if (strcmp(command, "save") == 0)
            handle_save();
        else if (strcmp(command, "remove") == 0)
            handle_remove();
        else if (strcmp(command, "exit") == 0)
            break;          
    }
}

void handle_load() {
    char buffer[BUFFER_LENGTH];
    
    printf("Data file name? ");
    if (read_line(stdin, buffer, BUFFER_LENGTH) <= 0)
        return;

    FILE *fp = fopen(buffer, "r");
    if (fp == NULL) {
        printf("No such file exists.\n");
        return;
    }
    load(fp);
    fclose(fp);
}

void handle_add() {
    char buffer[BUFFER_LENGTH];
    char *artist = NULL, *title = NULL, *path = NULL;

    printf("    Artist: ");
    if (read_line(stdin, buffer, BUFFER_LENGTH) > 0)
        artist = strdup(buffer);
    printf("    Title: ");
    if (read_line(stdin, buffer, BUFFER_LENGTH) > 0)
        title = strdup(buffer);
    printf("    Path: ");
    if (read_line(stdin, buffer, BUFFER_LENGTH) > 0)
        path = strdup(buffer);
 
    /* add to the music library */    
    add_song(artist, title, path);
}

void handle_status() {
    printf("Status\n");
    status();
}

void handle_search() {
    char name[BUFFER_LENGTH], title[BUFFER_LENGTH];

    printf("    Artist: ");
    if (read_line(stdin, name, BUFFER_LENGTH) <= 0) {
        printf("Artist name required\n");
        return;
    }
    printf("    Title: ");
    if (read_line(stdin, title, BUFFER_LENGTH) <= 0)
        search_artist(name);
    else
        search_song(name, title);
}

void handle_play() {
    char *index_str;
    
    if ((index_str = strtok(NULL, " ")) == NULL)
        return;

    int index = atoi(index_str);
    play(index);
}

void handle_save() {
    char *file_name;
    if ((file_name = strtok(NULL, " ")) == NULL)
        return;

    FILE *fp = fopen(file_name, "w");
    save_as_file(fp);
    fclose(fp);
}

void handle_remove() { 
    char *index_str;

    if ((index_str = strtok(NULL, " ")) == NULL)
        return;
   
    int index = atoi(index_str);
    remove_index_snode(index);
}
