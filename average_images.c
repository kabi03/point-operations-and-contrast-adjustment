#include <stdio.h>
#include <mex.h>
#include <math.h>

void average_images(unsigned char **image_in, unsigned char *image_out, int counter, int n){
    double sum;
    double average;

    for (int i=0; i<n; i++){   
        sum = 0;
        
        for(int j=0; j<counter; j++){
            sum += image_in[j][i];
        }

        average = sum / (double)counter;
        image_out[i] = (unsigned char)round(average);
    }
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mxArray *image_in_m[nrhs];
    mxArray *image_out_m;
    const mwSize *dims;
    
    int dimx;
    int dimy;
    
    unsigned char *image_in[nrhs];
    unsigned char *image_out;


    for(int i=0; i<nrhs; i++){
        image_in_m[i] = mxDuplicateArray(prhs[i]);
    }
       
//  Getting the dimensions of the input image
    dims = mxGetDimensions(prhs[0]);
    dimy = (int)dims[0];
    dimx = (int)dims[1];
    
// Creating a matrix for the output image
    image_out_m = plhs[0] = mxCreateNumericArray (2, dims, mxUINT8_CLASS, mxREAL);
	
//Link pointers for images
    for(int i=0; i<nrhs; i++){
        image_in[i] = (unsigned char*)mxGetData(image_in_m[i]);
    }
    
    image_out = (unsigned char*)mxGetData(image_out_m);

    average_images(image_in, image_out, nrhs, dimx*dimy);

	return;
}