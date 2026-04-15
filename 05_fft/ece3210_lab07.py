import numpy as np
import _ece3210_lab07
import matplotlib.pyplot as plt
import time

def dft ( x ) :
    """ This is the discrete Fourier transform implementation .
    Parameters
    - - - - - - - - - -
    x : ndarray ( real or complex )
    array to be transformed
    Returns
    -------
    X : ndarray ( real or complex )
    array of transform result
    """

    X_w = _ece3210_lab07.dft(x)
    return X_w
def fft ( x ) :

    """ This is the fast Fourier transform implementation .
    Parameters
    - - - - - - - - - -
    x : ndarray ( real or complex )
    array to be transformed
    Returns
    -------
    X : ndarray ( real or complex )
    array of transform result
    """
    X_w = _ece3210_lab07.fft(x)
    return X_w

def ifft ( X ) :
    """ This is the inverse fast Fourier transform implementation .
    Parameters
    - - - - - - - - - -
    X : ndarray ( real or complex )
    array to be transformed
    Returns
    -------
    x : ndarray ( real or complex )
    array of transform result
    """
    X_w = _ece3210_lab07.ifft(X)
    return X_w

def convolve (f , g ) :
    """ Implementation of linear convolution performed
    in the time - domain .
    Parameters
    - - - - - - - - - -
    f : ndarray ( real or complex )
    input array with length L
    g : ndarray ( real or complex )
    input array with length P
    Results
    -------
    y : ndarray ( real or complex )
    result of convolution with length L +P -1
    """
    convolved = _ece3210_lab07.fft_convolve(f, g)
    return convolved

def fft_convolve (f , g ) :
    """ FFT - based implementation of linear convolution .
    Parameters
    - - - - - - - - - -
    f : ndarray ( real or complex )
    input array with length L
    g : ndarray ( real or complex )
    input array with length P
    Results
    -------
    y : ndarray ( real or complex )
    result of convolution with length L +P -1
    """
    convolved = _ece3210_lab07.fft_convolve(f, g)
    return convolved

def benchmark_dft_fft(sizes):
    dft_times = []
    fft_times = []

    for size in sizes:
        x = np.random.random(size) * 100

        start_time = time.time()
        dft(x)
        dft_times.append(time.time() - start_time)

        start_time = time.time()
        fft(x)
        fft_times.append(time.time() - start_time)

    return dft_times, fft_times

def benchmark_convolution_methods(array_lengths):
    conv_times = []
    fft_conv_times = []

    for L in array_lengths:
        x = np.random.uniform(-1000, 1000, L)
        h = np.random.uniform(-1000, 1000, L)

        start_time = time.time()
        convolve(x, h)
        conv_times.append(time.time() - start_time)

        start_time = time.time()
        fft_convolve(x, h)
        fft_conv_times.append(time.time() - start_time)

    return conv_times, fft_conv_times

def main():

    sizes = 2 ** np.arange(3, 12)

    dft_times, fft_times = benchmark_dft_fft(sizes)
    plt.figure(figsize=(10, 6))    
    plt.loglog(sizes, dft_times, 'o-', label='DFT Computation Time')
    plt.loglog(sizes, fft_times, 's-', label='FFT Computation Time')
    plt.xlabel('Array size (log scale)')
    plt.ylabel('Computation time (log scale)')
    plt.title('DFT vs FFT Computation Time Benchmark')
    plt.legend()
    plt.grid(True, which="both", ls="--")
    
    array_lengths = [1000, 3000, 6000, 10000, 30000, 60000, 100000]

    conv_times, fft_conv_times = benchmark_convolution_methods(array_lengths)

    plt.figure(figsize=(10, 6))
    plt.loglog(array_lengths, conv_times, 'o-', label='Convolution (Time Domain) Time')
    plt.loglog(array_lengths, fft_conv_times, 's-', label='Convolution (Frequency Domain) Time')
    plt.xlabel('Array length (log scale)')
    plt.ylabel('Computation time (log scale)')
    plt.title('Convolution vs FFT Convolution Computation Time Benchmark')
    plt.legend()
    plt.grid(True, which="both", ls="--")

    plt.show()

if __name__ == "__main__":
    main()
