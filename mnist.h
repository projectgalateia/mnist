#ifndef __MNIST_H__
#define __MNIST_H__

#ifdef USE_MNIST_LOADER
#ifdef MNIST_STATIC
#define _STATIC static
#else
#define _STATIC 
#endif

#ifdef MNIST_DOUBLE
#define MNIST_DATA_TYPE double
#else
#define MNIST_DATA_TYPE unsigned char
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct mnist_data {
	MNIST_DATA_TYPE data[28][28];
	unsigned int label;
} mnist_data;

static unsigned int mnist_bin_to_int(char *v)
{
	int i;
	unsigned int ret = 0;

	for (i = 0; i < 4; ++i) {
		ret <<= 8;
		ret |= (unsigned char)v[i];
	}

	return ret;
}

_STATIC int mnist_load(
	const char *image_filename,
	const char *label_filename,
	mnist_data **data,
	unsigned int *count)
{
	int i;
	char tmp[4];

	unsigned int image_cnt, label_cnt;

	FILE *ifp = fopen(image_filename, "rb");
	FILE *lfp = fopen(label_filename, "rb");

	if (!ifp || !lfp) {
		fclose(ifp);
		fclose(lfp);
		return -1;
	}

	fread(tmp, 1, 4, ifp);
	if (mnist_bin_to_int(tmp) != 2051) {
		return -2;
	}

	fread(tmp, 1, 4, lfp);
	if (mnist_bin_to_int(tmp) != 2049) {
		return -3;
	}

	fread(tmp, 1, 4, ifp);
	image_cnt = mnist_bin_to_int(tmp);

	fread(tmp, 1, 4, lfp);
	label_cnt = mnist_bin_to_int(tmp);

	if (image_cnt != label_cnt) {
		return -4;
	}
	fread(tmp, 1, 4, ifp);
	fread(tmp, 1, 4, ifp);

	*count = image_cnt;
	*data = malloc(sizeof(mnist_data) * image_cnt);

	for (i = 0; i < image_cnt; ++i) {
		int j;
		unsigned char read_data[28 * 28];
		mnist_data *d = &(*data)[i];

		fread(read_data, 1, 28*28, ifp);

#ifdef MNIST_DOUBLE
		for (j = 0; j < 28*28; ++j) {
			d->data[j/28][j%28] = read_data[j] / 255.0;
		}
#else
		memcpy(d->data, read_data, 28*28);
#endif

		fread(tmp, 1, 1, lfp);
		d->label = tmp[0];
	}

	return 0;
}

#endif /* USE_MNIST_LOADER */
#endif /* __MNIST_H__ */

