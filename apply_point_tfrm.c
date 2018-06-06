#include "mex.h"

void change_image(int c, int b, int w, int h, unsigned char *input, unsigned char *output){
        for (int y = 0; i < h; i++){
            for (int j = 0; j < w; j++){
                int ind = j*h + i;
                int temp = c*input[ind] + b;
                output[ind] = temp;
            
                if (temp >= 255){
                output[ind] = 255;
                }
                
                else if (temp <= 0){
                output[ind] = 0;
                }
                
                else {
                output[ind] = temp;
                }   
            }
       }
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    
    //error messages for number of inputs
    if(nlhs != 3){
        mexErrMsgTxt("Only three inputs.");
    }
    
    if(nrhs != 1){
        mexErrMsgTxt("Only one output");
    }
    
    //error messages are displayed if the input aren't double or uint8
    const mxArray *img = prhs[0];
    if (!mxIsDouble(img) && !mxIsUint8(img)){
        mexErrMsgTxt("invert_colours can only accept images of type 'double' or 'uint8'");
    }
    //inputs for image 
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    
    int height   = dims[0];
    int width    = dims[1];
    
    mxClassID input_type = mxGetClassID(img);
    
    
    
    //output variables 
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    
   
   
    
    //contrast and brightness 
    contrast = mxGetScalar(prhs[1]);
    brightness = mxGetScalar(prhs[2]);
   
 
    
    if (mxIsUint8(img)){
        unsigned char *img_ptr = (unsigned char *)mxGetData(img);
        unsigned char *out_ptr = (unsigned char *)mxGetData(output);
        
      
       change_image(contrast, brightness, width, height, img_ptr, out_ptr);

    }
       
}    