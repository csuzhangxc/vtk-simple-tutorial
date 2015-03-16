#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class vtkRenderer;
class vtkPolyData;
class vtkActor;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_selectDataFileAction_triggered();
    void on_valueVerticalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    // 来自文件的各点取值
    std::vector<std::vector<double> > pointsValue;
    double minValue;
    double maxValue;


    vtkRenderer *renderer;    // 渲染器
    vtkPolyData *polyData;    // 二维多边形数据
    vtkActor *polyActor;      // 多边形Actor
    vtkActor *contourActor;   // 等值线Actor


    // 从文件读取各点取值
    bool loadData(const QString &filename,
                  std::vector<std::vector<double> > &values,
                  double &minValue, double &maxValue);

    // 构造必要环境并进行初始渲染
    void setup();

    // 更新UI及渲染
    void updateUiRender();

    // 构造渲染多边形
    void setupPoly();

    // 提取渲染等值线
    void setupContour();
};

#endif // MAINWINDOW_H
