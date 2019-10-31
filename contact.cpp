#include "contact.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

Scene* contact::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = contact::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in contactScene.cpp\n");
}

// on "init" you need to initialize your instance
bool contact::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 5);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(edgeBody);
	addChild(edgeNode);

	auto sprite1 = Sprite::create("Arceus.png");
	sprite1->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 3));
	sprite1->setScale(0.5);
	sprite1->setFlippedX(true);
	auto spriteBody1 = PhysicsBody::createBox(sprite1->getContentSize());
	spriteBody1->setCollisionBitmask(1);
	spriteBody1->setContactTestBitmask(true);
	spriteBody1->setGravityEnable(false);
	spriteBody1->setDynamic(false);
	sprite1->setPhysicsBody(spriteBody1);
	addChild(sprite1);

	auto sprite2 = Sprite::create("Arceus.png");
	sprite2->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 1.2));
	sprite2->setScale(0.5);
	auto spriteBody2 = PhysicsBody::createBox(sprite2->getContentSize());
	spriteBody2->setCollisionBitmask(2);
	spriteBody2->setContactTestBitmask(true);
	sprite2->setPhysicsBody(spriteBody2);
	addChild(sprite2);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(contact::onPhysicContact, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

bool contact::onPhysicContact(cocos2d::PhysicsContact &contact) {
	auto shapeA = contact.getShapeA()->getBody();
	auto shapeB = contact.getShapeB()->getBody();

	if ((shapeA->getCollisionBitmask() == 1 && shapeB->getCollisionBitmask() == 2) ||
		(shapeA->getCollisionBitmask() == 2 && shapeB->getCollisionBitmask() == 1)) {
		CCLOG("contact!");
		return true;
	}
	else {
		return false;
	}
}