#include "TmxMap.h"

USING_NS_CC;

TmxMap *TmxMap::create(const std::__cxx11::string &name)
{
    TmxMap *pRet = new(std::nothrow) TmxMap();
    if (pRet && pRet->initWithTMXFile(name) ){
        pRet->autorelease();
        return pRet;
    }else{
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool TmxMap::initWithTMXFile(const std::__cxx11::string &name)
{
    if( !TMXTiledMap::initWithTMXFile(name) ){
        return false;
    }

    auto vSize = Director::getInstance()->getVisibleSize();
    auto mSize = this->getContentSize();

    this->setAnchorPoint(Vec2(0,0));
    this->setPosition(0, 0);

    rightEdge = -(mSize.width - vSize.width - 1);
    leftEdge = -1.0f;
    moveSpeed = 80;

    leftEdgeArrived = false;
    rightEdgeArrived = false;
}

void TmxMap::moveHor(float delta)
{
    auto posX = delta * moveSpeed + this->getPositionX();
    if( posX > leftEdge ){
        posX = leftEdge;
        leftEdgeArrived = true;
    }else{
        leftEdgeArrived = false;
    }

    if( posX < rightEdge ){
        posX = rightEdge;
        rightEdgeArrived = true;
    }else{
        rightEdgeArrived = false;
    }
    this->setPositionX(posX);
}



void TmxMap::setMoveSpeed(float value)
{
    moveSpeed = value;
}

bool TmxMap::isLeftEdgeArrived() const
{
    return leftEdgeArrived;
}

bool TmxMap::isRightEdgeArrived() const
{
    return rightEdgeArrived;
}
