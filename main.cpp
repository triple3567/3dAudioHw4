#include "AudioFile.h"
#include "HRTFContainter.h"
#include "util.h"

int main(){

    //load input
    string input = "./data/new_sound.wav";
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
    vector<float> left_processed;
    vector<float> right_processed;
    HRTFContainer hrtf = HRTFContainer();

    int azimuth_loc[8] = {0,4,8,12,8,4,2,0};
    int elevation = 9;

    for(int i = 0; i < 8; i++){
        if(i == 4){
            elevation = 18;
        }

        float* curr_left = new float[numSamples/8];
        float* curr_right = new float[numSamples/8];
        float* curr_left_processed = new float[numSamples/8 + 199];
        float* curr_right_processed = new float[numSamples/8 + 199];

        for(int j = 0; j < numSamples / 8; j++){
            curr_left[j] = wav_array_left[(i * numSamples/8) + j];
            curr_right[j] = wav_array_right[(i * numSamples/8) + j];
        }

        curr_left_processed = conv(curr_left, hrtf.get_hrir_l(azimuth_loc[i],elevation), numSamples/8, 200);
        curr_right_processed = conv(curr_right, hrtf.get_hrir_r(azimuth_loc[i],elevation), numSamples/8, 200);

        for(int j = 0; j < numSamples/8 + 199; j++){
            left_processed.push_back(curr_left_processed[j]);
            right_processed.push_back(curr_right_processed[j]);
        }

    }
    
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