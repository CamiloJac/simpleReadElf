#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <elf.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd, opt; 
    uint8_t *mem; // memory for executable
    struct stat st; // get file status
 
    if (argc < 3) {
        printf("Usage: %s [-h -l -S -s] <executable>\n", argv[0]);
        exit(0);
    }    

    if ((fd = open(argv[2], O_RDONLY)) < 0) {
        perror("open");
        exit(-1);
    }

    if (fstat(fd, &st) < 0) { 
        perror("fstat");
        exit(-1);
    }

    while ((opt = getopt(argc, argv, "hlSs")) != -1) {
        switch (opt) {
        case 'h':
            printf("You selected h!\n");
            break;
        case 'l':
            printf("You selected l!\n");
            break;
        case 'S':
            printf("You selected S!\n");
            break;
        case 's':
            printf("You selected s!\n!");
            break;
        default:
            printf("Unknown option selected!\n");
            exit(0);
        }
    }

    
}
