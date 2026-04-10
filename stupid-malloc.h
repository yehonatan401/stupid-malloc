
////////////////////////////////////////////////
// create by yehonatan bondrenko on 6 april 2026
////////////////////////////////////////////////
#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
#include <stddef.h>
#include ".h"
#define ten_kb 10000
static char massive[ten_kb];
typedef struct Block {
    size_t size;
    int is_free;
    struct Block *next;
}Block;

Block *freelist = nullptr;
void idk_how_call_this() {
    freelist = (Block *)massive;
    freelist->next = nullptr;
    freelist->is_free = 1;
    freelist->size = sizeof(massive) - sizeof(Block);
}


void coul() {
    Block *t = freelist;
    while (t != NULL && t->next != NULL) {
        if (t->next->is_free && t->is_free ) {
            t->size = ALIGN(t->size + t->next->size + sizeof(Block));

            t->next = t->next->next;
        }else {
            t = t->next;


        }

    }

}


void split(Block *thing,size_t size_req);

// malloc function
void* stupidMalloc(const size_t size_req) {
    if (freelist == NULL) {
        idk_how_call_this();
    }

    Block *corrent = freelist;

    while (corrent != NULL) {
        if (corrent->is_free && corrent->size >= size_req) {

            if (corrent->size > size_req + sizeof(Block) +1) {
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
// free function
void stupidFree(void *ptr) {
    if (!ptr) return;
    Block *h = (Block *)((char *)ptr - sizeof(Block));
    h->is_free = 1;
    coul();
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

void *stupidRealloc(void *ptr, size_t size_req) {
    if (!ptr) return stupidMalloc(size_req);
    if (size_req == 0) {
        stupidFree(ptr);
        return NULL;
    }

    size_req = ALIGN(size_req);
    Block *this = (Block *)((char *)ptr - sizeof(Block));


    if (this->size >= size_req) {

        if (this->size >= size_req + sizeof(Block) + ALIGNMENT) {
            split(this, size_req);
        }
        return ptr;
    }

    if (this->is_free && this->next->is_free && (this->size + sizeof(Block) + this->next->size) >= size_req) {
        this->size += sizeof(Block) + this->next->size;
        this->next = this->next->next;

        if (this->size >= size_req + sizeof(Block) + ALIGNMENT) {
            split(this, size_req);
        }
        return ptr;
    }

    void *new_ptr = stupidMalloc(size_req);
    if (!new_ptr) return NULL;
    // i write this function in asm
    stupidMemcpy(new_ptr, ptr, this->size);

    stupidFree(ptr);
    return new_ptr;
}
