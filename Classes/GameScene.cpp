#include "GameScene.h"
#include <typeinfo>
#include <iostream>


USING_NS_CC;

Scene *GameScene::creatScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, -1000));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = GameScene::create();

    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{
    if( !Layer::init() ){
        return false;
    }

    Vec2 orgin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();

    camera = Camera::createOrthographic(size.width, size.height, 0, 1);
    camera->setCameraFlag(CameraFlag::DEFAULT);
    this->addChild(camera);

    auto tmxMap = TMXTiledMap::create("firstMap.tmx");
    this->addChild(tmxMap);
    auto scaleFactor = size.height / tmxMap->getContentSize().height;
    tmxMap->setScale(scaleFactor);
    tmxMap->setLocalZOrder(0);

    groundLayer = tmxMap->getObjectGroup("ground");
    for( Value v : groundLayer->getObjects() ){
        ValueMap map = v.asValueMap();
        int x = map["x"].asInt() * scaleFactor;
        int y = map["y"].asInt() * scaleFactor;
        int w = map["width"].asInt() * scaleFactor;
        int h = map["height"].asInt() * scaleFactor;

        auto phyBody = PhysicsBody::createBox(Size(w,h), PhysicsMaterial(1000.0f,0, 0.4f));
        phyBody->setDynamic(false);
        phyBody->setContactTestBitmask(0x00000001);
        phyBody->setCategoryBitmask(0x00000001);
        auto ground = Node::create();
        this->addChild(ground);
        ground->setPhysicsBody(phyBody);
        ground->setPosition(x + (w / 2), y + (h / 2));
        ground->setScale(scaleFactor);
        ground->setTag(2);
    }

    player = Player::create();
    player->setPosition(200,200);
    player->setLocalZOrder(10);
    this->addChild(player);

    camera->setPosition(200, 200);

    setKeyboardEnabled(true);

    EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [=](PhysicsContact& contact) -> bool {
        Node* nodeA = contact.getShapeA()->getBody()->getNode();
        Node* nodeB = contact.getShapeB()->getBody()->getNode();
        if( (nodeA->getTag() == 1 && nodeB->getTag() == 2) || (nodeA->getTag() == 2 && nodeB->getTag() == 1) ){
            player->setActionStatus(Player::ActionStatus::STANDING);
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    this->scheduleUpdate();

    return true;
}

void GameScene::update(float delta)
{
    if( keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] ){
        player->setPositionX(-80 * delta + player->getPositionX());
    }else if( keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] ){
        player->setPositionX(80 * delta + player->getPositionX());
    }
    if(keyMap[EventKeyboard::KeyCode::KEY_SPACE] ){
        player->jump(Vec2(0, 200));
    }
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
    keyMap[keyCode] = true;
    switch( keyCode ){
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = false;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = false;
        break;
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = false;
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
        break;
    default:
        break;
    }
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
    keyMap[keyCode] = false;
}
