#include "AudioFile.h"
#include "HRTFContainter.h"
#include "util.h"

int main(){

    //load input
    string input = "./data/PROD_TAG.wav";
    AudioFile<float> wav = AudioFile<float>(input);
    wav.printSummary();

    //interpret input
    float* wav_array_left;
    float* wav_array_right;
    interpretInput(wav, wav_array_left, wav_array_right);

    //apply HRTF
    int numSamples = wav.getNumSamplesPerChannel(); 
    float* left_processed;
    float* right_processed;
    left_processed = new float[numSamples+199];
    right_processed = new float[numSamples+199];
    HRTFContainer hrtf = HRTFContainer();
    left_processed = conv(wav_array_left, hrtf.get_hrir_l(0,9), numSamples, 200);
    right_processed = conv(wav_array_right, hrtf.get_hrir_r(0,9), numSamples, 200);
    
    //generate output wav file
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