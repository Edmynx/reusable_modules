#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct node {
    void *data;
    struct node *next;
} node_t;

struct queue {
    node_t *front;
    node_t *back;
};

static node_t* wrap_element(void *element) {
    node_t *elem = malloc(sizeof(node_t));
    elem->data = element;
    elem->next = NULL;
    return elem;
}

static void print_int(void* elementp) {
    printf("%d\n\n", *(int *)elementp);
}

static bool equal (void* elementp, const void* keyp) {
    return *(int *)elementp == *(int *)keyp;
}

// Can't get working.
queue_t* qopen(void);

// Dependent on open.
void qclose(queue_t *qp) {
    if (!qp) {
        fprintf(stderr, "Error: qp points to null\n");
        return;
    }

    // free(qp);
    qp = NULL;
}

// Works for now.
int32_t qput(queue_t *qp, void *elementp) {
    if (!qp) {
        fprintf(stderr, "Error: qp is null");
        return 1;
    }

    struct queue* queue_p = qp;
    node_t *elem = wrap_element(elementp);

    if (!queue_p->front && !queue_p->back) {
        queue_p->front = elem;
        queue_p->back = elem;
        return 0;
    }

    queue_p->back->next = elem;
    queue_p->back = elem;

    return 0;
}

// Works for now.
void* qget(queue_t *qp) {
    if (!qp) {
        fprintf(stderr, "Error: qp is null");
        return NULL;
    }

    struct queue* queue_p = qp;

    if (!queue_p->front && !queue_p->back) {
        fprintf(stderr, "Error: queue is empty");
        return NULL;
    }

    node_t *first_elem = queue_p->front;
    queue_p->front = queue_p->front->next;

    return first_elem->data;
}

// Works for now.
void qapply(queue_t *qp, void (*fn)(void* elementp)) {
    if (!qp) {
        fprintf(stderr, "Error: qp is null");
        return;
    }

    struct queue* queue_p = qp;

    if (!queue_p->front && !queue_p->back) {
        fprintf(stderr, "Error: queue is empty");
        return;
    }
    
    node_t *current_node = queue_p->front;

    while (current_node) {
        fn(current_node->data);
        current_node = current_node->next;
    }
}

// Works for now.
void* qsearch(queue_t *qp, bool (*searchfn)(void* elementp,const void* keyp), const void* skeyp) {   
    if (!qp) {
        fprintf(stderr, "Error: qp is null");
        return NULL;
    }

    struct queue* queue_p = qp;

    if (!queue_p->front && !queue_p->back) {
        fprintf(stderr, "Error: queue is empty");
        return NULL;
    }

    node_t *current_node = queue_p->front;

    while (current_node) {
        if (searchfn(current_node->data, skeyp)) {
            return current_node->data;
        } else {
            current_node = current_node->next;
        }
    }

    return NULL;
}

// Works for now.
void* qremove(queue_t *qp, bool (*searchfn)(void* elementp,const void* keyp), const void* skeyp) {
    if (!qp) {
        fprintf(stderr, "Error: qp is null");
        return NULL;
    }

    struct queue* queue_p = qp;

    if (!queue_p->front && !queue_p->back) {
        fprintf(stderr, "Error: queue is empty");
        return NULL;
    }

    if (searchfn(queue_p->front->data, skeyp)) {
        return qget(qp);
    } else {
        node_t *previous_node = queue_p->front;
        node_t *current_node = queue_p->front->next;
        
        while (current_node) {
            if (searchfn(current_node->data, skeyp)) {
                previous_node->next = current_node->next;
                return current_node->data;
            }
            previous_node = current_node;
            current_node = current_node->next;
        }
    }

    return NULL;
}

// Works for now.
void qconcat(queue_t *q1p, queue_t *q2p) {
    if (!q1p || !q2p) {
        fprintf(stderr, "Error: either q1p or q2p is null");
        return;
    }

    struct queue* queue_1p = q1p;
    struct queue* queue_2p = q2p;

    if (!queue_1p->front && !queue_1p->back) {
        fprintf(stderr, "Error: q1p is empty");
        return;
    } else if (!queue_2p->front && !queue_2p->back) {
        fprintf(stderr, "Error: q2p is empty");
        return;
    } else {
        queue_1p->back->next = queue_2p->front;
        queue_1p->back = queue_2p->back;
        qclose(q2p);
    }
}

// Most functions seem to work assuming the queue is properly initialized.
int main(void) {
    int elem1 = 1;
    int elem2 = 2;
    int elem3 = 3;

    int elem4 = 4;
    int elem5 = 5;
    int elem6 = 6;

    struct queue q = {NULL, NULL};
    struct queue q2 = {NULL, NULL};

    qput((queue_t *)&q, (void *) &elem1);
    qput((queue_t *)&q, (void *) &elem2);
    qput((queue_t *)&q, (void *) &elem3);

    qput((queue_t *)&q2, (void *) &elem4);
    qput((queue_t *)&q2, (void *) &elem5);
    qput((queue_t *)&q2, (void *) &elem6);

    qconcat(&q, &q2);
    qapply(&q, print_int);

    int key = 4;
    void *res = qsearch((queue_t *)&q, equal, (void *)&key);
    printf("%d\n\n", *(int *)res);

    res = qremove((queue_t *)&q, equal, (void *)&key);
    printf("%d\n\n", *(int *)res);

    printf("%d\n", *(int *)qget((queue_t *)&q));
    printf("%d\n", *(int *)qget((queue_t *)&q));
    printf("%d\n", *(int *)qget((queue_t *)&q));
    printf("%d\n", *(int *)qget((queue_t *)&q));
    printf("%d\n", *(int *)qget((queue_t *)&q));
    printf("%d\n", *(int *)qget((queue_t *)&q));
}

// int main(void) {
//     int elem1 = 1;
//     queue_t *qp = qopen();
//     qput(qp, (void *)&elem1);

//     struct queue* ptr = (struct queue*)qp;
//     printf("%d\n", ptr->front->data);
// }

