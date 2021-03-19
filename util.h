#include <stdlib.h>
#include "AudioFile.h"
/**
 * Borrowed from https://toto-share.com/2011/11/cc-convolution-source-code/
**/

static void interpretInput(AudioFile<float> wav, float* left_output, float* right_output){
	int numSamples = wav.getNumSamplesPerChannel(); 
    left_output = new float[numSamples];
    right_output = new float[numSamples];
    for (int i = 0; i < numSamples; i++)
    {
        left_output[i] = wav.samples[0][i];
        right_output[i] = wav.samples[1][i];
    }
	return;
}


static float *conv(float *A, float *B, int lenA, int lenB)
{
	int nconv;
	int i, j, i1;
	float tmp;
	float *C;

	//allocated convolution array	
	nconv = lenA+lenB-1;
	C = (float*) calloc(nconv, sizeof(float));

	//convolution process
	for (i=0; i<nconv; i++)
	{
		i1 = i;
		tmp = 0.0;
		for (j=0; j<lenB; j++)
		{
			if(i1>=0 && i1<lenA)
				tmp = tmp + (A[i1]*B[j]);

			i1 = i1-1;
			C[i] = tmp;
		}
	}

	//return convolution array
	return(C);
}