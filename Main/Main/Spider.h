#ifndef SPIDER_H
#define SPIDER_H

#include "Leg.h"

class Spider{
    private:
        Leg legArray[4];
        int frequency;
    public:
        Spider(int n);
        void creepGait();
        void initPwm();
        void initCalibration();
};

#endif