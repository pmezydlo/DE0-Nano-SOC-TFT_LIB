#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "hwlib.h"
#include "socal/socal.h"
#include "socal/hps.h"
#include "socal/alt_gpio.h"
#include "hps_0.h"

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

int main() {

	void *virtual_base;
	int fd;
	int loop_count;
	int led_direction;
	int led_mask;
	void *h2p_lw_led_addr;

	// map the address space for the LED registers into user space so we can interact with them.
	// we'll actually map in the entire CSR span of the HPS since we want to access various registers within that span

	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return( 1 );
	}

	virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );

	if( virtual_base == MAP_FAILED ) {
		printf( "ERROR: mmap() failed...\n" );
		close( fd );
		return( 1 );
	}
	


	// toggle the LEDs a bit

	loop_count = 0;
	led_mask = 0x01;
	led_direction = 0; // 0: left to right direction
	int offset=0;	
 	h2p_lw_led_addr=virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + ONCHIP_MEMORY2_0_BASE ) & ( unsigned long)( HW_REGS_MASK ) );
	int zm = ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + ONCHIP_MEMORY2_0_BASE ) & ( unsigned long)( HW_REGS_MASK ) );      


	while(1) {
		printf("virtual_base");
		printf("%d",virtual_base);

		printf("h2p_lw_led_addr");
		printf("%d",h2p_lw_led_addr);


		printf("( ( unsigned long  )( ALT_LWFPGASLVS_OFST + ONCHIP_MEMORY2_0_BASE ) & ( unsigned long)( HW_REGS_MASK ) );  ");
		printf("%d",zm);

                 printf("Podaj adres: ");
                 scanf("%d",&offset);
	


                   printf("Podaj liczbe: ");
                 scanf("%d",&led_mask);

	alt_write_word(h2p_lw_led_addr+offset, led_mask);
		
	} // while
	

	// clean up our memory mapping and exit
	
	if( munmap( virtual_base, HW_REGS_SPAN ) != 0 ) {
		printf( "ERROR: munmap() failed...\n" );
		close( fd );
		return( 1 );
	}

	close( fd );

	return( 0 );
}