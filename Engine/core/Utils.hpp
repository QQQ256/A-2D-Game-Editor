#pragma once

#include "Singleton.hpp"

class Utils : public Singleton<Utils>{
public:
    float clamp(float v, float lo, float hi)
    {
        return v < lo ? lo : hi < v ? hi
                                    : v;
    }
};