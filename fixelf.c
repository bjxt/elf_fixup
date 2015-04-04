#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "elf.h"

int main(int argc, char *argv[])
{
	int i;
	int opt;
	/* flags*/
	int vaddr_s = 0, fs_s =0, ms_s=0, off_s=0, e_s = 0;
	uint64_t vaddr,fs,ms,off;
	char *e;
	char *temp;

	FILE *file;
	int phdr_off =0 ;
	Elf64_Ehdr main_hdr;
	Elf64_Phdr phdr;



        while ((opt = getopt(argc, argv, "v:f:m:o:e:")) != -1)
        {
            switch (opt)
            {
            	case 'v':
            	    	temp = optarg;
	    	    	vaddr = strtol(temp, NULL, 16);
			vaddr_s = 1;
            	    	break;
            	case 'f':

            	    	temp = optarg;
			fs = strtol(temp, NULL, 16);
			fs_s = 1;
			break;
            	case 'm':

            	    	temp = optarg;
			ms = strtol(temp, NULL, 16);
			ms_s = 1;
			break;
            	case 'o':

            	    	temp = optarg;
			off = strtol(temp, NULL, 16);
			off_s = 1;
			break;
		case 'e':
			e = optarg;
			e_s =1;
			break;			
		default :
	    	case 'h' :
			fprintf(stderr, "Used argument %c\n", optopt);
            	    	fprintf(stderr, "Usage: %s [ -v <vaddr> -f <file sz> -m <memsz> -o <offset> ] -e elf_file\n", argv[0]);
            	    	return 1;
            }
        }

	if(!e_s)
	{
		fprintf(stderr, "elf file is mandatory\n");
		return 1;
	}
	if (!(vaddr_s || fs_s || ms_s || off_s))
	{
		fprintf(stderr, "You need to change atleast one parameter\n");
		return 1;
	}

	file = fopen(e, "rw+b");
	if(!file)
	{
		fprintf(stderr, "Unable to open file %s\n", e);
		return 1;
	}
	
	fread(&main_hdr, sizeof(main_hdr), 1, file);
	phdr_off = main_hdr.e_phoff;
	printf("Program header offset = %d\n", phdr_off);

	fseek(file, phdr_off, 0);
	while(!feof(file))
	{
		fread(&phdr, sizeof(phdr), 1, file);
		if(phdr.p_type == 1)
		{
			printf("Found a text segment\n");
			break;
		}
	}

	if(feof(file))
	{
		fprintf(stderr, "Couldn't find text\n");
		return 1;
	}

	if(vaddr_s)
	{
		printf("Current vaddr = %lx\n", phdr.p_vaddr);
		phdr.p_vaddr = vaddr;
		printf("Updated to %lx\n", vaddr);
	}
	if(fs_s)
	{
		printf("Current filesz = %lx\n", phdr.p_filesz);
		phdr.p_filesz = fs;
		printf("Updated to %lx\n", fs);
	}
	if(ms_s)
	{
		printf("Current memsz = %lx\n", phdr.p_memsz);
		phdr.p_memsz = ms;
		printf("Updated to %lx\n", ms);
	}
	if(off_s)
	{
		printf("Current offset = %lx\n", phdr.p_offset);
		phdr.p_offset = off;
		printf("Updated to %lx\n", off);
	}

	
	fseek(file, phdr_off, 0);
	fwrite(&phdr, sizeof(phdr), 1, file);
	fclose(file);	
}
