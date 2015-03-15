# 第一个 VTK 程序

## 在 Qt 中使用 VTK

### ImageViewer 程序

**说明：**本示例程序修改自 **VTK-6.1.0/Examples/GUI/Qt/ImageViewer**。

新建 **Qt Widgets** 程序，将 **.pro** 文件修改为类似如下：

```
/* .pro文件 */
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = QtVTK
TEMPLATE = app

INCLUDEPATH += D:/VTK-6.1.0/MinGW/include/vtk-6.1

LIBS += -LD:/VTK-6.1.0/MinGW/lib/ \
        -lvtkGUISupportQt-6.1d \
        -lvtkIOImage-6.1d \
        -lvtkInteractionImage-6.1d \
        -lvtkRenderingCore-6.1d \
        -lvtkCommonExecutionModel-6.1d \
        -lvtkCommonCore-6.1d \
        -lvtkRenderingOpenGL-6.1d

SOURCES += main.cpp

HEADERS  +=
````

其中 ```
INCLUDEPATH += D:/VTK-6.1.0/MinGW/include/vtk-6.1```
 为添加 VTK 头文件所在路径； ```LIBS += -LD:/VTK-6.1.0/MinGW/lib/``` 为添加 VTK 库文件所在路径（对于 MinGW 编译为 *.a* 文件所在路径，对于 VS 编译为 *.lib* 文件所在路径）； ```LIBS += -lvtk***-6.1d``` 等为添加具体的库文件（请注意实际使用到的库文件版本）。

将 **main.cpp** 修改为类似如下：

```
/* main.cpp */
#include <QApplication>

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)

#include "vtkImageViewer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkPNGReader.h"
#include "QVTKWidget.h"
#include "vtkImageData.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  QVTKWidget widget;

  char filename[] = "D:/test.png";
  vtkPNGReader* reader = vtkPNGReader::New();
  reader->SetFileName(filename);
  reader->Update();

  vtkImageViewer* imageView = vtkImageViewer::New();
  imageView->SetInputConnection(reader->GetOutputPort());

  widget.SetRenderWindow(imageView->GetRenderWindow());
  imageView->SetupInteractor(widget.GetRenderWindow()->GetInteractor());
  imageView->SetColorLevel(138.5);
  imageView->SetColorWindow(233);

  int *dims = reader->GetOutput()->GetDimensions();
  widget.resize(dims[0], dims[1]);
  widget.show();

  app.exec();

  imageView->Delete();
  reader->Delete();
  return 0;
}
```

将其中的 ```char filename[] = "D:/test.png";``` 指定为需要通过使用 VTK 显示的图片的路径（如果不是 *png* 图片，需要修改对应的 *Reader* 对象）。

编译运行后（为能在 QtCreator 中直接启动程序，可能需要将 VTK 编译安装后的 *bin* 路径添加到系统环境变量 *PATH*），程序将在窗口中显示程序中指定文件名对应的图片（如上面代码中的 *D:/test.png*）。

### 注意

**main.cpp** 文件中如果不正确设置如下的模块初始化：

```
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)
```

可能会报 ```Error: no override found for '********'``` 错误。

如果不添加 ```
VTK_MODULE_INIT(vtkInteractionStyle)```
 ，可能会在运行时产生警告，并在调试状态关闭程序时发生崩溃（*segmentation fault*）。

### 参考

1. [http://www.vtk.org/Wiki/VTK/VTK_6_Migration/Factories_now_require_defines](http://www.vtk.org/Wiki/VTK/VTK_6_Migration/Factories_now_require_defines)
2. [http://public.kitware.com/pipermail/vtkusers/2014-July/084396.html](http://public.kitware.com/pipermail/vtkusers/2014-July/084396.html)
