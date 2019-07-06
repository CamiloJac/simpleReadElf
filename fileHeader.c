#include <stdio.h>
#include <string.h>
#include <elf.h>
#include <stdint.h>


void dispFileHdr(uint8_t *mem)
{
    int i;
    Elf64_Ehdr *ehdr;

    /*
     * The inital ELF Header starts at 
     * of our mapped memory
     */
    ehdr = (Elf64_Ehdr *)mem;
    
        
    printf("ELF Header:\n  Magic:   ");
    for (i = 0; i < 16; i++) {
        printf("%02x ", mem[i]);
    }
    printf("\n");
}
