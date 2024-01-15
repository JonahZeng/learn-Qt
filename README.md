# learn-Qt
---
为了使用OpenGL ES，我使用Qt 5.15.9版本。
从源码看，Qt5 的OpenGL ES是通过Goolge的angle库模拟实现的，并不是正真意义上的OpenGL ES，所以如果你只是单纯的想使用OpenGL ES的话，直接使用angle是更好的选择；

## build Qt5 and Doc on Windows
you need below tools first:
- MSVC v143 C++ complier on windows
- download [libclang](https://mirrors.tuna.tsinghua.edu.cn/qt/development_releases/prebuilt/libclang/) for compile document, if you don't need document, skip this step; once you descied to build documents, you should add {libclang-install-dir}/bin to your env variable
- Perl version 5.12 or later   [http://www.activestate.com/activeperl/]
- Python version 2.7 or later  [http://www.activestate.com/activepython/]
- Ruby version 1.9.3 or later  [http://rubyinstaller.org/]
- download src from [chinese mirror site](https://mirrors.tuna.tsinghua.edu.cn/qt/official_releases/qt/5.15/5.15.9/single/)
- ~~downlaod [jom](https://mirrors.tuna.tsinghua.edu.cn/qt/official_releases/jom/) for accelerate build, add to your env variable~~

I don't recommand jom, it has some strange issue on incremental build;
uncompress software: tar for .tar.gz, 7z for .7z .zip, I found some strange error(miss file) when I uncompress .zip with git bash unzip;

open `x64 Native Tools Command Prompt for VS 2022` from start menu，enter below command:
```bat
C:\Program Files\Microsoft Visual Studio\2022\Community>cd /d D:\qt5159
D:\qt5159>configure -prefix %CD%\qtbase -opensource -nomake tests -nomake examples -debug-and-release -skip webengine -skip webview -mp
```
I don't want compile webengine because it contains chromdium, so skip all related modules;

start build:
```bat
D:\qt5159>nmake
```
install:
```bat
D:\qt5159>nmake install
```

build doc:
```bat
D:\qt5159>nmake docs
```

tips: if you want build single module:
```bat
nmake -j4 module-<qtdeclarative>
```
now you can use cmake find_package(Qt5 REQUIRED), of course you should set CMAKE_PREFIX_PATH include %CD%qtbase/bin directory;

## chapter1
build a calculator.