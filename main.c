#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"


int main(int argc, char* argv[])
{
	int i;

	//Step 1: Declare the handle and set it to NULL
	BIT_FLAGS hBit_flags = NULL;

	//Step 2: Init the object using some init function
	hBit_flags = bit_flags_init_number_of_bits(5);
	if (hBit_flags == NULL)
	{
		printf("Failed to allocate the memory for the bit_flag object.\n");
		exit(1);
	}

	//Step 3: Use the object to do work
	/*1- Checking the size/capacity after init_default()*/
	printf("1- Checking the size and capacity after the init default function\n");
	printf("Size = %d\n", bit_flags_get_size(hBit_flags));
	printf("Capacity = %d\n\n", bit_flags_get_capacity(hBit_flags));

	/*2- Checking set_flag and its resize operation*/
	printf("2- Testing set_flag and its resize operation\n");
	printf("Testing flag positions: 2, 5, 7, 32, 29\n");
	bit_flags_set_flag(hBit_flags, 2);
	bit_flags_set_flag(hBit_flags, 5);
	bit_flags_set_flag(hBit_flags, 7);
	bit_flags_set_flag(hBit_flags, 32);
	bit_flags_set_flag(hBit_flags, 29);
	for (i = 1; i <= bit_flags_get_capacity(hBit_flags); i++)
	{
		printf("%d", bit_flags_check_flag(hBit_flags, i - 1));
		if (i % 4 == 0)
		{
			printf(" ");
		}
	}
	printf("\n");
	printf("Size = %d\n", bit_flags_get_size(hBit_flags));
	printf("Capacity = %d\n\n", bit_flags_get_capacity(hBit_flags));

	/*3- Testing bit_flags_unset_flags and its resize operation*/
	printf("3- Testing unset_flag and its resize operation\n");
	printf("Testing flag positions: 2, 7, 29, 64\n");
	bit_flags_unset_flag(hBit_flags, 2);
	bit_flags_unset_flag(hBit_flags, 7);
	bit_flags_unset_flag(hBit_flags, 29);
	bit_flags_unset_flag(hBit_flags, 64);
	for (i = 1; i <= bit_flags_get_capacity(hBit_flags); i++)
	{
		printf("%d", bit_flags_check_flag(hBit_flags, i - 1));
		if (i % 4 == 0)
		{
			printf(" ");
		}
	}
	printf("\n");
	printf("Size = %d\n", bit_flags_get_size(hBit_flags));
	printf("Capacity = %d\n\n", bit_flags_get_capacity(hBit_flags));

	//Step 4: Destroy the object
	bit_flags_destroy(&hBit_flags);
	if (hBit_flags == NULL)
	{
		printf("VICTORY!!!\n");
	}

	return 0;
}