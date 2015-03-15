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
