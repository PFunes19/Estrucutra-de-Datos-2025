#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct CNode {
    int data;
    struct CNode *next;
} CNode;

typedef struct {
    CNode *tail;
    size_t sz;
} CList;

void    clist_init(CList *list);
bool    clist_is_empty(const CList *list);
size_t  clist_size(const CList *list);
bool    clist_add_front(CList *list, int value);
bool    clist_add_back (CList *list, int value);
bool    clist_add_at   (CList *list, size_t pos, int value);
bool    clist_remove_front(CList *list, int *out_value);
bool    clist_remove_back (CList *list, int *out_value);
bool    clist_remove_at   (CList *list, size_t pos, int *out_value);
size_t  clist_search(const CList *list, int value);
typedef void (*CListEachFn)(int *data, size_t index, void *user);
void    clist_traverse(CList *list, CListEachFn fn, void *user);
bool    clist_get_head(const CList *list, int *out_value);
bool    clist_get_tail(const CList *list, int *out_value);
void    clist_display(const CList *list);
void    clist_clear  (CList *list);
static CNode* make_node(int value);
static CNode* node_at(const CList *list, size_t pos);

void clist_init(CList *list) {
    list->tail = NULL;
    list->sz = 0;
}

bool clist_is_empty(const CList *list) {
    return list->sz == 0;
}

size_t clist_size(const CList *list) {
    return list->sz;
}

static CNode* make_node(int value) {
    CNode *n = (CNode*)malloc(sizeof(CNode));
    if (!n) return NULL;
    n->data = value;
    n->next = NULL;
    return n;
}

bool clist_add_front(CList *list, int value) {
    CNode *n = make_node(value);
    if (!n) return false;
    if (list->tail == NULL) {
        n->next = n;
        list->tail = n;
    } else {
        n->next = list->tail->next;
        list->tail->next = n;
    }
    list->sz++;
    return true;
}

bool clist_add_back(CList *list, int value) {
    if (!clist_add_front(list, value)) return false;
    list->tail = list->tail->next;
    return true;
}

bool clist_add_at(CList *list, size_t pos, int value) {
    if (pos > list->sz) return false;
    if (pos == 0)        return clist_add_front(list, value);
    if (pos == list->sz) return clist_add_back(list, value);
    CNode *prev = node_at(list, pos - 1);
    if (!prev) return false;
    CNode *n = make_node(value);
    if (!n) return false;
    n->next = prev->next;
    prev->next = n;
    list->sz++;
    return true;
}

bool clist_remove_front(CList *list, int *out_value) {
    if (list->tail == NULL) return false;
    CNode *head = list->tail->next;
    if (out_value) *out_value = head->data;
    if (list->sz == 1) {
        free(head);
        list->tail = NULL;
        list->sz = 0;
        return true;
    }
    list->tail->next = head->next;
    free(head);
    list->sz--;
    return true;
}

bool clist_remove_back(CList *list, int *out_value) {
    if (list->tail == NULL) return false;
    CNode *tail = list->tail;
    CNode *head = tail->next;
    if (list->sz == 1) {
        if (out_value) *out_value = tail->data;
        free(tail);
        list->tail = NULL;
        list->sz = 0;
        return true;
    }
    CNode *prev = head;
    while (prev->next != tail) prev = prev->next;
    if (out_value) *out_value = tail->data;
    prev->next = head;
    list->tail = prev;
    free(tail);
    list->sz--;
    return true;
}

bool clist_remove_at(CList *list, size_t pos, int *out_value) {
    if (list->sz == 0) return false;
    if (pos >= list->sz) return false;
    if (pos == 0) return clist_remove_front(list, out_value);
    if (pos == list->sz - 1) return clist_remove_back(list, out_value);
    CNode *prev = node_at(list, pos - 1);
    if (!prev) return false;
    CNode *victim = prev->next;
    prev->next = victim->next;
    if (out_value) *out_value = victim->data;
    free(victim);
    list->sz--;
    return true;
}

size_t clist_search(const CList *list, int value) {
    if (list->sz == 0) return (size_t)-1;
    CNode *head = list->tail->next;
    CNode *cur = head;
    size_t idx = 0;
    do {
        if (cur->data == value) return idx;
        cur = cur->next;
        idx++;
    } while (cur != head);
    return (size_t)-1;
}

void clist_traverse(CList *list, CListEachFn fn, void *user) {
    if (list->sz == 0 || fn == NULL) return;
    CNode *head = list->tail->next;
    CNode *cur = head;
    size_t idx = 0;
    do {
        fn(&cur->data, idx, user);
        cur = cur->next;
        idx++;
    } while (cur != head);
}

bool clist_get_head(const CList *list, int *out_value) {
    if (list->tail == NULL) return false;
    if (out_value) *out_value = list->tail->next->data;
    return true;
}

bool clist_get_tail(const CList *list, int *out_value) {
    if (list->tail == NULL) return false;
    if (out_value) *out_value = list->tail->data;
    return true;
}

void clist_display(const CList *list) {
    printf("CList(size=%zu): ", list->sz);
    if (list->sz == 0) {
        printf("[empty]\n");
        return;
    }
    CNode *head = list->tail->next;
    CNode *cur = head;
    printf("[");
    do {
        printf("%d", cur->data);
        cur = cur->next;
        if (cur != head) printf(" -> ");
    } while (cur != head);
    printf("] (circular)\n");
}

void clist_clear(CList *list) {
    if (list->sz == 0) return;
    CNode *head = list->tail->next;
    list->tail->next = NULL;
    CNode *cur = head;
    while (cur) {
        CNode *next = cur->next;
        free(cur);
        cur = next;
    }
    list->tail = NULL;
    list->sz = 0;
}

static CNode* node_at(const CList *list, size_t pos) {
    if (list->sz == 0 || pos >= list->sz) return NULL;
    CNode *cur = list->tail->next;
    while (pos--) cur = cur->next;
    return cur;
}

static void add_k_callback(int *data, size_t index, void *user) {
    (void)index;
    int k = *(int*)user;
    *data += k;
}

static void show_menu(void) {
    printf("\n=== Circular Linked List Tester ===\n");
    printf("1) Add to front\n");
    printf("2) Add to end\n");
    printf("3) Add at position\n");
    printf("4) Remove from front\n");
    printf("5) Remove from end\n");
    printf("6) Remove from position\n");
    printf("7) Search value\n");
    printf("8) Traverse (add k to every node)\n");
    printf("9) Size\n");
    printf("10) Is Empty?\n");
    printf("11) Clear list\n");
    printf("12) Display list\n");
    printf("13) Get Head\n");
    printf("14) Get Tail\n");
    printf("0) Exit\n");
    printf("Select: ");
}

int main(void) {
    CList list;
    clist_init(&list);
    int choice;
    do {
        clist_display(&list);
        show_menu();
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input. Exiting.\n");
            return 1;
        }
        if (choice == 1) {
            int v; printf("Value to add (front): "); scanf("%d", &v);
            if (clist_add_front(&list, v)) printf("OK: added to front.\n");
            else printf("ERR: could not add.\n");
        }
        else if (choice == 2) {
            int v; printf("Value to add (end): "); scanf("%d", &v);
            if (clist_add_back(&list, v)) printf("OK: added to end.\n");
            else printf("ERR: could not add.\n");
        }
        else if (choice == 3) {
            size_t pos; int v;
            printf("Position (0..%zu): ", clist_size(&list)); scanf("%zu", &pos);
            printf("Value to add: "); scanf("%d", &v);
            if (clist_add_at(&list, pos, v)) printf("OK: added at %zu.\n", pos);
            else printf("ERR: invalid position or allocation failure.\n");
        }
        else if (choice == 4) {
            int out;
            if (clist_remove_front(&list, &out)) printf("OK: removed from front: %d\n", out);
            else printf("ERR: list is empty.\n");
        }
        else if (choice == 5) {
            int out;
            if (clist_remove_back(&list, &out)) printf("OK: removed from end: %d\n", out);
            else printf("ERR: list is empty.\n");
        }
        else if (choice == 6) {
            size_t pos; int out;
            if (clist_is_empty(&list)) {
                printf("List is empty.\n");
            } else {
                printf("Position to remove (0..%zu): ", clist_size(&list)-1);
                scanf("%zu", &pos);
                if (clist_remove_at(&list, pos, &out))
                    printf("OK: removed %d at %zu\n", out, pos);
                else
                    printf("ERR: invalid position.\n");
            }
        }
        else if (choice == 7) {
            int v; printf("Value to search: "); scanf("%d", &v);
            size_t idx = clist_search(&list, v);
            if (idx == (size_t)-1) printf("Not found.\n");
            else printf("Found at index %zu.\n", idx);
        }
        else if (choice == 8) {
            int k; printf("k to add to every node: "); scanf("%d", &k);
            clist_traverse(&list, add_k_callback, &k);
            printf("Traverse applied.\n");
        }
        else if (choice == 9) {
            printf("Size = %zu\n", clist_size(&list));
        }
        else if (choice == 10) {
            printf("Is Empty? %s\n", clist_is_empty(&list) ? "Yes" : "No");
        }
        else if (choice == 11) {
            clist_clear(&list);
            printf("List cleared.\n");
        }
        else if (choice == 12) {
            clist_display(&list);
        }
        else if (choice == 13) {
            int v;
            if (clist_get_head(&list, &v)) printf("Head = %d\n", v);
            else printf("List is empty.\n");
        }
        else if (choice == 14) {
            int v;
            if (clist_get_tail(&list, &v)) printf("Tail = %d\n", v);
            else printf("List is empty.\n");
        }
        else if (choice == 0) {
        }
        else {
            printf("Unknown option.\n");
        }
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) { }
    } while (choice != 0);
    clist_clear(&list);
    return 0;
}
