#ifndef __HTTP_AND_SQL_H__
#define __HTTP_AND_SQL_H__

#include "cocos2d.h"
#include "network/HttpClient.h"

class HTTPandSQL : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	
	void onCompleteHttpRequest(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
	
	// implement the "static create()" method manually
	CREATE_FUNC(HTTPandSQL);
};

#endif // __HELLOWORLD_SCENE_H__
