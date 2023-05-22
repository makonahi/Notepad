#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Безымянный - блокнот");
    QString fileName = "Безымянный";
    this-> setCentralWidget((ui-> textEdit));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Menu_Open_triggered() //меню открыть
{
    QString name = title(fileName);
    name = "*"+ title(fileName);
    //QString strokaadres;
    //strokaadres = "C:/Users/student.GIS/Documents/" + fileName;

    if (flag ==0 && name.contains(".txt"))
    {
        open_flag();
    }
    else if (flag ==1 && name.contains(".txt"))
    {
        to_open();
    }
    else if (flag == 0 && name.contains(".txt") ==0)
    {
        open_flag();
    }
    else if (flag == 1 && name.contains(".txt") ==0)
    {
        to_open();
    }

    //        flag =1;

}

void MainWindow::on_Menu_Save_triggered() //меню сохранить
{
    if (flag ==0 && fileName.contains(".txt"))
    {
        if (fileName.isEmpty()) //файл не выбран
        {
            return;
        }
        else {
            flag = 1;
            QFile file; //класс файлов
            file.setFileName(fileName);
            file.open(QIODevice::WriteOnly);// открываем только на запись
            file.write (ui-> textEdit-> toPlainText().toUtf8()); //запись в файл через цепочку преобразований
            file.close();// закрываем файл
            QWidget::setWindowTitle(title(fileName));


        }
    }
    else if (flag ==0 && fileName.contains(".txt") == 0){
        to_save();
    }
}

void MainWindow::on_Menu_Save_As_triggered() // сохранить как
{
    QString fileName2 = fileName;
    QString strokaadres;
    strokaadres = "C:\\Users\\student\\Documents\\" + fileName2;

    fileName= QFileDialog::getSaveFileName(this, tr ("Сохранить файл как"),strokaadres, tr("Text files (*.txt)"));

    if (fileName.isEmpty()) //файл не выбран{
    {

        fileName = fileName2;
        return;
    }
    else {
        //        fileName= QFileDialog::getSaveFileName(this, tr ("Сохранить как файл"),"C:\\Users\\student\\Documents" , tr("Text files (*.txt)"));

        flag = 1;
        QFile file; //класс файлов
        file.setFileName(fileName);
        file.open(QIODevice::WriteOnly);// открываем только на запись
        file.write (ui-> textEdit-> toPlainText().toUtf8()); //запись в файл через цепочку преобразований
        file.close();// закрываем файл
        QWidget::setWindowTitle(title(fileName));
    }
}

void MainWindow::closeEvent(QCloseEvent *event)//обработчик закрытия окон
{

    if (flag == 0 && fileName.contains(".txt")==0)
    {
        QString quest = "Вы хотите сохранить изменения в файле "  "\"" + fileName + "\"" +"?";
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Блокнот",quest , QMessageBox::Yes|QMessageBox::No|QMessageBox::Close);
        if (reply == QMessageBox::Yes)

        {
            QString fileName2 = fileName;
            //строка для имени файла
            //1 вариант экранихировать слэши - Windows style
            QString strokaadres;
            strokaadres = "C:\\Users\\student\\Documents\\" + fileName2;
            fileName= QFileDialog::getSaveFileName(this, tr ("Сохранить файл"),strokaadres, tr("Text files (*.txt)"));

            if (fileName.isEmpty()) //файл не выбран{
            {
                fileName = fileName2;
                event-> ignore();// игнорируем сигнал
                return;
            }
            else {

                QFile file; //класс файлов
                file.setFileName(fileName);
                flag =1;
                file.open(QIODevice::WriteOnly);// открываем только на запись
                file.write (ui-> textEdit-> toPlainText().toUtf8()); //запись в файл через цепочку преобразований
                file.close();// закрываем файл
                QWidget::setWindowTitle(title(fileName));

            }
            event-> accept();// принимаем сигнал
        }
        else  if (reply == QMessageBox::No) {
            event-> accept();// принимаем сигнал
        }
        else{
            event-> ignore();// игнорируем сигнал
        }
    }
    else if (flag == 0 && fileName.contains(".txt"))
    {
        QString quest = "Вы хотите сохранить изменения в файле "  "\"" + fileName + "\"" +"?";
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Блокнот",quest , QMessageBox::Yes|QMessageBox::No|QMessageBox::Close);
        if (reply == QMessageBox::Yes)
        {
            save_without_window();
            event-> accept();// принимаем сигнал
        }
        else  if (reply == QMessageBox::No) {
            event-> accept();// принимаем сигнал
        }
        else{
            event-> ignore();// игнорируем сигнал
        }
    }
    else
        event-> accept();// принимаем сигнал

}

/*
1. Доделать остальные пункты
2. Сделать привязку поля текста к размерам окна
3. Имя файла в заголовке окна
4. Работа с русскими буквами
5. Проверки на сохранение изменений (не забываем * у имени)
 */

void MainWindow::on_Menu__Exit_triggered() // выход через файл
{
    close();
}

void MainWindow::on_Menu_Cteate_triggered()// создать
{
    QString name = title(fileName);
    name = "*"+ title(fileName);

    if (flag ==0 && name.contains(".txt"))
    {
        QString quest = "Вы хотите сохранить изменения в файле "  "\"" + fileName + "\"" +"?";
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Блокнот",quest , QMessageBox::Yes|QMessageBox::No|QMessageBox::Close);
        if (reply == QMessageBox::Yes)
        {
            save_without_window();
            ui->textEdit->clear();
            fileName = "Безымянный";
            QString name = title(fileName);
            name = "*"+ title(fileName);
            QWidget::setWindowTitle(title(fileName));
            flag = 1;
        }
        else  if (reply == QMessageBox::No) {
            ui->textEdit->clear();
            fileName = "Безымянный";
            QString name = title(fileName);
            name = "*"+ title(fileName);
            QWidget::setWindowTitle(title(fileName));
            flag = 1;
        }

        //                ui->textEdit->clear();
        //                fileName = "Безымянный";
        //                QWidget::setWindowTitle(title(fileName));
    }
    else if (flag ==1 && name.contains(".txt"))
    {
        ui->textEdit->clear();
        fileName = "Безымянный";
        QString name = title(fileName);
        name = "*"+ title(fileName);
        QWidget::setWindowTitle(title(fileName));
        flag = 1;
    }
    else if (flag == 0 && name.contains(".txt") ==0)
    {
        to_flag_is_0();

    }

    else if (flag == 1 && name.contains(".txt") ==0)
    {
        ui->textEdit->clear();
        fileName = "Безымянный";
        QString name = title(fileName);
        name = "*"+ title(fileName);
        QWidget::setWindowTitle(title(fileName));
        flag = 1;
    }
    if (name.contains(".txt") ==0 && ui->textEdit->toPlainText().size() == 0)
    {
        fileName = "Безымянный";
        QWidget::setWindowTitle("Безымянный - блокнот");
        flag = 1;
    }
    //    flag = 1;



}

QString MainWindow:: title(QString filename) // сделать название
{
    if (filename.contains("/"))
    {
        int len = filename.size();
        int x = filename.lastIndexOf("/");
        QString file_mormal_name = filename.right(len-x-1);
        return file_mormal_name;
    }
    else {
        return "Безымянный - блокнот";
    }
}

void MainWindow::on_textEdit_textChanged() // для звездочки
{
    QString name = title(fileName);
    name = "*"+ title(fileName);
    if (fileName.isEmpty()) //файл не выбран
    {
        //        flag =1;
        return;
    }
    flag = 0;
    if (flag ==0 && name.contains(".txt"))
    {
        QWidget::setWindowTitle(name);
    }
    else if (flag ==1 && name.contains(".txt"))
        QWidget::setWindowTitle(title(fileName));
    else if (flag == 0 && name.contains(".txt") ==0)
        QWidget::setWindowTitle("*Безымянный - блокнот");


    else if (flag == 1 && name.contains(".txt") ==0)
        QWidget::setWindowTitle("Безымянный - блокнот");
    if (name.contains(".txt") ==0 && ui->textEdit->toPlainText().size() == 0)
    {
        QWidget::setWindowTitle("Безымянный - блокнот");
        flag =1;
    }


    //        if(ui->textEdit->toPlainText().size() == 0)
    //        {
    //            QWidget::setWindowTitle("Безымянный - блокнот");
    //            flag =1;
    //        }
    //        else if (ui->textEdit->toPlainText().size() != 0)
    //        {
    //            QWidget::setWindowTitle("*Безымянный - блокнот");
    //            flag =0;
    //        }
    //        else {
    //            QWidget::setWindowTitle(title (fileName));
    //        }

    //    if (flag ==0)
    //    {
    //            QWidget::setWindowTitle(name);
    //    }
    //    else
    //            QWidget::setWindowTitle(title (fileName));

    //        if(ui->textEdit->toPlainText().size() == 0)
    //        {
    //            QWidget::setWindowTitle("Безымянный - блокнот");
    //            flag =1;
    //        }
    //        else
    //        {
    //            QWidget::setWindowTitle("*Безымянный - блокнот");
    //            flag =0;
    //        }



}

void MainWindow:: to_open() //функция открыть
{
    QString fileName2 = fileName;QString strokaadres;
    strokaadres = "C:\\Users\\student\\Documents\\" + fileName2;
    fileName= QFileDialog::getOpenFileName(this, tr ("Открыть файл"),strokaadres , tr("Text files (*.txt)"));
    QString name = title(fileName);

    //    flag=1;
    if (fileName.isEmpty()) //файл не выбран
    {
        fileName = fileName2;
        return;
    }
    else {
        flag = 1;
        ui->textEdit->clear();
        QFile file; //класс файлов
        file.setFileName(fileName);

        file.open(QIODevice::ReadOnly);// открываем только на чтение
        QByteArray ba; // массив для передачи данных
        ba.clear();
        long long int size;
        size = file.size(); // получаем размер файла
        ba = file.read(size); //чтение файла
        ui-> textEdit-> append(QString(ba));//  копируем в оле редактора
        file.close();// закрываем файл
        QWidget::setWindowTitle(title(fileName));
    }

    flag = 1;
}

void MainWindow:: to_save()// функция сохранить
{
    QString fileName2 = fileName;
    //строка для имени файла
    //1 вариант экранихировать слэши - Windows style
    //QString strokaadres;
    //strokaadres = "C:\\Users\\student\\Documents\\" + fileName2; решил не менять пока
    fileName= QFileDialog::getSaveFileName(this, tr ("Сохранить файл"),"C:\\Users\\student\\Documents\\", tr("Text files (*.txt)"));

    if (fileName.isEmpty()) //файл не выбран{
    {
        fileName = fileName2;
        return;
    }
    else {

        QFile file; //класс файлов
        file.setFileName(fileName);
        flag =1;
        file.open(QIODevice::WriteOnly);// открываем только на запись
        file.write (ui-> textEdit-> toPlainText().toUtf8()); //запись в файл через цепочку преобразований
        file.close();// закрываем файл
        QWidget::setWindowTitle(title(fileName));

    }
}

void MainWindow:: to_flag_is_0()
{
    QString fileName2 = fileName;
    QString quest = "Вы хотите сохранить изменения в файле "  +fileName +"?";
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Блокнот",quest , QMessageBox::Yes|QMessageBox::No|QMessageBox::Close);

    if (reply == QMessageBox::Yes)
    {


        if (fileName.isEmpty()) //файл не выбран{
        {
            fileName = fileName2;
            return;
        }
        else {
            QString fileName; //строка для имени файла
            QString strokaadres;
            strokaadres = "C:\\Users\\student\\Documents\\" + fileName2;
            fileName = QFileDialog::getSaveFileName(this, tr ("Создать файл"),strokaadres , tr("Text files (*.txt)"));

            if (fileName.isEmpty()) //файл не выбран{
            {
                fileName = fileName2;
                return;
            }
            QFile file; //класс файлов
            file.setFileName(fileName);
            flag = 1;
            file.open(QIODevice::WriteOnly);// открываем только на запись
            file.write (ui-> textEdit-> toPlainText().toUtf8()); //запись в файл через цепочку преобразований
            file.close();// закрываем файл
            ui->textEdit->clear();
            fileName = "Безымянный";
            QWidget::setWindowTitle("Безымянный - блокнот");
        }


    }
    else if (reply == QMessageBox::No)
    {
        flag = 1;
        ui->textEdit->clear();
        fileName = "Безымянный";
        QWidget::setWindowTitle(title(fileName));

    }

    //        else {
    //                flag =1 ;
    //            fileName = "Безымянный";
    //            QWidget::setWindowTitle("Безымянный - блокнот");
    //        }
}

void MainWindow:: open_flag()
{
    QString quest = "Вы хотите сохранить изменения в файле "  "\"" + fileName + "\"" +"?";
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Блокнот",quest , QMessageBox::Yes|QMessageBox::No|QMessageBox::Close);
    if (reply == QMessageBox::Yes)
    {
        QString fileName2 = fileName;
        QString strokaadres;
        strokaadres = "C:\\Users\\student\\Documents\\" + fileName2;
        fileName = QFileDialog::getSaveFileName(this, tr ("Создать файл"),strokaadres , tr("Text files (*.txt)"));
        //        flag=1;

        if (fileName.isEmpty()) //файл не выбран{
        {
            fileName = fileName2;
            return;
        }
        else {

            QFile file; //класс файлов
            file.setFileName(fileName);
            flag=1;
            file.open(QIODevice::WriteOnly);// открываем только на запись
            file.write (ui-> textEdit-> toPlainText().toUtf8()); //запись в файл через цепочку преобразований
            file.close();// закрываем файл
            QWidget::setWindowTitle(title(fileName));
            to_open();
        }
    }
    else if (reply == QMessageBox::No)
    {
        flag=1;
        to_open();
    }


}

void MainWindow:: save_without_window()
{
    flag = 1;
    QFile file; //класс файлов
    file.setFileName(fileName);
    file.open(QIODevice::WriteOnly);// открываем только на запись
    file.write (ui-> textEdit-> toPlainText().toUtf8()); //запись в файл через цепочку преобразований
    file.close();// закрываем файл
    QWidget::setWindowTitle(title(fileName));
}

void MainWindow::on_Light_triggered()
{
    qApp->setPalette(this->style()->standardPalette());
}

void MainWindow::on_Dark_triggered()
{
    // Создаём палитру для тёмной темы оформления
    QPalette darkPalette;

    // Настраиваем палитру для цветовых ролей элементов интерфейса
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    // Устанавливаем данную палитру
    qApp->setPalette(darkPalette);
}
