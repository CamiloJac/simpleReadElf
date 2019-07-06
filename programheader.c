#include "programheader.h"

void parsel(uint8_t *mem)
{
    printf("Enter parsel\n");
    int i;

    printf("Before ehdr\n");

    Elf64_Ehdr *ehdr;
    ehdr = (Elf64_Ehdr *)mem;

    printf("Before phdr\n");
    
    Elf64_Phdr *phdr;
    phdr = (Elf64_Phdr *)&mem[ehdr->e_phoff];

    printf("Before check\n");

    if (mem[0] != 0x7f && strcmp(&mem[1], "ELF")) {
        fprintf(stderr, "not an ELF file\n");
        exit(-1);
    }

    printf("After mem/Before prints\n");

    printf("/nElf file type is %d\n", ehdr->e_type);
    printf("Entry point 0x%lx\n", ehdr->e_entry);
    printf("There are %d program headers, starting at offset %ld\n", ehdr->e_phnum, ehdr->e_phoff);
    
    printf("\nProgram Headers:\n");
    for (i = 0; i < ehdr->e_phnum; i++) {
        switch(phdr[i].p_type) {
        case PT_PHDR:
            printf("PHDR 0x%lx 0x%lx 0x%lx\n     0x%lx 0x%lx %d 0x%lx", phdr[i].p_offset, phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz, phdr[i].p_flags, phdr[i].p_align);
            break;
        case PT_INTERP:
            printf("INTERP 0x%lx 0x%lx 0x%lx\n     0x%lx 0x%lx %d 0x%lx", phdr[i].p_offset, phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz, phdr[i].p_flags, phdr[i].p_align);
            break;
        case PT_LOAD:
            printf("LOAD 0x%lx 0x%lx 0x%lx\n     0x%lx 0x%lx %d 0x%lx", phdr[i].p_offset, phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz, phdr[i].p_flags, phdr[i].p_align);
            break;
        case PT_DYNAMIC:
            printf("DYNAMIC 0x%lx 0x%lx 0x%lx\n     0x%lx 0x%lx %d 0x%lx", phdr[i].p_offset, phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz, phdr[i].p_flags, phdr[i].p_align);
            break;
        case PT_NOTE:
            printf("NOTE 0x%lx 0x%lx 0x%lx\n     0x%lx 0x%lx %d 0x%lx", phdr[i].p_offset, phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz, phdr[i].p_flags, phdr[i].p_align);
            break;
        case PT_GNU_EH_FRAME:
            printf("GNU_EH_FRAME 0x%lx 0x%lx 0x%lx\n     0x%lx 0x%lx %d 0x%lx", phdr[i].p_offset, phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz, phdr[i].p_flags, phdr[i].p_align);
            break;
        case PT_GNU_STACK:
            printf("GNU_STACK 0x%lx 0x%lx 0x%lx\n     0x%lx 0x%lx %d 0x%lx", phdr[i].p_offset, phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz, phdr[i].p_flags, phdr[i].p_align);
            break;
        case PT_GNU_RELRO:
            printf("GNU_RELRO 0x%lx 0x%lx 0x%lx\n     0x%lx 0x%lx %d 0x%lx", phdr[i].p_offset, phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz, phdr[i].p_flags, phdr[i].p_align);
            break;
        }
    }
}
