#ifndef __ACTION_H__
#define __ACTION_H__

#include "cocos2d.h"

class animatedAction : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	
	cocos2d::Animation *createAnimation(std::string prefixName, int pFrameOrder, float delay);
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
	void move();

	cocos2d::Sprite *model;
	cocos2d::Animation *animation;
    // implement the "static create()" method manually
    CREATE_FUNC(animatedAction);
};

#endif // __HELLOWORLD_SCENE_H__
