mnist
=====

A single-header MNIST dataset loader for C/C++


Basic Usage
-----

Include mnist.h in your code.

You should define `USE_MNIST_LOADER` macro to make it active.

Call `mnist_load` function with image filename, label filename, pointer to pointer of `mnist_data` type, and pointer to `unsigned int`.

You may define `MNIST_DOUBLE` to load data as double type, ranging from 0.0 to 1.0 (256 steps).


Usage Example
-----
```cpp
#define USE_MNIST_LOADER
#define MNIST_DOUBLE
#include "mnist.h"

#include <stdio.h>

int main(int argc, char **argv)
{
        mnist_data *data;
        unsigned int cnt;
        int ret;

        if (ret = mnist_load("train-images-idx3-ubyte", "train-labels-idx1-ubyte", &data, &cnt)) {
                printf("An error occured: %d\n", ret);
        } else {
                printf("image count: %d\n", cnt);
        
                free(data);

        }

        return 0;
}
```
