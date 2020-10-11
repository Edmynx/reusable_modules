#include "hash.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define get16bits(d) (*((const uint16_t *)(d)))

static uint32_t super_fast_hash(const char *data, int len, uint32_t tablesize) {
    uint32_t hash = len, tmp;
    int rem;

    if (len <= 0 || data == NULL)
        return 0;
        
    rem = len & 3;
    len >>= 2;

    for (; len > 0; len--) {
        hash += get16bits(data);
        tmp = (get16bits(data + 2) << 11) ^ hash;
        hash = (hash << 16) ^ tmp;
        data += 2 * sizeof(uint16_t);
        hash += hash >> 11;
    }

    switch(rem) {
        case 3: hash += get16bits(data);
            hash ^= hash << 16;
            hash ^= data[sizeof(uint16_t)] << 18;
            hash += hash >> 11;
            break;
        case 2: hash += get16bits(data);
            hash ^= hash << 11;
            hash += hash >> 17;
            break;
        case 1: hash += *data;
            hash ^= hash << 10;
            hash += hash >> 11;
    }

    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;
    return hash % tablesize;
}

struct hashtable {
    uint32_t size;
    uint32_t length;
    queue_t **table;
};

hashtable_t *hopen(uint32_t hsize) {
    if (hsize < 1) {
        fprintf(stderr, "Error: Invalid size provided");
        return NULL;
    }

    struct hashtable* htp = malloc(sizeof(struct hashtable));

    if (!htp) {
        fprintf(stderr, "Error: Failed to allocate memory");
        return NULL;
    }

    queue_t **table = malloc(sizeof(queue_t *) * hsize);
    
    if (!table) {
        fprintf(stderr, "Error: Failed to allocate memory");
        return NULL;
    }

    htp->size = hsize;
    htp->length = 0;
    htp->table = table;
    
    return (hashtable_t *) htp;
}

void hclose(hashtable_t *htp) {
    if (!htp) {
        fprintf(stderr, "Error: htp is null");
        return;
    }

    struct hashtable *hash_ptr = htp;

    for (int i = 0; i < hash_ptr->length; ++i) {
        qclose(hash_ptr->table[i]);
    }

    free(hash_ptr->table);
    free(hash_ptr);
}

int32_t hput(hashtable_t *htp, void *ep, const char *key, int keylen);

void happly(hashtable_t *htp, void (*fn)(void* ep)) {
    if (!htp) {
        fprintf(stderr, "Error: htp is null");
        return;
    }

    struct hashtable *hash_ptr = htp;

    if (hash_ptr->length == 0) {
        fprintf(stderr, "Error: hashtable is empty");
        return;
    }

    for (int i = 0; i < hash_ptr->length; ++i) {
        qapply(hash_ptr->table[i], fn);
    }
}

void *hsearch(hashtable_t *htp, bool (*searchfn)(void* elementp, const void* searchkeyp), const char *key, int32_t keylen) {
    if (!htp) {
        fprintf(stderr, "Error: htp is null");
        return NULL;
    }

    struct hashtable *hash_ptr = htp;

    if (hash_ptr->length == 0) {
        fprintf(stderr, "Error: hashtable is empty");
        return NULL;
    }

    uint32_t index = super_fast_hash(key, keylen, hash_ptr->length);
    return qsearch(hash_ptr->table[index], searchfn, key);
}

void *hremove(hashtable_t *htp, bool (*searchfn)(void* elementp, const void* searchkeyp), const char *key, int32_t keylen) {
    if (!htp) {
        fprintf(stderr, "Error: htp is null");
        return NULL;
    }

    struct hashtable *hash_ptr = htp;

    if (hash_ptr->length == 0) {
        fprintf(stderr, "Error: hashtable is empty");
        return NULL;
    }

    uint32_t index = super_fast_hash(key, keylen, hash_ptr->length);
    return qremove(hash_ptr->table[index], searchfn, key);
}

int main(void) {
    struct hashtable *htp = hopen(5);
    queue_t *queue = qopen();
    int elem = 1;

    qput(queue, (void *) &elem);
    htp->table[0] = queue;
    htp->length++;

    printf("%d\n", *(int *)qget(htp->table[0]));
    hclose(htp);
}
