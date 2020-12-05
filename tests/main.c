#include <managed_array.h>
#include <managed_string.h>

int main(int argc, char *argv[])
{
    array *arr_0 = array_make_new(sizeof(int), 0);

    int buf[] = {1, 2, 3, 4, 5, 6, 7, 8};
    array_set_buffer(arr_0, 8, buf);

    array_free(arr_0);

    return 0;
}
