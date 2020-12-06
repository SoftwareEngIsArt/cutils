#include "io_utils.h"

void wait_key_promt(char c)
{
    /* Check character value */
    if (c < 0x20 || c > 0x7e || c != '\n')
        c = 0;

    /* Send promt message */
    if (!c)
        puts("Press any key to continue");
    else if (c == '\n')
        puts("Press enter to continue");
    else
        printf("Press %c to continue\n", c);

    printf("\n...");

    /* Loop untill character is caught */
    for (;;)
        if (getc(stdin) == c)
            break;
}