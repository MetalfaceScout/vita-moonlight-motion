#include "util.h"
#include "debug.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap_app_list_entries(PAPP_LIST a, PAPP_LIST b) {
    PAPP_LIST tmp = malloc(sizeof(APP_LIST));
    tmp->id = a->id;
    tmp->name = a->name;

    a->id = b->id;
    a->name = b->name;
    b->id = tmp->id;
    b->name = tmp->name;

    free(tmp);
}

void sort_app_list(PAPP_LIST list) {
    if (list == NULL) {
        return;
    }

    int swapped = 0;
    PAPP_LIST cur = NULL;
    PAPP_LIST prev = NULL;

    do {
        swapped = 0;
        cur = list;

        while (cur->next != prev) {
            if (strcmp(cur->name, cur->next->name) > 0) {
                swap_app_list_entries(cur, cur->next);
                swapped = 1;
            }
            cur = cur->next;
        }
        prev = cur;
    } while (swapped);
}

int ensure_buf_size(void **buf, size_t *buf_size, size_t required_size) {
  if (*buf_size >= required_size)
    return 0;

  *buf_size = required_size;
  *buf = realloc(*buf, *buf_size);
  if (!*buf) {
    fprintf(stderr, "Failed to allocate %zu bytes\n", *buf_size);
    abort();
  }

  return 0;
}