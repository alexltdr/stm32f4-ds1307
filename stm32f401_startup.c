#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

__asm__(".type Reset_Handler, %function");
__asm__(".type Default_Handler, %function");
__asm__(".type main, %function");

void Reset_Handler(void);
void Default_Handler(void);
int main(void);

void NMI_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)    __attribute__((weak, alias("Default_Handler")));

uint32_t vector_tbl[] __attribute__((section(".isr_vector_tbl"))) = {
    (uint32_t)&_estack,             /* 0  : pile */
    (uint32_t)&Reset_Handler,       /* 1  */
    (uint32_t)&NMI_Handler,         /* 2  */
    (uint32_t)&HardFault_Handler,   /* 3  */
    (uint32_t)&MemManage_Handler,   /* 4  */
    (uint32_t)&BusFault_Handler,    /* 5  */
    (uint32_t)&UsageFault_Handler,  /* 6  */
    0, 0, 0, 0,                     /* 7-10 : réservés */
    (uint32_t)&SVC_Handler,         /* 11 */
    (uint32_t)&DebugMon_Handler,    /* 12 */
    0,                              /* 13 : réservé */
    (uint32_t)&PendSV_Handler,      /* 14 */
    (uint32_t)&SysTick_Handler,     /* 15 : SysTick */
};

void Default_Handler(void) {
    while(1) {
    }
}

void Reset_Handler(void) {
    uint32_t data_mem_size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint32_t bss_mem_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    uint32_t *p_src_mem = (uint32_t *)&_etext;
    uint32_t *p_dest_mem = (uint32_t *)&_sdata;

    for (uint32_t i = 0; i < data_mem_size / sizeof(uint32_t); i++) {
        *p_dest_mem++ = *p_src_mem++;
    }

    p_dest_mem = (uint32_t *)&_sbss;
    for(uint32_t i = 0; i < bss_mem_size / sizeof(uint32_t); i++) {
        *p_dest_mem++ = 0;
    }
    main();
    while(1) {}
}
