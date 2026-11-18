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
        . = ALIGN(4);
        _ro_start = .;
        *(.rodata)
        . = ALIGN(4);
        _ro_end   = .;
    } > FLASH

    .data : 
    {
        _data_start = .;
        *(.data)
        . = ALIGN(4);
        _data_end   = .;
    } > SRAM AT > FLASH

    .bss : 
    {
        _bss_start = .;
        *(.bss)
        . = ALIGN(4);
        _bss_end   = .;
    } > SRAM
}