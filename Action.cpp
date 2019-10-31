#include "Action.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

Scene* animatedAction::createScene()
{
	auto scene = Scene::create();

	auto layer = animatedAction::create();

	scene->addChild(layer);

	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in animatedActionScene.cpp\n");
}

// on "init" you need to initialize your instance
bool animatedAction::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SpriteBatchNode *spriteNode = SpriteBatchNode::create("sprites.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist");

	model = Sprite::createWithSpriteFrameName("Duck_1.png");
	model->setScale(2);
	model->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 2));
	spriteNode->addChild(model);
	this->addChild(spriteNode);

	auto animate = Animate::create(animatedAction::createAnimation("Duck_", 78, 0.01));
	animate->retain();
	model->runAction(RepeatForever::create(animate));

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(animatedAction::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

void animatedAction::move() {
	animation->release();
	animation = animatedAction::createAnimation("Duck_", 78, 0.01);
	auto animate = Animate::create(animation);
	animation->retain();
	model->runAction(RepeatForever::create(animate));
}

bool animatedAction::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent) {
	animation->release();
	model->stopAllActions();
	animation = animatedAction::createAnimation("Smile_", 3, 0.5);
	auto animate = Animate::create(animation);
	animation->retain();

	auto sqe = Sequence::create(animate, CCCallFuncN::create(CC_CALLBACK_0(animatedAction::move, this)), nullptr);
	model->runAction(sqe);
	return true;
}

cocos2d::Animation *animatedAction::createAnimation(std::string prefixName, int pFrameOrder, float delay) {
	Vector<SpriteFrame*> animeFrames;

	for (int i = 0; i <= pFrameOrder; i++) {
		std::string index = StringUtils::format("%d", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(prefixName + index + ".png");
		animeFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animeFrames, delay);
	return animation;
}