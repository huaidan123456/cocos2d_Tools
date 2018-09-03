//
//  ALTools.cpp
//  GameTest-mobile
//
//  Created by Allen on 2018/6/8.
//

#include "ALTools.h"
#include <time.h>

USING_NS_CC;

#define M_PI_VALUE 3.1415926f

long ALTools::getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    
    return tv.tv_sec;
}


float ALTools::getAngle(const Point& beginPoint,const Point& endPoint)
{
    float len_y = endPoint.y - beginPoint.y;
    float len_x = endPoint.x - beginPoint.x;
    
    
    if(len_y == 0.0f)
    {
        if(len_x < 0)
        {
            return 270;
        }
        else if(len_x > 0)
        {
            return 90;
        }
        return 0;
    }
    
    if(len_x == 0.0f)
    {
        if(len_y >= 0)
        {
            return 0;
        }
        else if(len_y < 0)
        {
            return 180;
        }
        
    }
    return  atan2f(len_x,len_y)*180/M_PI_VALUE;
}


/// <summary>
/// 使用极坐标系来描述某点(返回点的笛卡尔坐标系描述)
/// </summary>
/// <param name="_origin">极点</param>
/// <param name="_radius">极轴</param>
/// <param name="_angle">角度(无符号整数)</param>
/// <returns>返回点的笛卡尔坐标系描述</returns>
Point ALTools::PolarCoor(Point _origin, float _radius, int _angle)
{
    
    _angle = _angle % 360;
    if (_angle == 0||_angle == 360)
    {
        //return CCPoint(_origin.x , _origin.y+ _radius);
        return Point(0 , _radius);
    }
    else if (_angle == 90||_angle ==-270)
    {
        //return CCPoint(_origin.x+ _radius, _origin.y );
        return Point(_radius, 0 );
    }
    else if (_angle == 180||_angle ==-180)
    {
        return Point(0 , 0- _radius);
    }
    else if (_angle == 270||_angle == -90)
    {
        return Point(0- _radius, 0 );
    }
    else
    {
        
        if ((_angle > 0 && _angle < 90))
        {
            return Point(_radius * sin(M_PI * _angle / 180.00), _radius * sin(M_PI * (90 - _angle) / 180.00));
        }
        if ((_angle <-270 && _angle > -360))
        {
            _angle+=360;
            return Point(_radius * sin(M_PI * _angle / 180.00), _radius * sin(M_PI * (90 - _angle) / 180.00));
        }
        if ((_angle > 90 && _angle < 180))
        {
            return Point(_radius * sin(M_PI * (180 - _angle) / 180.00), 0 - _radius * sin(M_PI * (90 - (180 - _angle)) / 180.00));
        }
        if ((_angle <-180 && _angle >-270))
        {
            _angle+=360;
            return Point(_radius * sin(M_PI * (180 - _angle) / 180.00), 0 - _radius * sin(M_PI * (90 - (180 - _angle)) / 180.00));
        }
        
        if ((_angle > 180 && _angle < 270))
        {
            return Point(0 - _radius * sin(M_PI * (_angle - 180) / 180.00), 0 - _radius * sin(M_PI * (90 - (_angle - 180)) / 180.00));
        }
        if ((_angle < -90 && _angle > -180))
        {
            _angle+=360;
            return Point(0 - _radius * sin(M_PI * (_angle - 180) / 180.00), 0 - _radius * sin(M_PI * (90 - (_angle - 180)) / 180.00));
        }
        
        if ((_angle > 270 && _angle < 360) )
        {
            return Point(0 - _radius * sin(M_PI * (360 - _angle) / 180.00), _radius * sin(M_PI * (90 - (360 - _angle)) / 180.00));
        }
        if ((_angle < 0 && _angle > -90))
        {
            _angle+=360;
            return Point(0 - _radius * sin(M_PI * (360 - _angle) / 180.00), _radius * sin(M_PI * (90 - (360 - _angle)) / 180.00));
        }
        
        
    }
    return Point(0, 0);
}



///////////////////////////////////////////
//点和矩形的碰撞
///////////////////////////////////////////
bool ALTools::pointToRect(Point _p,Rect _rect)
{
    
    if(_p.x>=_rect.getMinX()&&_p.x<=_rect.getMaxX()&&_p.y>=_rect.getMinY()&&_p.y<=_rect.getMaxY())
    {
        return true;
    }else
    {
        
        return false;
    }
}

//画一个矩形
void ALTools::getDrawNodeByRect(Node* miNode,int _z,Rect _rect,int _s)
{
    DrawNode* front = DrawNode::create();
    Point miRect[4] = {Vec2(_rect.getMinX(),_rect.getMinY()),Vec2(_rect.getMaxX(),_rect.getMinY()),Vec2(_rect.getMaxX(),_rect.getMaxY()),Vec2(_rect.getMinX(),_rect.getMaxY())};
    
    Color4F miColor;
    switch(_s)
    {
        case 0://颜色1 黄色
            miColor = Color4F::YELLOW;
            break;
        case 1://绿色
            miColor = Color4F::GREEN;
            break;
        case 2://蓝色
            miColor = Color4F::BLUE;
            break;
        case 3://红色
            miColor = Color4F::RED;
            break;
        case 4://黑色
            miColor = Color4F::BLACK;
            break;
    }
    front->drawPolygon(miRect,4,miColor,0,miColor);
    miNode->addChild(front,_z);
}

//画一条线
void ALTools::drawLineByPointAngle(Node* miNode,Point _c,float _angle,float _length,int _z,int _s)
{
    //根据点和角度和长度来确定一条直线
    Point _endPoint = PolarCoor(_c,_length,_angle);
    CCLOG("%f,%f",_endPoint.x,_endPoint.y);
    DrawNode* front = DrawNode::create();
    
    _endPoint.x = _endPoint.x+_c.x;
    _endPoint.y = _endPoint.y+_c.y;
    
    Color4F miColor ;
    switch(_s)
    {
        case 0://颜色1 黄色
            miColor = Color4F::YELLOW;
            break;
        case 1://绿色
            miColor = Color4F::GREEN;
            break;
        case 2://蓝色
            miColor = Color4F::BLUE;
            break;
        case 3://红色
            miColor = Color4F::RED;
            break;
        case 4://黑色
            miColor = Color4F::BLACK;
            break;
    }
    //    front->drawLine(_c,_endPoint,miColor);
    miNode->addChild(front,_z);
}


/**
 *  //两个矩形碰撞
 */
bool ALTools::rectToRect(Rect c1,Rect c2)
{
    //看第一个矩形4个定点是否在第二个句型中
    if(c1.getMinX()<c2.getMaxX()&&c1.getMinX()>c2.getMinX()&&c1.getMinY()>c2.getMinY()&&c1.getMinY()<c2.getMaxY())
    {
        return true;
    }else if(c1.getMaxX()<c2.getMaxX()&&c1.getMaxX()>c2.getMinX()&&c1.getMinY()>c2.getMinY()&&c1.getMinY()<c2.getMaxY())
    {
        return true;
    }else if(c1.getMinX()<c2.getMaxX()&&c1.getMinX()>c2.getMinX()&&c1.getMaxY()>c2.getMinY()&&c1.getMaxY()<c2.getMaxY())
    {
        return true;
    }else if(c1.getMaxX()<c2.getMaxX()&&c1.getMaxX()>c2.getMinX()&&c1.getMaxY()>c2.getMinY()&&c1.getMaxY()<c2.getMaxY())
    {
        return true;
    }
    
    //看第2个矩形4个定点是否在第1个句型中
    if(c2.getMinX()<c1.getMaxX()&&c2.getMinX()>c1.getMinX()&&c2.getMinY()>c1.getMinY()&&c2.getMinY()<c1.getMaxY())
    {
        return true;
    }else if(c2.getMaxX()<c1.getMaxX()&&c2.getMaxX()>c1.getMinX()&&c2.getMinY()>c1.getMinY()&&c2.getMinY()<c1.getMaxY())
    {
        return true;
    }else if(c2.getMinX()<c1.getMaxX()&&c2.getMinX()>c1.getMinX()&&c2.getMaxY()>c1.getMinY()&&c2.getMaxY()<c1.getMaxY())
    {
        return true;
    }else if(c1.getMaxX()<c1.getMaxX()&&c2.getMaxX()>c1.getMinX()&&c2.getMaxY()>c1.getMinY()&&c2.getMaxY()<c1.getMaxY())
    {
        
        return true;
    }
    
    return false;
    
}

/**
 *  //两个矩形的横坐标有重合
 */
bool ALTools::rectXtoRectX(Rect c1,Rect c2)
{
    //看第一个矩形4个定点是否在第二个句型中
    if(c1.getMinX()<c2.getMaxX()&&c1.getMinX()>c2.getMinX())
    {
        return true;
    }else if(c1.getMaxX()<c2.getMaxX()&&c1.getMaxX()>c2.getMinX())
    {
        return true;
    }else if(c1.getMinX()<c2.getMaxX()&&c1.getMinX()>c2.getMinX())
    {
        return true;
    }else if(c1.getMaxX()<c2.getMaxX()&&c1.getMaxX()>c2.getMinX())
    {
        return true;
    }
    
    //看第2个矩形4个定点是否在第1个句型中
    if(c2.getMinX()<c1.getMaxX()&&c2.getMinX()>c1.getMinX())
    {
        return true;
    }else if(c2.getMaxX()<c1.getMaxX()&&c2.getMaxX()>c1.getMinX())
    {
        return true;
    }else if(c2.getMinX()<c1.getMaxX()&&c2.getMinX()>c1.getMinX())
    {
        return true;
    }else if(c1.getMaxX()<c1.getMaxX()&&c2.getMaxX()>c1.getMinX())
    {
        
        return true;
    }
    
    return false;
    
}

/**
 *  //线和矩形的碰撞
 */
bool ALTools::lineToRect(Point _c,float _angle,float _length,Rect _rect)
{
    
    for(int i=0;i<_length;i++)
    {
        Point _endPoint = PolarCoor(_c,i,_angle);
        _endPoint.x = _c.x+_endPoint.x;
        _endPoint.y = _c.y+_endPoint.y;
        if(pointToRect(_endPoint,_rect))
        {
            return true;
        }
        
    }
    
    return false;
}


/**
 *  //获取贝塞尔
 */
//修改为返回贝塞尔上所有点的方法
std::vector<Point> ALTools::getBezierPoints(const Vec2& from, const Vec2& control, const Vec2& to, unsigned int segments)
{
    //记录点
    std::vector<Point> allPoints;
    
    
    Vec2 vertex;
    Vec2 firstVertex = Vec2(from.x, from.y);
    Vec2 lastVertex = Vec2(to.x, to.y);
    
    float t = 0;
    for(unsigned int i = segments + 1; i > 0; i--)
    {
        float x = powf(1 - t, 2) * from.x + 2.0f * (1 - t) * t * control.x + t * t * to.x;
        float y = powf(1 - t, 2) * from.y + 2.0f * (1 - t) * t * control.y + t * t * to.y;
        vertex = Vec2(x, y);
        Point miPoint = vertex;
        allPoints.push_back(miPoint);
        
        lastVertex = vertex;
        t += 1.0f / segments;
    }
    return allPoints;
}



/**
 *  设置Node的灰度
 */
void ALTools::setupNodeGray(cocos2d::Node* node)
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
void ALTools::removeNodeGray(cocos2d::Node* node)
{
    if (node)
    {
        GLProgram * pProgram = ShaderCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP);
        node->setGLProgram(pProgram);
        CHECK_GL_ERROR_DEBUG();
    }
}

