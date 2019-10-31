/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Action.h"
#include <iostream>

USING_NS_CC;

Sprite *mainBg;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	{
		// create Main BG
		/*mainBg = Sprite::create("dxd1.jpg");
		mainBg->setScale(0.3);
		mainBg->setPosition(Vec2(0, 0));
		mainBg->setAnchorPoint(Vec2(0, 0));
		addChild(mainBg);

		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);*/

		///////////////
		//auto obj = Sprite::create("saber.jpg");
		//obj->setAnchorPoint(Vec2(0, 0));
		//obj->setPosition(Vec2(0, 0));
		//obj->setScale(1);
		//obj->setRotation(45);
		//obj->setSkewX(20);
		//obj->setSkewY(20);

		//auto actionMoveTo = MoveTo::create(2, Vec2(200, 200));
		//auto actionRotateTo = RotateTo::create(2, 0);

		//auto actionMoveBy1 = MoveBy::create(2, Vec2(200, 200));
		//auto actionMoveBy2 = MoveBy::create(2, Vec2(-200, -200));
		//auto actionRotateBy = RotateBy::create(2, 90);

		//auto actionSpawn1 = Spawn::create(actionMoveBy1, actionRotateBy, nullptr);
		//auto actionSpawn2 = Spawn::create(actionMoveBy2, actionRotateBy, nullptr);
		//auto actionSequence = Sequence::create(actionSpawn1, actionSpawn2, nullptr);

		//auto actionSequenceRepeat = RepeatForever::create(actionSequence);
		//obj->runAction(actionSequenceRepeat);
		//
		//addChild(obj);


		//   /////////////////////////////
		//   // 2. add a menu item with "X" image, which is clicked to quit the program
		//   //    you may modify it.

		//   // add a "close" icon to exit the progress. it's an autorelease object
		//   auto closeItem = MenuItemImage::create(
		//                                          "CloseNormal.png",
		//                                          "CloseSelected.png",
		//                                          CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

		//   if (closeItem == nullptr ||
		//       closeItem->getContentSize().width <= 0 ||
		//       closeItem->getContentSize().height <= 0)
		//   {
		//       problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
		//   }
		//   else
		//   {
		//       float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
		//       float y = origin.y + closeItem->getContentSize().height/2;
		//       closeItem->setPosition(Vec2(x,y));
		//   }

		//   // create menu, it's an autorelease object
		//   auto menu = Menu::create(closeItem, NULL);
		//   menu->setPosition(Vec2::ZERO);
		//   this->addChild(menu, 1);

		//   /////////////////////////////
		//   // 3. add your codes below...

		//   // add a label shows "Hello World"
		//   // create and initialize a label

		//   auto label = Label::createWithTTF("Hello Thoai", "fonts/Marker Felt.ttf", 24);
		//   if (label == nullptr)
		//   {
		//       problemLoading("'fonts/Marker Felt.ttf'");
		//   }
		//   else
		//   {
		//       // position the label on the center of the screen
		//       label->setPosition(Vec2(origin.x + visibleSize.width/2,
		//                               origin.y + visibleSize.height - label->getContentSize().height));

		//       // add the label as a child to this layer
		//       this->addChild(label, 1);
		//   }

		//   // add "HelloWorld" splash screen"
		//   auto sprite = Sprite::create("HelloWorld.png");
		//   if (sprite == nullptr)
		//   {
		//       problemLoading("'HelloWorld.png'");
		//   }
		//   else
		//   {
		//       // position the sprite on the center of the screen
		//       sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

		//       // add the sprite as a child to this layer
		//       this->addChild(sprite, 0);
		   //}
	}
	return true;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event) {
	auto sqe = animatedAction::createScene();
	Director::getInstance()->replaceScene(sqe);
	{
		/*Vec2 touchLocation = touch->getLocation();
		auto actionMoveTo = MoveTo::create(1, touchLocation);
		mainBg->runAction(actionMoveTo);*/

		//auto bg = Sprite::create("bg.jpg");
		//bg->setScale(0.2);
		//bg->setAnchorPoint(Vec2(0, 0));
		//bg->setPosition(touchLocation);

		//addChild(bg);
	}
	return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event) {
	Vec2 touchLocation = touch->getLocation();

	mainBg->setPosition(touchLocation);
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event) {
	mainBg->setPosition(Vec2(0, 0));
}

bool HelloWorld::sayHello() {
	std::vector<int> arr = { 1, 6, 5, 2, 5, 7, 9 };
	std::string test = "test123";

	for (int i = 0; i < arr.size(); i++)
		CCLOG("Here is  %i", arr.at(i));
	return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
