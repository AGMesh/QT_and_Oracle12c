#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QSqlTableModel;
class QSqlRelationalTableModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QStringList list;
    QStringList list1;
    QStringList list2;

    QSqlRelationalTableModel *model1;

    QSqlRelationalTableModel *ScheduleModel;
    QSqlTableModel *TeachersModel;
    QSqlTableModel *LessonsModel;
    QSqlTableModel *TypesModel;
    QSqlTableModel *CabinetsModel;
    QSqlTableModel *TimesModel;
    QSqlTableModel *GroupsModel;

private slots:
    void dbConnect();
    void on_pushButton_Query_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_clicked();
    void on_pushButton_6_clicked();
    void on_action_triggered();
    void on_action_6_triggered();
    void on_action_7_triggered();
    void on_action_2_triggered();
    void on_action_3_triggered();
    void on_action_4_triggered();
    void on_action_5_triggered();
};

#endif // MAINWINDOW_H
