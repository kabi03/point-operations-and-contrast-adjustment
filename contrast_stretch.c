#include "mex.h"
void contrast_stretch(int width, int height, unsigned char *input, unsigned char *output){
    double rmax =0;
    double rmin =255;
    
        for (int i = 0; i < height; i++){
            
            for (int j = 0; j < width; j++){
                int ind = j*height + i;
                
                if (input[ind]>rmax){   
                    rmax  = input[ind];
                }
                
                if (input[ind]<rmin){   
                    rmin  = input[ind];
                }
            }
        }
    
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                int ind = j*height + i;
                output[ind] = 255*((input[ind]-rmin)/(rmax-rmin));
            }
            
        }
}
  
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){

    // Error messages if input and output arguments are the wrong size
    if(nrhs != 1){
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
   
    // Assigning the output variables
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    
    if (mxIsUint8(img)){
        unsigned char *img_ptr = (unsigned char *)mxGetData(img);
        unsigned char *out_ptr = (unsigned char *)mxGetData(output);
        
    contrast_stretch(width, height, img_ptr, out_ptr);

    }        
}    