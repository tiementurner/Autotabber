#include "../inc/includes.hpp"
#include "../inc/wavheader.hpp"        
        
void analyze(size_t bytesRead, float* buffer, const uint16_t BUFFER_SIZE, FILE* wavFile)
{
    int N = 512;
    std::vector<double> peaks;
    while ((bytesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE / (sizeof buffer[0]), wavFile)) > 0)
    {
        fftw_complex in[N], out[N];
        for (int i = 0; i < N; i++) {
            in[i][0] = buffer[i];
            in[i][1] = 0.0;
        }
        fftw_plan p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_execute(p);
        
        double magnitude[N];
        for (int i = 0; i < N; i++) {
            magnitude[i] = std::sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
        }
        
        int bin_width = 20;
        for (int i = bin_width; i < N / 2 - bin_width; i++) {
            if (magnitude[i] > magnitude[i - bin_width] && magnitude[i] > magnitude[i + bin_width]) {
                peaks.push_back(44100.0 * i / N);
            }
        }

        std::sort(peaks.begin(), peaks.end());
        for (int i = 0; i < peaks.size(); i++) {
            std::cout << "Peak " << i + 1 << ": " << peaks[i] << " Hz" << std::endl;
        }
        
        cout << "Read " << bytesRead << " bytes." << endl;
    }
}