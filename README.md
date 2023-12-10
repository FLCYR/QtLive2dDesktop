# Introduction

**QtLive2dDesktop** 是一个显示live2d模型的桌面宠物程序，基于Qt开发,支持鼠标交互，添加模型，帧率设置。

![](https://github.com/FLCYR/QtLive2dDesktop/blob/master/imgs/capture.png)

![](https://img-blog.csdnimg.cn/direct/2fa56dd63358464e97405d0c42ea4b08.gif)

![](https://github.com/FLCYR/QtLive2dDesktop/blob/master/imgs/multi.gif)

# Installation

**Windows**

```powershell
git clone git@github.com:FLCYR/QtLive2dDesktop.git
```

安装Visual Studio 2019，使用Qt的IDE打开**QtLive2D.pro** ，选择x64，Release模式即可编译运行。

# Download

[Reslease](https://github.com/FLCYR/QtLive2dDesktop/releases) 

# Description

- 只支持.moc3的模型。

- 模型文件不能有错误或缺少文件，具体看 **\*.model3.json**文件 。有些从网上下载的Live2D模型文件会有错误，用软件加载会导致闪退。

- 有些专门用于vtube的Live2D模型，如果要用作桌面模型展示，需要做一些处理。
  
  1. 在 **\*.model3.json**文件同目录下新建两个文件夹**expressions** 和**motions** 。
  
  2. 把所有 **\*.exp3.josn**的文件放进**expressions** 文件夹。
  
  3. 把所有 **\*.motion3.json**的文件放进**motions**文件夹。

- 模型控制的SDK来自[Live2D Cubism SDK](https://www.live2d.com/en/) 。

- 详细移植过程可以参考我写的博客。
  
  [CSDN](https://blog.csdn.net/y123456wydhckd/article/details/134899183?spm=1001.2014.3001.5501)
  
  [ 博客园](https://www.cnblogs.com/duichoumian/p/17891450.html)

# TO-DO

- [ ] 增加更换背景功能。

- [ ] 给模型增加ChatGPT功能,支持智能对话。

- [ ] TTS，实现文本转语音。
