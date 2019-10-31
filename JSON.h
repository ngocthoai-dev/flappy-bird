#ifndef __JSON_H__
#define __JSON_H__

#include "cocos2d.h"

class JSON : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(JSON);
};

#endif // __HELLOWORLD_SCENE_H__
