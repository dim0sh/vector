#include <stdio.h>
#include <stdlib.h>

typedef struct Vec 
{
    int * data;
    int size;
    int count;
}vec_t;

void print_arr(int * arr,int n)
{
    for (int i = 0; i<n; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
int * arr_resize(int * arr, int size, int increment)
{
    int *tmp = (int *) calloc(size+increment,(size+increment)*sizeof(int));
    for (int i = 0; i<size; i++)
    {
        tmp[i] = arr[i];
    }
    free(arr);
    arr = tmp;
    tmp = NULL;
    return arr;
}
void vec_resize(vec_t * vec,int increment)
{
    vec->data = arr_resize(vec->data,vec->size,increment);
    vec->size+=increment;
}
void vec_pushback(vec_t * vec, int key)
{
    if (vec->count == vec->size) {
        vec_resize(vec,vec->size);
    }
    vec->data[vec->count] = key;
    vec->count++;
}
int vec_pop(vec_t * vec)
{
    int val = vec->data[vec->count-1];
    vec->data[vec->count-1] = 0;
    vec->count--;

    if (vec->size > 5)
    {
        if (vec->size/3 == vec->count)
        {
            vec_resize(vec,-(vec->size/2));
        }
    }
    return val;
}
void destroy_vec(vec_t * vec)
{
    // for (int i = 0; i<vec->size; i++)
    // {
    //     free((int *)vec->data[i]);
    // }
    free(vec->data);
    free(vec);
}
void init_empty_vec_of_size(vec_t ** vec, int size)
{
    vec_t * new = (vec_t *) malloc(sizeof(vec_t));
    new->size = size;
    new->count = 0;
    new->data = (int *) calloc(new->size,sizeof(int)*new->size);
    *vec = new;
}

int main()
{
    vec_t * vec;
    init_empty_vec_of_size(&vec,5);
    
    vec_pushback(vec,2);
    print_arr(vec->data,vec->size);
    vec_pushback(vec,2);
    vec_pushback(vec,2);
    vec_pushback(vec,2);
    vec_pushback(vec,2);
    print_arr(vec->data,vec->size);
    vec_pushback(vec,2);
    print_arr(vec->data,vec->size);
    vec_pop(vec);
    vec_pop(vec);
    print_arr(vec->data,vec->size);
    printf("size:%d\n",vec->size);
    printf("count:%d\n",vec->count);
    vec_pop(vec);
    print_arr(vec->data,vec->size);
    destroy_vec(vec);
    init_empty_vec_of_size(&vec,10);
    print_arr(vec->data,vec->size);
}