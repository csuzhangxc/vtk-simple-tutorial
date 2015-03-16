#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkContourFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    renderer(nullptr),
    polyData(nullptr),
    polyActor(nullptr),
    contourActor(nullptr)
{
    ui->setupUi(this);

    setup();
}

MainWindow::~MainWindow()
{
    if (nullptr != renderer)
        renderer->Delete();
    if (nullptr != polyData)
        polyData->Delete();
    if (nullptr != polyActor)
        polyActor->Delete();
    if (nullptr != contourActor)
        contourActor->Delete();

    delete ui;
}

bool MainWindow::loadData(const QString &filename,
        std::vector<std::vector<double> > &values,
                          double &minValue, double &maxValue)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly))
        return false;

    values.clear();
    minValue = 1.0E100;
    maxValue = -1.0E100;

    QRegExp regExp("\\s+");
    QString line;
    QStringList lst;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        line = in.readLine().trimmed();
        if (line.isEmpty())
            break;
        lst = line.split(regExp);
        if (!values.empty()
                && lst.count() != static_cast<int>(values.back().size()))
        {
            // 各行 列数不相等
            values.clear();
            minValue = 1.0E100;
            maxValue = -1.0E100;
            return false;
        }
        std::vector<double> lineValue;
        for (const QString &e : lst)
        {
            double value = e.toDouble();
            lineValue.push_back(value);
            if (value < minValue)
                minValue = value;
            if (value > maxValue)
                maxValue = value;
        }
        values.push_back(std::move(lineValue));
    }

    return true;
}

void MainWindow::setup()
{
    // 设置窗口渲染器
    renderer = vtkRenderer::New();
    renderer->SetBackground(1.0, 1.0, 1.0);
    vtkRenderWindow *renWin = ui->vtkWidget->GetRenderWindow();
    renWin->AddRenderer(renderer);

    if (loadData("data.txt", pointsValue, minValue, maxValue))
        updateUiRender();

    renWin->Render();
}

void MainWindow::updateUiRender()
{
    if (pointsValue.empty())
        return;
    int mid = (minValue+maxValue)/2;
    ui->valueVerticalSlider->setRange(minValue, maxValue);
    ui->valueVerticalSlider->setValue(mid);
    ui->minValueLabel->setText(QString::number(minValue));
    ui->maxValueLabel->setText(QString::number(maxValue));
    setupPoly();
    setupContour();
}

void MainWindow::setupPoly()
{
    if (pointsValue.empty() || pointsValue.at(0).empty())
        return;

    size_t rowCount = pointsValue.size();
    size_t colCount = pointsValue.at(0).size();

    polyData = vtkPolyData::New();                    // 多边形数据
    vtkPoints *points = vtkPoints::New();             // 各点几何数据
    vtkDoubleArray *scalars = vtkDoubleArray::New();  // 点标量数据
    vtkCellArray *cells = vtkCellArray::New();        // 各单元拓扑结构

    for (size_t i = 0; i < rowCount; ++i)
    {
        for (size_t j = 0; j < colCount; ++j)
        {
            double point[] = {static_cast<double>(i),
                              static_cast<double>(colCount-j),
                              0.0};
            vtkIdType id = points->InsertNextPoint(point);
            scalars->InsertTuple1(id, pointsValue.at(i).at(j));
        }
    }

    for (size_t i = 0; i < pointsValue.size()-2; ++i)
    {
        for (size_t j = 0; j < pointsValue.at(0).size()-2; ++j)
        {
            vtkIdType pts[] = {static_cast<vtkIdType>(i*pointsValue.at(0).size()+j),
                               static_cast<vtkIdType>((i+1)*pointsValue.at(0).size()+j),
                               static_cast<vtkIdType>((i+1)*pointsValue.at(0).size()+j+1),
                               static_cast<vtkIdType>(i*pointsValue.at(0).size()+j+1)};
            cells->InsertNextCell(4, pts);
        }
    }

    // 设置多边形的 几何点 拓扑单元 点标量
    polyData->SetPoints(points);
    polyData->SetPolys(cells);
    polyData->GetPointData()->SetScalars(scalars);

    // 多边形数据映射
    vtkPolyDataMapper *polyMapper = vtkPolyDataMapper::New();
    polyMapper->SetInputData(polyData);
    polyMapper->SetScalarRange(0.0, 255.0);

    // 设置多边形Actor
    if (nullptr != polyActor)
    {
        renderer->RemoveActor(polyActor);
        polyActor->Delete();
        polyActor = nullptr;
    }
    if (nullptr != contourActor)
    {
        renderer->RemoveActor(contourActor);
        contourActor->Delete();
        contourActor = nullptr;
    }
    polyActor = vtkActor::New();
    polyActor->SetMapper(polyMapper);
    renderer->AddActor(polyActor);

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Zoom(1.5);

    points->Delete();
    scalars->Delete();
    cells->Delete();
    polyMapper->Delete();
}

void MainWindow::setupContour()
{
    if (nullptr == polyData)
        return;

    // 等值线过滤
    vtkContourFilter *contourFilter = vtkContourFilter::New();
    contourFilter->SetValue(0, ui->selectedValueLabel->text().toDouble());
    contourFilter->SetInputData(polyData);

    vtkPolyDataMapper *contourMapper = vtkPolyDataMapper::New();
    contourMapper->SetInputConnection(contourFilter->GetOutputPort());
    contourMapper->ScalarVisibilityOff();

    if (nullptr != contourActor)
    {
        renderer->RemoveActor(contourActor);
        contourActor->Delete();
        contourActor = nullptr;
    }
    contourActor = vtkActor::New();
    contourActor->SetMapper(contourMapper);
    contourActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
    contourActor->GetProperty()->SetLineWidth(2.0);

    renderer->AddActor(contourActor);

    contourFilter->Delete();
    contourMapper->Delete();
}

void MainWindow::on_selectDataFileAction_triggered()
{
    QString filename = QFileDialog::getOpenFileName();
    if (filename.isEmpty())
        return;
    if (loadData(filename, pointsValue, minValue, maxValue))
        updateUiRender();
}

void MainWindow::on_valueVerticalSlider_valueChanged(int value)
{
    ui->selectedValueLabel->setText(QString::number(value));
    setupContour();
    ui->vtkWidget->GetRenderWindow()->Render();
}
