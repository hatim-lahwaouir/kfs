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
#define ATTRIBUTE               240 
/* The video memory address. */
#define VIDEO                   0xB8000

extern volatile  unsigned char* video;
extern int xpos;
extern int ypos;
void cls (void);
void putchar (int c);
void itoa (char *buf, int base, int d);
void printf (const char *format, ...);
void	*ft_memset(void *b, int c, uint32_t len);
void scrollUp();
void clear_screens();
void switchScreen();


// screen struct 
struct s_screens{
	int xpos;
	int ypos;
};
// gdt  
struct gdt_entry_struct{
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t flags;
    uint8_t base_high;
}__attribute__((packed));

struct gdt_ptr_struct{
    uint16_t limit;
    uint32_t base; 
}__attribute__((packed));

void initGdt();
void setGdtGate(uint32_t num, uint32_t base,uint32_t limit,uint8_t access, uint8_t gran);


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


extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();


struct InterruptRegister {
	uint32_t cr2;
	uint32_t ds;
	uint32_t edi, esi,ebp, esp, ebx,edx, ecx, eax;
	uint32_t int_nbr,err_code;
	uint32_t eip,csm, eflags, useresp, ss;
};


void isr_handler(struct InterruptRegister *regs);



void  outPortB(uint16_t port, uint8_t value);
char inPortB(uint16_t port);

void irq_install_handler(int irq, void (*handler)(struct InterruptRegister *r));
void irq_uinistall_handler(int irq);

// key boared 

void initKeyboard();
void KeyboardHandler(struct InterruptRegister *regs);

#endif
