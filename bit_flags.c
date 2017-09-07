/***********************************************************
Author: Joanel Vasquez
Date: June 6, 2016
Effort: About 3 hours
Purpose: The purpose of this assignment is to create an object that holds bits strings. 
         The user will be able to change any of the bits from 0 to 1 and viceversa.
Interface proposal: A function that could be added to the interface is one that lets us
                    see the integer value after the bit has been changed. This will help 
					us see which integer is changing and specific values of the integer
					could be returned.
***********************************************************/

//Libraries
#include <stdlib.h>
#include "bit_flags.h"

//Structure with the memory footprint
struct bit_flags
{
	int size;
	int capacity;
	unsigned int* data; 
};

typedef struct bit_flags Bit_flags;

/*****FIRST BOOK END (DEFAULT)******/
BIT_FLAGS bit_flags_init_default(void)
{
	Bit_flags* pBit_flags;

	pBit_flags = (Bit_flags*)malloc(sizeof(Bit_flags));
	if (pBit_flags != NULL)
	{
		pBit_flags->size = 5; //holding 5 flags
		pBit_flags->capacity = 32; //how many flags you could hold
		pBit_flags->data = (unsigned int*)malloc(sizeof(unsigned int)*pBit_flags->capacity);
		if (pBit_flags->data == NULL)
		{
			free(pBit_flags);
			pBit_flags = NULL;
		}
	}

	return pBit_flags;
}

/*********************FIRST BOOK END**********************/
BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
	Bit_flags* pBit_flags;
	int i;

	//Allocates some space for the object
	pBit_flags = malloc(sizeof(Bit_flags));
	if (pBit_flags != NULL)
	{
		pBit_flags->size = number_of_bits;
		pBit_flags->capacity = 32;
		while (number_of_bits >= pBit_flags->capacity)
		{
			pBit_flags->capacity += 32;
		}

		pBit_flags->data = (unsigned int*) malloc(sizeof(unsigned int)*pBit_flags->capacity); //
		if (pBit_flags == NULL)
		{
			free(pBit_flags);
			pBit_flags = NULL;
		}

		for (i = 0; i < pBit_flags->size; i++)
		{
			pBit_flags->data[i] = 0;
		}
	}

	return pBit_flags;
}

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	int i;
	unsigned int* temp;
	Bit_flags* pBit_flags = (Bit_flags*) hBit_flags;

	while ((flag_position) >= pBit_flags->capacity)
	{
		temp = (unsigned int*)malloc(sizeof(unsigned int) * (pBit_flags->capacity + 32));
		if (temp == NULL)
		{
			return FAILURE;
		}

		for (i = 0; i < pBit_flags->size; i++)
		{
			temp[i] = pBit_flags->data[i];
		}

		free(pBit_flags->data);
		pBit_flags->data = temp;
		pBit_flags->capacity += 32;
	}

	if (flag_position >= pBit_flags->size)
	{
		pBit_flags->size = flag_position + 1;
	}
	pBit_flags->data[flag_position / 32] |= (1 << (flag_position));

	return SUCCESS;
}

Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	int i;
	unsigned int* temp;

	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;

	while ((flag_position) >= pBit_flags->capacity)
	{
		temp = (unsigned int*)malloc(sizeof(unsigned int) * (pBit_flags->capacity + 32));
		if (temp == NULL)
		{
			return FAILURE;
		}

		for (i = 0; i < pBit_flags->size; i++)
		{
			temp[i] = pBit_flags->data[i];
		}

		free(pBit_flags->data);
		pBit_flags->data = temp;
		pBit_flags->capacity += 32;
	}

	if (flag_position >= pBit_flags->size)
	{
		pBit_flags->size = flag_position + 1;
	}
	pBit_flags->data[flag_position / 32] &= ~(1 << (flag_position));

	return SUCCESS;
}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;

	if (flag_position >= pBit_flags->size)
	{
		return -1;
	}

	if ((pBit_flags->data[flag_position / 32] & (1 << (flag_position))) != 0)
	{
		return 1;
	}
	return 0;
}

int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;

	return pBit_flags->size;
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;

	return pBit_flags->capacity;
}

/*************SECOND BOOK END****************/
void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*) *phBit_flags;

	free(pBit_flags->data);
	free(pBit_flags);
	*phBit_flags = NULL;
}