
typedef uint64_t   Elf64_Addr;
typedef uint16_t   Elf64_Half;
typedef int16_t   Elf64_SHalf;
typedef uint64_t   Elf64_Off;
typedef int32_t   Elf64_Sword;
typedef uint32_t   Elf64_Word;
typedef uint64_t   Elf64_Xword;
typedef int64_t   Elf64_Sxword;


typedef struct  __attribute__ ((__packed__)) elf64_hdr {
  unsigned char e_ident[16];     /* ELF "magic number" */
  Elf64_Half e_type;
  Elf64_Half e_machine;
  Elf64_Word e_version;
  Elf64_Addr e_entry;           /* Entry point virtual address */
  Elf64_Off e_phoff;            /* Program header table file offset */
  Elf64_Off e_shoff;            /* Section header table file offset */
  Elf64_Word e_flags;
  Elf64_Half e_ehsize;
  Elf64_Half e_phentsize;
  Elf64_Half e_phnum;
  Elf64_Half e_shentsize;
  Elf64_Half e_shnum;
  Elf64_Half e_shstrndx;
} Elf64_Ehdr;


typedef struct  __attribute__ ((__packed__)) elf64_phdr {
  Elf64_Word p_type;
  Elf64_Word p_flags;
  Elf64_Off p_offset;           /* Segment file offset */
  Elf64_Addr p_vaddr;           /* Segment virtual address */
  Elf64_Addr p_paddr;           /* Segment physical address */
  Elf64_Xword p_filesz;         /* Segment size in file */
  Elf64_Xword p_memsz;          /* Segment size in memory */
  Elf64_Xword p_align;          /* Segment alignment, file & memory */
} Elf64_Phdr;


