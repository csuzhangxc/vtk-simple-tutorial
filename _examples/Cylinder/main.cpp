#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)

#include "vtkCylinderSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkInteractorStyleTrackballCamera.h"

int main()
{
  // 圆柱体数据模型
  vtkCylinderSource *cylinder = vtkCylinderSource::New();
  cylinder->SetResolution(8);

  // 将几何数据转换为可被渲染引擎绘制的可视化表达
  vtkPolyDataMapper *cylinderMapper = vtkPolyDataMapper::New();
  cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

  // 需要被渲染绘制的对象
  vtkActor *cylinderActor = vtkActor::New();
  cylinderActor->SetMapper(cylinderMapper);
  cylinderActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);
  cylinderActor->RotateX(30.0);
  cylinderActor->RotateY(-45.0);

  // 渲染器 渲染窗口 交互器
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer(renderer);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow(renWin);

  // 交互方式
  vtkInteractorStyleTrackballCamera *style = vtkInteractorStyleTrackballCamera::New();
  iren->SetInteractorStyle(style);

  // 将需要被渲染的对象添加到渲染器
  renderer->AddActor(cylinderActor);
  renderer->SetBackground(0.1, 0.2, 0.4);
  renWin->SetSize(200, 200);

  // 设置用于观察场景的相机
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(1.5);
  renWin->Render();

  // 开始渲染 进入事件循环
  iren->Start();

  // 清除实例
  cylinder->Delete();
  cylinderMapper->Delete();
  cylinderActor->Delete();
  renderer->Delete();
  renWin->Delete();
  iren->Delete();
  style->Delete();

  return 0;
}
