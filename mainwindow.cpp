#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(released()), this, SLOT(plot()));
    creat_tree();
    caught_select();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creat_tree()
{
    QStandardItemModel *model = new QStandardItemModel();
    // firstlevel
    QStandardItem *firstlevel_1 = new QStandardItem("TH");
    QStandardItem *firstlevel_2 = new QStandardItem("WI");
    QStandardItem *firstlevel_3 = new QStandardItem("RT");
    QStandardItem *firstlevel_4 = new QStandardItem("RS");
    // secondlevel
    QStandardItem *secendlevel_1_1 = new QStandardItem("cur_temp");
    QStandardItem *secondlevel_1_2 = new QStandardItem("cur_dew_point_tem");
    QStandardItem *secondlevel_1_3 = new QStandardItem("cur_rel_hum");
    QStandardItem *secondlevel_1_4 = new QStandardItem("cur_water_vapor_pre");
    QStandardItem *secondlevel_2_1 = new QStandardItem("cur_wind_dire");
    QStandardItem *secondlevel_2_2 = new QStandardItem("cur_wind_speed");
    QStandardItem *secondlevel_2_3 = new QStandardItem("max_wind_speed/min");
    QStandardItem *secondlevel_2_4 = new QStandardItem("dire_max_wind_speed/min");
    QStandardItem *secondlevel_3_1 = new QStandardItem("cur_road_tem");
    QStandardItem *secondlevel_4_1 = new QStandardItem("cur_snow_th");
    QStandardItem *secondlevel_4_2 = new QStandardItem("cur_water_th");
    QStandardItem *secondlevel_4_3 = new QStandardItem("cur_ice_th");
    QStandardItem *secondlevel_4_4 = new QStandardItem("cur_free_tem");
    QStandardItem *secondlevel_4_5 = new QStandardItem("cur_snow_mel_con");

    model->appendRow(firstlevel_1);
    model->appendRow(firstlevel_2);
    model->appendRow(firstlevel_3);
    model->appendRow(firstlevel_4);

    firstlevel_1->appendRow(secendlevel_1_1);
    firstlevel_1->appendRow(secondlevel_1_2);
    firstlevel_1->appendRow(secondlevel_1_3);
    firstlevel_1->appendRow(secondlevel_1_4);

    firstlevel_2->appendRow(secondlevel_2_1);
    firstlevel_2->appendRow(secondlevel_2_2);
    firstlevel_2->appendRow(secondlevel_2_3);
    firstlevel_2->appendRow(secondlevel_2_4);

    firstlevel_3->appendRow(secondlevel_3_1);

    firstlevel_4->appendRow(secondlevel_4_1);
    firstlevel_4->appendRow(secondlevel_4_2);
    firstlevel_4->appendRow(secondlevel_4_3);
    firstlevel_4->appendRow(secondlevel_4_4);
    firstlevel_4->appendRow(secondlevel_4_5);

    ui->treeView->setModel(model);
    ui->treeView->show();
    ui->treeView->expandAll();
}


void MainWindow::caught_select()
{
    QObject::connect(ui->treeView, &QTreeView::clicked, [=] (const QModelIndex &index) {
        QString text = index.data().toString();
        select = text.toStdString();
        //ui->textEdit->setText(QString::number(M[select]));
    });

}


vector<string> MainWindow::open_file(const string &time)
{
    const string path = "E:\\学校\\气象\\2017信息工程\\气象信息系统工程课程实验\\实验材料\\样本数据\\data\\";
    string file_name = fbegin + time + fend;
    string name = path + file_name;
    vector<string> data;
    string word;
    ifstream fs(name);
    if(fs)
        while (fs >> word)
            data.push_back(word);
    return data;
}

void MainWindow::show_text()
{
    QDateTime time1 = ui->dateTimeEdit->dateTime();
    QDateTime time2 = ui->dateTimeEdit_2->dateTime();
    QString str = time1.toString("yyyy-mm-dd hh:mm");
    QString str2 = time2.toString("yyyy-mm-dd hh:mm");
//    string str3 = time1.toString("yyyy-mm-dd hh:mm").toStdString();
    QString out = "ploting pic from " + str + " to " +str2;
    ui->textEdit->setText(out);
}

vector<float> MainWindow::get_data()
{
    vector<float> data;
    QDateTime time = ui->dateTimeEdit->dateTime();
    while (time <= ui->dateTimeEdit_2->dateTime()){
        string name = time.toString("mmss").toStdString();
        vector<string> D = open_file(name);
        // modify
        try {
            data.push_back(stof(D[M[select]]));
        } catch (exception) {
            data.push_back(0);
        }

        time = time.addSecs(60);
    }
    return data;
}

void MainWindow::show_pics()
{
    QChart *chart = new QChart();
    ui->graphicsView->setChart(chart);

    // creat series
    QLineSeries *series = new QLineSeries();

    vector<float> data = get_data();
    int index = 0;
    QDateTime time = ui->dateTimeEdit->dateTime();
    while (time <= ui->dateTimeEdit_2->dateTime()){
        double timeD = time.toString("mm").toDouble();
        series->append(timeD, data[index]);
        time = time.addSecs(60);
        index++;
    }

    chart->addSeries(series);
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(stoi(ui->dateTimeEdit->dateTime().toString("mm").toStdString()), stoi(ui->dateTimeEdit_2->dateTime().toString("mm").toStdString()));
    axisX->setMinorTickCount(2);
    axisX->setTitleText("time/min");

    QValueAxis *axisY = new QValueAxis;
    axisY->setMinorTickCount(2);
    axisY->setTitleText(QString::fromStdString(V[select]));

    //为序列设置坐标轴
    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);
}

void MainWindow::plot()
{
    show_text();
    show_pics();
}
