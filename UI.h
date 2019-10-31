#ifndef __UI_H__
#define __UI_H__

#include "cocos2d.h"

class UI : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void onClickMenuItem(cocos2d::Ref *sender);
    // implement the "static create()" method manually
    CREATE_FUNC(UI);
};

#endif // __HELLOWORLD_SCENE_H__
