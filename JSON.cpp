#include "JSON.h"
#include "SimpleAudioEngine.h"
#include "json\document.h"
#include "json\rapidjson.h"
#include <iostream>

USING_NS_CC;

Scene* JSON::createScene()
{
	auto scene = Scene::create();

	auto layer = JSON::create();

	scene->addChild(layer);

	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in JSONScene.cpp\n");
}

// on "init" you need to initialize your instance
bool JSON::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//std::string str = "{\"Username\": \"Thoai\"}";
	//rapidjson::Document doc;
	//doc.Parse<0>(str.c_str());
	//if (doc.HasParseError())
	//	CCLOG("Error");
	//else {
	//	if (doc.IsObject() && doc.HasMember("Username")) {
	//		CCLOG("%s", doc["Username"].GetString());
	//	}
	//}

	std::string str = FileUtils::getInstance()->getStringFromFile("./res/test.json");
	CCLOG("%s", str.c_str());
	rapidjson::Document doc;
	doc.Parse<0>(str.c_str());
	if (doc.HasParseError())
		CCLOG("ERROR");
	else {
		if (doc.IsObject() && doc.HasMember("student")) {
			rapidjson::Value &st = doc["student"];
			for (rapidjson::SizeType i = 0; i < st.Size(); i++) {
				CCLOG("name: %s, age: %i, address: %s", st[i]["name"].GetString(), st[i]["age"].GetInt(), st[i]["address"].GetString());
			}
		}
	}
	return true;
}