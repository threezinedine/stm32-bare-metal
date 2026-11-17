#include <stdint.h>

#define SRAM_START_ADDR				   (0x20000000)
#define SRAM_SIZE					   (10 * 1024)						 // 10 KB
#define STACK_TOP					   (SRAM_START_ADDR + SRAM_SIZE - 4) // Stack top address
#define CORTEX_DEFAULT_ISR_VECTOR_SIZE (16)
#define STM32F103C8T6_ISR_VECTOR_SIZE  (68)

static void Reset_Handler(void);
static void Default_Handler(void);
void		NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void		HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void		MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void		BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void		UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void		SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void		DebugMonitor_Handler(void) __attribute__((weak, alias("Default_Handler")));
void		PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void		SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));

uint32_t isr_vector[CORTEX_DEFAULT_ISR_VECTOR_SIZE + STM32F103C8T6_ISR_VECTOR_SIZE]
	__attribute__((section(".isr_vector"))) = {
		STACK_TOP,
		(uint32_t)Reset_Handler,		// Reset handler
		(uint32_t)NMI_Handler,			// NMI handler
		(uint32_t)HardFault_Handler,	// Hard fault handler
		(uint32_t)MemManage_Handler,	// Memory management fault handler
		(uint32_t)BusFault_Handler,		// Bus fault handler
		(uint32_t)UsageFault_Handler,	// Usage fault handler
		0,								// Reserved
		0,								// Reserved
		0,								// Reserved
		0,								// Reserved
		(uint32_t)SVC_Handler,			// SVCall handler
		(uint32_t)DebugMonitor_Handler, // Debug monitor handler
		0,								// Reserved
		(uint32_t)PendSV_Handler,		// PendSV handler
		(uint32_t)SysTick_Handler,		// SysTick handler
};

const uint32_t a = 23;

extern void k_main(void);

static void Reset_Handler(void)
{
	k_main();
}

static void Default_Handler(void)
{
	while (1)
	{
	}
}