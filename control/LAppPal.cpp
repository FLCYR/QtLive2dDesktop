/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "LAppPal.hpp"
#include <cstdio>
#include <stdarg.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Model/CubismMoc.hpp>
#include "LAppDefine.hpp"

#include <QString>
#include <QDebug>
#include <QFile>
#include <QFileInfo>


using std::endl;
using namespace Csm;
using namespace std;
using namespace LAppDefine;

double LAppPal::s_currentFrame = 0.0;
double LAppPal::s_lastFrame = 0.0;
double LAppPal::s_deltaTime = 0.0;


csmByte* LAppPal::LoadFileAsBytes(const string filePath, csmSizeInt* outSize)
{


    int  size = 0;
    QString absPath = QString(filePath.c_str());
    QFileInfo info(absPath);
    size = info.size();
    //size+=10000;
    QFile file(absPath);
    if(file.open(QIODevice::ReadOnly))
    {

        char* buf = new char[size];
        //qDebug()<<"open file: "<<absPath;
        //qDebug()<<"file size bytes: "<<size;
        //int recv = file.read(buf,size);
       // qDebug()<<"have read: "<<recv;

        file.read(buf,size);
        file.close();
        *outSize = size;
        return reinterpret_cast<csmByte*>(buf);
    }
    else
    {
        qDebug()<<"file not found: "<<absPath;
        return NULL;
    }


    //filePath;//
//       const char* path = filePath.c_str();

//       int size = 0;
//       struct stat statBuf;
//       if (stat(path, &statBuf) == 0)
//       {
//           size = statBuf.st_size;
//       }

//       std::fstream file;
//       char* buf = new char[size];

//       file.open(path, std::ios::in | std::ios::binary);
//       if (!file.is_open())
//       {
//           if (DebugLogEnable)
//           {
//               PrintLog("file open error");
//           }
//           return NULL;
//       }
//       file.read(buf, size);
//       file.close();

//       *outSize = size;
//       return reinterpret_cast<csmByte*>(buf);
}

void LAppPal::ReleaseBytes(csmByte* byteData)
{
    delete[] byteData;
}

csmFloat32  LAppPal::GetDeltaTime()
{
    return static_cast<csmFloat32>(s_deltaTime);
}

void LAppPal::UpdateTime()
{
    s_currentFrame = glfwGetTime();
    s_deltaTime = s_currentFrame - s_lastFrame;
    s_lastFrame = s_currentFrame;
}

void LAppPal::PrintLog(const csmChar* format, ...)
{
    va_list args;
    csmChar buf[256];
    va_start(args, format);
    vsnprintf_s(buf, sizeof(buf), format, args); // 標準出力でレンダリング
#ifdef CSM_DEBUG_MEMORY_LEAKING
// メモリリークチェック時は大量の標準出力がはしり重いのでprintfを利用する
    std::printf(buf);
#else
    std::cerr << buf << std::endl;
#endif
    va_end(args);
}

void LAppPal::PrintMessage(const csmChar* message)
{
    PrintLog("%s", message);
}
