#include "mex.h"

void contrast_piecewise(int width, int height, unsigned char *input, unsigned char *output, int r1, int s1, int r2, int s2){
    int a1 = r1/s1;
    int a2 = (r2-r1)/(s2-s1);
    int a3 = (255-r2)/(255-s2);
    int temp;
    
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            
            int ind = j*height + i;
             if (input[ind]>=0&&input[ind]<r1){
                    output[ind] = a1*input[ind];
             }else if (input[ind]>=r1&&input[ind]<r2){
                  output[ind] = a2*(input[ind]-r1) + s1;
              }else if (input[ind]>=r2&&input[ind]<=255){
                 output[ind] = a2*(input[ind]-r2) + s2;
             }        
            
            if (output[ind] >= 255){
              output[ind] = 255;
             }else if (output[ind] <= 0){
                output[ind] = 0;
             }else{
                output[ind] = output[ind];
            }   
        }
    }
}
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    // Input and output 
    int r1,r2,s1,s2;
    
    // If input and output arguments are not the right size, display error message
    if(nrhs != 5){
        mexErrMsgTxt("Only one input argument is accepted");
    }
    
    if(nlhs != 1){
        mexErrMsgTxt("Only one output required");
    }
    
    // Inputs for image are declared
    const mxArray *img = prhs[0];
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    
    int height   = dims[0];
    int width    = dims[1];
    
    mxClassID input_type = mxGetClassID(img);
    
    //If the input is not double or uint8, display error message
    if (!mxIsDouble(img) && !mxIsUint8(img)){
        mexErrMsgTxt("invert_colours can only accept images of type 'double' or 'uint8'");
    }
    
    // The inputs for contrast and brightness 
    r1 = mxGetScalar(prhs[1]);
    s1 = mxGetScalar(prhs[2]);
    r2 = mxGetScalar(prhs[3]);
    s2 = mxGetScalar(prhs[4]);
   
    // Output variables 
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    if (mxIsUint8(img)){
        unsigned char *img_ptr = (unsigned char *)mxGetData(img);
        unsigned char *out_ptr = (unsigned char *)mxGetData(output);
        
       
       contrast_piecewise(width, height, img_ptr, out_ptr, r1, s1, r2, s2);
    }
     
}    