#include <iostream>
#include <vector>
#include "../libsndfile/include/sndfile.h"

int main()
{
    // Open the WAV file
    SF_INFO info;
    SNDFILE *file = sf_open("../High-E.wav", SFM_READ, &info);
    if (file == NULL) {
        std::cerr << "Failed to open file: " << sf_strerror(file) << std::endl;
        return 1;
    }

    // Extract the number of channels and sample rate from the file header
    int channels = info.channels;
    int sample_rate = info.samplerate;

    // Allocate memory for the sample data
    std::vector<double> samples(info.frames * channels);

    // Read the sample data from the file
    sf_count_t count = sf_readf_double(file, &samples[0], info.frames);
    if (count != info.frames) {
        std::cerr << "Failed to read samples: " << sf_strerror(file) << std::endl;
        return 1;
    }

    // Close the file
    sf_close(file);

    // Do something with the samples, such as processing or analyzing them

    return 0;
}