#include <cstdio>
#include <cmath>
#include <stdio.h>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>


extern "C" {
#include "fft.h"
}

namespace py = pybind11;

py::array_t<std::complex<double>> calc_dft(py::array_t<std::complex<double>> &x_t_np) {

    array x_t;
    x_t.len = (size_t)x_t_np.request().size;
    x_t.data = (double _Complex*)(x_t_np.data());

    py::array_t<std::complex<double>> X_w_np((pybind11::ssize_t)(x_t.len));
    array X_w;
    X_w.len = (size_t)X_w_np.request().size;
    X_w.data = (double _Complex *)(X_w_np.data());

    dft(&X_w, &x_t);

    return X_w_np;
}

py::array_t<std::complex<double>> calc_fft(py::array_t<std::complex<double>> &x_t_np) {

    //calculating length to pad
    size_t input_len = x_t_np.request().size;
    int power_value = static_cast<int>(ceil(log2(input_len)));
    size_t padded_len = static_cast<size_t>(pow(2, power_value));

    //creating correct padded array size
    py::array_t<std::complex<double>> X_w_np(padded_len);

    //copying data into array
    std::copy(x_t_np.data(), x_t_np.data() + input_len, X_w_np.mutable_data());


    for (size_t i = input_len; i < padded_len; ++i) {
    	X_w_np.mutable_data()[i] = std::complex<double>(0.0, 0.0);
	}


//    #pragma omp parallel for
    for (size_t i = input_len; i < padded_len; ++i) {
    	X_w_np.mutable_data()[i] = std::complex<double>(0.0, 0.0);
	}

    
    array x_t;
    x_t.len = padded_len;
    x_t.data = (double _Complex*)(X_w_np.data());

    fft(&x_t);

    return X_w_np;
}


py::array_t<std::complex<double>> calc_ifft(py::array_t<std::complex<double>> &x_t_np) {
 
//calculating length to pad
     size_t input_len = x_t_np.request().size;
     int power_value = static_cast<int>(ceil(log2(input_len)));
     size_t padded_len = static_cast<size_t>(pow(2, power_value));
 
     //creating correct padded array size
     py::array_t<std::complex<double>> X_w_np(padded_len);
 
     //copying data into array
     std::copy(x_t_np.data(), x_t_np.data() + input_len, X_w_np.mutable_data());
 
      for (size_t i = input_len; i < padded_len; ++i) {
        X_w_np.mutable_data()[i] = std::complex<double>(0.0, 0.0);
      }


     #pragma omp parallel for
     for (size_t i = input_len; i < padded_len; ++i) {
         X_w_np.mutable_data()[i] = std::complex<double>(0.0, 0.0);
     }
     array x_t;
     x_t.len = padded_len;
     x_t.data = (double _Complex*)(X_w_np.data());
 
     ifft(&x_t);
 
     return X_w_np;

}

py::array_t<std::complex<double>> calc_convolve(py::array_t<std::complex<double>> &f_np, py::array_t<std::complex<double>> &g_np) {
    // Create the array structures for f and g using the information from Python arrays
    array f;
    f.len = (size_t)f_np.request().size;
    f.data = reinterpret_cast<double _Complex*>(f_np.request().ptr);

    array g;
    g.len = (size_t)g_np.request().size;
    g.data = reinterpret_cast<double _Complex*>(g_np.request().ptr);

    // Prepare the output array with the appropriate size
    py::array_t<std::complex<double>> y_np((pybind11::ssize_t)(f.len + g.len - 1));

    // Create the array structure for y using the output Python array
    array y;
    y.len = (size_t)y_np.request().size;
    y.data = reinterpret_cast<double _Complex*>(y_np.request().ptr);

    // Call the convolution function
    convolve(&y, &f, &g);

    // Return the convolved result
    return y_np;
}

py::array_t<std::complex<double>> calc_fft_convolve(py::array_t<std::complex<double>> &f_np, py::array_t<std::complex<double>> &g_np) {

    size_t f_len = f_np.request().size;
    size_t g_len = g_np.request().size;
    size_t sum_len = f_len + g_len - 1;
    int power_value = static_cast<int>(ceil(log2(sum_len)));
    size_t padded_len = static_cast<size_t>(pow(2, power_value));


    // Create the padded arrays for f and g
    py::array_t<std::complex<double>> f_padded(padded_len);
    py::array_t<std::complex<double>> g_padded(padded_len);

    // Copy the data into the padded arrays
    std::copy(f_np.data(), f_np.data() + f_len, f_padded.mutable_data());
    std::copy(g_np.data(), g_np.data() + g_len, g_padded.mutable_data());

    // Zero-padding done manually for complex numbers
    std::fill(f_padded.mutable_data() + f_len, f_padded.mutable_data() + padded_len, std::complex<double>(0.0, 0.0));
    std::fill(g_padded.mutable_data() + g_len, g_padded.mutable_data() + padded_len, std::complex<double>(0.0, 0.0));

    // Prepare the array structures for C functions
    array f_c_array;
    f_c_array.len = padded_len;
    f_c_array.data = reinterpret_cast<double _Complex*>(f_padded.mutable_data());

    array g_c_array;
    g_c_array.len = padded_len;
    g_c_array.data = reinterpret_cast<double _Complex*>(g_padded.mutable_data());

    // Call the convolution function
    fft_convolve(&f_c_array, &g_c_array);

    // Return the result in a new Python array
    return py::array_t<std::complex<double>>(sum_len, reinterpret_cast<std::complex<double>*>(f_c_array.data));

}








    PYBIND11_MODULE(_ece3210_lab07, m) {
    m.doc() = "a collection of functions for ECE 3210 lab 7";
    m.def("dft", &calc_dft, "computes the dft of an array");
    m.def("fft", &calc_fft, "computes the fft of an array");
    m.def("ifft", &calc_ifft, "computes the ifft of an array");
    m.def("fft_convolve", &calc_fft_convolve, "computes the convolution using the fft");
    m.def("convolve", &calc_convolve, "computes the time domain convolution");
    }

