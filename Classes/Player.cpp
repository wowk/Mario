#include "Player.h"

USING_NS_CC;

bool Player::init()
{
    if( !Node::init() ) return false;

    sprite = Sprite::create("player.png");
    sprite->setScale(0.05);
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    auto phyBody = PhysicsBody::createBox(
                sprite->getContentSize(),
                PhysicsMaterial(500.0f,0, 0.4f));
    phyBody->setContactTestBitmask(0xFFFFFFFF);
    phyBody->setCategoryBitmask(0xFFFFFFFF);
    phyBody->setRotationEnable(false);
    sprite->addComponent(phyBody);
    sprite->setTag(1);
    this->addChild(sprite);
    actionStatus = ActionStatus::JUMPING;

    return true;
}

void Player::jump(const Vec2 &v)
{
    if( actionStatus == ActionStatus::JUMPING ){
        return;
    }
    auto phyBody = dynamic_cast<PhysicsBody*>(sprite->getComponent("PhysicsBody"));
    phyBody->setVelocity(v);
    setActionStatus(ActionStatus::JUMPING);
}

void Player::setActionStatus(Player::ActionStatus as)
{
    actionStatus = as;
}

const Size Player::scaleSize() const
{
    return sprite->getContentSize() * sprite->getScale();
}
