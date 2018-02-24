#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "string_tools.h"

#define NUM_CHARS 256
#define BUFFER_LENGTH 100

typedef struct artist Artist;
typedef struct song Song;
typedef struct snode SNode;

struct artist {
    char *name;
    Artist *next;
    SNode *head, *tail;
};

struct song {
    Artist *artist;
    char *title;
    char *path;
    int index;
};

struct snode {
    struct snode *prev, *next;
    Song *song;
};


void directory_initialize();
void load();
Artist *create_artist_instance(char *name);
Song *create_song_instance(Artist *ptr_artist, char *title, char *path);
SNode *create_snode_instance(Song *ptr_song);
Artist *add_artist(char *name);
void add_song(char *artist, char *title, char *path);
void add_node_to_artist(Artist *ptr_artist, SNode *ptr_snode);
void add_node_to_index(Song *ptr_song, SNode *ptr_snode); 
void status();
void print_artist(Artist *ptr_artist);
void print_song(Song *ptr_song);
void search_artist(char *name);
void search_song(char *name, char *title);
Artist *find_artist(char *name);
SNode *find_snode(Artist *ptr_artist, char *title); 
SNode *find_song(int index);
void play(int index);
void save_as_file(FILE *fp);
void save_artist(Artist *ptr_artist, FILE *fp);
void save_song(Song *ptr_song, FILE *fp); 
void remove_index_snode(int index);
void remove_artist_snode(Artist *ptr_artist, SNode *ptr_snode);
void remove_artist(Artist *ptr_artist);
void destroy_artist(Artist *ptr_artist); 
void destroy_song(Song *ptr_song);

#endif
