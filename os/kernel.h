#ifndef KERNEL__H
#define KERNEL__H 

typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef signed short int16_t;
typedef unsigned short uint16_t;

typedef signed long int int32_t;
typedef unsigned long int uint32_t;

/* Some screen stuff. */
/* The number of columns. */
#define COLUMNS                 80
/* The number of lines. */
#define LINES                   24
/* The attribute of an character. */
#define ATTRIBUTE               240 
/* The video memory address. */
#define VIDEO                   0xB8000

void cls (void);
void putchar (int c);
void itoa (char *buf, int base, int d);
void printf (const char *format, ...);
void	*ft_memset(void *b, int c, uint32_t len);




// gdt  
struct s_gdt_entry{
	uint16_t  first_limit;
	uint16_t  first_base;
	uint8_t   midde_base;
	uint8_t  access_byte;
	uint8_t  flags;
	uint8_t  last_base;
} __attribute__((packed));


struct s_gdt_ptr{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

void initGdt();
void setGate(uint32_t num, uint32_t base,uint32_t limit,uint8_t access, uint8_t gran);


// idt

struct s_idt_entry {
	uint16_t first_offset;
	uint16_t sel;
	uint8_t always0;
	uint8_t flags;
	uint16_t second_offset;
} __attribute__((packed));

struct s_idt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));


void initIDT();
void setIdtGate(uint32_t num, uint32_t base,uint32_t sel,uint8_t flags);


// isr 
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void isr128();
extern void isr177();


struct InterruptRegister {
	uint32_t cr2;
	uint32_t ds;
	uint32_t edi, esi,ebp, esp, ebx,edx, ecx, eax;
	uint32_t int_nbr,err_code;
	uint32_t eip,csm, eflags, useresp, ss;
};


void isr_handler(struct InterruptRegister *regs);




#endif
