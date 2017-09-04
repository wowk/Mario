#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "TmxMap.h"
#include "Player.h"
#include <map>


class GameScene : public cocos2d::Layer {
public:
    static cocos2d::Scene *creatScene();
    bool init();
    void update(float delta);
    CREATE_FUNC(GameScene);

public:
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
private:
    cocos2d::Camera* camera;
    cocos2d::TMXObjectGroup* groundLayer;
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;

    Player* player;
    TmxMap* tmxMap;
};

#endif//__GAME_SCENE_H__
