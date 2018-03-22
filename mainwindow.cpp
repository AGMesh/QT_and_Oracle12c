#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ComboBoxItemDelegate.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDate>
#include <QDebug>
#include <QStringList>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ScheduleModel(0),
    TeachersModel(0),
    LessonsModel(0),
    TypesModel(0),
    CabinetsModel(0),
    TimesModel(0),
    GroupsModel(0),
    model1(0)
{
    ui->setupUi(this);

    connect(ui->actionConnect, SIGNAL(triggered()),
            this, SLOT(dbConnect()));


    ui->tableWidgetAdd->setRowCount(7);
    ui->tableWidgetAdd->setColumnCount(1);

    list << "" << "Teachers" << "Lessons" << "Types" << "Cabinets" << "Times" << "Groups";
    ui->comboBox_all->addItems(list);

    list1 << "" << "28.08.2017 - 01.09.2017" << "04.09.2017 - 08.09.2017" << "11.09.2017 - 15.09.2017" << "18.09.2017 - 22.09.2017" << "25.09.2017 - 29.09.2017" << "02.10.2017 - 06.10.2017" << "09.10.2017 - 13.10.2017" << "16.10.2017 - 20.10.2017" << "23.10.2017 - 27.10.2017" << "30.10.2017 - 03.11.2017" << "06.11.2017 - 10.11.2017" << "13.11.2017 - 17.11.2017" << "20.11.2017 - 24.11.2017" << "27.11.2017 - 01.12.2017" << "04.12.2017 - 08.12.2017" << "11.12.2017 - 15.12.2017";
    ui->comboBox_Week->addItems(list1);

    list2 << "" << "ИЭУИС 3-1" << "ИЭУИС 3-2" << "ИЭУИС 3-3" << "ИЭУИС 3-4";
    ui->comboBox_Group->addItems(list2);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dbConnect()
{
    if (QSqlDatabase::isDriverAvailable("QOCI"))
        qDebug() << "Success!";
    else
        qDebug() << "Failure!";
    QSqlDatabase db = QSqlDatabase::addDatabase("QOCI");
    db.setHostName("192.168.1.2");
    db.setPort(1521);
    db.setDatabaseName("orcl");
    db.setUserName("SYSTEM");
    db.setPassword("Admin123");
    bool ok = db.open();
    if (!ok)
        qDebug() << db.lastError().text();
    ScheduleModel = new QSqlRelationalTableModel(this, db);
    TeachersModel  = new QSqlTableModel(this, db);
    LessonsModel = new QSqlTableModel(this, db);
    TypesModel = new QSqlTableModel(this, db);
    CabinetsModel = new QSqlTableModel(this, db);
    TimesModel = new QSqlTableModel(this, db);
    GroupsModel = new QSqlTableModel(this, db);

/*
    ScheduleModel->setTable("Schedule");
    ScheduleModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ScheduleModel->setRelation(1, QSqlRelation("Times", "Time_id", "Time_name"));
    ScheduleModel->setRelation(2, QSqlRelation("Lessons", "Lesson_id", "Lesson_name"));
    ScheduleModel->setRelation(3, QSqlRelation("Types", "Type_id", "Type_name"));
    ScheduleModel->setRelation(4, QSqlRelation("Teachers", "Teacher_id", "Teacher_name"));
    ScheduleModel->setRelation(5, QSqlRelation("Cabinets", "Cabinet_id", "Cabinet_name"));
    ScheduleModel->setRelation(6, QSqlRelation("Groups", "Group_id", "Group_name"));
    ScheduleModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Дата"));
    ScheduleModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Время"));
    ScheduleModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Предмет"));
    ScheduleModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Тип занятия"));
    ScheduleModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Преподаватель"));
    ScheduleModel->setHeaderData(5, Qt::Horizontal, QObject::tr("Кабинет"));
    ScheduleModel->setHeaderData(6, Qt::Horizontal, QObject::tr("Группа"));
    ScheduleModel->select();

    ui->tableViewSTUDY_GROUP->setModel(ScheduleModel);

    ui->tableViewSTUDY_GROUP->setItemDelegateForColumn(1, new QSqlRelationalDelegate(ui->tableViewSTUDY_GROUP));
    ui->tableViewSTUDY_GROUP->setItemDelegateForColumn(2, new QSqlRelationalDelegate(ui->tableViewSTUDY_GROUP));
    ui->tableViewSTUDY_GROUP->setItemDelegateForColumn(3, new QSqlRelationalDelegate(ui->tableViewSTUDY_GROUP));
    ui->tableViewSTUDY_GROUP->setItemDelegateForColumn(4, new QSqlRelationalDelegate(ui->tableViewSTUDY_GROUP));
    ui->tableViewSTUDY_GROUP->setItemDelegateForColumn(5, new QSqlRelationalDelegate(ui->tableViewSTUDY_GROUP));
    ui->tableViewSTUDY_GROUP->setItemDelegateForColumn(6, new QSqlRelationalDelegate(ui->tableViewSTUDY_GROUP));
    ui->tableViewSTUDY_GROUP->resizeColumnsToContents();
*/
    TeachersModel->setTable("Teachers");
    TeachersModel->select();

    LessonsModel->setTable("Lessons");
    LessonsModel->select();

    TypesModel->setTable("Types");
    TypesModel->select();

    CabinetsModel->setTable("Cabinets");
    CabinetsModel->select();

    TimesModel->setTable("Times");
    TimesModel->select();

    GroupsModel->setTable("Groups");
    GroupsModel->select();

    QAbstractItemModel *Schedule = ScheduleModel;
    QAbstractItemModel *Teachers = TeachersModel ;
    QAbstractItemModel *Lessons = LessonsModel ;
    QAbstractItemModel *Types = TypesModel ;
    QAbstractItemModel *Cabinets = CabinetsModel ;
    QAbstractItemModel *Times = TimesModel ;
    QAbstractItemModel *Groups = GroupsModel ;

    //ui->tableViewCOURSE->setModel(Schedule);

    QStringList list;
    list << "Дата" << "Преподаватель" << "Предмет" << "Тип занятия" << "Кабинет" << "Время" << "Группа";
    ui->tableWidgetAdd->setVerticalHeaderLabels(list);
    ui->tableWidgetAdd->horizontalHeader()->setVisible(false);
    ui->tableWidgetAdd->setColumnWidth(0,550);


    ComboBoxItemDelegate *delegate1 = new ComboBoxItemDelegate(ui->tableWidgetAdd);
    delegate1->setModel(Teachers);
    delegate1->setModelKeyColumn(0);
    delegate1->setModelViewColumn(1);
    ComboBoxItemDelegate *delegate2 = new ComboBoxItemDelegate(ui->tableWidgetAdd);
    delegate2->setModel(Lessons);
    delegate2->setModelKeyColumn(0);
    delegate2->setModelViewColumn(1);
    ComboBoxItemDelegate *delegate3 = new ComboBoxItemDelegate(ui->tableWidgetAdd);
    delegate3->setModel(Types);
    delegate3->setModelKeyColumn(0);
    delegate3->setModelViewColumn(1);
    ComboBoxItemDelegate *delegate4 = new ComboBoxItemDelegate(ui->tableWidgetAdd);
    delegate4->setModel(Cabinets);
    delegate4->setModelKeyColumn(0);
    delegate4->setModelViewColumn(1);
    ComboBoxItemDelegate *delegate5 = new ComboBoxItemDelegate(ui->tableWidgetAdd);
    delegate5->setModel(Times);
    delegate5->setModelKeyColumn(0);
    delegate5->setModelViewColumn(1);
    ComboBoxItemDelegate *delegate6 = new ComboBoxItemDelegate(ui->tableWidgetAdd);
    delegate6->setModel(Groups);
    delegate6->setModelKeyColumn(0);
    delegate6->setModelViewColumn(1);

    //ui->tableViewCOURSE->setItemDelegateForColumn(1, delegate);


    //ui->tableViewAdd->set;


    ui->tableWidgetAdd->setItemDelegateForRow(1, delegate1);
    ui->tableWidgetAdd->setItemDelegateForRow(2, delegate2);
    ui->tableWidgetAdd->setItemDelegateForRow(3, delegate3);
    ui->tableWidgetAdd->setItemDelegateForRow(4, delegate4);
    ui->tableWidgetAdd->setItemDelegateForRow(5, delegate5);
    ui->tableWidgetAdd->setItemDelegateForRow(6, delegate6);


   /*
    courseModel->setTable("Teachers");
    courseModel->select();

    ui->tableViewCOURSE->setModel(courseModel);
*/






    //groupModel->setTable("Cabinets");
    //groupModel->select();

    //ui->tableViewGROUP->setModel(groupModel);



}


void MainWindow::on_pushButton_Query_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    QSqlQuery query(db);
    QStringList list;
    QString s = ui->comboBox_all->currentText();
    query.exec("SELECT * FROM "+s); //SELECT * FROM TEST


    qDebug() << query.lastError().text();
    ui->listWidget->clear();
    while (query.next()){
        int id = query.value(0).toInt();
        QString str = query.value(1).toString();
        qDebug() << id << " - " << str;

        list << QString("%1 - %2").arg(id).arg(str);

        //ui->listWidget->addItem(str);

    }
    ui->listWidget->addItems(list);
}

void MainWindow::on_pushButton_2_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("qt_aql_default_connect");
    QSqlQuery query(db);
    QString s = ui->comboBox_all->currentText();
    s.remove(s.length()-1,1);
    query.prepare("INSERT INTO "+s+"s"+" ("+s+"_name) VALUES (:name)");
    query.bindValue(":name", ui->lineEdit_AddName->text());

    bool ok = query.exec();
    if(!ok)
        qDebug() << query.lastError().text();

    ui->lineEdit_AddName->clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("qt_aql_default_connect");

    db.transaction();

    QSqlQuery query(db);

    if (ui->listWidget->currentRow() >= 0)
    {
        QString s = ui->comboBox_all->currentText();
        s.remove(s.length()-1,1);
        //qDebug() << ui->listWidget->currentRow();
        QString str = ui->listWidget->item(ui->listWidget->currentRow())->data(Qt::DisplayRole).toString();
        int num = str.left(str.indexOf(" ")).toInt();
        //qDebug() << num;
        query.prepare("DELETE FROM "+s+"s"+" WHERE "+s+"_id = :id");
        query.bindValue(":id", num);
        bool ok = query.exec();
        if(!ok){
            qDebug() << query.lastError().text();

            db.rollback();
        }
        if(!query.isActive())
            QMessageBox::warning(this, tr("Database error!"), query.lastError().text());

        db.commit();

    }
    else
        QMessageBox::warning(this, tr("Strings"), tr("No selected rows."));
}

void MainWindow::on_pushButton_4_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    QSqlQuery query(db);
    QStringList list1, list2, list3, list4, list5;
    QString s = ui->comboBox_Group->currentText();
    QString d0 = ui->comboBox_Week->currentText();
    d0.remove(10,d0.length()-10);
    QString y = d0;
    y.remove(0, 6);
    QString d = d0;
    d.remove(2, 9);
    QString m = d0;
    m.remove(0, 3);
    m.remove(2, 5);
    QDate d1(y.toInt(), m.toInt(), d.toInt());
    //1 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d1.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 1 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_3->clear();
    while (query.next()){
        list1 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_3->addItems(list1);
    if (list1.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_3->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //2 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d1.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 2 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_4->clear();
    while (query.next()){
        list2 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_4->addItems(list2);
    if (list2.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_4->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //3 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d1.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 3 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_5->clear();
    while (query.next()){
        list3 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_5->addItems(list3);
    if (list3.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_5->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //4 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d1.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 4 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_6->clear();
    while (query.next()){
        list4 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_6->addItems(list4);
    if (list4.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_6->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //5 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d1.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 5 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_7->clear();
    while (query.next()){
        list5 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_7->addItems(list5);
    if (list5.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_7->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //Второй день недели
    list1.clear();
    list2.clear();
    list3.clear();
    list4.clear();
    list5.clear();
    QDate d2 = d1.addDays(1);
    //1 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d2.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 1 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_11->clear();
    while (query.next()){
        list1 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_11->addItems(list1);
    if (list1.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_11->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //2 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d2.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 2 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_12->clear();
    while (query.next()){
        list2 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_12->addItems(list2);
    if (list2.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_12->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //3 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d2.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 3 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_9->clear();
    while (query.next()){
        list3 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_9->addItems(list3);
    if (list3.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_9->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //4 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d2.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 4 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_8->clear();
    while (query.next()){
        list4 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_8->addItems(list4);
    if (list4.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_8->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //5 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d2.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 5 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_10->clear();
    while (query.next()){
        list5 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_10->addItems(list5);
    if (list5.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_10->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //Третий день недели
    list1.clear();
    list2.clear();
    list3.clear();
    list4.clear();
    list5.clear();
    QDate d3 = d2.addDays(1);
    //1 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d3.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 1 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_14->clear();
    while (query.next()){
        list1 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_14->addItems(list1);
    if (list1.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_14->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //2 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d3.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 2 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_15->clear();
    while (query.next()){
        list2 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_15->addItems(list2);
    if (list2.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_15->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //3 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d3.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 3 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_13->clear();
    while (query.next()){
        list3 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_13->addItems(list3);
    if (list3.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_13->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //4 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d3.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 4 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_16->clear();
    while (query.next()){
        list4 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_16->addItems(list4);
    if (list4.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_16->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //5 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d3.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 5 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_17->clear();
    while (query.next()){
        list5 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_17->addItems(list5);
    if (list5.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_17->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //Четвертый день недели
    list1.clear();
    list2.clear();
    list3.clear();
    list4.clear();
    list5.clear();
    QDate d4 = d3.addDays(1);
    //1 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d4.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 1 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_19->clear();
    while (query.next()){
        list1 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_19->addItems(list1);
    if (list1.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_19->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //2 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d4.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 2 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_20->clear();
    while (query.next()){
        list2 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_20->addItems(list2);
    if (list2.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_20->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //3 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d4.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 3 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_18->clear();
    while (query.next()){
        list3 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_18->addItems(list3);
    if (list3.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_18->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //4 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d4.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 4 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_21->clear();
    while (query.next()){
        list4 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_21->addItems(list4);
    if (list4.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_21->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //5 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d4.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 5 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_22->clear();
    while (query.next()){
        list5 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_22->addItems(list5);
    if (list5.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_22->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //Пятый день недели
    list1.clear();
    list2.clear();
    list3.clear();
    list4.clear();
    list5.clear();
    QDate d5 = d4.addDays(1);
    //1 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d5.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 1 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_24->clear();
    while (query.next()){
        list1 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_24->addItems(list1);
    if (list1.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_24->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //2 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d5.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 2 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_25->clear();
    while (query.next()){
        list2 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_25->addItems(list2);
    if (list2.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_25->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //3 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d5.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 3 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_23->clear();
    while (query.next()){
        list3 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_23->addItems(list3);
    if (list3.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_23->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //4 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d5.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 4 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_26->clear();
    while (query.next()){
        list4 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_26->addItems(list4);
    if (list4.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_26->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    //5 Пара
    query.exec("SELECT Type_name, Lesson_name, Teacher_name, Cabinet_name FROM Schedule s, Types t, Lessons l, Teachers r, Cabinets c, Groups g WHERE s.Data = \'"+d5.toString("dd.MM.yyyy")+"\' and g.Group_name = \'"+s+"\' and g.Group_id = s.Group_id and s.Time_id = 5 and s.Type_id = t.Type_id and s.Lesson_id = l.Lesson_id and s.Teacher_id = r.Teacher_id and s.Cabinet_id = c.Cabinet_id");
    ui->listWidget_27->clear();
    while (query.next()){
        list5 << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
    }
    ui->listWidget_27->addItems(list5);
    if (list5.isEmpty()==0)
    for (int i = 0; i < 4; i++)
    {
        ui->listWidget_27->item(i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("qt_aql_default_connect");
    QSqlQuery query(db);
    query.prepare("INSERT INTO Schedule (Data, Teacher_id, Lesson_id, Type_id, Cabinet_id, Time_id, Group_id) VALUES (:s1, :s2, :s3, :s4, :s5, :s6, :s7)");
    query.bindValue(":s1", ui->tableWidgetAdd->item(0, 0)->text());
    query.bindValue(":s2", ui->tableWidgetAdd->item(1, 0)->text().toInt());
    query.bindValue(":s3", ui->tableWidgetAdd->item(2, 0)->text().toInt());
    query.bindValue(":s4", ui->tableWidgetAdd->item(3, 0)->text().toInt());
    query.bindValue(":s5", ui->tableWidgetAdd->item(4, 0)->text().toInt());
    query.bindValue(":s6", ui->tableWidgetAdd->item(5, 0)->text().toInt());
    query.bindValue(":s7", ui->tableWidgetAdd->item(6, 0)->text().toInt());

    qDebug() << ui->tableWidgetAdd->item(0, 0)->text() << ui->tableWidgetAdd->item(1, 0)->text().toInt() << ui->tableWidgetAdd->item(2, 0)->text().toInt() << ui->tableWidgetAdd->item(3, 0)->text().toInt();

    bool ok = query.exec();
    if(!ok)
        qDebug() << query.lastError().text();
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->tableViewSTUDY_GROUP->reset();
    ScheduleModel->setTable("Schedule");
    ScheduleModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ScheduleModel->setRelation(2, QSqlRelation("Times", "Time_id", "Time_name"));
    ScheduleModel->setRelation(3, QSqlRelation("Lessons", "Lesson_id", "Lesson_name"));
    ScheduleModel->setRelation(4, QSqlRelation("Types", "Type_id", "Type_name"));
    ScheduleModel->setRelation(5, QSqlRelation("Teachers", "Teacher_id", "Teacher_name"));
    ScheduleModel->setRelation(6, QSqlRelation("Cabinets", "Cabinet_id", "Cabinet_name"));
    ScheduleModel->setRelation(7, QSqlRelation("Groups", "Group_id", "Group_name"));
    ScheduleModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    ScheduleModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Дата"));
    ScheduleModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Время"));
    ScheduleModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Предмет"));
    ScheduleModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Тип занятия"));
    ScheduleModel->setHeaderData(5, Qt::Horizontal, QObject::tr("Преподаватель"));
    ScheduleModel->setHeaderData(6, Qt::Horizontal, QObject::tr("Кабинет"));
    ScheduleModel->setHeaderData(7, Qt::Horizontal, QObject::tr("Группа"));
    ui->tableViewSTUDY_GROUP->verticalHeader()->setVisible(false);
    ScheduleModel->select();

    ui->tableViewSTUDY_GROUP->setModel(ScheduleModel);

    ui->tableViewSTUDY_GROUP->setItemDelegateForColumn(2, new QSqlRelationalDelegate(ui->tableViewSTUDY_GROUP));
    ui->tableViewSTUDY_GROUP->setItemDelegateForColumn(3, new QSqlRelationalDelegate(ui->tableViewSTUDY_GROUP));
    ui->tableViewSTUDY_GROUP->setItemDelegateForColumn(4, new QSqlRelationalDelegate(ui->tableViewSTUDY_GROUP));
    ui->tableViewSTUDY_GROUP->setItemDelegateForColumn(5, new QSqlRelationalDelegate(ui->tableViewSTUDY_GROUP));
    ui->tableViewSTUDY_GROUP->setItemDelegateForColumn(6, new QSqlRelationalDelegate(ui->tableViewSTUDY_GROUP));
    ui->tableViewSTUDY_GROUP->setItemDelegateForColumn(7, new QSqlRelationalDelegate(ui->tableViewSTUDY_GROUP));
    ui->tableViewSTUDY_GROUP->resizeColumnsToContents();
}

void MainWindow::on_pushButton_clicked()
{
    /*bool i = ScheduleModel->submitAll();
    if (i) qDebug() << "Норм";
    else qDebug() << ScheduleModel->lastError();*/


    /*
    QSqlDatabase db = QSqlDatabase::database("qt_aql_default_connect");
    QSqlQuery query(db);
    query.prepare("UPDATE Schedule SET Data = :s1, Teacher_id = :s5, Lesson_id = :s3, Type_id = :s4, Cabinet_id = :s6, Time_id = :s2, Group_id = :s7 WHERE Schedule_id = :s8");
    query.bindValue(":s1", ui->tableWidgetAdd->item(0, 0)->text());
    query.bindValue(":s2", ui->tableWidgetAdd->item(1, 0)->text().toInt());
    query.bindValue(":s3", ui->tableWidgetAdd->item(2, 0)->text().toInt());
    query.bindValue(":s4", ui->tableWidgetAdd->item(3, 0)->text().toInt());
    query.bindValue(":s5", ui->tableWidgetAdd->item(4, 0)->text().toInt());
    query.bindValue(":s6", ui->tableWidgetAdd->item(5, 0)->text().toInt());
    query.bindValue(":s7", ui->tableWidgetAdd->item(6, 0)->text().toInt());

    qDebug() << ui->tableWidgetAdd->item(0, 0)->text() << ui->tableWidgetAdd->item(1, 0)->text().toInt() << ui->tableWidgetAdd->item(2, 0)->text().toInt() << ui->tableWidgetAdd->item(3, 0)->text().toInt();

    bool ok = query.exec();
    if(!ok)
        qDebug() << query.lastError().text();


        */





    /*
    //int i = ui->tableViewSTUDY_GROUP->currentIndex();
    int r = ui->tableViewSTUDY_GROUP->currentIndex().row();

    QSqlDatabase db = QSqlDatabase::database("qt_aql_default_connect");
    QSqlQuery query(db);

    /*query.prepare("UPDATE Schedule SET Data = :s1, Teacher_id = :s5, Lesson_id = :s3, Type_id = :s4, Cabinet_id = :s6, Time_id = :s2, Group_id = :s7 WHERE Schedule_id = :s8");
    query.bindValue(":s1", ui->tableViewSTUDY_GROUP->model()->data(ui->tableViewSTUDY_GROUP->model()->index(r, 1)));
    query.bindValue(":s2", ui->tableViewSTUDY_GROUP->model()->data(ui->tableViewSTUDY_GROUP->model()->index(r, 2)));
    query.bindValue(":s3", ui->tableViewSTUDY_GROUP->model()->data(ui->tableViewSTUDY_GROUP->model()->index(r, 3)));
    query.bindValue(":s4", ui->tableViewSTUDY_GROUP->model()->data(ui->tableViewSTUDY_GROUP->model()->index(r, 4)));
    query.bindValue(":s5", ui->tableViewSTUDY_GROUP->model()->data(ui->tableViewSTUDY_GROUP->model()->index(r, 5)));
    query.bindValue(":s6", ui->tableViewSTUDY_GROUP->model()->data(ui->tableViewSTUDY_GROUP->model()->index(r, 6)));
    query.bindValue(":s7", ui->tableViewSTUDY_GROUP->model()->data(ui->tableViewSTUDY_GROUP->model()->index(r, 7)));
    query.bindValue(":s8", ui->tableViewSTUDY_GROUP->model()->data(ui->tableViewSTUDY_GROUP->model()->index(r, 0)));

    QModelIndex a1 = ui->tableViewSTUDY_GROUP->model()->index(r, 1);
    QModelIndex a2 = ui->tableViewSTUDY_GROUP->model()->data(ui->tableViewSTUDY_GROUP->model()->index(r, 2)).toModelIndex();
    QString a3 = ui->tableViewSTUDY_GROUP->model()->data(ui->tableViewSTUDY_GROUP->model()->index(r, 3)).toString();
    QString a4 = ui->tableViewSTUDY_GROUP->model()->data(ui->tableViewSTUDY_GROUP->model()->index(r, 4)).toString();
    QString a5 = ui->tableViewSTUDY_GROUP->model()->data(ui->tableViewSTUDY_GROUP->model()->index(r, 5)).toString();
    QString a6 = ui->tableViewSTUDY_GROUP->model()->data(ui->tableViewSTUDY_GROUP->model()->index(r, 6)).toString();
    QString a7 = ui->tableViewSTUDY_GROUP->model()->data(ui->tableViewSTUDY_GROUP->model()->index(r, 7)).toString();
    QString a8 = ui->tableViewSTUDY_GROUP->model()->data(ui->tableViewSTUDY_GROUP->model()->index(r, 0)).toString();
    //qDebug() << "UPDATE Schedule SET Data = " << a1 << ", Teacher_id = " << a5 << ", Lesson_id = " << a3 << ", Type_id = " << a4 << ", Cabinet_id = " << a6 << ", Time_id = " << a2 << ", Group_id = " << a7 << " WHERE Schedule_id = " << a8;


    bool ok = query.exec();
    if(!ok)
        qDebug() << query.lastError().text();*/


}

void MainWindow::on_pushButton_6_clicked()
{
    int r = ui->tableViewSTUDY_GROUP->currentIndex().row();
    QSqlDatabase db = QSqlDatabase::database("qt_aql_default_connect");
    QSqlQuery query(db);

    query.prepare("DELETE FROM Schedule WHERE Schedule_id = :s1");
        query.bindValue(":s1", ui->tableViewSTUDY_GROUP->model()->data(ui->tableViewSTUDY_GROUP->model()->index(r, 0)));
        bool ok = query.exec();
        if(!ok)
            qDebug() << query.lastError().text();
}

void MainWindow::on_action_triggered()
{
    ui->tabWidget->setCurrentIndex(1);
    MainWindow::on_pushButton_7_clicked();
}

void MainWindow::on_action_6_triggered()
{
    ui->tabWidget->setCurrentIndex(1);
    MainWindow::on_pushButton_clicked();
}

void MainWindow::on_action_7_triggered()
{
    ui->tabWidget->setCurrentIndex(1);
    MainWindow::on_pushButton_6_clicked();
}

void MainWindow::on_action_2_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
    MainWindow::on_pushButton_Query_clicked();
}

void MainWindow::on_action_3_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
    MainWindow::on_pushButton_2_clicked();
}

void MainWindow::on_action_4_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
    MainWindow::on_pushButton_3_clicked();
}

void MainWindow::on_action_5_triggered()
{
    ui->tabWidget->setCurrentIndex(3);
    MainWindow::on_pushButton_5_clicked();
}
