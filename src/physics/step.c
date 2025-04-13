#include "../cons.h"





int __step;



int check_step(float time){
    if (time / STEP_TIME < __step){
        return __step;
    }
    __step++;
    
    return __step;
}