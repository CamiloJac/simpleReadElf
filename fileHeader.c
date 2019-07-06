#include <stdio.h>
#include <string.h>
#include <elf.h>
#include <stdint.h>


char * getOSABI(unsigned char);
char * getEType(uint16_t);
char * getMachine(uint16_t);

void dispFileHdr(uint8_t *mem)
{
    int i;
    Elf64_Ehdr *ehdr;

    /*
     * The inital ELF Header starts at 0
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

    printf("  OS/ABI:%43s\n", getOSABI(ehdr->e_ident[EI_OSABI])); 
                            
    printf("  ABI Version:%24d\n", ehdr->e_ident[EI_ABIVERSION]); 
    
    printf("  Type:%54s\n", getEType(ehdr->e_type));                             

    printf("  Machine:%29d\n", ehdr->e_machine);
    
    printf("  Version:%#30x\n", ehdr->e_version);
    
    printf("  Entry point address:%#20lx\n", ehdr->e_entry);

    printf("  Start of program headers:%12ld (bytes into file)\n", ehdr->e_phoff);
    
    printf("  Start of section headers:%15ld (bytes into file)\n", ehdr->e_shoff);

    printf("  Flags:%#30x\n", ehdr->e_flags);

    printf("  Size of this header:%17d (bytes)\n", ehdr->e_ehsize);

    printf("  Size of program headers:%13d (bytes)\n", ehdr->e_phentsize);

    printf("  Number of program headers:%10d\n", ehdr->e_phnum);

    printf("  Size of section headers:%13d (bytes)\n", ehdr->e_shentsize);

    printf("  Number of section headers:%11d\n", ehdr->e_shnum);
}


char * getOSABI(unsigned char EI_VAL)
{
    switch (EI_VAL) {
    case 0:
    case 1:
        return "Unix - System V";
    case 2:
        return "HP - UX";
    case 3:
        return "NetBSD";
    case 4:
        return "Linux ABI";
    case 5:
        return "Solaris";
    case 6:
        return "IRIX";
    case 7:
        return "FreeBSD";
    case 8:
        return "TRU64 UNIX";
    case 9:
        return "ARM";
    case 10:
        return "Stand-alone";
    }
}


char * getEType(uint16_t e_type)
{
    switch (e_type) {
    case 0:
        return "NONE (Unknown type)";
    case 1:
        return "REL (Relocatable file)";
    case 2:
        return "EXEC (Executable file)";
    case 3:
        return "DYN (Shared object file)";
    case 4:
        return "CORE (Core file)";
    }
}
