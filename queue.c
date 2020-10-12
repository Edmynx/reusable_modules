#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct node_t {
    void *data;
    struct node_t *next;
};

static struct node_t* wrap_element(void *element) {
    struct node_t *elem = malloc(sizeof(struct node_t));
    elem->data = element;
    elem->next = NULL;
    return elem;
}

struct queue {
    struct node_t *front;
    struct node_t *back;
}; 

static void print_int(void* elementp) {
    printf("%d\n\n", *(int *)elementp);
}

static bool equal (void* elementp, const void* keyp) {
    return *(int *)elementp == *(int *)keyp;
}

queue_t* qopen(void) {
    queue_t *qp = (queue_t *)malloc(sizeof(struct queue));
    ((struct queue *) qp)->front = NULL;
    ((struct queue *) qp)->back = NULL;
    return qp;
}

void qclose(queue_t *qp) {
    if (!((struct queue *)qp)) {
        fprintf(stderr, "Error: Queue does not exist\n");
    }

    else {
        struct node_t *next_node = ((struct queue *) qp)->front;
        while (next_node) {
            struct node_t *current_node = next_node;
            next_node = next_node->next;
            free(current_node);
        }
        free(((struct queue *) qp));
    }
}

int32_t qput(queue_t *qp, void *elementp) {
    if (!((struct queue *) qp)) {
        fprintf(stderr, "Error: Queue does not exist");
        return 1;
    }

    struct node_t *elem = wrap_element(elementp);

    if (!((struct queue *) qp)->front && !((struct queue *) qp)->back) {
        ((struct queue *) qp)->front = elem;
        ((struct queue *) qp)->back = elem;
    }

    else {
        ((struct queue *) qp)->back->next = elem;
        ((struct queue *) qp)->back = elem;
    }

    return 0;
}

void* qget(queue_t *qp) {
    if (!((struct queue *) qp)) {
        fprintf(stderr, "Error: Queue does not exist");
        return NULL;
    }

    if (!((struct queue *) qp)->front && !((struct queue *) qp)->back) {
        fprintf(stderr, "Error: Queue is empty");
        return NULL;
    }

    struct node_t *first_elem = ((struct queue *) qp)->front;
    ((struct queue *) qp)->front = ((struct queue *) qp)->front->next;

    return first_elem->data;
}

void qapply(queue_t *qp, void (*fn)(void* elementp)) {
    if (!((struct queue *) qp)) {
        fprintf(stderr, "Error: Queue does not exist");
        return;
    }

    if (!((struct queue *) qp)->front && !((struct queue *) qp)->back) {
        fprintf(stderr, "Error: Queue is empty");
    }
    
    else {
        struct node_t *current_node = ((struct queue *) qp)->front;
        while (current_node) {
            fn(current_node->data);
            current_node = current_node->next;
        }
    } 
}

void* qsearch(queue_t *qp, bool (*searchfn)(void* elementp,const void* keyp), const void* skeyp) {   
    if (!((struct queue *) qp)) {
        fprintf(stderr, "Error: Queue does not exist");
        return NULL;
    }

    if (!((struct queue *) qp)->front && !((struct queue *) qp)->back) {
        fprintf(stderr, "Error: Queue is empty");
        return NULL;
    }

    struct node_t *current_node = ((struct queue *) qp)->front;

    while (current_node) {
        if (searchfn(current_node->data, skeyp)) {
            return current_node->data;
        } 
        
        else {
            current_node = current_node->next;
        }
    }

    return NULL;
}

void* qremove(queue_t *qp, bool (*searchfn)(void* elementp,const void* keyp), const void* skeyp) {
    if (!((struct queue *) qp)) {
        fprintf(stderr, "Error: Queue does not exist");
        return NULL;
    }

    if (!((struct queue *) qp)->front && !((struct queue *) qp)->back) {
        fprintf(stderr, "Error: Queue is empty");
        return NULL;
    }

    if (searchfn(((struct queue *) qp)->front->data, skeyp)) {
        return qget(((struct queue *) qp));
    } 

    struct node_t *previous_node = ((struct queue *) qp)->front;
    struct node_t *current_node = ((struct queue *) qp)->front->next;
    
    while (current_node) {
        if (searchfn(current_node->data, skeyp)) {
            previous_node->next = current_node->next;
            return current_node->data;
        }
        previous_node = current_node;
        current_node = current_node->next;
    }
    return NULL;
}

void qconcat(queue_t *q1p, queue_t *q2p) {
    if (!((struct queue *) q1p) || !((struct queue *) q2p)) {
        fprintf(stderr, "Error: Either q1p or q2p does not exist");
        return;
    }

    if (!((struct queue *) q1p)->front && !((struct queue *) q1p)->back) {
        fprintf(stderr, "Error: q1p is empty");
        return;
    } 

    if (!((struct queue *) q2p)->front && !((struct queue *) q2p)->back) {
        fprintf(stderr, "Error: q2p is empty");
        return;
    } 

    ((struct queue *) q1p)->back->next = ((struct queue *) q2p)->front;
    ((struct queue *) q1p)->back = ((struct queue *) q2p)->back;
    qclose(((struct queue *) q2p));
}

int main(void) {
    int elem1 = 1;
    int elem2 = 2;
    int elem3 = 3;

    int elem4 = 4;
    int elem5 = 5;
    int elem6 = 6;

    queue_t *q = qopen();
    queue_t *q2 = qopen();

    qput(q, (void *) &elem1);
    qput(q, (void *) &elem2);
    qput(q, (void *) &elem3);

    qput(q2, (void *) &elem4);
    qput(q2, (void *) &elem5);
    qput(q2, (void *) &elem6);

    qconcat(q, q2);
    qapply(q, print_int);

    int key = 4;
    void *res = qsearch(q, equal, (void *)&key);

    printf("%d\n\n", *(int *)res);

    key = 2;
    res = qremove(q, equal, (void *)&key);
    printf("%d\n\n", *(int *)res);

    printf("%d\n", *(int *)qget(q));
    printf("%d\n", *(int *)qget(q));
    printf("%d\n", *(int *)qget(q));
    printf("%d\n", *(int *)qget(q));
    printf("%d\n", *(int *)qget(q));

    qclose(q);
}

