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
        void updateAllGradual(bool liftA, bool liftB, bool liftC, bool liftD);
        void trotGait(String dir, bool rotate);
        void trotSetUp(String dir, bool rotate);
        void sit();
};

#endif