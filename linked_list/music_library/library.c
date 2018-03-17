#include "library.h"

#define INDEX_LENGTH 100

Artist *artist_directory[NUM_CHARS];
SNode *index_directory[INDEX_LENGTH];
int num_index = 0;

void directory_initialize() {
    for (int i = 0; i < NUM_CHARS; i++)
        artist_directory[i] = NULL;
    for (int i = 0; i < INDEX_LENGTH; i++)
        index_directory[i] = NULL;
}

void load(FILE *fp) {
    char buffer[BUFFER_LENGTH];
    char *name, *title, *path;

    while (1) {
        if (read_line(fp, buffer, BUFFER_LENGTH) <= 0)
            break; 
        
        name = strtok(buffer, "#");
        if (strcmp(name, " ") == 0)
            name = NULL;
        else
            name = strdup(name);
        
        title = strtok(NULL, "#");
        if (strcmp(title, " ") == 0)
            title = NULL;
        else
            title = strdup(title);
        
        path = strtok(NULL, "#");
        if (strcmp(path, " ") == 0)
            path = NULL;
        else
            path = strdup(path);

        add_song(name, title, path);
    }
}

Artist *create_artist_instance(char *name) {
    Artist *ptr_artist = (Artist *)malloc(sizeof(Artist));
    ptr_artist->name = name;
    ptr_artist->next = NULL;
    ptr_artist->head = NULL;
    ptr_artist->tail = NULL;

    return ptr_artist;
}

Song *create_song_instance(Artist *ptr_artist, char *title, char *path) {
    Song *ptr_song = (Song *)malloc(sizeof(Song));
    ptr_song->artist = ptr_artist;
    ptr_song->title = strdup(title);
    ptr_song->path = strdup(path);
    ptr_song->index = num_index;
    num_index++;        // problem : if removed, generating empty index
    
    return ptr_song;
}

SNode *create_snode_instance(Song *ptr_song) {
    SNode *ptr_snode = (SNode *)malloc(sizeof(SNode));
    ptr_snode->song = ptr_song;
    ptr_snode->prev = NULL;
    ptr_snode->next = NULL;

    return ptr_snode;
}

Artist *add_artist(char *name) {
    Artist *ptr_artist = create_artist_instance(name);
        
    if (artist_directory[(unsigned char)name[0]] == NULL)
       artist_directory[(unsigned char)name[0]] = ptr_artist;
    else { 
        Artist *p = artist_directory[(unsigned char)name[0]];
        Artist *q = NULL;

        while (p != NULL && strcmp(p->name, name) < 0) {
            q = p;
            p = p->next;
        }
        if (q == NULL) {    // add at the front
            ptr_artist->next = p;
            artist_directory[(unsigned char)name[0]] = ptr_artist;
        }
        else {              // add after q
            ptr_artist->next = p;
            q->next = ptr_artist;
        }
    }
    return ptr_artist;
}

void add_song(char *artist, char *title, char *path) {
    // find if the artist already exist
    Artist *ptr_artist = find_artist(artist);
    if (ptr_artist == NULL) {
        ptr_artist = add_artist(artist);
    }
 
    // add the song to the artist pointed by ptr_artist
    Song *ptr_song = create_song_instance(ptr_artist, title, path);
    SNode *ptr_snode = create_snode_instance(ptr_song);
    add_node_to_artist(ptr_artist, ptr_snode);
    ptr_snode = create_snode_instance(ptr_song);
    add_node_to_index(ptr_song, ptr_snode);
}

void add_node_to_artist(Artist *ptr_artist, SNode *ptr_snode) {
    SNode *p = ptr_artist->head;
    
    while (p != NULL && strcmp(p->song->title, ptr_snode->song->title) < 0)
        p = p->next;

    // add ptr_snode before p
    // 1. if empty  2. at the front  3. at the end  4. in the middle
    if (ptr_artist->head == NULL) {     // 1
        ptr_artist->head = ptr_snode;
        ptr_artist->tail = ptr_snode;
    }
    else if (p == ptr_artist->head) {   // 2
        ptr_snode->next = ptr_artist->head;
        ptr_artist->head->prev = ptr_snode;
        ptr_artist->head = ptr_snode;
    }
    else if (p == NULL) {               // 3
        ptr_snode->prev = ptr_artist->tail;
        ptr_artist->tail->next = ptr_snode;
        ptr_artist->tail = ptr_snode;
    }
    else {                              // 4
        ptr_snode->prev = p->prev;
        ptr_snode->next = p;
        p->prev->next = ptr_snode;
        p->prev = ptr_snode;
    }       
}

void add_node_to_index(Song *ptr_song, SNode *ptr_snode) {
    int index = ptr_song->index % INDEX_LENGTH;

    if (index_directory[index] == NULL)
        index_directory[index] = ptr_snode;
    else {
        SNode *p = index_directory[index];
        SNode *q = NULL;
        while (p != NULL && strcmp(p->song->title, ptr_song->title) < 0) {
            q = p;
            p = p->next;
        }
        if (q == NULL) {    // add at the front
            ptr_snode->next = p;
            index_directory[index] = ptr_snode;
        }
        else {              // add after q
            ptr_snode->next = p;
            q->next = ptr_snode;
        }   
    }
}

void status() {
    for (int i = 0; i < NUM_CHARS; i++) {
        Artist *ptr_artist = artist_directory[i];
        while (ptr_artist != NULL) {
            print_artist(ptr_artist);
            ptr_artist = ptr_artist->next;
        }
    }
}

void print_artist(Artist *ptr_artist) {
    printf("%s\n", ptr_artist->name);
    SNode *ptr_snode = ptr_artist->head;
    while (ptr_snode != NULL) {
        print_song(ptr_snode->song);
        ptr_snode = ptr_snode->next;
    }
}

void print_song(Song *ptr_song) {
    printf("    %d) %s, %s\n", ptr_song->index, ptr_song->title, ptr_song->path);
}

void search_artist(char *name) {
    Artist *ptr_artist = find_artist(name);
    if (ptr_artist == NULL) {
        printf("No such artist exists.\n");
        return;
    }
    print_artist(ptr_artist);
}

void search_song(char *name, char *title) {
    Artist *ptr_artist = find_artist(name);
    if (ptr_artist == NULL) {
        printf("No such artist exists.\n");
        return;
    }
    SNode *ptr_snode = find_snode(ptr_artist, title);
    if (ptr_snode == NULL) {
        printf("No such song exists.\n");
        return;
    }
    printf("%s\n", ptr_artist->name);
    print_song(ptr_snode->song);
}

Artist *find_artist(char *name) {
    Artist *p = artist_directory[(unsigned char)name[0]];    
    if (p == NULL)
        return NULL;
    
    while (p != NULL && strcmp(p->name, name) != 0) 
        p = p->next;

    return p;
}

SNode *find_song(int index) {
    SNode *ptr_snode = index_directory[index % INDEX_LENGTH];
    while (ptr_snode != NULL && ptr_snode->song->index != index)
        ptr_snode = ptr_snode->next;

    return ptr_snode;
}

SNode *find_snode(Artist *ptr_artist, char *title) {
    SNode *ptr_snode = ptr_artist->head;
    while (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) != 0)
        ptr_snode = ptr_snode->next;
    
    return ptr_snode;
}

void play(int index) {
    SNode *ptr_snode = find_song(index);
    if (ptr_snode == NULL) {
        printf("No such song exists.\n");
        return;
    }
    print_song(ptr_snode->song);
}

void save_as_file(FILE *fp) {
    for (int i = 0; i < NUM_CHARS; i++) {
        Artist *ptr_artist = artist_directory[i];
        while (ptr_artist != NULL) {
            save_artist(ptr_artist, fp);
            ptr_artist = ptr_artist->next;
        }
    }
}

void save_artist(Artist *ptr_artist, FILE *fp) {
    SNode *ptr_snode = ptr_artist->head;
    while (ptr_snode != NULL) {
        save_song(ptr_snode->song, fp);
        ptr_snode = ptr_snode->next;
    }
}

void save_song(Song *ptr_song, FILE *fp) {
    fprintf(fp, "%s#", ptr_song->artist->name);
    fprintf(fp, "%s#", ptr_song->title);
    fprintf(fp, "%s#\n", ptr_song->path);
}

void remove_song(int index) {
    SNode *ptr_snode = find_song(index);
    if (ptr_snode == NULL) {
        printf("No such song exists.\n");
        return;
    }
}

void remove_index_snode(int index) {
    SNode *p = index_directory[index % INDEX_LENGTH];
    SNode *q = NULL;
    while (p->song->index != index) {
        q = p;
        p = p->next;
    }
    Song *ptr_song = p->song;
    if (q == NULL)      // remove at the front
        index_directory[index % INDEX_LENGTH] = p->next;
    else                // add after q
        q->next = p->next;

    free(p);

    Artist *ptr_artist = ptr_song->artist;
    SNode *ptr_snode= find_snode(ptr_artist, ptr_song->title);
    if (ptr_snode == NULL) {
        printf("Not found snode - something wrong.\n");
        return;
    }
    remove_artist_snode(ptr_artist, ptr_snode);
    destroy_song(ptr_song);
}

void remove_artist_snode(Artist *ptr_artist, SNode *ptr_snode) {
    SNode *first = ptr_artist->head;
    SNode *last = ptr_artist->tail;
    if (first == ptr_snode && last == ptr_snode) {  // unique node
        first = NULL;
        last = NULL;
        remove_artist(ptr_artist);
    }
    else if (first == ptr_snode) {                  // head node
        ptr_artist->head = ptr_snode->next;
        ptr_snode->next->prev = NULL;
    }
    else if (last == ptr_snode) {                   // tail node
        ptr_artist->tail = ptr_snode->prev;
        ptr_snode->prev->next = NULL;
    }
    else {                                          // middle node
        ptr_snode->prev->next = ptr_snode->next;
        ptr_snode->next->prev = ptr_snode->prev;
    }

    free(ptr_snode);
}

void remove_artist(Artist *ptr_artist) {
    Artist *p = artist_directory[(unsigned char)ptr_artist->name[0]];
    Artist *q = NULL;
    while (p != NULL && strcmp(p->name, ptr_artist->name) != 0) {
        q = p;
        p = p->next;
    }
    if (q == NULL)      // at the first
        artist_directory[(unsigned char)ptr_artist->name[0]] = p->next;
    else                // after q
        q->next = p->next;

    destroy_artist(ptr_artist);
}

void destroy_artist(Artist *ptr_artist) {
    free(ptr_artist->name);
    free(ptr_artist);
}

void destroy_song(Song *ptr_song) {
    free(ptr_song->title);
    free(ptr_song->path);
    free(ptr_song);
}


