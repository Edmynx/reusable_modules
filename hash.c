/* 
 * hash.c -- implements a generic hash table as an indexed set of queues.
 *
 */

#include "hash.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* 
 * SuperFastHash() -- produces a number between 0 and the tablesize-1.
 * 
 * The following (rather complicated) code, has been taken from Paul
 * Hsieh's website under the terms of the BSD license. It's a hash
 * function used all over the place nowadays, including Google Sparse
 * Hash.
 */

#define get16bits(d) (*((const uint16_t *)(d)))

static uint32_t super_fast_hash(const char *data, int len, uint32_t tablesize) {
    uint32_t hash = len, tmp;
    int rem;

    if (len <= 0 || data == NULL)
        return 0;
        
    rem = len & 3;
    len >>= 2;

    /* Main loop */
    for (; len > 0; len--) {
        hash += get16bits(data);
        tmp = (get16bits(data + 2) << 11) ^ hash;
        hash = (hash << 16) ^ tmp;
        data += 2 * sizeof(uint16_t);
        hash += hash >> 11;
    }
    /* Handle end cases */
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

typedef struct hashtable {
    queue_t **hqp;
    uint32_t hsize;
    uint32_t hcount;
} hashstruct_t;

hashtable_t *hopen(uint32_t hsize) {
    if (hsize < 1) {
        fprintf(stderr, "Error: Invalid size provided\n");
        return NULL;
    }

    hashstruct_t *htp = (hashtable_t *)malloc(sizeof(hashstruct_t));

    if (!htp) {
        fprintf(stderr, "Error: Failed to allocate memory for hashtable\n");
        return NULL;
    }

    htp->hqp = malloc(sizeof(queue_t *) * hsize);

    if (!(htp->hqp)) {
        fprintf(stderr, "Error: Failed to allocate memory for table queues\n");
        return NULL;
    }

    queue_t **qp = htp->hqp;
    queue_t **qpend = qp + hsize;
    for (qp; qp < qpend; qp++) {
        qp = qopen();
    }

    htp->hsize = hsize;
    htp->hcount = 0;

    return (hashtable_t *)htp;
}

void hclose(hashtable_t *htp) {
    if (!((hashstruct_t *)htp)) {
        fprintf(stderr, "Error: Hashtable does not exist");
        return;
    }

    queue_t **qp = ((hashstruct_t *)htp)->hqp;
    queue_t **qpend = qp + ((hashstruct_t *)htp)->hsize; 
    for (qp; qp < qpend; qp++) {
        qclose(qp);
    }

    free(htp->hqp);
    free(htp);
}

int32_t hput(hashtable_t *htp, void *ep, const char *key, int keylen) {
    if(!((hashstruct_t *) htp)) {
        fprintf(stderr, "Error: Hashtable does not exist");
        return 1;
    }
    uint32_t hash = super_fast_hash(key, keylen, ((hashstruct_t *) htp)->hsize);
    qput(((hashstruct_t *) htp)->hqp[hash], ep);
    ((hashstruct_t *) htp)->hcount + 1;
    return 0;
}
    
void happly(hashtable_t *htp, void (*fn)(void* ep)) {
    if (!((hashstruct_t *) htp)) {
        fprintf(stderr, "Error: Htp does not exist");
        return;
    }

    if (((hashstruct_t *) htp)->hcount == 0) {
        fprintf(stderr, "Error: Hashtable is empty");
        return;
    }

    queue_t *qp = ((hashstruct_t *)htp)->hqp;
    queue_t *qpend = qp + ((hashstruct_t *)htp)->hsize; 
    for (qp; qp < qpend; qp++) {
        qapply(qp, fn);
    }
}

void *hsearch(hashtable_t *htp, bool (*searchfn)(void* elementp, const void* searchkeyp), const char *key, int32_t keylen) {
    if (!((hashstruct_t *)htp)) {
        fprintf(stderr, "Error: Hashtable does not exist");
        return NULL;
    }

    if (((hashstruct_t *) htp)->hcount == 0) {
        fprintf(stderr, "Error: Hashtable is empty");
        return NULL;
    }

    uint32_t hash = super_fast_hash(key, keylen, ((struct hashtable *) htp)->hsize);
    return qsearch(((hashstruct_t *) htp)->hqp[hash], searchfn, key);
}

void *hremove(hashtable_t *htp, bool (*searchfn)(void* elementp, const void* searchkeyp), const char *key, int32_t keylen) {
   if (!((struct hashtable *)htp)) {
        fprintf(stderr, "Error: Hashtable does not exist");
        return NULL;
    }

    if (((struct hashtable *) htp)->hcount == 0) {
        fprintf(stderr, "Error: Hashtable is empty");
         NULL;
    }

    uint32_t hash = super_fast_hash(key, keylen, ((struct hashtable *) htp)->hsize);
    return qremove(((struct hashtable *) htp)->hqp[hash], searchfn, key);
}
