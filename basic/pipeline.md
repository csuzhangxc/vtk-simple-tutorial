# 可视化管线

## 可视化管线

VTK 可视化管线主要负责读取或者生成数据，分析或生成数据的衍生版本，写入硬盘文件或者传递数据到渲染引擎进行显示。

VTK 中采用数据流的方法将信息转换为几何数据，主要涉及到两种基本的对象类型：

* vtkDataObject
* vtkAlgorithm

### vtkDataObject

```vtkDataObject``` 可以看做一般的数据集合，有规则结构的数据称为一个 Dataset（```vtkDataSet```，继承自```vtkDataObject```）。

```vtkDataSet``` 中包括几何结构、拓扑结构及属性数据。属性数据既可以关联到点，也可以关联到单元上。

单元（cell）是点的拓扑组合，是构成 Dataset 结构的基本单位，常用来进行插值计算。

```vtkDataObject``` 与 ```vtkDataSet``` 支持的具体数据对象可参考各自类文档。

### vtkAlgorithm

```vtkAlgorithm``` 包含各类 sources（源算法）、filters（过滤器）、mappers（映射器）。

Sources 通过读取（Reader 对象）或者创建数据对象（程序源对象）两种方式来产生数据。

Filters 处理输入数据并产生新的数据对象。

Mappers 接收数据并将其转换为可被渲染引擎绘制的可视化表达。

### 管线的连接与执行

可视化管线主要通过 ```SetInputConnection```、```
AddInputConnection```
、```
GetOutputPort```
 （均为 ```vtkAlgorithm``` 成员函数）进行连接。连接时，可以有多个 Input 或 Output。

管线连接的起点为 Sources，终点为 Mappers，中间可以有 0 个、1 个或多个 Filters。

管线连接时，必须确保参与连接的对象相互兼容。

管线只有当计算需要时才会执行（Lazy Evaluation，惰性计算）。

当管线中的 DataSet 或 Algorithm 发生改变时，管线需要重新执行。```vtkObject``` 内通过成员变量 ```MTime``` 记录最后修改时间（Modification Time）。

## 参考

1. [http://blog.csdn.net/www_doling_net/article/details/26690929](http://blog.csdn.net/www_doling_net/article/details/26690929)
2. [http://www.vtk.org/doc/nightly/html/classvtkDataObject.html](http://www.vtk.org/doc/nightly/html/classvtkDataObject.html)
3. [http://www.vtk.org/doc/nightly/html/classvtkDataSet.html](http://www.vtk.org/doc/nightly/html/classvtkDataSet.html)
