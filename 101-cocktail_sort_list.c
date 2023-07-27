#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

typedef struct listint_s
{
    int n;
    struct listint_s *next;
    struct listint_s *prev;
} listint_t;

void cocktail_sort_list(listint_t **list);
void swap_nodes(listint_t *a, listint_t *b);

void print_list(listint_t *list)
{
    listint_t *current = list;

    while (current != NULL)
    {
        printf("%d ", current->n);
        current = current->next;
    }

    printf("\n");
}

void swap_nodes(listint_t *a, listint_t *b)
{
    int temp = a->n;
    a->n = b->n;
    b->n = temp;
}

listint_t *create_listint(const int *array, size_t size)
{
    listint_t *list = NULL;
    listint_t *node;
    int *tmp;

    for (size_t i = 0; i < size; i++)
    {
        node = malloc(sizeof(listint_t));
        if (!node)
            return NULL;
        tmp = (int *)&node->n;
        *tmp = array[i];
        node->next = list;
        node->prev = NULL;
        if (list)
            list->prev = node;
        list = node;
    }

    return list;
}

void cocktail_sort_list(listint_t **list)
{
    int swapped;
    listint_t *current;
    listint_t *next;

    do
    {
        swapped = 0;
        current = *list;
        next = current->next;

        while (next != NULL)
        {
            if (current->n > next->n)
            {
                swap_nodes(current, next);
                swapped = 1;
            }
            current = next;
            next = current->next;
        }

        if (!swapped)
            break;

        current = *list;
        next = current->prev;

        while (next != NULL)
        {
            if (current->n < next->n)
            {
                swap_nodes(current, next);
                swapped = 1;
            }
            current = next;
            next = current->prev;
        }
    } while (swapped);
}

int main(void)
{
    listint_t *list;
    int array[] = {19, 48, 99, 71, 13, 52, 96, 73, 86, 7};
    size_t n = sizeof(array) / sizeof(array[0]);

    list = create_listint(array, n);
    if (!list)
        return (1);
    print_list(list);
    printf("\n");
    cocktail_sort_list(&list);
    printf("\n");
    print_list(list);
    return (0);
}
