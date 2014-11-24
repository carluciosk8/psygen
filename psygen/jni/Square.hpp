#pragma once

#include "Engine/Geometry.hpp"

class Square : public psy::Geometry
{
public:
    Square();
    virtual ~Square();

    virtual void inflate();
    virtual void shrink();
    virtual int  estimate_memory();
    virtual int  estimate_time();
    virtual void update(float dt);

    virtual void draw();
    virtual void estimate_bound();
};
