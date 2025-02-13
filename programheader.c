#include "programheader.h"

char * getFileType(unsigned e_type)
{
    switch (e_type) {
    case ET_NONE:
        return "ET_NONE (An unknown type)";
        break;
    case ET_REL:
        return "ET_REL (A relocatable file)";
        break;
    case ET_EXEC:
        return "ET_EXEC (An executable file)";
        break;
    case ET_DYN:
        return "ET_DYN (A shared object)";
        break;
    case ET_CORE:
        return "ET_CORE (A core file)";
        break;
    default:
        return "Unknown";
        break;
    }
}

char * getFlags(unsigned p_flags)
{
    switch (p_flags) {
    case 4:
        return "R";
        break;
    case 5:
        return "R E";
        break;
    case 6:
        return "RW";
        break;
    case 7:
        return "RWE";
        break;
    }
}

void parseL(uint8_t *mem)
{
    int i;
    Elf64_Ehdr *ehdr;
    Elf64_Phdr *phdr;
    Elf64_Shdr *shdr;

    ehdr = (Elf64_Ehdr *)mem;
    phdr = (Elf64_Phdr *)&mem[ehdr->e_phoff];
    shdr = (Elf64_Shdr *)&mem[ehdr->e_shoff];

    /*
    * Check the header for the magic number
    */
    if (mem[0] != 0x7f && strcmp(&mem[1], "ELF")) {
        fprintf(stderr, "not an ELF file\n");
        exit(-1);
    }

    printf("\nElf file type is %s\n", getFileType(ehdr->e_type));
    printf("Entry point 0x%lx\n", ehdr->e_entry);
    printf("There are %d program headers, starting at offset %ld\n",
        ehdr->e_phnum, ehdr->e_phoff);
    
    printf("\nProgram Headers:\n");
    printf("Type\t     Offset\t\tVirtAddr\t   PhysAddr\n\t     FileSiz\t\tMemSiz\t\t   Flags Align\n");
    for (i = 0; i < ehdr->e_phnum; i++) {
        switch(phdr[i].p_type) {
        case PT_PHDR:
            printf("PHDR\t     0x%016lx 0x%016lx 0x%016lx\n\t     0x%016lx 0x%016lx %s 0x%lx\n", phdr[i].p_offset, 
                phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz, getFlags(phdr[i].p_flags), phdr[i].p_align);
            break;
        case PT_INTERP:
            printf("INTERP\t     0x%016lx 0x%016lx 0x%016lx\n\t     0x%016lx 0x%016lx %s 0x%lx\n", phdr[i].p_offset, 
                phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz, getFlags(phdr[i].p_flags), phdr[i].p_align);
            printf("\t[Requesting program interpreter: %s]\n", &mem[phdr[i].p_offset]);
            break;
        case PT_LOAD:
            printf("LOAD\t     0x%016lx 0x%016lx 0x%016lx\n\t     0x%016lx 0x%016lx %s 0x%lx\n", phdr[i].p_offset, 
                phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz, getFlags(phdr[i].p_flags), phdr[i].p_align);
            break;
        case PT_DYNAMIC:
            printf("DYNAMIC\t     0x%016lx 0x%016lx 0x%016lx\n\t     0x%016lx 0x%016lx %s 0x%lx\n", phdr[i].p_offset, 
                phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz, getFlags(phdr[i].p_flags), phdr[i].p_align);
            break;
        case PT_NOTE:
            printf("NOTE\t     0x%016lx 0x%016lx 0x%016lx\n\t     0x%016lx 0x%016lx %s 0x%lx\n", phdr[i].p_offset, 
                phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz, getFlags(phdr[i].p_flags), phdr[i].p_align);
            break;
        case PT_GNU_EH_FRAME:
            printf("GNU_EH_FRAME 0x%016lx 0x%016lx 0x%016lx\n\t     0x%016lx 0x%016lx %s 0x%lx\n", phdr[i].p_offset, 
                phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz, getFlags(phdr[i].p_flags), phdr[i].p_align);
            break;
        case PT_GNU_STACK:
            printf("GNU_STACK    0x%016lx 0x%016lx 0x%016lx\n\t     0x%016lx 0x%016lx %s 0x%lx\n", phdr[i].p_offset, 
                phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz, getFlags(phdr[i].p_flags), phdr[i].p_align);
            break;
        case PT_GNU_RELRO:
            printf("GNU_RELRO    0x%016lx 0x%016lx 0x%016lx\n\t     0x%016lx 0x%016lx %s 0x%lx\n", phdr[i].p_offset, 
                phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz, getFlags(phdr[i].p_flags), phdr[i].p_align);
            break;
        }
    }

    printf("\nSection to Segment mapping:\n");

}