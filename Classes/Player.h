#ifndef __PLAYER_H__
#define __PALYER_H__

#include "cocos2d.h"

class Player : public cocos2d::Node {
public:
    CREATE_FUNC(Player);
    bool init();
    enum ActionStatus {JUMPING, STANDING};

public:
    void jump(const cocos2d::Vec2 &);
    void setActionStatus(ActionStatus);

private:
    cocos2d::Sprite* sprite;
    ActionStatus actionStatus;
};

#endif//__PLAYER_H__
