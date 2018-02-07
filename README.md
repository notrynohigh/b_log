# b_log
```
使用接口如下：

#define log_i(...)                           /**< information log      */
#define log_w(...)                           /**< warning log          */
#define log_e(...)                           /**< error log            */
#define log_a(cond, ...)                     /**< assert log           */

主要功能：
（所有配置在b_log_config.h）

1、打印等级配置   #define B_LOG_LEVEL_CFG    B_LOG_LEVEL_I
2、每个C文件可以单独配置是否打印
   1、设置 B_LOG_CTRL_TOGETHER  0
   #define B_LOG_CTRL_TOGETHER            0
   2、在每个C文件，include "b_log.h"上面如果加了 #define B_LOG_ENABLE 那么这个C文件里的打印有效
   
3、V0.0.1不支持缓存,后面版本加入。
4、在b_log_port.c里完成一个字符打印输出即可使用
5、配置每个级别打印的额外参数：
   #define B_LOG_I_LEVEL_PARAM    (B_LOG_PARAM_NULL)  
   #define B_LOG_W_LEVEL_PARAM    (B_LOG_PARAM_FUNC | B_LOG_PARAM_LINE) 
   #define B_LOG_E_LEVEL_PARAM    (B_LOG_PARAM_FILE | B_LOG_PARAM_FUNC | B_LOG_PARAM_LINE) 
   #define B_LOG_A_LEVEL_PARAM    (B_LOG_PARAM_FILE | B_LOG_PARAM_FUNC | B_LOG_PARAM_LINE)
   可选择性打印函数名、文件名、行号
```



