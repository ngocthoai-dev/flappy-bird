#include "GameOver.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

int finalScore;
Scene* GameOver::createScene(int score)
{
	finalScore = score;
	auto scene = Scene::create();

	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameOverScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("./flappy-bird/background.png");
	background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background);

	__String *tempScore = __String::createWithFormat("Your Score : %i", finalScore);
	auto label = Label::createWithTTF(tempScore->getCString(), "./fonts/Marker Felt.ttf", visibleSize.height*0.1);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	label->setColor(Color3B::RED);
	addChild(label);

	return true;
}