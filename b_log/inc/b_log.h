/**
 ****************************************************************************
 * MIT License
 * @file b_log.h  
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
#ifndef __B_LOG_H__
#define __B_LOG_H__

#include "b_log_config.h"
#include "stdint.h"

/**
 * @addtogroup B_LOG
 * @{
 */

/**
 * @defgroup B_LOG_LEVEL b_log enable level
 * @{
 */
#define B_LOG_LEVEL_I    0
#define B_LOG_LEVEL_W    1
#define B_LOG_LEVEL_E    2
#define B_LOG_LEVEL_A    3
#define B_LOG_LEVEL_N    4
/**
 * @}
 */

/**
 * @defgroup B_LOG_PARAM b_log param
 * @{
 */
#define B_LOG_PARAM_NULL       0X0
#define B_LOG_PARAM_LINE       0X1
#define B_LOG_PARAM_FUNC       0X2
#define B_LOG_PARAM_FILE       0X4
/**
 * @}
 */ 
#define B_LOG_BUF_MIN          64
#define B_LOG_PARAM_DEFAULT    __FILE__,__func__,__LINE__
#if B_LOG_CTRL_TOGETHER
#ifndef B_LOG_ENABLE
#define B_LOG_ENABLE           1
#endif
#endif

#if B_LOG_CACHE_ENABLE
typedef struct
{
    char cache_buf[B_LOG_CACHE_SIZE];
	  uint32_t count;
}b_log_cache_info_t; 
#endif
/**
 * @addtogroup B_LOG_INTERFACE
 * @{
 */
void b_log_out(uint8_t ,const char *, const char *, uint32_t , char *fmt, ...);
#if B_LOG_CACHE_ENABLE
void b_log_flush(void);
#define b_log_f()    b_log_flush()
#else
#define b_log_f()
#endif

#ifdef B_LOG_ENABLE
#if (B_LOG_LEVEL_CFG <= B_LOG_LEVEL_I)
#define b_log_i(...)    b_log_out(B_LOG_LEVEL_I, B_LOG_PARAM_DEFAULT, __VA_ARGS__)
#else
#define b_log_i(...)
#endif
#if (B_LOG_LEVEL_CFG <= B_LOG_LEVEL_W)
#define b_log_w(...)    b_log_out(B_LOG_LEVEL_W, B_LOG_PARAM_DEFAULT, __VA_ARGS__)
#else
#define b_log_w(...)
#endif
#if (B_LOG_LEVEL_CFG <= B_LOG_LEVEL_E)
#define b_log_e(...)    b_log_out(B_LOG_LEVEL_E, B_LOG_PARAM_DEFAULT, __VA_ARGS__)
#else
#define b_log_e(...)
#endif
#if (B_LOG_LEVEL_CFG <= B_LOG_LEVEL_A)
#define b_log_a(cond, ...)    do{ if(!(cond)){b_log_out(B_LOG_LEVEL_A, B_LOG_PARAM_DEFAULT, __VA_ARGS__);while(1);}}while(0) 
#else
#define b_log_a(cond, ...)
#endif
#else
#define b_log_i(...) 
#define b_log_w(...) 
#define b_log_e(...) 
#define b_log_a(cond, ...) 
#endif

/**
 * @}
 */

/**
 * @defgroup USER_INTERFACE user interface
 * @{
 */
#define log_i(...)          b_log_i(__VA_ARGS__)                      /**< information log      */
#define log_w(...)          b_log_w(__VA_ARGS__)                      /**< warning log          */
#define log_e(...)          b_log_e(__VA_ARGS__)                      /**< error log            */
#define log_a(cond, ...)    b_log_a(cond, __VA_ARGS__)                /**< assert log           */
#define log_f()             b_log_f()                                 /**< log flush            */
/**
 * @}
 */


/**
 * @}
 */





#endif




