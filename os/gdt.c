#include "kernel.h"




extern void gdt_flush(uint32_t);


struct s_gdt_entry gdt_entries[6];
struct s_gdt_ptr gdt_ptr;



void initGdt(){
	gdt_ptr.limit = (sizeof(struct s_gdt_entry) * 5 ) - 1;
	printf("%d\n", sizeof(struct s_gdt_entry));

	gdt_ptr.base = (uint32_t)(&gdt_entries);

	setGate(0,0,0,0,0);
	setGate(1,0,0xFFFFFFFF,0x9A,0xCF); // kernel code segment
	setGate(2,0,0xFFFFFFFF,0x92,0xCF); // kernel data segment
	gdt_flush((uint32_t)&gdt_ptr);
}



void setGate(uint32_t num, uint32_t base,uint32_t limit,uint8_t access, uint8_t gran){

	gdt_entries[num].first_base = (base & 0xFFFF);
	gdt_entries[num].midde_base = ((base >> 16) & 0xFF);
	gdt_entries[num].last_base = ((base >> 24) & 0xFF);
	gdt_entries[num].first_limit = (limit & 0xFFFF);
	gdt_entries[num].flags = (limit >> 16) & 0x0F;
	gdt_entries[num].flags |= (gran & 0xF0);
	gdt_entries[num].access_byte = access;
}

