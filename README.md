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
I don't want compile webengine because it contains chromium, so skip all related modules;

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

## understand Qt event system
1. 最为常见的事件处理方式是重写虚函数，比如paintEvent(), mousePressEvent()等等，如果你在重写函数中不做必要的处理，记得要调用基类的默认处理；
```cpp
void MyCheckBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // handle left mouse button here
    } else {
        // pass on other buttons to base class
        QCheckBox::mousePressEvent(event);
    }
}
```
2. 如果你想替换基类的事件处理，则需要重写所有的事件处理虚函数，但是如果只是想扩展基类的处理机制，则只需要重写event()函数即可，对你感兴趣的事件做处理，不感兴趣的事件仍然使用基类的event()即可：
```cpp
bool MyWidget::event(QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        if (ke->key() == Qt::Key_Tab) {
            // special tab handling here
            return true;
        }
    } else if (event->type() == MyCustomEventType) {
        MyCustomEvent *myEvent = static_cast<MyCustomEvent *>(event);
        // custom event handling here
        return true;
    }

    return QWidget::event(event);
}
```
3. 如果你还是不满足，或者需要在一个qobject对象中监听拦截其他qobject事件，则可以考虑使用`QObject::installEventFilter()`，给当前object安装一个过滤器，这个过滤器是其他object，其他object的eventFilter()函数负责拦截监听处理事件；
```cpp
bool FilterObject::eventFilter(QObject *object, QEvent *event)
{
    if (object == target && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Tab) {
            // Special tab handling
            return true;
        } else
            return false;
    }
    return false;
}
```
显然，在事件分发处理优先级上，`eventFilter() > event() > override virtual xxxEvent()`;
更强大也更危险的操作是给QApplication安装eventFilter，这样可以拦截掉所有的object的event，当然这样会造成效率损失

## 手动发送event
1. QCoreApplication::sendEvent()，立即处理这个event，阻塞当前thread；event对象最好在栈上创建，处理过程中不会销毁该event对象，如果在堆上创建，则需要你手动释放；
2. QCoreApplication::postEvent()，发送到消息队列，不阻塞，在下一次事件循环中处理这个事件；postEvent也用于qobject初始化过程，这样可以在object初始化完成以后立即处理某些事件；必须在堆上创建event对象，因为事件对列在处理完以后会自动释放。

## 自定义事件
继承QEvent类，使用QEvent::registerEventType()自动获取一个合法不重复的type(int类型)值作为你的event type，然后就可以使用sendEvent()，postEvent()发送

## chapter1
build a calculator.