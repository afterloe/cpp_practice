#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;
    char **id_cars;
} Person;

extern void alloc_person(Person **, int);
extern void load_data(Person **, int);
extern void printf_data(Person *, int);
extern void free_memory(Person **, int);

int main()
{
    int list_size = 5;
    Person *list = NULL;
    alloc_person(&list, list_size);
    load_data(&list, list_size);
    printf_data(list, list_size);
    free_memory(&list, list_size);
    return EXIT_SUCCESS;
}

void alloc_person(Person **list, int count)
{
    if (NULL == list)
    {
        return;
    }
    Person *tmp = (Person *)malloc(sizeof(Person) * count);
    for (int i = 0; i < count; i++)
    {
        tmp[i].name = (char *)malloc(64);
        tmp[i].id_cars = (char **)malloc(sizeof(char *) * 3);
        for (int j = 0; j < 3; j++)
        {
            tmp[i].id_cars[j] = (char *)malloc(64);
        }
    }

    *list = tmp;
}

void load_data(Person **list_ptr, int size)
{
    if (NULL == list_ptr)
    {
        printf("[error]: ! data list ptr alloc memory failed.");
        return;
    }
    Person *tmp = *list_ptr;
    for (int i = 0; i < size; i++)
    {
        sprintf(tmp[i].name, "named: person_%d", i + 1010);
        for (int j = 0; j < 3; j++)
        {
            sprintf(tmp[i].id_cars[j], "身份证明-%d/%d", i, j + 110102);
        }
    }
    printf("load data success. \n");
}

void printf_data(Person *data_list, int size)
{
    if (data_list == NULL)
    {
        printf("[error]: ! data list is null.");
        return;
    }

    for (int i = 0; i < size; i++)
    {
        printf("待检测核酸人员: %s\n", data_list->name);
        for (int j = 0; j < 3; j++)
        {
            printf("    %s\n", data_list->id_cars[j]);
        }
        data_list++;
    }
}

void free_memory(Person **ptr, int size)
{
    if (NULL == ptr)
    {
        return;
    }
    Person *tmp = *ptr;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            free(tmp[i].id_cars[j]);
            tmp[i].id_cars[j] = NULL;
        }
        free(tmp[i].name);
        tmp[i].name = NULL;
    }

    free(tmp);
    tmp = NULL;
}