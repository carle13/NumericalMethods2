#include <ctime>
#include <sys/timeb.h>

int mm_systime()
{
    timeb tb;
    ftime(&tb);
    int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
    return nCount;
}