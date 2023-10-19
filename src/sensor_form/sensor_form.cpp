#include "sensor_form.h"
#include "./../ui_sensor_form.h"

sensor_form::sensor_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sensor_form)
{
    ui->setupUi(this);

    //connect(ui->comboBox, SIGNAL(currentIndexChanged(const QString&)),this, SLOT(on_comboBox_currentIndexChanged(const QString&)));
    connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(on_PushButtun_clicked()));

    QStringList colors;
    colors << "red" << "blue" << "green" << "black";
QList<QColor> colorList;
colorList << QColor(255, 0, 0)
          << QColor(255, 165, 0)
          << QColor(255, 255, 0)
          << QColor(0, 128, 0)
          << QColor(0, 128, 128)
          << QColor(0, 0, 255)
          << QColor(75, 0, 130)
          << QColor(238, 130, 238)
          << QColor(128, 0, 0)
          << QColor(128, 0, 128)
          << QColor(0, 255, 255)
          << QColor(255, 0, 255)
          << QColor(165, 42, 42)
          << QColor(0, 191, 255)
          << QColor(0, 0, 128)
          << QColor(128, 128, 0)
          << QColor(220, 20, 60)
          << QColor(255, 99, 71)
          << QColor(154, 205, 50)
          << QColor(210, 105, 30)
          << QColor(0, 250, 154)
          << QColor(186, 85, 211)
          << QColor(30, 144, 255)
          << QColor(255, 215, 0);
    int seriesCount =24;
    for (int i = 0; i < seriesCount; i++) {

    QLineSeries *series ;
    series = new QLineSeries;
    series->setPen(QPen(QBrush(colorList.at(i)),5));
    if(i==0){
    *series<<QPointF(0.1,1.0);
    *series<<QPointF(100.0,10.0);
    }
    else if(i==1){
    *series<<QPointF(0.1,20.0);
    *series<<QPointF(100.0,30.0);
    }
    else if(i==2){
    *series<<QPointF(0.1,1.0);
    *series<<QPointF(100.0,100.0);
    }
    else if(i==3){
    *series<<QPointF(0.1,800.0);
    *series<<QPointF(100.0,1200.0);
    }else{
    *series<<QPointF(0.1,1.0);
    *series<<QPointF(100.0,10.0);
    }
    series->setUseOpenGL(true);
    seriesList.append(series);
}

    Distance_chart = new QChart();
    Distance_chart->legend()->hide();
    Distance_chart->addSeries(seriesList[0]);
    QValueAxis* axisY = new QValueAxis;
    axisY->setRange(0.0, 10.0);
    Distance_chart->addAxis(axisY, Qt::AlignLeft);
    Distance_chart->setTitle("Distance");
    Distance_chartView = new QChartView(Distance_chart);

    temperature_chart = new QChart();
    temperature_chart->legend()->hide();
    temperature_chart->addSeries(seriesList[1]);
    QValueAxis* temperature_axisY = new QValueAxis;
    temperature_axisY->setRange(20.0, 30.0);
    temperature_chart->addAxis(temperature_axisY, Qt::AlignLeft);
    temperature_chart->setTitle("Temperature ");
    temperature_chartView = new QChartView(temperature_chart);

    relative_humidity_chart = new QChart();
    relative_humidity_chart->legend()->hide();
    relative_humidity_chart->addSeries(seriesList[2]);
    QValueAxis* relative_humidity_axisY = new QValueAxis;
    relative_humidity_axisY->setRange(0.0, 100.0);
    relative_humidity_chart->addAxis(relative_humidity_axisY, Qt::AlignLeft);
    relative_humidity_chart->setTitle("Relative Humidity  ");
    relative_humidity_chartView = new QChartView(relative_humidity_chart);

    pressure_chart = new QChart();
    pressure_chart->legend()->hide();
    pressure_chart->addSeries(seriesList[3]);
    QValueAxis* pressure_axisY = new QValueAxis;
    pressure_axisY->setRange(800.0, 1200.0);
    pressure_chart->addAxis(pressure_axisY, Qt::AlignLeft);
    pressure_chart->setTitle("Pressure ");
    pressure_chartView = new QChartView(pressure_chart);

    ui->verticalLayout_2->addWidget(Distance_chartView);



    ui->verticalLayout_2->addWidget(temperature_chartView);
    ui->verticalLayout_2->addWidget(relative_humidity_chartView);
    ui->verticalLayout_2->addWidget(pressure_chartView);

    temperature_chartView->hide();
    relative_humidity_chartView->hide();
    pressure_chartView->hide();

    main_gui_node = new gui_node();
    main_gui_node->start();
    connect(Distance_chart->scene(), &QGraphicsScene::changed,main_gui_node, &gui_node::handleSceneChanged);


    main_gui_node->startUpdates(seriesList);
    
}

void sensor_form::on_comboBox_currentIndexChanged(const QString &arg1)
{


    if(arg1=="topic_Ultrasound"){
        Distance_chartView->show();
        connect(Distance_chart->scene(), &QGraphicsScene::changed,main_gui_node,  &gui_node::handleSceneChanged);

        temperature_chartView->hide();
        relative_humidity_chartView->hide();
        pressure_chartView->hide();
        disconnect(temperature_chart->scene(), &QGraphicsScene::changed,main_gui_node, 0);
        disconnect(relative_humidity_chart->scene(), &QGraphicsScene::changed,main_gui_node, 0);
        disconnect(pressure_chart->scene(), &QGraphicsScene::changed,main_gui_node, 0);
    }

    if(arg1=="topic_ENV"){
        temperature_chartView->show();
        relative_humidity_chartView->show();
        pressure_chartView->show();
        connect(temperature_chart->scene(), &QGraphicsScene::changed,main_gui_node, &gui_node::handleSceneChanged);
        connect(relative_humidity_chart->scene(), &QGraphicsScene::changed,main_gui_node, &gui_node::handleSceneChanged);
        connect(pressure_chart->scene(), &QGraphicsScene::changed,main_gui_node, &gui_node::handleSceneChanged);
        //hide Distance
        Distance_chartView->hide();
        disconnect(Distance_chart->scene(), &QGraphicsScene::changed,main_gui_node, 0);
    }
}

void sensor_form::on_PushButtun_clicked(){
    ui->comboBox->clear();
    name_node =rclcpp::Node::make_shared("get_name");
    auto topic_name_map = name_node->get_topic_names_and_types();;
    QList<QString> topic_list;
    for(const auto& i :topic_name_map){
        topic_list.append(QString::fromStdString(i.first));
    }
    ui->comboBox->addItems(topic_list);
}


sensor_form::~sensor_form()
{
    delete main_gui_node;
    rclcpp::shutdown();
    delete ui;
}
