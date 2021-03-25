#include <stdlib.h>
#include "AudioFile.h"

static float *conv(float *inputA, float *inputB, int lengthA, int lengthB)
{
	int num_conv;
	int i, j, k;
	float temp;
	float *output;

	num_conv = lengthA+lengthB-1;
	output = (float*) calloc(num_conv, sizeof(float));

	for (i=0; i<num_conv; i++)
	{
		k = i;
		temp = 0.0;
		for (j=0; j<lengthB; j++)
		{
			if(k>=0 && k<lengthA)
				temp = temp + (inputA[k]*inputB[j]);

			k = k-1;
			output[i] = temp;
		}
	}

	return(output);
}