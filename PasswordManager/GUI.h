#pragma once

#include <QWidget>
#include <QListWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QLayout>
#include <QTextBlock>
#include <QTableWidget>
#include <set>
#include <QSlider>
#include <QPainter>
#include <QListView>
#include "ui_GUI.h"
#include "Service.h"
#include "Repository.h"
#include "Domain.h"

class MainWinClass;
class AddNewWinClass;
class SearchWinClass;
class MyTableModel;

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();

private:
    Ui::GUIClass ui;
    MainWinClass* MainWin;
    AddNewWinClass* AddnewWin;
    SearchWinClass* SearchWin;
    QWidget * TableWin;
    Service* srv;
    Repository* repo;
    void initGUI();
    void connectSignals();
};

//start window classes
class MainWinClass : public QWidget {
public:
    MainWinClass();
    ~MainWinClass() = default;
    QPushButton* AddNewBtn, *SearchBtn;
};

//add new account window classes
class AddNewWinClass : public QWidget {
public:
    AddNewWinClass();
    ~AddNewWinClass() = default;
    QPushButton* AddBtn, *GenPasswordBtn;
    QLineEdit* DomainEdit, *UsernameEdit, *PasswordEdit;    
    QAction* back;
};

//search window classes
class SearchWinClass : public QWidget {
public:
    SearchWinClass();
    ~SearchWinClass() = default;
    QLineEdit* SearchEdit;
    QPushButton* SearchBtn, *ViewAll;
    MyTableModel* table;
    QTableView* tv;
    QAction* back;
    void reloadList(const vector<Account>& acc);
};

//table model class
class MyTableModel : public QAbstractTableModel
{
public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    void setAccount(const vector<Account>& acc); 
private:
    vector<Account> acc;
};
