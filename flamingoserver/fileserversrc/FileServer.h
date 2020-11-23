/** 
 *  文件服务器主服务类，FileServer.h
 **/
#pragma once
#include <memory>
#include <list>
#include <map>
#include <mutex>
#include "../net/TcpServer.h"
#include "../net/EventLoop.h"
#include "FileSession.h"

using namespace net;

struct StoredUserInfo
{
    int32_t userid;
    std::string username;
    std::string password;
    std::string nickname;
};

// nocopy 
class FileServer final
{
public:
    FileServer() = default;
    ~FileServer() = default;

    FileServer(const FileServer &rhs) = delete;
    FileServer &operator=(const FileServer &rhs) = delete;

    // 创建 TCPServer, 设置连接回调函数
    bool init(const char *ip, short port, EventLoop *loop, const char *fileBaseDir = "filecache/");
    // 终止 TCPServer
    void uninit();

private:
    // 新连接到来调用或连接断开，所以需要通过conn->connected()来判断，一般只在主loop里面调用
    // 创建一个新会话， 设置可读事件回调函数
    void onConnected(std::shared_ptr<TcpConnection> conn);  
    
    //连接断开, 这里只是移除了会话
    void onDisconnected(const std::shared_ptr<TcpConnection>& conn);
   

private:
    std::unique_ptr<TcpServer>                      m_server;     
    std::list<std::shared_ptr<FileSession>>         m_sessions;
    std::mutex                                      m_sessionMutex;    //多线程之间保护m_sessions
    std::string                                     m_strFileBaseDir;   //文件目录
};
