#ifndef __TMX_MAP_H__
#define __TMX_MAP_H__

#include "cocos2d.h"

class TmxMap : public cocos2d::TMXTiledMap {
public:
    static TmxMap* create(const std::string & name);
    bool initWithTMXFile(const std::string & name);

protected:
    explicit TmxMap(){}

public:
    void moveHor(float delta/* negative means left, positive means right*/);
    void moveVer(float delta/* negative means left, positive means right*/);
    void setMoveSpeed(float value);

    bool isLeftEdgeArrived() const;
    bool isRightEdgeArrived() const;

private:
    bool leftEdgeArrived;
    bool rightEdgeArrived;
    float leftEdge;
    float rightEdge;
    float moveSpeed;
};

#endif//__MAP_H__
