#ifndef THREAD__H
#define THREAD__H

#include <QObject>
#include <QThread>
class thread_ : public QThread
{
    Q_OBJECT

public:
    enum RUNMODE
    {
        forMode,
        whileMode
    } ;


    thread_();

    void run();

    inline void setInterval(double interval){
        this->interval = interval;
    }
    inline void setTime(int t){
        this->time = t;
    }
    inline void setMode(RUNMODE r){
        this->mode = r;
    }
    inline void setRun(bool flag){
        bRun = flag;
    }
signals:

    void send_signal();

    void done_signal();
private:
    double interval;
    int time;
    RUNMODE mode;
    bool bRun;
};

#endif // THREAD__H
