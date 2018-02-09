/**
 ****************************************************************************
 * MIT License
 * @file b_log.c  
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
#include "b_log.h"
#include "b_log_port.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "stdlib.h"
/**
 * @addtogroup B_LOG
 * @{
 */
 
/**
 * @defgroup B_LOG_SRC
 * @{
 */


static uint8_t sg_log_buf[B_LOG_BUF_SIZE];
static const uint32_t scg_log_param_table[B_LOG_LEVEL_N] = 
   {B_LOG_I_LEVEL_PARAM, B_LOG_W_LEVEL_PARAM, B_LOG_E_LEVEL_PARAM, B_LOG_A_LEVEL_PARAM};
static const char scg_log_head_table[B_LOG_LEVEL_N] = 
   {'I', 'W', 'E', 'A'};
#if (B_LOG_BUF_SIZE < B_LOG_BUF_MIN)	 
	 #error "log config error: B_LOG_FILE_NAME_LEN_MAX < 64"	 
#endif

#if B_LOG_CACHE_ENABLE
static b_log_cache_info_t g_b_log_cache_info = 
{
    .count = 0,
};
#endif	 
/**
 * @defgroup B_LOG_INTERFACE 
 * @{
 */
#if B_LOG_CACHE_ENABLE
static void b_log_cache_handle(char *pbuf)	 
{
    uint32_t len = 0;
	  uint32_t i = 0;
	  if(pbuf == NULL)
		{
		    return;
		}
		len = strlen(pbuf);
	  for(i = 0;i < len;i++)
		{
		    if(pbuf[i] != '\n')
				{
				    g_b_log_cache_info.cache_buf[g_b_log_cache_info.count++] = pbuf[i];
					  if(g_b_log_cache_info.count >= (B_LOG_CACHE_SIZE - 1))
						{
						    g_b_log_cache_info.cache_buf[g_b_log_cache_info.count] = 0;
							  b_log_put_string(g_b_log_cache_info.cache_buf);
							  g_b_log_cache_info.count = 0;
						}
				}
				else
				{
				    g_b_log_cache_info.cache_buf[g_b_log_cache_info.count] = 0;
					  b_log_put_string(g_b_log_cache_info.cache_buf);
					  g_b_log_cache_info.count = 0;
				}
		}
}	 
#endif

void b_log_out(uint8_t type, const char *ptr_file, const char *ptr_func, uint32_t line, char *fmt, ...)
{
	  uint32_t buf_len = 0;
	  uint32_t param = 0;
	  uint8_t name_len = 0;
	  int str_len = 0;
	  char *p_tmp = NULL, *pbuf = (char *)sg_log_buf;
	  char line_number[8];
	  va_list ap;
		if(ptr_file == NULL || ptr_func == NULL || fmt == NULL || type >= B_LOG_LEVEL_N || B_LOG_BUF_SIZE < B_LOG_BUF_MIN)
		{
		    return;
		}
		memset(pbuf, 0, B_LOG_BUF_SIZE);
		param = scg_log_param_table[type];
		str_len = strlen(B_LOG_HEAD_STRING);
		if(str_len < 0)
		{
		    return;
		}
		memcpy(pbuf, B_LOG_HEAD_STRING, str_len);
		buf_len += str_len;
		pbuf[buf_len++] = ' ';
		pbuf[buf_len++] = scg_log_head_table[type];
		pbuf[buf_len++] = ' ';
		if(param & B_LOG_PARAM_FILE)
		{
		    name_len = strlen(ptr_file);
			  p_tmp = (char *)ptr_file;
			  if(name_len > B_LOG_FILE_NAME_LEN_MAX)
				{
				    p_tmp = (char *)(ptr_file + name_len - B_LOG_FILE_NAME_LEN_MAX);
					  name_len = B_LOG_FILE_NAME_LEN_MAX;
				}
				memcpy(pbuf + buf_len, p_tmp, name_len);
				buf_len += name_len;
				pbuf[buf_len++] = ' ';
		}
		if(param & B_LOG_PARAM_FUNC)
		{
			  p_tmp = (char *)ptr_func;
		    name_len = strlen(ptr_func);
			  memcpy(pbuf + buf_len, p_tmp, name_len);
			  buf_len += name_len;
			  pbuf[buf_len++] = ' ';
		}
		if(param & B_LOG_PARAM_LINE)
		{
				str_len = sprintf(line_number, "%d", line);
				if(str_len < 0)
				{
						return;
				}
				memcpy(pbuf + buf_len, line_number, str_len);
				buf_len += str_len;
				pbuf[buf_len++] = ' ';
	  }
		va_start(ap, fmt);
		str_len = vsnprintf(pbuf + buf_len, B_LOG_BUF_SIZE - buf_len - 1, fmt, ap);
		va_end(ap);
		if(str_len < 0)
		{
		    return;
		}
#if B_LOG_CACHE_ENABLE
    b_log_cache_handle(pbuf);		
#else
    b_log_put_string(pbuf);   
#endif
}

#if B_LOG_CACHE_ENABLE
void b_log_flush()
{
	  if(g_b_log_cache_info.count > 0)
		{
        g_b_log_cache_info.cache_buf[g_b_log_cache_info.count] = 0x0;
        b_log_put_string(g_b_log_cache_info.cache_buf);
        g_b_log_cache_info.count = 0;
		}
}
#endif


/**
 * @}
 */

/**
 * @}
 */


/**
 * @}
 */

