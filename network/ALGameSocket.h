//
//  ALGameSocket.h
//  ALGameSocketDemo
//
//  Created by Allen on 2018/2/26.
//  Copyright © 2018年 Allen. All rights reserved.
//

#ifndef ALGameSocket_h
#define ALGameSocket_h

#include <stdio.h>
#include <iostream>
#ifdef WIN32
#include <windows.h>
#include <WinSock2.h>

#pragma comment(lib, "WS2_32.lib")

#else
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>

#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SOCKET int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

#endif

#ifndef CHECKF
#define CHECKF(x) \
do \
{ \
if (!(x)) { \
printf("CHECK '%s' = false  ['%s',%d]\n", #x, __FILE__, __LINE__); \
return 0; \
} \
} while (0)
#endif

#define _MAX_MSGSIZE 16 * 1024        // 暂定一个消息最大为16k
#define BLOCKSECONDS    30            // INIT函数阻塞时间
#define INBUFSIZE    (64*1024)        //?    具体尺寸根据剖面报告调整  接收数据的缓存
#define OUTBUFSIZE    (8*1024)        //? 具体尺寸根据剖面报告调整。 发送数据的缓存，当不超过8K时，FLUSH只需要SEND一次


class ALGameSocket
{
public:
    ALGameSocket();
    ~ALGameSocket();
    
    /**
     创建一个Socket,并且连接

     @param pszServerIP 服务器的ip地址
     @param nServerPort 端口号
     @param nBlockSec 设置阻塞时间（非阻塞情况下 select的阻塞时间）
     @param bKeepAlive 是否需要保持连接检测对方主机是否崩溃
     @return 是否创建并且连接成功
     */
    bool createSocket(const char* pszServerIP, int nServerPort, int nBlockSec = BLOCKSECONDS, bool bKeepAlive = false);
    
    
    /**
     发送msg（将要发送的消息放到发送缓冲区中）
     */
    bool sendMsg(void* pBuf, int nSize);
    
    
    /**
     接收msg
     */
    bool receiveMsg(void* pBuf,int& nSize);
    
    
    /**
     向服务器发送流
     */
    bool flush(void);
    
    
    /**
     检查

     @return true 正常状态  false 出现错误等
     */
    bool check(void);
    
    
    /**
     销毁操作
     */
    void destroy(void);
    
    
    /**
     获取socket值
     */
    SOCKET getSocket(void) const { return m_sockClient; }
    
private:
   
    
    /**
     从网络中读取尽可能多的数据，实际向服务器请求数据的地方

     @return 是否接受到数据
     */
    bool recvFromSock(void);
    
    /**
     是否发生错误（注意：异步模式未完成非错误）

     @return 是否有错误
     */
    bool hasError();
    
    
    /**
     关闭socket
     */
    void closeSocket();
    
    
    /**
     *  ============ 变量 ==============
     */
    
    
    /** socket*/
    SOCKET m_sockClient;
    
    //** 发送数据缓冲 *//
    char m_bufOutput[OUTBUFSIZE];  // TODO: 可以优化成指针数组
    int m_nOutbufLen;
    
    //** 环形缓冲区 *//
    char m_bufInput[INBUFSIZE];
    int m_nInbufLen;
    int m_nInbufStart;     // INBUF使用循环式队列，该变量为队列起点，0 - (SIZE-1)
    
    
};

#endif /* ALGameSocket_h */
