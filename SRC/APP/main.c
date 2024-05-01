 #include "tm4c123.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "UART.h"
#include "GPS.h"

int  main(void)
{
		char gprmc_sentence[] = "$GPRMC,123456.789,A,1234.5678,N,5678.1234,E,...";

    float latitude=0.0, longitude=0.0;
	  float current_latitude, current_longitude;
	  float prev_latitude = 3014.190430;
	  float prev_longitude = 3126.626221;
	  float distance=0.0;


    int i = 0;
    char c;	
	  uart_init();
    Delay(1); 
    printstring("Hello World \n");
    Delay(10); 
		

    while(1)
    {
         c = UART1_Receiver(); /* get a character from UART1 */
        if(c == '$') {
            i = 0; /* reset index if we found a new sentence starting */
        }
        *(gprmc_sentence+i) = c;
        i++;
        if(c == '\n') { /* end of sentence */
           gprmc_sentence[i] = '\0'; /* null terminate the string */
            /* check if it's a GPRMC sentence */
					    if (gprmc_sentence[0] == '$' && gprmc_sentence[1] == 'G' && gprmc_sentence[2] == 'P' &&
                  gprmc_sentence[3] == 'R' && gprmc_sentence[4] == 'M' && gprmc_sentence[5] == 'C') {
               printstring(gprmc_sentence);  
               extract_lat_lon( gprmc_sentence, &latitude, &longitude);
							 current_latitude  = latitude;
							 current_longitude = longitude;
               
						 	 printstring("latitude\n");
					   	 printFloat_UART0(latitude);
						   UART0_Transmitter('\n');
						   printstring("longitude\n");
						   printFloat_UART0(longitude);
						   UART0_Transmitter('\n');
							 printstring("prev_latitude\n");
						   printFloat_UART0(prev_latitude);
						   UART0_Transmitter('\n');
							 printstring("prev_longitude\n");
						   printFloat_UART0(prev_longitude);
						   UART0_Transmitter('\n');		
							 distance=GPS_calc_distance(current_latitude,current_longitude,prev_latitude,prev_longitude);
							 printstring("distance\n");
						   printFloat_UART0 (distance);
					     UART0_Transmitter('\n');
										
					 
									}else {
        // Invalid GPRMC sentence
        latitude = 0.0f;
        longitude = 0.0f;
    }
						
   }
  }
}










		
		








