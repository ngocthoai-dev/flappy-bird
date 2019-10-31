#include "HTTPandSQL.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HTTPandSQL::createScene()
{
	auto scene = Scene::create();

	auto layer = HTTPandSQL::create();

	scene->addChild(layer);

	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HTTPandSQLScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HTTPandSQL::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//auto request = new network::HttpRequest();
	//request->setUrl("https://www.google.com/images/branding/googlelogo/1x/googlelogo_color_272x92dp.png");
	//request->setRequestType(network::HttpRequest::Type::GET);
	//request->setResponseCallback(CC_CALLBACK_2(HTTPandSQL::onCompleteHttpRequest, this));
	//network::HttpClient::getInstance()->send(request);
	//request->release();



	return true;
}

void HTTPandSQL::onCompleteHttpRequest(network::HttpClient *sender, network::HttpResponse *response) {
	std::vector<char> *buffer = response->getResponseData();
	std::string path = "img.png";
	FILE *fp = fopen(path.c_str(), "wb");
	fwrite(buffer->data(), 1, buffer->size(), fp);
	fclose(fp);

	auto sprite = Sprite::create(path);
	sprite->setPosition(Vec2(300, 300));
	addChild(sprite);
}