#ifndef SPIDER_H
#define SPIDER_H

#include "Leg.h"

class Spider{
    private:
        Leg legArray[4];
        Leg *a;
        Leg *b;
        Leg *c;
        Leg *d;
        int frequency;
    public:
        Spider(int n);
        void creepGait();
        void initPwm();
        void initCalibration();
        void standBy();
        void updateAllGradual();
};

#endif