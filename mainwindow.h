#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDateTime>
#include <vector>
#include <string>
#include <QString>
#include <QTreeView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <map>
#include <fstream>
#include <QtCharts>
#include <exception>

using std::vector;
using std::string;
using std::map;
using std::ifstream;
using std::stof;
using std::stoi;
using std::exception;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void show_text();
    vector<float> get_data();
    void creat_tree();
    void caught_select();
    vector<string> open_file(const string &time);
    void show_pics();

    const string fbegin = "Z_SURF_I_00016-REG_2012121816";
    const string fend = "_O_AWS-RD_FTM.txt";
    string select;
    map<string, int> M = {{"cur_temp",7},{"cur_dew_point_tem",12},{"cur_rel_hum",13},{"cur_water_vapor_pre",16},
                          {"cur_wind_dire",27},{"cur_wind_speed",28},{"max_wind_speed/min",33},{"dire_max_wind_speed/min",32},
                          {"cur_road_tem",35},{"cur_snow_th",47},{"cur_water_th",48},{"cur_ice_th",49},{"cur_free_tem",50},
                          {"cur_snow_mel_con",51}};

    map<string, string> V = {{"cur_temp","0.1°C"},{"cur_dew_point_tem","0.1°C"},{"cur_rel_hum","1%"},{"cur_water_vapor_pre","0.1hPa"},
                          {"cur_wind_dire","1°"},{"cur_wind_speed","0.1m/s"},{"max_wind_speed/min","0.1m/s"},{"dire_max_wind_speed/min","1°"},
                          {"cur_road_tem","0.1°C"},{"cur_snow_th","1mm"},{"cur_water_th","0.1mm"},{"cur_ice_th","0.1mm"},{"cur_free_tem","0.1°C"},
                          {"cur_snow_mel_con","1%"}};



private slots:
    void plot();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
