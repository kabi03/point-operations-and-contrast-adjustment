#include "mex.h"

void contrast_highlight(int width, int height, unsigned char *input, unsigned char *output, int a, int b, int Imin){
    for (int i = 0; i < height; i++){
      for (int j = 0; j < width; j++){
          int ind = j*height + i;
            if (input[ind]<a){
                output[ind]=Imin;
            }else if (input[ind]>=a&&input[ind]<=b){
                output[ind]=input[ind];
            }else if (input[ind]>b){
                output[ind]=Imin;
            } 
        }
      }
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    // Declare input and output variables
    int a,b,Imin;
    
    // Error messages if input and output arguments are not the right size
    if(nrhs != 4){
        mexErrMsgTxt("Can only accept one input argument");
    }
    
    if(nlhs != 1){
        mexErrMsgTxt("One output required");
    }
    
    // Declaring inputs for image
    const mxArray *img = prhs[0];
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    
    int height   = dims[0];
    int width    = dims[1];
    
    mxClassID input_type = mxGetClassID(img);
    
    //Error message if the input is not double or uint8
    if (!mxIsDouble(img) && !mxIsUint8(img)){
        mexErrMsgTxt("invert_colours can only accept images of type 'double' or 'uint8'");
    }
    
    // Declaring the inputs for constrast and brigtness
    a = mxGetScalar(prhs[1]);
    b = mxGetScalar(prhs[2]);
    Imin = mxGetScalar(prhs[3]);
    
    // Assigning the output variables
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    if (mxIsUint8(img)){
        unsigned char *img_ptr = (unsigned char *)mxGetData(img);
        unsigned char *out_ptr = (unsigned char *)mxGetData(output);
        
       
       contrast_highlight (width, height, img_ptr, out_ptr, a, b, Imin);

    }
}    