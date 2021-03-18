#include "AudioFile.h"
#include "HRTFContainter.h"
#include "convolute.h"

int main(){

    //load input
    string input = "PROD_TAG.wav";
    AudioFile<float> wav = AudioFile<float>(input);
    wav.printSummary();

    //interpret input
    float* wav_array_left;
    float* wav_array_right;
    int numSamples = wav.getNumSamplesPerChannel(); 
    wav_array_left = new float[numSamples];
    wav_array_right = new float[numSamples];
    for (int i = 0; i < numSamples; i++)
    {
        wav_array_left[i] = wav.samples[0][i];
        wav_array_right[i] = wav.samples[1][i];
    }

    //apply HRTF
    float* left_processed;
    float* right_processed;
    left_processed = new float[numSamples+199];
    right_processed = new float[numSamples+199];

    HRTFContainer hrtf = HRTFContainer();
    left_processed = conv(wav_array_left, hrtf.get_hrir_l(5,27), numSamples, 200);
    right_processed = conv(wav_array_right, hrtf.get_hrir_r(5,27), numSamples, 200);
    
    AudioFile<float> processed = AudioFile<float>();
    processed.setNumChannels(2);
    processed.setNumSamplesPerChannel(numSamples+199);
    processed.setSampleRate(44100);
    processed.setBitDepth(16);

        for (int j=0; j < numSamples+199; j++)
        {
            processed.samples[0][j] = left_processed[j];
            processed.samples[1][j] = right_processed[j];
        }

    processed.save("final.wav");
    processed.printSummary();

    

    return 0;
}