#define DR_WAV_IMPLEMENTATION
#include "dr_libs-master/dr_wav.h"
#include <iostream>
#include <vector>

int main() {
    unsigned int channels;
    unsigned int sampleRate;
    drwav_uint64 totalSampleCount;
    
    // Load the WAV file into a floating point buffer
    float* pSampleData = drwav_open_file_and_read_pcm_frames_f32("Low-E.wav", &channels, &sampleRate, &totalSampleCount, NULL);
    
    if (pSampleData == NULL) {
        std::cerr << "Failed to load WAV file!" << std::endl;
        return -1;
    }

    std::cout << "Channels: " << channels << std::endl;
    std::cout << "Sample Rate: " << sampleRate << std::endl;
    std::cout << "Total Samples: " << totalSampleCount << std::endl;

    // Prepare for DSP processing
    std::vector<float> audioSamples(pSampleData, pSampleData + totalSampleCount * channels);
    for (auto it = begin(audioSamples);it != end(audioSamples); it++) {
        std::cout << *it << ", ";
    }
    
    // Do DSP with `audioSamples`
    
    drwav_free(pSampleData, NULL);
    return 0;
}