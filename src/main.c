#include <stdint.h>

#define RCC_BASE_ADDR (0x40021000)

#define RCC_APB2ENR_OFFSET (0x18)
#define RCC_APB2ENR_ADDR   (*(volatile uint32_t*)(RCC_BASE_ADDR + RCC_APB2ENR_OFFSET))

#define IOPCEN (1 << 4)

#define GPIOC_BASE_ADDR (0x40011000)
#define GPIOC_CRL		(*(volatile uint32_t*)(GPIOC_BASE_ADDR))
#define GPIOC_CRH		(*(volatile uint32_t*)(GPIOC_BASE_ADDR + 0x4))
#define GPIOC_IDR		(*(volatile uint32_t*)(GPIOC_BASE_ADDR + 0x8))
#define GPIOC_ODR		(*(volatile uint32_t*)(GPIOC_BASE_ADDR + 0xc))
#define GPIOC_BSRR		(*(volatile uint32_t*)(GPIOC_BASE_ADDR + 0x10))
#define GPIOC_BRR		(*(volatile uint32_t*)(GPIOC_BASE_ADDR + 0x14))
#define GPIOC_LCKR		(*(volatile uint32_t*)(GPIOC_BASE_ADDR + 0x18))

void init_rcc(void);
void pc13_config(void);
void pc13_turn_on(void);
void pc13_turn_off(void);
void pc13_toggle(void);

void k_main(void)
{
	init_rcc();
	pc13_config();

	while (1)
	{
		for (uint32_t i = 0; i < 120000; ++i)
		{
		}
		pc13_toggle();
	}
}

void init_rcc(void)
{
	RCC_APB2ENR_ADDR |= IOPCEN;
}

void pc13_config(void)
{
	GPIOC_CRH &= ~(0xFU << 20);
	GPIOC_CRH |= (0b0001U << 20);
}

void pc13_turn_on(void)
{
	GPIOC_ODR &= ~(1 << 13);
}

void pc13_turn_off(void)
{
	GPIOC_ODR |= (1 << 13);
}

void pc13_toggle(void)
{
	GPIOC_ODR ^= (1U << 13);
}