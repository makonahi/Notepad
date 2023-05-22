#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCursor>
#include <QtWidgets>
#include <QStyleFactory>
#include <QMouseEvent>
#include <QCloseEvent>// библиотека с функциями обработчика закрытия окон
#include <QFileDialog> //библиоетека с диалоговыми окнами
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Menu_Open_triggered();

    void on_Menu_Save_triggered();

    void on_Menu_Save_As_triggered();
    void closeEvent (QCloseEvent *event); // будем изменять обработчик закрытия формы

    void on_Menu__Exit_triggered();

    void on_Menu_Cteate_triggered();


    void on_textEdit_textChanged();
    void to_open();
    void to_save();
    void to_flag_is_0();
    void open_flag();
    void save_without_window();
    void on_Light_triggered();

    void on_Dark_triggered();

private:
    Ui::MainWindow *ui;
    bool message = 1;
    bool flag=1,begin =1;
    bool for_text_change=1;
    bool star = 0;
    QString fileName = "Безымянный";
    QString title(QString filename);
    bool open = 0;
};

#endif // MAINWINDOW_H
