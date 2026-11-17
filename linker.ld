MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 32K
    SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 10K
}

SECTIONS 
{
    .text : 
    {
        *(.isr_vector)
        *(.text)
    } > FLASH

    .rodata : 
    {
        *(.rodata)
    } > FLASH

    .data : 
    {
        *(.data)
    } > SRAM AT > FLASH

    .bss : 
    {
        *(.bss)
    } > SRAM
}