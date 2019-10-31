#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene(int score);

	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(GameOver);
};

#endif // __HELLOWORLD_SCENE_H__
