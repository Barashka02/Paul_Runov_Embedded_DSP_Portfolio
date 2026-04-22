#include <iostream>
#include <cmath>
#include "Biquad.h"

using namespace std;

int main() {

    // lowpass biquad coefficients ~1kHz cutoff at 48kHz
    float b0 = 0.0029f, b1 = 0.0058f, b2 = 0.0029f;
    float a1 = -1.8226f, a2 = 0.8342f;

    // --- impulse response test ---
    cout << "--- Impulse response (should decay smoothly) ---" << endl;
    Biquad lpf(a1, a2, b0, b1, b2);
    cout << lpf.process(1.0f) << endl;
    cout << lpf.process(0.0f) << endl;
    cout << lpf.process(0.0f) << endl;
    cout << lpf.process(0.0f) << endl;
    cout << lpf.process(0.0f) << endl;
    cout << lpf.process(0.0f) << endl;
    cout << lpf.process(0.0f) << endl;
    cout << lpf.process(0.0f) << endl;

    // --- step response test ---
    cout << "--- Step response (should converge to stable value) ---" << endl;
    Biquad lpf2(a1, a2, b0, b1, b2);
    for (int i = 0; i < 20; i++) {
        cout << lpf2.process(1.0f) << endl;
    }

    // --- reset test ---
    cout << "--- Reset test ---" << endl;
    lpf.init();
    cout << lpf.process(1.0f) << endl;  // should match first impulse output

    // --- cascade two stages ---
    cout << "--- Cascaded stages (steeper rolloff) ---" << endl;
    Biquad stage1(a1, a2, b0, b1, b2);
    Biquad stage2(a1, a2, b0, b1, b2);
    cout << stage2.process(stage1.process(1.0f)) << endl;
    cout << stage2.process(stage1.process(0.0f)) << endl;
    cout << stage2.process(stage1.process(0.0f)) << endl;
    cout << stage2.process(stage1.process(0.0f)) << endl;
    cout << stage2.process(stage1.process(0.0f)) << endl;

    // --- frequency test ---
    cout << "--- Frequency test ---" << endl;
    float fs = 48000.0f;
    Biquad lpf3(a1, a2, b0, b1, b2);
    Biquad lpf4(a1, a2, b0, b1, b2);

    float amp_low = 0.0f;
    for (int i = 0; i < 1000; i++) {
        float x = sin(2.0f * 3.14159f * 100.0f * i / fs);
        float y = lpf3.process(x);
        if (i > 100) amp_low = fmax(amp_low, fabs(y));
    }

    float amp_high = 0.0f;
    for (int i = 0; i < 1000; i++) {
        float x = sin(2.0f * 3.14159f * 10000.0f * i / fs);
        float y = lpf4.process(x);
        if (i > 100) amp_high = fmax(amp_high, fabs(y));
    }

    cout << "100Hz amplitude:   " << amp_low  << endl;  // should be ~1.0
    cout << "10kHz amplitude:   " << amp_high << endl;  // should be much less

    return 0;
}
