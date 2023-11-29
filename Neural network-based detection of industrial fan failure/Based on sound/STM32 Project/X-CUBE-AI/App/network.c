/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Mon Aug 30 17:14:06 2021
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "network.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "layers.h"

#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 5
#define AI_TOOLS_VERSION_MINOR 0
#define AI_TOOLS_VERSION_MICRO 0


#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 3
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "2ccf535609a93158b829644dbce954a4"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-5.0.0)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Mon Aug 30 17:14:06 2021"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array node_20_scratch0_array;   /* Array #0 */
AI_STATIC ai_array node_17_scratch0_array;   /* Array #1 */
AI_STATIC ai_array node_14_scratch0_array;   /* Array #2 */
AI_STATIC ai_array node_11_scratch0_array;   /* Array #3 */
AI_STATIC ai_array node_24_C_array;   /* Array #4 */
AI_STATIC ai_array node_24_B_array;   /* Array #5 */
AI_STATIC ai_array node_20_bias_array;   /* Array #6 */
AI_STATIC ai_array node_20_weights_array;   /* Array #7 */
AI_STATIC ai_array node_17_bias_array;   /* Array #8 */
AI_STATIC ai_array node_17_weights_array;   /* Array #9 */
AI_STATIC ai_array node_14_bias_array;   /* Array #10 */
AI_STATIC ai_array node_14_weights_array;   /* Array #11 */
AI_STATIC ai_array node_11_bias_array;   /* Array #12 */
AI_STATIC ai_array node_11_weights_array;   /* Array #13 */
AI_STATIC ai_array input1_output_array;   /* Array #14 */
AI_STATIC ai_array node_11_output_array;   /* Array #15 */
AI_STATIC ai_array node_14_output_array;   /* Array #16 */
AI_STATIC ai_array node_17_output_array;   /* Array #17 */
AI_STATIC ai_array node_20_output_array;   /* Array #18 */
AI_STATIC ai_array node_24_output_array;   /* Array #19 */
AI_STATIC ai_array node_25_output_array;   /* Array #20 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor node_20_scratch0;   /* Tensor #0 */
AI_STATIC ai_tensor node_17_scratch0;   /* Tensor #1 */
AI_STATIC ai_tensor node_14_scratch0;   /* Tensor #2 */
AI_STATIC ai_tensor node_11_scratch0;   /* Tensor #3 */
AI_STATIC ai_tensor node_24_C;   /* Tensor #4 */
AI_STATIC ai_tensor node_24_B;   /* Tensor #5 */
AI_STATIC ai_tensor node_20_bias;   /* Tensor #6 */
AI_STATIC ai_tensor node_20_weights;   /* Tensor #7 */
AI_STATIC ai_tensor node_17_bias;   /* Tensor #8 */
AI_STATIC ai_tensor node_17_weights;   /* Tensor #9 */
AI_STATIC ai_tensor node_14_bias;   /* Tensor #10 */
AI_STATIC ai_tensor node_14_weights;   /* Tensor #11 */
AI_STATIC ai_tensor node_11_bias;   /* Tensor #12 */
AI_STATIC ai_tensor node_11_weights;   /* Tensor #13 */
AI_STATIC ai_tensor input1_output;   /* Tensor #14 */
AI_STATIC ai_tensor node_11_output;   /* Tensor #15 */
AI_STATIC ai_tensor node_14_output;   /* Tensor #16 */
AI_STATIC ai_tensor node_17_output;   /* Tensor #17 */
AI_STATIC ai_tensor node_20_output;   /* Tensor #18 */
AI_STATIC ai_tensor node_20_output0;   /* Tensor #19 */
AI_STATIC ai_tensor node_24_output;   /* Tensor #20 */
AI_STATIC ai_tensor node_25_output;   /* Tensor #21 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain node_11_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain node_14_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain node_17_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain node_20_chain;   /* Chain #3 */
AI_STATIC_CONST ai_tensor_chain node_24_chain;   /* Chain #4 */
AI_STATIC_CONST ai_tensor_chain node_25_chain;   /* Chain #5 */


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_conv2d_nl_pool node_11_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d_nl_pool node_14_layer; /* Layer #1 */
AI_STATIC ai_layer_conv2d_nl_pool node_17_layer; /* Layer #2 */
AI_STATIC ai_layer_conv2d_nl_pool node_20_layer; /* Layer #3 */
AI_STATIC ai_layer_gemm node_24_layer; /* Layer #4 */
AI_STATIC ai_layer_nl node_25_layer; /* Layer #5 */


/**  Array declarations section  **********************************************/
AI_ARRAY_OBJ_DECLARE(
    node_20_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 896,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_17_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 704,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_14_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 1216,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_11_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 2176,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_24_C_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 2,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_24_B_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 1152,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_20_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 64,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_20_weights_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 18432,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_17_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 32,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_17_weights_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 9216,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_14_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 32,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_14_weights_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 9216,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_11_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 32,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_11_weights_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 288,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    input1_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
    NULL, NULL, 960,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_11_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 8704,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_14_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 2592,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_17_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 800,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_20_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 576,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_24_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 2,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    node_25_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
    NULL, NULL, 2,
     AI_STATIC)




/**  Tensor declarations section  *********************************************/
AI_TENSOR_OBJ_DECLARE(
  node_20_scratch0, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 64, 7, 2), AI_STRIDE_INIT(4, 4, 4, 256, 1792),
  1, &node_20_scratch0_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_17_scratch0, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 11, 2), AI_STRIDE_INIT(4, 4, 4, 128, 1408),
  1, &node_17_scratch0_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_14_scratch0, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 19, 2), AI_STRIDE_INIT(4, 4, 4, 128, 2432),
  1, &node_14_scratch0_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_11_scratch0, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 34, 2), AI_STRIDE_INIT(4, 4, 4, 128, 4352),
  1, &node_11_scratch0_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_24_C, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &node_24_C_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_24_B, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 576, 1, 2), AI_STRIDE_INIT(4, 4, 4, 2304, 2304),
  1, &node_24_B_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_20_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &node_20_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_20_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 32, 3, 3, 64), AI_STRIDE_INIT(4, 4, 128, 384, 1152),
  1, &node_20_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_17_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &node_17_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_17_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 32, 3, 3, 32), AI_STRIDE_INIT(4, 4, 128, 384, 1152),
  1, &node_17_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_14_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &node_14_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_14_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 32, 3, 3, 32), AI_STRIDE_INIT(4, 4, 128, 384, 1152),
  1, &node_14_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_11_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &node_11_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_11_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 3, 3, 32), AI_STRIDE_INIT(4, 4, 4, 12, 36),
  1, &node_11_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  input1_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 1, 32, 30), AI_STRIDE_INIT(4, 4, 4, 4, 128),
  1, &input1_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_11_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 17, 16), AI_STRIDE_INIT(4, 4, 4, 128, 2176),
  1, &node_11_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_14_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 9, 9), AI_STRIDE_INIT(4, 4, 4, 128, 1152),
  1, &node_14_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_17_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 5, 5), AI_STRIDE_INIT(4, 4, 4, 128, 640),
  1, &node_17_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_20_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &node_20_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_20_output0, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 576, 1, 1), AI_STRIDE_INIT(4, 4, 4, 2304, 2304),
  1, &node_20_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_24_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &node_24_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  node_25_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &node_25_output_array, NULL)


/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_11_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&input1_output),
  AI_TENSOR_LIST_ENTRY(&node_11_output),
  AI_TENSOR_LIST_ENTRY(&node_11_weights, &node_11_bias, NULL),
  AI_TENSOR_LIST_ENTRY(&node_11_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  node_11_layer, 0,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &node_14_layer, AI_STATIC,
  .tensors = &node_11_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 2, 2, 2, 2), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_14_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&node_11_output),
  AI_TENSOR_LIST_ENTRY(&node_14_output),
  AI_TENSOR_LIST_ENTRY(&node_14_weights, &node_14_bias, NULL),
  AI_TENSOR_LIST_ENTRY(&node_14_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  node_14_layer, 3,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &node_17_layer, AI_STATIC,
  .tensors = &node_14_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 2, 2, 2, 2), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_17_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&node_14_output),
  AI_TENSOR_LIST_ENTRY(&node_17_output),
  AI_TENSOR_LIST_ENTRY(&node_17_weights, &node_17_bias, NULL),
  AI_TENSOR_LIST_ENTRY(&node_17_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  node_17_layer, 6,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &node_20_layer, AI_STATIC,
  .tensors = &node_17_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 2, 2, 2, 2), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_20_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&node_17_output),
  AI_TENSOR_LIST_ENTRY(&node_20_output),
  AI_TENSOR_LIST_ENTRY(&node_20_weights, &node_20_bias, NULL),
  AI_TENSOR_LIST_ENTRY(&node_20_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  node_20_layer, 9,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &node_24_layer, AI_STATIC,
  .tensors = &node_20_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 2, 2, 2, 2), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_24_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&node_20_output0),
  AI_TENSOR_LIST_ENTRY(&node_24_output),
  AI_TENSOR_LIST_ENTRY(&node_24_B, &node_24_C),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_24_layer, 13,
  GEMM_TYPE,
  gemm, forward_gemm,
  &AI_NET_OBJ_INSTANCE, &node_25_layer, AI_STATIC,
  .tensors = &node_24_chain, 
  .alpha = 1.0, 
  .beta = 1.0, 
  .tA = 0, 
  .tB = 1, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  node_25_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&node_24_output),
  AI_TENSOR_LIST_ENTRY(&node_25_output),
  AI_TENSOR_LIST_EMPTY,
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  node_25_layer, 14,
  NL_TYPE,
  nl, forward_sm,
  &AI_NET_OBJ_INSTANCE, &node_25_layer, AI_STATIC,
  .tensors = &node_25_chain, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 153864, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 47360, 1,
                     NULL),
  AI_TENSOR_LIST_IO_ENTRY(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input1_output),
  AI_TENSOR_LIST_IO_ENTRY(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &node_25_output),
  &node_11_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, 4));
  AI_ASSERT(activations)
  AI_UNUSED(net_ctx)

  {
    /* Updating activations (byte) offsets */
    node_20_scratch0_array.data = AI_PTR(activations + 38656);
    node_20_scratch0_array.data_start = AI_PTR(activations + 38656);
    node_17_scratch0_array.data = AI_PTR(activations + 38656);
    node_17_scratch0_array.data_start = AI_PTR(activations + 38656);
    node_14_scratch0_array.data = AI_PTR(activations + 38656);
    node_14_scratch0_array.data_start = AI_PTR(activations + 38656);
    node_11_scratch0_array.data = AI_PTR(activations + 38656);
    node_11_scratch0_array.data_start = AI_PTR(activations + 38656);
    input1_output_array.data = AI_PTR(NULL);
    input1_output_array.data_start = AI_PTR(NULL);
    node_11_output_array.data = AI_PTR(activations + 3840);
    node_11_output_array.data_start = AI_PTR(activations + 3840);
    node_14_output_array.data = AI_PTR(activations + 0);
    node_14_output_array.data_start = AI_PTR(activations + 0);
    node_17_output_array.data = AI_PTR(activations + 35456);
    node_17_output_array.data_start = AI_PTR(activations + 35456);
    node_20_output_array.data = AI_PTR(activations + 33152);
    node_20_output_array.data_start = AI_PTR(activations + 33152);
    node_24_output_array.data = AI_PTR(activations + 33144);
    node_24_output_array.data_start = AI_PTR(activations + 33144);
    node_25_output_array.data = AI_PTR(NULL);
    node_25_output_array.data_start = AI_PTR(NULL);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT(weights)
  AI_UNUSED(net_ctx)

  {
    /* Updating weights (byte) offsets */
    
    node_24_C_array.format |= AI_FMT_FLAG_CONST;
    node_24_C_array.data = AI_PTR(weights + 153856);
    node_24_C_array.data_start = AI_PTR(weights + 153856);
    node_24_B_array.format |= AI_FMT_FLAG_CONST;
    node_24_B_array.data = AI_PTR(weights + 149248);
    node_24_B_array.data_start = AI_PTR(weights + 149248);
    node_20_bias_array.format |= AI_FMT_FLAG_CONST;
    node_20_bias_array.data = AI_PTR(weights + 148992);
    node_20_bias_array.data_start = AI_PTR(weights + 148992);
    node_20_weights_array.format |= AI_FMT_FLAG_CONST;
    node_20_weights_array.data = AI_PTR(weights + 75264);
    node_20_weights_array.data_start = AI_PTR(weights + 75264);
    node_17_bias_array.format |= AI_FMT_FLAG_CONST;
    node_17_bias_array.data = AI_PTR(weights + 75136);
    node_17_bias_array.data_start = AI_PTR(weights + 75136);
    node_17_weights_array.format |= AI_FMT_FLAG_CONST;
    node_17_weights_array.data = AI_PTR(weights + 38272);
    node_17_weights_array.data_start = AI_PTR(weights + 38272);
    node_14_bias_array.format |= AI_FMT_FLAG_CONST;
    node_14_bias_array.data = AI_PTR(weights + 38144);
    node_14_bias_array.data_start = AI_PTR(weights + 38144);
    node_14_weights_array.format |= AI_FMT_FLAG_CONST;
    node_14_weights_array.data = AI_PTR(weights + 1280);
    node_14_weights_array.data_start = AI_PTR(weights + 1280);
    node_11_bias_array.format |= AI_FMT_FLAG_CONST;
    node_11_bias_array.data = AI_PTR(weights + 1152);
    node_11_bias_array.data_start = AI_PTR(weights + 1152);
    node_11_weights_array.format |= AI_FMT_FLAG_CONST;
    node_11_weights_array.data = AI_PTR(weights + 0);
    node_11_weights_array.data_start = AI_PTR(weights + 0);
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 5587742,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if ( !ai_platform_api_get_network_report(network, &r) ) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= network_configure_weights(net_ctx, &params->params);
  ok &= network_configure_activations(net_ctx, &params->activations);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}

#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

