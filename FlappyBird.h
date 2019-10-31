#ifndef __FLAPPY_BIRD_H__
#define __FLAPPY_BIRD_H__

#include "cocos2d.h"

class FlappyBird : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void pipeInit(float);
	void update(float);
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	bool onContactBegan(cocos2d::PhysicsContact &contact);
	void stopFly(float);
	cocos2d::Animation *createAnimation(std::string prefixName, int pFrameOrder, float delay);

	// implement the "static create()" method manually
	CREATE_FUNC(FlappyBird);
private:
	cocos2d::SpriteBatchNode *spriteNode;
	cocos2d::PhysicsWorld *world;
	cocos2d::Sprite *bird;
	cocos2d::Label *label;
	int score = 0;
	int touch = 0;
	bool isFalling = true;
	void setPhysicWorld(cocos2d::PhysicsWorld *m_world) {
		world = m_world;
	}
};

#endif // __HELLOWORLD_SCENE_H__
