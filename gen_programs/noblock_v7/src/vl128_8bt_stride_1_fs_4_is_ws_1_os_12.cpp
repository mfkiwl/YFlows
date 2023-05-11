#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctime>
#include <iostream>
#include <arm_neon.h>
#include <m5ops.h>
#include <algorithm>
using namespace std;



int main (int argc, char *argv[]) {
    int height;
    int width;
    int depth;
    int filter_height;
    int filter_width;
    int num_filters;
    int padding;
    int strides;
    int h_block;
    int w_block;
    int f_block;
    int d_block;
    int curr;
    int idx;
    int64_t* inputs;
    int64_t* outputs;
    int64_t* filters;
    int i = 0;
    int j = 0;
    int input_h;
    int input_w;
    int output_h;
    int output_w;
    int output_depth;
    
    height = atoi(argv[1]);
    width = atoi(argv[2]);
    depth = 128;
    num_filters = atoi(argv[3]);
    filter_height = 4;
    filter_width = 4;
    padding = 3;
    strides = 1;
    int out_height = ceil((height - filter_height + 2 * padding) / strides + 1);
    int out_width = ceil((width - filter_width + 2 * padding) / strides + 1);
    inputs = (int64_t *)malloc(sizeof(int64_t) * (height + 2 * padding) * (width + 2 * padding) * depth / 64);
    outputs = (int64_t *)malloc(sizeof(int64_t) * out_height * out_width * num_filters);
    filters = (int64_t *)malloc(sizeof(int64_t) * filter_height * filter_width * num_filters * depth / 64);
    
    int64x2_t input;
    int64x2_t data1;
    int64x2_t data2;
    int64x2_t weight_cache_0;
    
    int64x2_t output_cache_0;
    int64x2_t output_cache_1;
    int64x2_t output_cache_2;
    int64x2_t output_cache_3;
    int64x2_t output_cache_4;
    int64x2_t output_cache_5;
    int64x2_t output_cache_6;
    int64x2_t output_cache_7;
    int64x2_t output_cache_8;
    int64x2_t output_cache_9;
    int64x2_t output_cache_10;
    int64x2_t output_cache_11;
    
    
    m5_reset_stats(0, 0);
    for (int f = 0; f < num_filters; f++) {
        output_cache_0=vdupq_n_u64(0);
        output_cache_1=vdupq_n_u64(0);
        output_cache_2=vdupq_n_u64(0);
        output_cache_3=vdupq_n_u64(0);
        output_cache_4=vdupq_n_u64(0);
        output_cache_5=vdupq_n_u64(0);
        output_cache_6=vdupq_n_u64(0);
        output_cache_7=vdupq_n_u64(0);
        output_cache_8=vdupq_n_u64(0);
        output_cache_9=vdupq_n_u64(0);
        output_cache_10=vdupq_n_u64(0);
        output_cache_11=vdupq_n_u64(0);
        weight_cache_0 = vld1q_s64((const int64_t*) &filters[(f * filter_height * filter_width +0)*128/64]);
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w ++) {
                idx = h * width * depth / 64 + w * depth / 64;
                input = vld1q_s64((const int64_t *)&inputs[idx]);
                 
                i = 3;
                j = 3;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data1 = vmulq_s8(input,weight_cache_0);
                    output_cache_0 = vaddq_u8(output_cache_0,data1);
                    outputs[output_h * out_width * num_filters + output_w * num_filters + f] += vaddvq_u8(output_cache_0);
                    
                }
                
                i = 3;
                j = 2;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_1 = vaddq_u8(output_cache_1,data1);
                }
                
                i = 3;
                j = 1;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_2 = vaddq_u8(output_cache_2,data1);
                }
                
                i = 3;
                j = 0;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    output_cache_0 = vmulq_s8(input,data2);
                }
                
                i = 2;
                j = 3;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_3 = vaddq_u8(output_cache_3,data1);
                    outputs[output_h * out_width * num_filters + output_w * num_filters + f] += vaddvq_u8(output_cache_3);
                    
                }
                
                i = 2;
                j = 2;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_4 = vaddq_u8(output_cache_4,data1);
                }
                
                i = 2;
                j = 1;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_5 = vaddq_u8(output_cache_5,data1);
                }
                
                i = 2;
                j = 0;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    output_cache_3 = vmulq_s8(input,data2);
                }
                
                i = 1;
                j = 3;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_6 = vaddq_u8(output_cache_6,data1);
                    outputs[output_h * out_width * num_filters + output_w * num_filters + f] += vaddvq_u8(output_cache_6);
                    
                }
                
                i = 1;
                j = 2;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_7 = vaddq_u8(output_cache_7,data1);
                }
                
                i = 1;
                j = 1;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_8 = vaddq_u8(output_cache_8,data1);
                }
                
                i = 1;
                j = 0;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    output_cache_6 = vmulq_s8(input,data2);
                }
                
                i = 0;
                j = 3;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_9 = vaddq_u8(output_cache_9,data1);
                    outputs[output_h * out_width * num_filters + output_w * num_filters + f] += vaddvq_u8(output_cache_9);
                    
                }
                
                i = 0;
                j = 2;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_10 = vaddq_u8(output_cache_10,data1);
                }
                
                i = 0;
                j = 1;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_11 = vaddq_u8(output_cache_11,data1);
                }
                
                i = 0;
                j = 0;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    output_cache_9 = vmulq_s8(input,data2);
                }
                
                
                w ++;
                i = 3;
                j = 3;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data1 = vmulq_s8(input,weight_cache_0);
                    output_cache_1 = vaddq_u8(output_cache_1,data1);
                    outputs[output_h * out_width * num_filters + output_w * num_filters + f] += vaddvq_u8(output_cache_1);
                    
                }
                
                i = 3;
                j = 2;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_2 = vaddq_u8(output_cache_2,data1);
                }
                
                i = 3;
                j = 1;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_0 = vaddq_u8(output_cache_0,data1);
                }
                
                i = 3;
                j = 0;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    output_cache_1 = vmulq_s8(input,data2);
                }
                
                i = 2;
                j = 3;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_4 = vaddq_u8(output_cache_4,data1);
                    outputs[output_h * out_width * num_filters + output_w * num_filters + f] += vaddvq_u8(output_cache_4);
                    
                }
                
                i = 2;
                j = 2;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_5 = vaddq_u8(output_cache_5,data1);
                }
                
                i = 2;
                j = 1;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_3 = vaddq_u8(output_cache_3,data1);
                }
                
                i = 2;
                j = 0;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    output_cache_4 = vmulq_s8(input,data2);
                }
                
                i = 1;
                j = 3;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_7 = vaddq_u8(output_cache_7,data1);
                    outputs[output_h * out_width * num_filters + output_w * num_filters + f] += vaddvq_u8(output_cache_7);
                    
                }
                
                i = 1;
                j = 2;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_8 = vaddq_u8(output_cache_8,data1);
                }
                
                i = 1;
                j = 1;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_6 = vaddq_u8(output_cache_6,data1);
                }
                
                i = 1;
                j = 0;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    output_cache_7 = vmulq_s8(input,data2);
                }
                
                i = 0;
                j = 3;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_10 = vaddq_u8(output_cache_10,data1);
                    outputs[output_h * out_width * num_filters + output_w * num_filters + f] += vaddvq_u8(output_cache_10);
                    
                }
                
                i = 0;
                j = 2;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_11 = vaddq_u8(output_cache_11,data1);
                }
                
                i = 0;
                j = 1;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_9 = vaddq_u8(output_cache_9,data1);
                }
                
                i = 0;
                j = 0;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    output_cache_10 = vmulq_s8(input,data2);
                }
                
                
                w ++;
                i = 3;
                j = 3;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data1 = vmulq_s8(input,weight_cache_0);
                    output_cache_2 = vaddq_u8(output_cache_2,data1);
                    outputs[output_h * out_width * num_filters + output_w * num_filters + f] += vaddvq_u8(output_cache_2);
                    
                }
                
                i = 3;
                j = 2;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_0 = vaddq_u8(output_cache_0,data1);
                }
                
                i = 3;
                j = 1;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_1 = vaddq_u8(output_cache_1,data1);
                }
                
                i = 3;
                j = 0;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    output_cache_2 = vmulq_s8(input,data2);
                }
                
                i = 2;
                j = 3;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_5 = vaddq_u8(output_cache_5,data1);
                    outputs[output_h * out_width * num_filters + output_w * num_filters + f] += vaddvq_u8(output_cache_5);
                    
                }
                
                i = 2;
                j = 2;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_3 = vaddq_u8(output_cache_3,data1);
                }
                
                i = 2;
                j = 1;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_4 = vaddq_u8(output_cache_4,data1);
                }
                
                i = 2;
                j = 0;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    output_cache_5 = vmulq_s8(input,data2);
                }
                
                i = 1;
                j = 3;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_8 = vaddq_u8(output_cache_8,data1);
                    outputs[output_h * out_width * num_filters + output_w * num_filters + f] += vaddvq_u8(output_cache_8);
                    
                }
                
                i = 1;
                j = 2;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_6 = vaddq_u8(output_cache_6,data1);
                }
                
                i = 1;
                j = 1;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_7 = vaddq_u8(output_cache_7,data1);
                }
                
                i = 1;
                j = 0;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    output_cache_8 = vmulq_s8(input,data2);
                }
                
                i = 0;
                j = 3;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_11 = vaddq_u8(output_cache_11,data1);
                    outputs[output_h * out_width * num_filters + output_w * num_filters + f] += vaddvq_u8(output_cache_11);
                    
                }
                
                i = 0;
                j = 2;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_9 = vaddq_u8(output_cache_9,data1);
                }
                
                i = 0;
                j = 1;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    data1 = vmulq_s8(input,data2);
                    output_cache_10 = vaddq_u8(output_cache_10,data1);
                }
                
                i = 0;
                j = 0;
                output_h = floor((h - i) / strides);
                output_w = floor((w - j) / strides);
                if (output_h >= 0 && output_h < out_height && output_w >= 0 && output_w < out_width) {
                    data2 = vld1q_s64((const int64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                    output_cache_11 = vmulq_s8(input,data2);
                }
                
                
            }
        }
    }
m5_dump_reset_stats(0, 0);
std::free(inputs);
std::free(outputs);
std::free(filters);
}