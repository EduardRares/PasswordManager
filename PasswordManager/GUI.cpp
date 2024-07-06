#include "GUI.h"

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    initGUI();
    connectSignals();
    repo = new Repository("accounts.txt");
    srv = new Service(repo);
}

GUI::~GUI()
{}

void GUI::initGUI()
{
    MainWin = new MainWinClass;
    MainWin->setWindowTitle("Password Manager");
    MainWin->setMinimumSize(300, 200);

    AddnewWin = new AddNewWinClass;
    AddnewWin->setMinimumSize(400, 300);

    SearchWin = new SearchWinClass;
    SearchWin->setMinimumSize(400, 300);

    MainWin->show();

}

void GUI::connectSignals()
{
    QObject::connect(MainWin->AddNewBtn, &QPushButton::clicked, [&]() {
        MainWin->hide();
        AddnewWin->show();
        });
    QObject::connect(MainWin->SearchBtn, &QPushButton::clicked, [&]() {
        MainWin->hide();
		SearchWin->show();
		});
    QObject::connect(AddnewWin->GenPasswordBtn, &QPushButton::clicked, [&]() {
		AddnewWin->PasswordEdit->setText(QString::fromStdString(srv->passwordGenerator()));
		});
    QObject::connect(AddnewWin->AddBtn, &QPushButton::clicked, [&]() {
		string domain = AddnewWin->DomainEdit->text().toStdString();
		string username = AddnewWin->UsernameEdit->text().toStdString();
		string password = AddnewWin->PasswordEdit->text().toStdString();
		srv->addAccount(domain, username, password);
        QMessageBox::information(this, "Success", "Account added successfully!");
		AddnewWin->DomainEdit->clear();
		AddnewWin->UsernameEdit->clear();
		AddnewWin->PasswordEdit->clear();
		});
    QObject::connect(SearchWin->ViewAll, &QPushButton::clicked, [&]() {
        SearchWin->reloadList(srv->getAllAccounts());
        });
    QObject::connect(SearchWin->SearchBtn, &QPushButton::clicked, [&]() {
        SearchWin->reloadList(srv->getSpecificAccounts(SearchWin->SearchEdit->text().toStdString()));
        });
    QObject::connect(AddnewWin->back, &QAction::triggered, [&]() {
        AddnewWin->hide();
        MainWin->show();
        });
    QObject::connect(SearchWin->back, &QAction::triggered, [&]() {
        SearchWin->hide();
		MainWin->show();
		});
}

MainWinClass::MainWinClass()
{
    QHBoxLayout* layout_main = new QHBoxLayout;
    this->setLayout(layout_main);
    AddNewBtn = new QPushButton("Add new");
    SearchBtn = new QPushButton("Search");
    AddNewBtn->setMinimumSize(100, 25);
    SearchBtn->setMinimumSize(100, 25);
    layout_main->addStretch();
    layout_main->addWidget(AddNewBtn);
    layout_main->addWidget(SearchBtn);
    layout_main->addStretch();
}

AddNewWinClass::AddNewWinClass()
{
    QGridLayout* layout_add = new QGridLayout;
    this->setLayout(layout_add);

    QMenuBar* menu = new QMenuBar;
    back = new QAction("Back");
    menu->addAction(back);
    this->layout()->setMenuBar(menu);

    DomainEdit = new QLineEdit;
    UsernameEdit = new QLineEdit;
    PasswordEdit = new QLineEdit;
    AddBtn = new QPushButton("Add");
    GenPasswordBtn = new QPushButton();
    QPixmap pixmap("RandomIcon.png");
    QIcon ButtonIcon(pixmap);
    GenPasswordBtn->setIcon(ButtonIcon);

    layout_add->addWidget(new QLabel("URL"), 0, 0);
    layout_add->addWidget(DomainEdit, 0, 1);
    layout_add->addWidget(new QLabel("Username"), 1, 0);
    layout_add->addWidget(UsernameEdit, 1, 1);
    QHBoxLayout* layout_password = new QHBoxLayout;
    layout_password->addWidget(PasswordEdit);
    layout_password->addWidget(GenPasswordBtn);
    layout_add->addWidget(new QLabel("Password"), 2, 0);
    layout_add->addLayout(layout_password, 2, 1, 1, 2);
    layout_add->addWidget(AddBtn, 3, 0, 1, 1);
}

SearchWinClass::SearchWinClass()
{
    QGridLayout* layout_search = new QGridLayout;
    this->setLayout(layout_search);

    QMenuBar* menu = new QMenuBar;
    back = new QAction("Back");
    menu->addAction(back);
    this->layout()->setMenuBar(menu);

    SearchEdit = new QLineEdit;
    SearchBtn = new QPushButton();
    ViewAll = new QPushButton("View all");
    QPixmap pixmap("SearchIcon.png");
    QIcon ButtonIcon(pixmap);
    SearchBtn->setIcon(ButtonIcon);

    layout_search->addWidget(new QLabel("URL"), 0, 0);
    layout_search->addWidget(SearchEdit, 0, 1);
    layout_search->addWidget(SearchBtn, 0, 2, 1, 2);
    layout_search->addWidget(ViewAll, 1, 0, 1, 2);

    table = new MyTableModel;
    tv = new QTableView;
    tv->setModel(table);
}

void SearchWinClass::reloadList(const vector<Account>& acc)
{
    QWidget* win = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;
    win->setLayout(layout);
    layout->addWidget(tv);
    table->setAccount(acc);
    win->show();
    win->setMinimumSize(400, 300);

}

int MyTableModel::rowCount(const QModelIndex&) const {
    return 100;
}

int MyTableModel::columnCount(const QModelIndex&) const {
    return 3;
}


QVariant MyTableModel::data(const QModelIndex& index, int role) const {
    if (index.row() < acc.size()) {
        if (role == Qt::DisplayRole) {
            if (index.column() == 0)
                return QString::fromStdString(acc[index.row()].getDomain());
            if (index.column() == 1)
                return QString::fromStdString(acc[index.row()].getUsername());
            if (index.column() == 2)
                return QString::fromStdString(acc[index.row()].getPassword());
        }
    }
    return QVariant();
}

void MyTableModel::setAccount(const vector<Account>& acc)
{
    this->acc = acc;
    auto topLeft = createIndex(0, 0);
    auto bottomRight = createIndex(rowCount(), columnCount());
    emit dataChanged(topLeft, bottomRight);
}
