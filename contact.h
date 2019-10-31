#ifndef __CONTACT_H__
#define __CONTACT_H__

#include "cocos2d.h"

class contact : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	bool onPhysicContact(cocos2d::PhysicsContact &contact);

	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(contact);
private:
	cocos2d::PhysicsWorld *world;
	void setPhysicWorld(cocos2d::PhysicsWorld *m_world) {
		world = m_world;
	}
};

#endif // __HELLOWORLD_SCENE_H__
