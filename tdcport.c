#include <stdio.h>
#include "mex.h" 

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    double* stamps_data, * channel_data;
    double* x, * z, * y, * channel_info;
    int i, j, k, m, n, count = 0;
    int H, V, P, M, clock;
    int syn_flag = 0, count_flag = 0, syn_count = 0;
    double temp_data;

    stamps_data = mxGetPr(prhs[0]);
    channel_data = mxGetPr(prhs[1]);
    channel_info = mxGetPr(prhs[2]);
    
      m = mxGetM(prhs[0]);
      n = mxGetN(prhs[2]);
    
    if (n == 5){
        H = channel_info[0];
        V = channel_info[1];
        P = channel_info[2];
        M = channel_info[3];
        clock = channel_info[4];
    }
    else{
        printf("Please input correct channel numbers.\n");
        printf("5 channels: H, V, P, M, CLOCK\n");
        return -1;
    }

    
    plhs[2] = mxCreateDoubleMatrix(m,2,mxREAL);
    z = mxGetPr(plhs[2]);
   
    plhs[1] = mxCreateDoubleMatrix(1,1,mxREAL);
    y = mxGetPr(plhs[1]);
   
  
    for (int i = 0; i < m; i++) {
        if (channel_data[i] == clock){
            count_flag = 1;
            temp_data = stamps_data[i];
            syn_count++;
            if (i>(m-100)){
                for (int k =1;k<(m-i-2);k++){
                    if(channel_data[m-k] == 8){
                        syn_flag = 1;}    
                }
                if(syn_flag == 0){
                    count_flag = 0; 
                }
                syn_flag = 0;
            }
        }
        else{
            if (count_flag == 1){
                if (channel_data[i] == H)
                {
                     z[count] = stamps_data[i]-temp_data; z[m+count]=12;
                }
                else if (channel_data[i] == V)
                {
                     z[count] = stamps_data[i]-temp_data; z[m+count]=13;
                }
                else if (channel_data[i] == P)
                {
                     z[count] = stamps_data[i]-temp_data; z[m+count]=17;
                }
                else if (channel_data[i] == M)
                {
                     z[count] = stamps_data[i]-temp_data; z[m+count]=19;
                }
           count++;
            }
        }
    }
    y[0] = syn_count-1;
    plhs[0] = mxCreateDoubleMatrix(count,2,mxREAL);
    x = mxGetPr(plhs[0]);
  
     for (int j = 0; j < count; j++) 
     {
                 x[j] = z[j];
                 x[count+j] = z[m+j];
     }
    return 0;
} 


