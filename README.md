# DSP Portfolio — Paul Runov

Firmware implementations and technical documentation for real-time DSP on an STM32F769 Discovery board sampling at 48kHz, validated using oscilloscopes and function generators.  Also includes an 8051 MCU project, examples of C++ code, and a project involvoing CNN to digitize handwriting.
## DSP Projects
- 01 &nbsp;&nbsp; Polyphase Decimation and Interpolation — Polyphase filter decomposition in C at M=100 with a 900-tap anti-aliasing filter using a circular buffer.
- 02 &nbsp;&nbsp; 60Hz Noise Removal — Notch filter applied at a decimated sample rate to remove 60Hz interference, then upsampled back to 48kHz.
- 03 &nbsp;&nbsp; FIR Filter / Digital Audio Crossover — Real-time two-way audio crossover using an optimized linear phase FIR.
- 04 &nbsp;&nbsp; IIR Filter / Audio Restoration — Cascaded biquad IIR in C designed in Python and deployed to hardware.
- 05 &nbsp;&nbsp; FFT — Cooley-Tukey FFT written from scratch in C including bit reversal and butterfly operations.

## Embedded Projects
- 09 &nbsp;&nbsp; Breakout Game — Bare metal C and Assembly on 8051 microcontroller with interrupt-driven audio via DAC, potentiometer input via ADC, and LCD display output.

## C++
- 07 &nbsp;&nbsp; Data Structures — Templated linked list and dynamic string implementations demonstrating templates, dynamic memory management, and copy semantics.
- 08 &nbsp;&nbsp; Differential Drive Robot — ROS2 robot built as a learning project focused on integrating open source tools including Nav2, behavior trees, and TF2 transforms under a tight timeline.

## Misc
- 06 &nbsp;&nbsp; Handwriting to Digital Text — Image processing and CNN in Python to convert handwritten text to digital output.

## Hardware
STM32F769I Discovery Board — 48kHz real-time audio DSP
8051 Microcontroller — bare metal embedded with DAC, ADC, and LCD peripherals
Keysight oscilloscopes and function generators

## Languages
C, C++, Assembly, Python
