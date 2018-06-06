#include "mex.h"

void Masking(int width, int height, unsigned char *img1, unsigned char *img2, unsigned char *mask, unsigned char *output){
     for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            int ind = j*height + i;
            
            if (mask[ind]<=0){
                output[ind] = img1[ind];
            }else if (mask[ind]>0)
            {
                output[ind] = img2[ind];
            }
        }
        
     }
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    
    // Error messages  if input and output arguments arent the right size
    
    if(nrhs != 3){
        mexErrMsgTxt("Only one input argument is accepted");
    }
    
    if(nlhs != 1){
        mexErrMsgTxt("Only one output required");
    }
    
    const mxArray *a = prhs[0];
    mwSize ndims = mxGetNumberOfDimensions(a);
    const mwSize *dims = mxGetDimensions(a);
    
    const mxArray *b = prhs[1];
    mwSize ndims1 = mxGetNumberOfDimensions(b);
    const mwSize *dims1 = mxGetDimensions(b);
        
    const mxArray *mask = prhs[2];
    mwSize ndims2 = mxGetNumberOfDimensions(mask);
    const mwSize *dims2 = mxGetDimensions(mask);
    
    int height   = dims[0];
    int width    = dims[1];
    
    mxClassID input_type = mxGetClassID(b);
    
    //Error message if the input is not double or uint8
    if (!mxIsDouble(b) && !mxIsUint8(b)){
        mexErrMsgTxt("invert_colours can only accept images of type 'double' or 'uint8'");
    }
    // output variables 
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    if (mxIsUint8(b)){
        unsigned char *a_ptr = (unsigned char *)mxGetData(a);
        unsigned char *b_ptr = (unsigned char *)mxGetData(b);
        unsigned char *mask_ptr = (unsigned char *)mxGetData(mask);
        unsigned char *out_ptr = (unsigned char *)mxGetData(output);
       
      
        Masking(width, height, a_ptr, b_ptr, mask_ptr, out_ptr);
    }
}    