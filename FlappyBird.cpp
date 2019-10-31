#include "FlappyBird.h"
#include "GameOver.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

Scene* FlappyBird::createScene()
{
	auto scene = Scene::createWithPhysics();

	auto layer = FlappyBird::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in FlappyBirdScene.cpp\n");
}

// on "init" you need to initialize your instance
bool FlappyBird::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./flappy-bird/sound/themeSong.mp3");

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 5);
	edgeBody->setCollisionBitmask(1);
	edgeBody->setContactTestBitmask(true);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(edgeBody);
	addChild(edgeNode);

	auto background = Sprite::create("./flappy-bird/background.png");
	background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background);

	spriteNode = SpriteBatchNode::create("./flappy-bird/articuno.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("./flappy-bird/articuno.plist");
	bird = Sprite::createWithSpriteFrameName("articuno_0.png");
	bird->setPosition(visibleSize / 2);
	spriteNode->addChild(bird);

	auto animate = Animate::create(FlappyBird::createAnimation("articuno_", 38, 0.01));
	animate->retain();
	bird->runAction(RepeatForever::create(animate));

	__String *tempScore = __String::createWithFormat("%i", score);
	label = Label::createWithTTF(tempScore->getCString(), "./fonts/Marker Felt.ttf", visibleSize.height*0.1);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.8));
	label->setColor(Color3B::RED);
	addChild(label);

	this->scheduleUpdate();
	this->schedule(schedule_selector(FlappyBird::pipeInit), 0.003*visibleSize.width);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(FlappyBird::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(FlappyBird::onContactBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

cocos2d::Animation *FlappyBird::createAnimation(std::string prefixName, int pFrameOrder, float delay) {

	auto birdBody = PhysicsBody::createBox(bird->getContentSize().width, bird->getContentSize().height/2);
	birdBody->setCollisionBitmask(3);
	birdBody->setContactTestBitmask(true);
	birdBody->setGravityEnable(false);
	bird->setPhysicsBody(birdBody);
	addChild(spriteNode);

	Vector<SpriteFrame*> animeFrames;

	for (int i = 0; i <= pFrameOrder; i++) {
		std::string index = StringUtils::format("%d", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(prefixName + index + ".png");
		animeFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animeFrames, delay);
	return animation;
}

bool FlappyBird::onContactBegan(cocos2d::PhysicsContact &contact) {
	PhysicsBody *shapeA = contact.getShapeA()->getBody();
	PhysicsBody *shapeB = contact.getShapeB()->getBody();
	if (shapeA->getCollisionBitmask() == 3 && shapeB->getCollisionBitmask() == 2
		|| shapeA->getCollisionBitmask() == 2 && shapeB->getCollisionBitmask() == 3) {
		score++;
		__String *tempScore = __String::createWithFormat("%i", score);
		label->setString(tempScore->getCString());
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./flappy-bird/sound/hit.mp3");
	}
	else {
		if (shapeA->getCollisionBitmask() == 3 && shapeB->getCollisionBitmask() == 1
			|| shapeA->getCollisionBitmask() == 1 && shapeB->getCollisionBitmask() == 3) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./flappy-bird/sound/death.wav");
			touch++;
			if (touch == 3) {
				auto scene = GameOver::createScene(score);
				Director::getInstance()->replaceScene(scene);
			}
		}
	}
	return true;
}

void FlappyBird::stopFly(float) {
	isFalling = true;
}

bool FlappyBird::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
	isFalling = false;
	this->schedule(schedule_selector(FlappyBird::stopFly), 0.25);
	return true;
}

void FlappyBird::update(float) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (isFalling) {
		bird->setPositionX(visibleSize.width / 2);
		bird->setPositionY(bird->getPositionY() - visibleSize.height*0.0035);
	}
	else {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./flappy-bird/sound/wing_flap.wav");
		bird->setPositionX(visibleSize.width / 2);
		bird->setPositionY(bird->getPositionY() + visibleSize.height*0.0035);
	}
}

void FlappyBird::pipeInit(float) {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto topPipe = Sprite::create("./flappy-bird/pipe.png");
	auto botPipe = Sprite::create("./flappy-bird/pipe.png");
	botPipe->setFlipY(true);

	auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
	topPipeBody->setCollisionBitmask(1);
	topPipeBody->setContactTestBitmask(true);
	topPipeBody->setDynamic(false);
	topPipe->setPhysicsBody(topPipeBody);

	auto botPipeBody = PhysicsBody::createBox(botPipe->getContentSize());
	botPipeBody->setCollisionBitmask(1);
	botPipeBody->setContactTestBitmask(true);
	botPipeBody->setDynamic(false);
	botPipe->setPhysicsBody(botPipeBody);

	auto randomHeight = CCRANDOM_0_1();
	if (randomHeight < 0.4) {
		randomHeight = 0.4f;
	}
	else {
		if (randomHeight > 0.8) {
			randomHeight = 0.8f;
		}
	}
	auto topPipeHeightPosition = (randomHeight*visibleSize.height) + (topPipe->getContentSize().height / 2);
	topPipe->setPosition(Point(visibleSize.width + topPipe->getContentSize().width / 2, topPipeHeightPosition));
	botPipe->setPosition(Point(topPipe->getPositionX(), topPipeHeightPosition - (Sprite::create("./flappy-bird/bird.png")->getContentSize().height * 3) - topPipe->getContentSize().height));

	addChild(topPipe);
	addChild(botPipe);

	auto topPipeMove = MoveBy::create(0.008*visibleSize.width, Vec2(-visibleSize.width*1.5, 0));
	auto botPipeMove = MoveBy::create(0.008*visibleSize.width, Vec2(-visibleSize.width*1.5, 0));
	topPipe->runAction(topPipeMove);
	botPipe->runAction(botPipeMove);

	auto pointNode = Node::create();
	pointNode->setPosition(Vec2(topPipe->getPositionX(), topPipe->getPositionY() - (topPipe->getContentSize().height / 2) - (Sprite::create("./flappy-bird/bird.png")->getContentSize().height * 3) / 2));

	auto pointBody = PhysicsBody::createBox(Size(1, (Sprite::create("./flappy-bird/bird.png")->getContentSize().height * 3)));
	pointBody->setCollisionBitmask(2);
	pointBody->setContactTestBitmask(true);
	pointBody->setDynamic(false);

	pointNode->setPhysicsBody(pointBody);
	auto nodeMove = MoveBy::create(0.008*visibleSize.width, Vec2(-visibleSize.width*1.5, 0));
	pointNode->runAction(nodeMove);

	addChild(pointNode);
}