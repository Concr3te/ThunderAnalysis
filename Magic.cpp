#include <iostream>
#include <magic.h>

int main(int argc, char *argv[])
{
    magic_t cookie = magic_open(MAGIC_MIME);

    magic_load(cookie, NULL);

    fprintf(stdout, " File type %s\n", magic_file(cookie, argv[1]));

    magic_close(cookie);
}