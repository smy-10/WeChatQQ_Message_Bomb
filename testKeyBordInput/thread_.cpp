#include "thread_.h"

thread_::thread_()
{
    interval = 0;
    time = 0;
    bRun = false;
}

void thread_::run()
{
    if(mode == forMode)
    {
        for(auto i = 0;i<time;i++)
        {
            if(!bRun)
                break;

            emit send_signal();

            msleep(interval);
        }
        emit done_signal();
    }

    if(mode == whileMode)
    {

        while(1)
        {
            if(!bRun)
                break;
            emit send_signal();

            msleep(interval);
        }
    }
}
