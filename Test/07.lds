ENTRY(start)
MEMORY
{
	DDR0 : ORIGIN 		= 0x20000000<<2, LENGTH = 0x00000400<<2
	SHMEM_SYNC : ORIGIN = 0x000A8000<<2, LENGTH = 0x00000040<<2
	SHMEM : ORIGIN		= 0x000A8040<<2, LENGTH = 0x00017FC0<<2
	
	P1_IMU0 : ORIGIN = 0x80400<<2, LENGTH = 0x7C00<<2
	P1_IMU1 : ORIGIN = 0x88000<<2, LENGTH = 0x8000<<2
	P1_IMU2 : ORIGIN = 0x90000<<2, LENGTH = 0x8000<<2
	P1_IMU3 : ORIGIN = 0x98000<<2, LENGTH = 0x8000<<2
	
	P0_IMU0 : ORIGIN = 0x00400<<2, LENGTH = 0x7C00<<2
	P0_IMU1 : ORIGIN = 0x08000<<2, LENGTH = 0x8000<<2
	
	P0_IMU2 : ORIGIN = 0x50000<<2, LENGTH = 0x8000<<2
	P0_IMU3 : ORIGIN = 0x58000<<2, LENGTH = 0x8000<<2
	P0_IMU4 : ORIGIN = 0x60000<<2, LENGTH = 0x8000<<2
	P0_IMU5 : ORIGIN = 0x68000<<2, LENGTH = 0x8000<<2
	P0_IMU6 : ORIGIN = 0x70000<<2, LENGTH = 0x8000<<2
	P0_IMU7 : ORIGIN = 0x78000<<2, LENGTH = 0x8000<<2
	
}
SECTIONS
{

 . = ALIGN(4);
 .ddr0_data : {
        *(.ddr0_data)
 } > DDR0

 . = ALIGN(4);
 .stack : {
	*(.stack)
 } > P0_IMU1

 . = ALIGN(4);
 .text : {
        *(.text)
 } > P0_IMU0

 . = ALIGN(4);
 .data : {
	*(.data)
 } > P0_IMU1

 . = ALIGN(4);
 .bss (NOLOAD) : {
	*(.bss)
 } > P0_IMU1

  . = ALIGN(4);
 .init : {
        *(.init)
 } > P0_IMU0

 . = ALIGN(4);
 .fini : {
	*(.fini)
 } > P0_IMU0

 . = ALIGN(4);
 .nmsync : {
	*(.nmsync)
 } > SHMEM_SYNC

}
