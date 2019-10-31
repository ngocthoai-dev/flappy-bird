#include "UI.h"
#include "SimpleAudioEngine.h"
#include <iostream>
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* UI::createScene()
{
	auto scene = Scene::create();

	auto layer = UI::create();

	scene->addChild(layer);

	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in UIScene.cpp\n");
}

// on "init" you need to initialize your instance
bool UI::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//auto btn = ui::Button::create("CloseNormal.png");
	//btn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//btn->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
	//	switch (type) {
	//	case ui::Widget::TouchEventType::BEGAN:
	//		CCLOG("Btn 1 touch");
	//		break;
	//	case ui::Widget::TouchEventType::ENDED:
	//		CCLOG("Btn 1 click");
	//		break;
	//	default:
	//		break;
	//	}
	//});
	//addChild(btn);

	//auto checkBox = ui::CheckBox::create("CloseNormal.png", "CloseSelected.png");
	//checkBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//checkBox->addEventListener([&](Ref *sender, ui::CheckBox::EventType type) {
	//	switch (type)
	//	{
	//	case cocos2d::ui::CheckBox::EventType::SELECTED:
	//		break;
	//	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
	//		break;
	//	default:
	//		break;
	//	}
	//});
	//this->addChild(checkBox);

	//auto loadingBar  = ui::LoadingBar::create("bg.jpg");
	//loadingBar->setPosition(visibleSize / 2);
	//loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	//loadingBar->setPercent(0);
	//this->addChild(loadingBar);
	//auto touchListener = EventListenerTouchOneByOne::create();
	//touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
	//	this->schedule([=](float delta) {
	//		float percent = loadingBar->getPercent();
	//		percent++;
	//		loadingBar->setPercent(percent);
	//		if (percent >= 100.0f)
	//			this->unschedule("updateLoadingBar");
	//	}, 0.05, "updateLoadingBar");
	//	return true; // if you are consuming it
	//};

	//touchListener->onTouchEnded = [=](Touch* touch, Event* event) {
	//	this->unschedule("updateLoadingBar");
	//};
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//auto menuImages = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(UI::onClickMenuItem, this));
	//menuImages->setTag(1);

	//auto menuImages1 = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(UI::onClickMenuItem, this));
	//menuImages1->setTag(2);

	//auto menu = Menu::create(menuImages, menuImages1, nullptr);
	//menu->setPosition(visibleSize / 2);
	//menu->alignItemsVertically();
	//addChild(menu);

	//auto pageView = ui::PageView::create();
	//pageView->setContentSize(visibleSize);
	//addChild(pageView);

	//for (int i = 0; i < 3; i++) {
	//	auto page = ui::Layout::create();
	//	page->setContentSize(pageView->getContentSize());

	//	auto mySprite = cocos2d::Sprite::create("Arceus.png");
	//	mySprite->setPosition(mySprite->getContentSize()/2);
	//	page->addChild(mySprite);
	//	pageView->insertPage(page, i);
	//}

	//pageView->addEventListener([](Ref *sender, ui::PageView::EventType type) {
	//	if (type == ui::PageView::EventType::TURNING) {
	//		auto pageView = dynamic_cast<ui::PageView *>(sender);
	//		CCLOG("curr page = %d", pageView->getCurPageIndex());
	//	}
	//});

	//auto scrollView = ui::ScrollView::create();
	//scrollView->setPosition(visibleSize / 2);
	//scrollView->setDirection(ui::ScrollView::Direction::BOTH);
	//scrollView->setBounceEnabled(true);
	//addChild(scrollView);

	//auto mySprite = Sprite::create("CloseNormal.png");
	//mySprite->setScale(2);
	//mySprite->setPosition(mySprite->getBoundingBox().size / 2);
	//scrollView->addChild(mySprite);

	//scrollView->setInnerContainerSize(mySprite->getBoundingBox().size);
	//scrollView->setContentSize(mySprite->getContentSize());

	//auto slider = ui::Slider::create("./slider/slider1.png", "./slider/slider2.png");
	//slider->loadProgressBarTexture("./slider/slider3.png");
	//slider->setPosition(visibleSize / 2);
	//addChild(slider);
	//slider->addEventListener([](cocos2d::Ref *sender, ui::Slider::EventType type) {
	//	auto slider = dynamic_cast<ui::Slider *>(sender);
	//	if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
	//		CCLOG("%d", slider->getPercent());
	//	}
	//});

	auto myLabel = Label::createWithSystemFont("Enter your Password :", "Arial", 30);
	myLabel->setPosition(Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 2 + origin.y));
	myLabel->setColor(Color3B::RED);
	myLabel->setAlignment(TextHAlignment::CENTER);
	myLabel->enableGlow(Color4B::WHITE);
	this->addChild(myLabel);

	auto textField = ui::TextField::create("......", "Arial", 30);
	textField->setPosition(Vec2(myLabel->getPosition().x + myLabel->getContentSize().width + 25, visibleSize.height / 2));
	textField->setPasswordEnabled(true);
	this->addChild(textField);
	textField->addEventListener([](Ref *sender, ui::TextField::EventType type) {
		auto textField = dynamic_cast<ui::TextField *> (sender);
		switch (type)
		{
		case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
			CCLOG("displayed keyboard");
			break;
		case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
			CCLOG("dismissed keyboard");
			break;
		case cocos2d::ui::TextField::EventType::INSERT_TEXT:
			CCLOG("insert text: %s", textField->getString().c_str());
			break;
		case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
			CCLOG("deleted backward");
			break;
		default:
			break;
		}
	});

	return true;
}

void UI::onClickMenuItem(Ref *sender) {
	auto node = dynamic_cast<Node *> (sender);
	CCLOG("%d", node->getTag());
}