# 主要 class

## vtkAlgorithm & vtkPolyDataAlgorithm

```vtkAlgorithm``` 通过 ```
SetInputConnection```
、```
AddInputConnection```
、```
GetOutputPort```
 进行管线的连接。

 ```vtkPolyDataAlgorithm``` 继承自 ```
vtkAlgorithm```
，以多边形数据作为输出。Cylinder 程序中的 ```
vtkCylinderSource```
 继承自 ```
vtkPolyDataAlgorithm```
。

```vtkPolyDataAlgorithm``` 通过 ```
GetOutput```
 可以直接获得 ```
vtkPolyData*```
。

VTK 中所有 sources、 filters 均直接或间接继承自 ```
vtkAlgorithm```
。

## vtkAbstractMapper & vtkPolyDataMapper

```vtkAbstractMapper``` 相关子类用于将输入数据转换为几何图元（2D / 3D）。

```
vtkAbstractMapper <- vtkAbstractMapper3D <- vtkMapper <- vtkPolyDataMapper
```

```vtkAbstractMapper``` 也继承自 ```
vtkAlgorithm```
。

## vtkProp & vtkActor

```vtkProp``` 用于渲染场景数据的可视化表示（2D / 3D）。

```vtkProp``` 的子类负责确定场景中对象的位置、大小和方向信息。

Prop 依赖于两个对象，一个是 Mapper（```
vtkMapper```
）对象，负责存放数据和渲染信息；另一个是属性（```
vtkProperty```
）对象，负责控制颜色、不透明度等参数。

在 ```vtkProp``` 的子类中，```
vtkActor```
 用于表示场景中的几何数据（Geometry Data），```
vtkVolume```
 表示场景中的体数据（Volumetric Data），```
vtkActor2D```
 常用来表示二维空间中的数据。

 ```
 vtkProp <- vtkProp3D <- vtkActor
 ```

```vtkProp``` 也用于实现对象的拾取（picking）、拖动（dragging）。

## vtkRenderer

组成场景的对象包括 Prop、Camara、Light 都被集中在一个 ```vtkRenderer```
 对象中。

```vtkRenderer``` 负责管理场景的渲染过程。一个 ```vtkRenderWindow```
 中可以有多个 ```vtkRenderer``` 对象，这些 ```vtkRenderer``` 可以渲染在窗口中不同的矩形区域中（视口），甚至可以是覆盖的区域。

```vtkRenderer``` 继承自 ```vtkViewport```。

## vtkRendererWindow

```vtkRendererWindow``` 将操作系统与 VTK 渲染引擎连接到一起。不同平台下的 ```vtkRenderWindow``` 子类负责本地计算机系统中窗口创建和渲染过程管理。当使用 VTK 开发应用程序时，只需要使用平台无关的 ```vtkRendererWindow``` 类，运行时系统会自动替换为平台相关的 ```vtkRendererWindow``` 子类。

对于 ```QVTKWidget```，可以通过 ```GetRenderWindow``` 获取到 ```vtkRenderWindow*```。

## vtkRenderWindowInteractor

```vtkRenderWindowInteractor``` 提供平台独立的响应鼠标、键盘和时钟事件的交互机制，通过 VTK 的 Command / Observer 设计模式将监听到的特定平台的鼠标、键盘和时钟事件交由 ```vtkInteractorObserver``` 或其子类，如 ```vtkInteractorStyle``` 进行处理。

```vtkInteractorStyle``` 等监听这些消息并进行处理以完成旋转、拉伸和放缩等运动控制。

## 参考

1. [http://www.vtk.org/doc/nightly/html/classvtkAlgorithm.html](http://www.vtk.org/doc/nightly/html/classvtkAlgorithm.html)
2. [http://www.vtk.org/doc/nightly/html/classvtkPolyDataAlgorithm.html](http://www.vtk.org/doc/nightly/html/classvtkPolyDataAlgorithm.html)
3. [http://www.vtk.org/doc/nightly/html/classvtkAbstractMapper.html](http://www.vtk.org/doc/nightly/html/classvtkAbstractMapper.html)
4. [http://www.vtk.org/doc/nightly/html/classvtkProp.html](http://www.vtk.org/doc/nightly/html/classvtkProp.html)
5. [http://www.vtk.org/doc/nightly/html/classvtkRenderer.html](http://www.vtk.org/doc/nightly/html/classvtkRenderer.html)
6. [http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html](http://www.vtk.org/doc/nightly/html/classvtkRenderWindow.html)
7. [http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html](http://www.vtk.org/doc/nightly/html/classvtkRenderWindowInteractor.html)
8. [http://blog.csdn.net/www_doling_net/article/details/8536376](http://blog.csdn.net/www_doling_net/article/details/8536376)




