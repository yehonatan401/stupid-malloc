
////////////////////////////////////////////////
// create by yehonatan bondrenko in 30 mart 2026
////////////////////////////////////////////////

#include <stddef.h>
#define ten_kb 10000
static char massive[ten_kb];
typedef struct Block {
    size_t size;
    int is_free;
    struct Block *next;
}Block;

Block *freelist = nullptr;
void idk_how_call_this() {
    // freelist coardinations
    freelist = (Block *)massive;
    freelist->next = nullptr;
    freelist->is_free = 1;
    freelist->size = sizeof(massive) - sizeof(Block);
}


void coul() {
    Block *t = freelist;
    while (t != NULL && t->next != NULL) {
        if (t->next->is_free && t->is_free ) {
            t->size += t->next->size + sizeof(Block);

            t->next = t->next->next;
        }else {
            t = t->next;


        }

    }

}


void split(Block *thing,size_t size_req) {


    // coardinations of new_block
    Block *new_block = (Block *)((char *)thing + sizeof(Block) + size_req);


    new_block->next = thing->next;
    new_block->size = thing->size - size_req - sizeof(Block);
    new_block->is_free = 1;
    thing->next = new_block;
    thing->size = size_req;
    thing->is_free = 0;
}
// malloc function
void* stupid_malloc(size_t size_req) {
    if (freelist == NULL) {
        idk_how_call_this();
    }

    Block *corrent = freelist;

    while (corrent != NULL) {
        if (corrent->is_free && corrent->size >= size_req) {

            if (corrent->size > size_req) {
                  split(corrent,size_req);
                return (char *)corrent + sizeof(Block);
            }
            corrent->is_free = 0;
            return (char*)corrent + sizeof(Block);
        }
        corrent = corrent->next;
    }
    return NULL;
}
// free functions
void stupid_free(void *ptr) {
    if (!ptr) return;
    Block *h = (Block *)((char *)ptr - sizeof(Block));
    h->is_free = 1;
    coul();
}

