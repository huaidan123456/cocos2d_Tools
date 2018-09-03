//
//  ALGameUtils.cpp
//  GameTest-mobile
//
//  Created by Allen on 2018/7/18.
//

#include "ALGameUtils.h"

#define AL_PI_VALUE 3.1415926f


ALGameUtils* ALGameUtils::_gInstance = nullptr;
ALGameUtils* ALGameUtils::getInstance()
{
    if (!_gInstance) {
        _gInstance = new ALGameUtils();
    }
    return _gInstance;
}

void ALGameUtils::destroyInstance()
{
    if (_gInstance) {
        CC_SAFE_DELETE(_gInstance);
    }
}

ALGameUtils::ALGameUtils()
{
    
}

ALGameUtils::~ALGameUtils()
{
    
}



//============================
// !!!:生成随机数
//============================

/**
 * 获取随机整数 范围 [start,end]
 */
int ALGameUtils::getRandom(int startNum, int endNum)
{
    static std::once_flag alRandomSrand;
    std::call_once(alRandomSrand,[](){
        struct timeval tv;
        gettimeofday(&tv, NULL);
        srand(tv.tv_usec);
    });
    int range = endNum - startNum + 1;
    return rand() % range + startNum;
}

/**
 * 获取随机整数 范围 [0,1)
 */
float ALGameUtils::getRandom_0_1()
{
    static std::once_flag alRandomSrand;
    std::call_once(alRandomSrand,[](){
        struct timeval tv;
        gettimeofday(&tv, NULL);
        srand(tv.tv_usec);
    });
    
    return CCRANDOM_0_1();
}

/**
 通过传入概率 来获取是否抽中
 @param param 概率
 */
bool ALGameUtils::getRandomFromFloat(float param)
{
    return getRandom_0_1() <= param;
}




//============================
// !!!:碰撞相关
//============================

/**
 点是否在矩形中
 */
bool ALGameUtils::rectContainsPoint(const Rect& rect,const Vec2& point) const
{
    return rect.containsPoint(point);
}

/**
 两个矩形是否相交
 */
bool ALGameUtils::rectIntersectsRect(const Rect& rect1,const Rect& rect2) const
{
    return rect1.intersectsRect(rect2);
}

/**
 矩形和圆是否相交
 */
bool ALGameUtils::rectIntersectsCircle(const Rect& rect,const cocos2d::Vec2 &center, float radius) const
{
    return rect.intersectsCircle(center, radius);
}

/**
 矩形和线段是否相交
 */
bool ALGameUtils::rectIntersectsLine(const Rect& rect,const Vec2& point1,const Vec2& point2) const
{
    if (rectContainsPoint(rect, point1) || rectContainsPoint(rect, point2)) {
        return true;
    }
    
    // 矩形对角线
    Vec2 line1p1 = Vec2(rect.origin.x, rect.origin.y);
    Vec2 line1p2 = Vec2(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height);
    Vec2 line2p1 = Vec2(rect.origin.x,rect.origin.y + rect.size.height);
    Vec2 line2p2 = Vec2(rect.origin.x + rect.size.height,rect.origin.y);
    
    return (lineIntersectsLine(point1, point2, line1p1, line1p2) || lineIntersectsLine(point1, point2, line2p1, line2p2));
    
}

/**
 线段和线段是否相交
 */
bool ALGameUtils::lineIntersectsLine(const Vec2& line1P1,const Vec2& line1P2,const Vec2& line2P1,const Vec2& line2P2) const
{
    Rect rect1 = Rect(MIN(line1P1.x, line1P2.x), MIN(line1P1.y, line1P2.y), MAX(line1P1.x, line1P2.x) -MIN(line1P1.x, line1P2.x), MAX(line1P1.y, line1P2.y) - MIN(line1P1.y, line1P2.y));
    Rect rect2 = Rect(MIN(line2P1.x, line2P2.x), MIN(line2P1.y, line2P2.y), MAX(line2P1.x, line2P2.x) -MIN(line2P1.x, line2P2.x), MAX(line2P1.y, line2P2.y) - MIN(line2P1.y, line2P2.y));
    if (!rectIntersectsRect(rect1, rect2)) {
        return false;
    }
    
    // 计算叉积
    auto direct = [](const Vec2& linep1,const Vec2& linep2,const Vec2& point)->float{
        return (point.x - linep1.x) * (linep2.y - linep1.y) - (linep2.x - linep1.x) * (point.y - linep1.y);
    };
    
    // 判断点是否在线段上
    auto onsegment = [](const Vec2& point,const Vec2& linep1,const Vec2& linep2)->int{
        return point.x >= MIN(linep1.x, linep2.x) && point.x <= MAX(linep1.x, linep2.x) && point.y >= MIN(linep1.y, linep2.y) && point.y <= MAX(linep1.y, linep2.y);
    };
    
    float d1 = direct(line2P1,line2P2,line1P1);
    float d2 = direct(line2P1,line2P2,line1P2);
    float d3 = direct(line1P1,line1P2,line2P1);
    float d4 = direct(line1P1,line1P2,line2P2);
    if (d1 * d2 < 0 && d3 * d4 < 0) {
        return true;
    }else if(d1 == 0 && onsegment(line2P1,line2P2,line1P1)){
        return true;
    }else if(d2 == 0 && onsegment(line2P1,line2P2,line1P2)){
        return true;
    }else if(d3 == 0 && onsegment(line1P1,line1P2,line2P1)){
        return true;
    }else if(d4 == 0 && onsegment(line1P1,line1P2,line2P2)){
        return true;
    }
    
    return false;
}





//============================
// !!!: 角度相关
//============================

/**
 获取点到圆心的角度  角度为 0~360度
 
 @param circlePoint 圆心点
 @param point 点
 @return 返回角度  0 ~ 360
 */
float ALGameUtils::getCircleAngle(cocos2d::Point circlePoint, cocos2d::Point point)
{
    float xx = point.x - circlePoint.x;
    float yy = point.y - circlePoint.y;
    // 斜边
    float xie = sqrt(pow(xx, 2) + pow(yy, 2));
    // yy >= 0 弧度在于 0 到 π 之间。(0~180°)
    // yy < 0 弧度在于 π 到 2π 之间。(180°~360°)
    float rad = yy >= 0 ? (acos(xx / xie)) : (AL_PI_VALUE * 2 - acos(xx / xie));
    
    return 180.f / AL_PI_VALUE * rad;
    
}

/**
 获取点到圆心的角度  角度范围 0~180
 
 @param circlePoint 圆心点
 @param point 点
 @return 返回角度 0 ~ 180
 */
float ALGameUtils::getSemicycleAngle(cocos2d::Point circlePoint, cocos2d::Point point)
{
    float xx = point.x - circlePoint.x;
    float yy = point.y - circlePoint.y;
    // 斜边
    float xie = sqrt(pow(xx, 2) + pow(yy, 2));
    float rad = acos(xx / xie);
    
    return 180.f / AL_PI_VALUE * rad;
}



//============================
// !!!:调整颜色
//============================
/**
 *  设置Node的灰度
 */
void ALGameUtils::setupNodeGray(cocos2d::Node* node)
{
    if (node)
    {
        GLProgram* p = new GLProgram();
        p->initWithFilenames("gray.vsh", "gray.fsh");
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        p->link();
        p->updateUniforms();
        node->setGLProgram(p);
    }
}

/**
 *  移除node的灰色
 */
void ALGameUtils::removeNodeGray(cocos2d::Node* node)
{
    if (node)
    {
        GLProgram * pProgram = ShaderCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP);
        node->setGLProgram(pProgram);
        CHECK_GL_ERROR_DEBUG();
    }
}



