#include "sectionheader.h"

char * getSecFlags(unsigned sh_flags) 
{
    switch(sh_flags) {
    case SHF_WRITE:
        return "W";
        break;
    }
}
void parseSection(uint8_t *mem)
{
    int i;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;

    ehdr = (Elf64_Ehdr *)mem;
    shdr = (Elf64_Shdr *)&mem[ehdr->e_shoff];

    /*
    * Check the header for the magic number
    */
    if (mem[0] != 0x7f && strcmp(&mem[1], "ELF")) {
        fprintf(stderr, "not an ELF file\n");
        exit(-1);
    }

    char *stringTable;
    stringTable = &mem[shdr[ehdr->e_shstrndx].sh_offset];

    printf("\nThere are %d section headers, starting at offset 0x%lx:\n\n", ehdr->e_shnum, ehdr->e_shoff);

    for (i = 0; i < ehdr->e_shnum; i++) {
        printf("[%2d] %16d %016d %016lx %08lx\n     %016lx %016lx %6ld %4d %4d %4ld\n", i, 
            stringTable[shdr[i].sh_name], shdr[i].sh_type, shdr[i].sh_addr, shdr[i].sh_offset, 
            shdr[i].sh_size, shdr[i].sh_entsize, shdr[i].sh_flags, shdr[i].sh_link, shdr[i].sh_info, shdr[i].sh_addralign);
    }

}