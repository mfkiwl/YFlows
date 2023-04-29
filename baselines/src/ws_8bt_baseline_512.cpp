#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctime>
#include <iostream>
#include <arm_neon.h>
#include <m5ops.h>
#include <algorithm>

using namespace std;



int main(int argc, char *argv[])
{

    /* Please type the following in the command line
        ./<program_name> <input_height> <input_width> <input_depth (plase use 256)> <num_filters>
    */
    int height;
    int width;
    int depth;
    int filter_height;
    int filter_width;
    int num_filters;
    int padding;
    int strides;
    int curr;
    int64_t *inputs;
    int64_t *outputs;
    int64_t *filters;

    int output_depth;
    int pool_size;

    int input_size;
    int idx;

    int layer_counter = 0;
    double time_elapsed_ms;
    height = atoi(argv[1]);
    width = atoi(argv[2]);
    depth = 256;
    num_filters = atoi(argv[3]);
    filter_height = atoi(argv[4]);
    filter_width = atoi(argv[5]);
    padding = atoi(argv[4])-1;
    strides = atoi(argv[6]);
    int out_height = ceil((height - filter_height + 2 * padding) / strides + 1);
    int out_width = ceil((width - filter_width + 2 * padding) / strides + 1);
    inputs = (int64_t *)malloc(sizeof(int64_t) * (height + 2 * padding) * (width + 2 * padding) * depth / 64);
    outputs = (int64_t *)malloc(sizeof(int64_t) * out_height * out_width * num_filters);
    filters = (int64_t *)malloc(sizeof(int64_t) * filter_height * filter_width * num_filters * depth / 64);
    uint64x2x4_t data1;
    uint64x2x4_t data2;
    

    m5_reset_stats(0, 0);

    for (int f = 0; f < num_filters; f ++)
    {
        for (int i = 0; i < filter_height; i++)
        {
            for (int j = 0; j < filter_width; j++)
                {
                data2 = vld1q_u64_x4((const uint64_t *) & filters[(f * filter_height * filter_width + i * filter_width + j)*depth/64]);
                for (int h = 0; h < out_height; h++)
                {
                    for (int w = 0; w < out_width; w++)
                    {
                        int input_h = h * strides + i - padding;
                        int input_w = w * strides + j - padding;
                        data1 = vld1q_u64_x4((const uint64_t *)&inputs[(input_h * width + input_w) * depth /64]);  
                        data1.val[0] = vmulq_s8(data1.val[0],data2.val[0]);
                        data1.val[1] = vmulq_s8(data1.val[1],data2.val[1]);
                        data1.val[2] = vmulq_s8(data1.val[2],data2.val[2]);
                        data1.val[3] = vmulq_s8(data1.val[3],data2.val[3]);
                        outputs[h * out_width * num_filters + w * num_filters + f] += vaddvq_u8(vreinterpretq_u8_u64(data1.val[0]))+vaddvq_u8(vreinterpretq_u8_u64(data1.val[1]))+vaddvq_u8(vreinterpretq_u8_u64(data1.val[2]))+vaddvq_u8(vreinterpretq_u8_u64(data1.val[3]));
                    }
                }
            }
        }
    }


    m5_dump_reset_stats(0, 0);

    std::free(inputs);
    std::free(outputs);
    std::free(filters);
}