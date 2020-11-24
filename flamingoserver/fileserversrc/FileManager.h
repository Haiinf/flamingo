/** 
 *  文件管理类, FileManager.h
 *  zhangyl 2017.03.17
 **/
#pragma once
#include <string>
#include <list>
#include <mutex>

class FileManager final
{
public:
    FileManager();
    ~FileManager();

    FileManager(const FileManager& rhs) = delete;
    FileManager& operator = (const FileManager& rhs) = delete;

    // 将 basepath 作为文件管理目录，将此目录下的所有文件的名字加载到内存
    bool init(const char* basepath);

    // 判断文件是否存在，不存在在目录下查找
    bool isFileExsit(const char* filename);
    void addFile(const char* filename);

private:
    //上传的文件都以文件的md5值命名
    std::list<std::string>      m_listFiles;
    std::mutex                  m_mtFile;
    std::string                 m_basepath;
};