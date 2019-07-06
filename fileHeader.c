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
    
        

    printf("ELF Header:\n  Magic:%5x%3x%3x%3x ", ehdr->e_ident[EI_MAG0], 
            ehdr->e_ident[EI_MAG1], ehdr->e_ident[EI_MAG2], ehdr->e_ident[EI_MAG3]);
    for (i = 4; i < 16; i++) {
        printf("%02x ", mem[i]);
    }
    printf("\n");
    printf("  Class:%34s\n", ((ehdr->e_ident[EI_CLASS] == 0) ? "ELFNONE" : 
                            (ehdr->e_ident[EI_CLASS] == 1) ? "ELF32" :
                            "ELF64"));

    printf("  Data:%59s\n", ((ehdr->e_ident[EI_DATA] == 0) ? "Unknown data format" :
                            (ehdr->e_ident[EI_DATA] == 1) ? "2's complement, little endian" :
                            "2's complement, big endian"));    
    

    printf("  Version:%38s\n", ((ehdr->e_ident[EI_VERSION] == 0) ? "0 (invalid)" : "1 (current)"));
}
