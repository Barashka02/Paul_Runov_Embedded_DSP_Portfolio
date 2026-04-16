# DSP Portfolio — Paul Runov

Firmware implementations and technical documentation for real-time DSP on an STM32F769 Discovery board sampling at 48kHz, validated using oscilloscopes and function generators.

## DSP Projects

01 Polyphase Decimation and Interpolation — Polyphase filter decomposition in C at M=100 with a 900-tap anti-aliasing filter using a circular buffer.

02 60Hz Noise Removal — Notch filter applied at a decimated sample rate to remove 60Hz interference, then upsampled back to 48kHz.

03 FIR Filter / Digital Audio Crossover — Real-time two-way audio crossover using an optimized linear phase FIR.

04 IIR Filter / Audio Restoration — Cascaded biquad IIR in C designed in Python and deployed to hardware.

05 FFT — Cooley-Tukey FFT written from scratch in C including bit reversal and butterfly operations.

## Embedded Projects

09 Breakout Game — Bare metal C and Assembly on 8051 microcontroller with interrupt-driven audio via DAC, potentiometer input via ADC, and LCD display output.

## Misc

06 Handwriting to Digital Text — Image processing and CNN in Python to convert handwritten text to digital output.

## C++

07 Data Structures — Templated linked list and dynamic string implementations demonstrating templates, dynamic memory management, and copy semantics.

08 Differential Drive Robot — ROS2 robot built as a learning project focused on integrating open source tools including Nav2, behavior trees, and TF2 transforms under a tight timeline.

## Hardware

STM32F769I Discovery Board — 48kHz real-time audio DSP
8051 Microcontroller — bare metal embedded with DAC, ADC, and LCD peripherals
Keysight oscilloscopes and function generators

## Languages

C, C++, Assembly, Python
