/*
 * project_1_source.c
 *
 *  Created on: Oct 24, 2017
 *      Author: milosz
 */
/*

#include <stdio.h>
#include "xil_io.h"
int main (void)
{
	printf("Test Project\n\r");
	printf("Writing to a custom IP register...");

	int i;
	int j;
	for(i=0; i<100;i++)
	{
		Xil_Out32(0x43C00000, 0x01);
		for(j=0; j<10000000; j++);
		Xil_Out32(0x43C00000, 0x02);
		for(j=0; j<10000000; j++);
	}
	printf("Done\n\r");
	return 0;
}

*/
