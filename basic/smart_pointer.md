# 智能指针

## 对象创建与销毁

```vtkObject``` 将构造函数声明为 ```protected```，因此不能使用构造函数创建对象。

```vtkObject``` 通过静态函数 ```New()``` 创建对象，通过函数 ```Delete()``` 销毁对象。

## 引用计数

在引用计数中，每一个对象负责维护对象所有引用的计数值。

使用引用计数，可以实现数据之间的共享而不用拷贝，同时也可以实现简单的垃圾回收。

## 智能指针

智能指针会自动管理引用计数的增加与减少，如果检测到某对象的引用计数值减少为 0，则会自动地释放该对象的资源，从而达到自动管理内存的目的。

在 VTK 中，智能指针通过模板类 ```vtkSmartPointer``` 实现，使用前需 ```#include <vtkSmartPointer.h>```。

```
/* 使用智能指针管理对象 无需要调用 Delete */
vtkSmartPointer<vtkObject> MyObject = vtkSmartPointer<vtkObject>::New();
```

```
/* 将已创建对象交给智能指针进行管理 */
vtkPolyData *pd = vtkPolyData::New();
// ...

// 方法 1
vtkSmartPointer<vtkPolyData> MyObject;
MyObject.TakeReference(pd);                  // TakeReference 为成员函数

// 方法 2
vtkSmartPointer<vtkPolyData> MyObject
  = vtkSmartPointer<vtkPolyData>::Take(pd);  // Take 为静态成员函数
```

```
/* 使用智能指针获取对象 */
vtkSmartPointer<vtkXMLPolyDataReader> Reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();

// 不使用智能指针 Reader 超出作用域后数据将被释放
vtkPolyData* pd = Reader->GetOutput();

// 使用智能指针 Reader 与 pd 均超出作用域后数据才被释放
vtkSmartPointer<vtkPolyData> pd = Reader->GetOutput();
```

使用 ```GetPointer``` 可以从智能指针中获取普通指针对象。

智能指针与普通指针均可以传递给接收智能指针或普通指针为参数的函数。

智能指针函数返回值必须传递给智能指针对象。

智能指针成员变量在析构时自动释放其拥有的对象，无需调用 ```Delete```。

不要修改智能指针指向新的对象。

```
/* 使用示例 */
#include <vtkFloatArray.h>
#include <vtkSmartPointer.h>

void WithSmartPointers();
void WithoutSmartPointers();

int main(int argc, char *argv[])
{
  WithSmartPointers();
  WithoutSmartPointers();

  return 0;
}

void WithSmartPointers()
{
  vtkSmartPointer<vtkFloatArray> Distances = vtkSmartPointer<vtkFloatArray>::New();
}

void WithoutSmartPointers()
{
  vtkFloatArray* Distances = vtkFloatArray::New();
  Distances->Delete();
}
```

## 参考

1. [http://www.vtk.org/Wiki/VTK/Tutorials/SmartPointers](http://www.vtk.org/Wiki/VTK/Tutorials/SmartPointers)
2. [http://www.vtk.org/doc/nightly/html/classvtkSmartPointer.html](http://www.vtk.org/doc/nightly/html/classvtkSmartPointer.html)
3. [http://blog.csdn.net/www_doling_net/article/details/8540242](http://blog.csdn.net/www_doling_net/article/details/8540242)
