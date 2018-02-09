/**
 ****************************************************************************
 * MIT License
 * @file b_log_config.h  
 * @version v0.0.1
 * Copyright (c) [2017-2018] [Bean  email: notrynohigh@outlook.com]
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************
 */
#ifndef __B_LOG_CONFIG_H__
#define __B_LOG_CONFIG_H__

/**
 * @addtogroup B_LOG
 * @{
 */

/**
 * @defgroup B_LOG_CONFIG global configuration
 * @{
 */

#ifndef B_LOG_LEVEL_CFG
#define B_LOG_LEVEL_CFG    B_LOG_LEVEL_I            /**<  @ref B_LOG_LEVEL  */
#endif

/**
 * @brief there are two ways to control whether log output
 * if B_LOG_CTRL_TOGETHER == 1 Then B_LOG_LEVEL_CFG decide whether log output
 * if B_LOG_CTRL_TOGETHER == 0 Then log in all files can be controlled individually
 * #define B_LOG_ENABLE  
 * #include "b_log.h"
 * if you defined B_LOG_ENABLE above "#include "b_log.h"", log can output. it also be limited by B_LOG_LEVEL_CFG
 */
#define B_LOG_CTRL_TOGETHER            1

#define B_LOG_FILE_NAME_LEN_MAX        10         
#define B_LOG_BUF_SIZE                 128
#define B_LOG_HEAD_STRING              ">>"
/** config param @ref B_LOG_PARAM */
#define B_LOG_I_LEVEL_PARAM    (B_LOG_PARAM_NULL)  
#define B_LOG_W_LEVEL_PARAM    (B_LOG_PARAM_FUNC | B_LOG_PARAM_LINE) 
#define B_LOG_E_LEVEL_PARAM    (B_LOG_PARAM_FILE | B_LOG_PARAM_FUNC | B_LOG_PARAM_LINE) 
#define B_LOG_A_LEVEL_PARAM    (B_LOG_PARAM_FILE | B_LOG_PARAM_FUNC | B_LOG_PARAM_LINE) 
/**
 * @}
 */

/**
 * @defgroup B_LOG_CACHE_CFG b_log cache configuration
 * @{
 */
#define B_LOG_CACHE_ENABLE              0
#define B_LOG_CACHE_SIZE                512

/**
 * @}
 */


/**
 * @}
 */

#endif




