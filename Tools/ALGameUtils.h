//
//  ALGameUtils.h
//  GameTest-mobile
//
//  Created by Allen on 2018/7/18.
//

#ifndef ALGameUtils_h
#define ALGameUtils_h

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class ALGameUtils
{
public:
    static ALGameUtils* getInstance();
    static void destroyInstance();
    
    
    
    //============================
    // !!!:生成随机数
    //============================
    
    /**
     * 获取随机整数 范围 [start,end]
     */
    int getRandom(int startNum, int endNum);
    
    /**
     * 获取随机整数 范围 [0,1)
     */
    float getRandom_0_1();
    
    /**
     通过传入概率 来获取是否抽中
     @param param 概率
     */
    bool getRandomFromFloat(float param);
    
    
    //============================
    // !!!:碰撞相关
    //============================
    
    /**
     点是否在矩形中
     */
    bool rectContainsPoint(const Rect& rect,const Vec2& point) const;
    
    /**
     两个矩形是否相交
     */
    bool rectIntersectsRect(const Rect& rect1,const Rect& rect2) const;
    
    /**
     矩形和圆是否相交
     */
    bool rectIntersectsCircle(const Rect& rect,const cocos2d::Vec2 &center, float radius) const;
    
    /**
     矩形和线段是否相交
     */
    bool rectIntersectsLine(const Rect& rect,const Vec2& point1,const Vec2& point2) const;
    
    
    /**
     线段和线段是否相交
     */
    bool lineIntersectsLine(const Vec2& line1P1,const Vec2& line1P2,const Vec2& line2P1,const Vec2& line2P2) const;
    
    //============================
    // !!!: 角度相关
    //============================
    
    /**
     获取点到圆心的角度  角度为 0~360度

     @param circlePoint 圆心点
     @param point 点
     @return 返回角度  0 ~ 360
     */
    float getCircleAngle(cocos2d::Point circlePoint, cocos2d::Point point);
  
    /**
     获取点到圆心的角度  角度范围 0~180

     @param circlePoint 圆心点
     @param point 点
     @return 返回角度 0 ~ 180
     */
    float getSemicycleAngle(cocos2d::Point circlePoint, cocos2d::Point point);
    
    
    //============================
    // !!!:调整颜色
    //============================
    /**
     *  设置Node的灰度
     */
    void setupNodeGray(cocos2d::Node* node);
    
    /**
     *  移除node的灰色
     */
    void removeNodeGray(cocos2d::Node* node);
    
protected:
    ~ALGameUtils();
    
private:
    ALGameUtils();
    
    
private:
    static ALGameUtils* _gInstance;
};

#endif /* ALGameUtils_h */
