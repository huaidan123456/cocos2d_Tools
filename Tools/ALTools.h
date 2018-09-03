//
//  ALTools.h
//  GameTest-mobile
//
//  Created by Allen on 2018/6/8.
//

#ifndef ALTools_h
#define ALTools_h

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class ALTools
{
public:
    /**
     *  获取当前的时间戳 (以 秒 为单位)
     */
    static long getCurrentTime();
    
    /**
     *  根据两点获取一个角度
     */
    static float  getAngle(const Point& beginPoint,const Point& endPoint);
    
    /**
     *  //根据一个角度和轴求坐标
     */
    static Point PolarCoor(Point _origin, float _radius, int _angle);
    
    /**
     *  //点和矩形的碰撞
     */
    static bool pointToRect(Point _p,Rect _rect);
    
    /**
     *  //根据一个矩形和状态返回一个可以绘制的矩形
     */
    static void getDrawNodeByRect(Node* miNode,int _z,Rect _rect,int _s);

    
    /**
     *  //根据点和角度画线
     */
    static void drawLineByPointAngle(Node* miNode,Point _c,float _angle,float _length,int _z,int _s);
    

    
    /**
     *  //两个矩形碰撞
     */
    static bool rectToRect(Rect c1,Rect c2);
    
    /**
     *  //两个矩形的横坐标有重合
     */
    static bool rectXtoRectX(Rect c1,Rect c2);
    
    /**
     *  //线和矩形的碰撞
     */
    static bool lineToRect(Point _c,float _angle,float _length,Rect _rect);
    
    
    /**
     *  //获取贝塞尔
     */
    static std::vector<Point> getBezierPoints(const Vec2& from, const Vec2& control, const Vec2& to, unsigned int segments);
    
    /**
     *  设置Node的灰度
     */
    static void setupNodeGray(cocos2d::Node* node);
    
    /**
     *  移除node的灰色
     */
    static void removeNodeGray(cocos2d::Node* node);
};

#endif /* ALTools_h */
