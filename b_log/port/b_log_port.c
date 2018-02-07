#include "b_port.h"
#include "SEGGER_RTT.h"






void b_log_putc(char ch)
{
    SEGGER_RTT_PutChar(0, ch);
}
















