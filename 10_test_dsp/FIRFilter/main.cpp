#include <iostream>
#include "CircularBuffer.h"
#include "FIRFilter.h"

using namespace std;

int main() {

    // ─── CircularBuffer Tests ───────────────────────────────────────

    cout << "=== CircularBuffer ===" << endl;

    // wraparound test
    cout << "--- Wraparound ---" << endl;
    CircularBuffer buf(4);
    buf.write(1.0f);
    buf.write(2.0f);
    buf.write(3.0f);
    buf.write(4.0f);
    buf.write(5.0f);  // overwrites 1.0
    buf.write(6.0f);  // overwrites 2.0
    cout << buf[0] << endl;  // 6
    cout << buf[1] << endl;  // 5
    cout << buf[2] << endl;  // 4
    cout << buf[3] << endl;  // 3

    // copy constructor
    cout << "--- Copy constructor ---" << endl;
    CircularBuffer bufCopy(buf);
    cout << bufCopy[0] << endl;  // 6
    cout << bufCopy[1] << endl;  // 5
    buf.write(99.0f);
    cout << "buf[0]:     " << buf[0]     << endl;  // 99
    cout << "bufCopy[0]: " << bufCopy[0] << endl;  // still 6

    // assignment operator
    cout << "--- Assignment operator ---" << endl;
    CircularBuffer bufAssigned(4);
    bufAssigned = buf;
    cout << bufAssigned[0] << endl;  // 99
    buf.write(77.0f);
    cout << "buf[0]:         " << buf[0]         << endl;  // 77
    cout << "bufAssigned[0]: " << bufAssigned[0] << endl;  // still 99

    // reset
    cout << "--- Reset ---" << endl;
    buf.reset();
    cout << buf[0] << endl;  // 0
    cout << buf[1] << endl;  // 0

    // ─── FIRFilter Tests ────────────────────────────────────────────

    cout << "\n=== FIRFilter ===" << endl;

    // basic averaging filter — output should converge to 3.0
    cout << "--- Averaging filter ---" << endl;
    float coeffs[] = {0.333f, 0.333f, 0.333f};
    FIRFilter filter(coeffs, 3);
    cout << filter.process(3.0f) << endl;  // ~1.0
    cout << filter.process(3.0f) << endl;  // ~2.0
    cout << filter.process(3.0f) << endl;  // ~3.0

    // reset test
    cout << "--- Reset ---" << endl;
    filter.reset();
    cout << filter.process(3.0f) << endl;  // ~1.0 again

    // copy constructor
    cout << "--- Copy constructor ---" << endl;
    filter.process(3.0f);  // prime the filter
    filter.process(3.0f);
    FIRFilter filterCopy(filter);
    cout << filter.process(3.0f)     << endl;  // ~3.0
    cout << filterCopy.process(3.0f) << endl;  // ~3.0 — same state

    // prove deep copy — modify original, copy unaffected
    float newCoeffs[] = {1.0f, 0.0f, 0.0f};  // passthrough filter
    FIRFilter filterA(newCoeffs, 3);
    FIRFilter filterB(filterA);
    cout << "--- Deep copy proof ---" << endl;
    cout << filterA.process(5.0f) << endl;  // 5.0
    cout << filterB.process(5.0f) << endl;  // 5.0 — independent

    // assignment operator
    cout << "--- Assignment operator ---" << endl;
    FIRFilter filterC(coeffs, 3);
    filterC = filterA;
    cout << filterC.process(9.0f) << endl;  // 9.0 — passthrough coeffs

    return 0;
}
