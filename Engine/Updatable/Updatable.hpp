#pragma once
#include <memory>

class Updatable {
   public:
    virtual void update(const float dt){};
    virtual void physicsUpdate(const float dt){};
    virtual void ready() {};
};
