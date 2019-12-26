#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>
#include <QIODevice>
#include <QObject>
#include <QTextEdit>
#include <QByteArray>
#include <QInputDialog>
#include <string>
#include <iostream>

std::string TRUNK = "/home/katze/Downloads/Security/";
const char* NGINX_ERROR_LOG = "/opt/nginx-1.13.9/logs/error.log";
const char* NGINX_LISTS_CONF = "/opt/nginx-1.13.9/conf/lists.conf";
std::string SCRIPTS_DIR = TRUNK + "scripts/";
std::string GUI_DIR = TRUNK + "GUI/";
const char* MODSECURITY_CONF = "/usr/src/modsecurity/modsecurity-v3.0.0/modsecurity.conf";

const int START_WIDTH = 400;
const int START_HEIGHT = 380;

const int WEIDTH = 700;
const int HEIGHT = 600;

widget::widget(QWidget *parent) : QMainWindow(parent), ui(new Ui::widget) {
    ui->setupUi(this);
    this->resize(START_WIDTH,START_HEIGHT);
    //this->setWindowFlags(Qt::FramelessWindowHint);

    label = new QLabel(this);
    start_page = new QImage((GUI_DIR + "color.jpg").c_str());
    QImage podgon = start_page->scaled(START_WIDTH,START_HEIGHT,Qt::IgnoreAspectRatio);
    label->resize(START_WIDTH,START_HEIGHT);
    label->setPixmap(QPixmap::fromImage(podgon,Qt::AutoColor));
    label->show();

    main_label = new QLabel(this);
    main_label->setText("Welcome to ModSecurity!");
    main_label->setStyleSheet("font: 22pt;");
    main_label->setGeometry(START_WIDTH*3.5/100,START_HEIGHT*14/100,800,32);
    main_label->show();

    start_button = new QPushButton(this);
    start_button->setText("Start");
    start_button->setGeometry(START_WIDTH*30/100,START_HEIGHT*35/100,150,40);
    start_button->show();

    exit_button = new QPushButton(this);
    exit_button->setText("Exit");
    exit_button->setGeometry(START_WIDTH*30/100,START_HEIGHT*52/100,150,40);
    exit_button->show();

    about_us = new QPushButton(this);
    about_us->setText("About us");
    about_us->setGeometry(START_WIDTH*30/100,START_HEIGHT*69/100,150,40);
    about_us->show();

    connect(start_button,SIGNAL(clicked()),this,SLOT(start()));
    connect(exit_button,SIGNAL(clicked()),this,SLOT(want_to_exit()));
    connect(about_us,SIGNAL(clicked()),this,SLOT(info()));

}

void widget::want_to_exit() {
    message = new QMessageBox();
    message->setStandardButtons(QMessageBox::Cancel|QMessageBox::Yes);
    message->setText("Do you want to turn off the firewall?");
    message->setStyleSheet("font: 12pt;");
    message->show();

    int n = message->exec();
    delete message;
    if (n == QMessageBox::Yes) exiting();
}

void widget::info() {
    message = new QMessageBox();
    message->setStyleSheet("font: 14pt;");
    message->resize(150,150);
    message->setText("Akimov Kirill, 518 gr\nLavrentev Kirill, 514 gr\nMironova Liliya, 518 gr");
    message->setStandardButtons(QMessageBox::Close);
    message->show();
}

void widget::exiting() {
    //nginx stop
    QCoreApplication::exit();
}

void widget::start() {
    // nginx start
    this->resize(WEIDTH,HEIGHT);
    label_2 = new QLabel(this);
    base_page = new QImage((GUI_DIR + "color.jpg").c_str());
    QImage podgon_2 = base_page->scaled(WEIDTH,HEIGHT,Qt::IgnoreAspectRatio);
    label_2->resize(WEIDTH,HEIGHT);
    label_2->setPixmap(QPixmap::fromImage(podgon_2,Qt::AutoColor));
    label->hide();
    label_2->show();


    mode_label = new QLabel(this);
    mode_label->setText("Nginx mode");
    mode_label->setStyleSheet("font: 16pt;");
    mode_label->setGeometry(WEIDTH*7.5/100,HEIGHT*3/100,125,26);
    mode_label->show();

    make_proxy = new QPushButton(this);
    make_proxy->setText("Proxy");
    make_proxy->setGeometry(WEIDTH*6/100,HEIGHT*10/100,75,40);
    make_proxy->show();

    make_server = new QPushButton(this);
    make_server->setText("Server");
    make_server->setGeometry(WEIDTH*16.7/100,HEIGHT*10/100,75,40);
    make_server->show();

    is_run_nginx_button = new QPushButton(this);
    is_run_nginx_button->setText("Check Nginx state");
    is_run_nginx_button->setGeometry(WEIDTH*6/100,HEIGHT*20/100,150,40);
    is_run_nginx_button->show();

    par_label = new QLabel(this);
    par_label->setText("Paranoia");
    par_label->setStyleSheet("font: 16pt;");
    par_label->setGeometry(WEIDTH*10/100,HEIGHT*42/100,126,26);
    par_label->show();

    paranioa_level = new QPushButton(this);
    paranioa_level->setText("Change paranoia level");
    paranioa_level->setGeometry(WEIDTH*6/100,HEIGHT*49/100,150,40);
    paranioa_level->show();

    line_label = new QLabel(this);
    line_label->setText("Test your request:");
    line_label->setStyleSheet("font: 16pt;");
    line_label->setGeometry(WEIDTH*6/100,HEIGHT*63/100,190,28);
    line_label->show();

    line = new QLineEdit(this);
    line->show();
    line->setGeometry(WEIDTH*6/100,HEIGHT*69/100,613,30);

    change_ms_button = new QPushButton(this);
    change_ms_button->setText("Change WAF state");
    change_ms_button->setGeometry(WEIDTH*6/100,HEIGHT*78/100,125,40);
    change_ms_button->show();

    reload_nginx_button = new QPushButton(this);
    reload_nginx_button->setText("Reload nginx");
    reload_nginx_button->setGeometry(WEIDTH*6/100,HEIGHT*88/100,125,38);
    reload_nginx_button->show();


    black_label = new QLabel(this);
    black_label->setText("Blacklist");
    black_label->setStyleSheet("font: 16pt;");
    black_label->setGeometry(WEIDTH*43/100,HEIGHT*3/100,100,20);
    black_label->show();

    get_blacklist = new QPushButton(this);
    get_blacklist->setText("Get blacklist");
    get_blacklist->setGeometry(WEIDTH*39/100,HEIGHT*10/100,150,40);
    get_blacklist->show();

    blacklist_button = new QPushButton(this);
    blacklist_button->setText("Add to the blacklist");
    blacklist_button->setGeometry(WEIDTH*39/100,HEIGHT*20/100,150,40);
    blacklist_button->show();

    remove_blacklist = new QPushButton(this);
    remove_blacklist->setText("Remove from blacklist");
    remove_blacklist->setGeometry(WEIDTH*39/100,HEIGHT*30/100,150,40);
    remove_blacklist->show();


    white_label = new QLabel(this);
    white_label->setText("Whitelist");
    white_label->setStyleSheet("font: 16pt;");
    white_label->setGeometry(WEIDTH*76/100,HEIGHT*3/100,100,20);
    white_label->show();

    get_whitelist = new QPushButton(this);
    get_whitelist->setText("Get whitelist");
    get_whitelist->setGeometry(WEIDTH*72/100,HEIGHT*10/100,150,40);
    get_whitelist->show();
    
    whitelist_button = new QPushButton(this);
    whitelist_button->setText("Add to the whitelist");
    whitelist_button->setGeometry(WEIDTH*72/100,HEIGHT*20/100,150,40);
    whitelist_button->show();

    remove_whitelist = new QPushButton(this);
    remove_whitelist->setText("Remove from whitelist");
    remove_whitelist->setGeometry(WEIDTH*72/100,HEIGHT*30/100,150,40);
    remove_whitelist->show();

    logs_label = new QLabel(this);
    logs_label->setText("Logs:");
    logs_label->setStyleSheet("font: 16pt;");
    logs_label->setGeometry(WEIDTH*79/100,HEIGHT*42/100,100,25);
    logs_label->show();

    logs_button = new QPushButton(this);
    logs_button->setText("Watch logs");
    logs_button->setGeometry(WEIDTH*72/100,HEIGHT*49/100,150,40);
    logs_button->show();

    clean_log = new QPushButton(this);
    clean_log->setText("Clean logs");
    clean_log->setGeometry(WEIDTH*76.5/100,HEIGHT*59/100,90,40);
    clean_log->show();

    exit_button = new QPushButton(this);
    exit_button->setText("Exit");
    exit_button->setGeometry(WEIDTH*83/100,HEIGHT*88/100,80,40);
    exit_button->show();
/*
    stop_nginx_button = new QPushButton(this);
    stop_nginx_button->setText("Stop nginx");
    stop_nginx_button->setGeometry(WEIDTH*15/100,HEIGHT*20/100,150,40);
    stop_nginx_button->show();*/

    connect(exit_button,SIGNAL(clicked()),this,SLOT(want_to_exit()));
    connect(logs_button,SIGNAL(clicked()),this,SLOT(watch_logs()));
    connect(whitelist_button,SIGNAL(clicked()),this,SLOT(add_in_the_whitelist()));
    connect(blacklist_button,SIGNAL(clicked()),this,SLOT(add_in_the_blacklist()));
    connect(get_blacklist,SIGNAL(clicked()),this,SLOT(get_blacklist_info()));
    connect(get_whitelist,SIGNAL(clicked()),this,SLOT(get_whitelist_info()));
    connect(remove_blacklist,SIGNAL(clicked()),this,SLOT(remove_from_blacklist()));
    connect(remove_whitelist,SIGNAL(clicked()),this,SLOT(remove_from_whitelist()));
    connect(make_proxy,SIGNAL(clicked()),this,SLOT(make_waf_proxy()));
    connect(make_server,SIGNAL(clicked()),this,SLOT(make_waf_server()));
    connect(paranioa_level,SIGNAL(clicked()),this,SLOT(change_paranoia_level()));
    connect(reload_nginx_button,SIGNAL(clicked()),this,SLOT(reload_nginx()));
    //connect(stop_nginx_button,SIGNAL(clicked()),this,SLOT(stop_nginx()));
    connect(is_run_nginx_button,SIGNAL(clicked()),this,SLOT(is_run_nginx()));
    connect(change_ms_button,SIGNAL(clicked()),this,SLOT(change_ms_state()));
    connect(line,SIGNAL(returnPressed()),this,SLOT(send_request()));
    connect(clean_log,SIGNAL(clicked()),this,SLOT(clean_the_log()));
}

void widget::reload_nginx() {
    QProcess process;
    process.start((SCRIPTS_DIR + "nginx_reload.sh").c_str(),QStringList());

    if (!process.waitForStarted()||!process.waitForFinished()) return;

    qDebug() << process.readAllStandardError();

    edit = new QMessageBox();
    QByteArray b = process.readAllStandardOutput();
    edit->setText(QString(b));
    edit->setStyleSheet("font: 12pt;");
    edit->show();
}

/*void widget::stop_nginx() {
    QProcess process;
    process.start((SCRIPTS_DIR + "nginx_stop.sh").c_str(),QStringList());

    if (!process.waitForStarted()||!process.waitForFinished()) return;

    qDebug() << process.readAllStandardError();

    edit = new QMessageBox();
    edit->setText("Nginx stopped");
    edit->show();
}*/

void widget::is_run_nginx() {
    QProcess process;
    process.start((SCRIPTS_DIR + "is_run_nginx.sh").c_str(),QStringList());

    if (!process.waitForStarted()||!process.waitForFinished()) return;

     qDebug() << process.readAllStandardError();

     edit = new QMessageBox();
     QByteArray b = process.readAllStandardOutput();
     edit->setText(QString(b));
     edit->setStyleSheet("font: 12pt;");
     edit->show(); 
}

void widget::get_blacklist_info() {
    QProcess process;
    process.start((SCRIPTS_DIR + "list.sh").c_str(),QStringList() << NGINX_LISTS_CONF << "--get-black");

    if (!process.waitForStarted()||!process.waitForFinished()) return;

     qDebug() << process.readAllStandardError();

     edit = new QMessageBox();
     QByteArray b = process.readAllStandardOutput();
     edit->setText(QString(b));
     edit->setStyleSheet("font: 12pt;");
     edit->show();
}

void widget::get_whitelist_info() {
    QProcess process;
    process.start((SCRIPTS_DIR + "list.sh").c_str(),QStringList() << NGINX_LISTS_CONF << "--get-white");

    if (!process.waitForStarted()||!process.waitForFinished()) return;

     qDebug() << process.readAllStandardError();

     edit = new QMessageBox();
     QByteArray b = process.readAllStandardOutput();
     edit->setText(QString(b));
     edit->setStyleSheet("font: 12pt;");
     edit->show();
}

void widget::watch_logs() {
    QProcess process;
    process.start((SCRIPTS_DIR + "log.sh").c_str(),QStringList() << NGINX_ERROR_LOG << "-n" << "10");

    if (!process.waitForStarted()||!process.waitForFinished()) return;

    qDebug() << process.readAllStandardError();

    edit = new QMessageBox();
    QByteArray b = process.readAllStandardOutput();
    edit->setText(QString(b));
    edit->setStyleSheet("font: 11pt;");
    edit->show();
}

void widget::add_in_the_blacklist() {
    QProcess process;

    bool bOk;
    QString str = QInputDialog::getText(0,"Input","IP-address",QLineEdit::Normal,"0.0.0.0",&bOk);

    if (bOk) {
        process.start((SCRIPTS_DIR + "list.sh").c_str(),QStringList() << NGINX_LISTS_CONF << "--add-black" << QString(str));

        if (!process.waitForStarted()||!process.waitForFinished()) return;

        qDebug() << process.readAllStandardError();

        edit = new QMessageBox();
        edit->setText("IP-address added to the blacklist");
        edit->setStyleSheet("font: 12pt;");
        edit->show();
    }

}

void widget::add_in_the_whitelist() {
    QProcess process;

    bool bOk;
    QString str = QInputDialog::getText(0,"Input","IP-address",QLineEdit::Normal,"0.0.0.0",&bOk);

    if (bOk) {
        process.start((SCRIPTS_DIR + "list.sh").c_str(),QStringList() << NGINX_LISTS_CONF << "--add-white" << QString(str));

        if (!process.waitForStarted()||!process.waitForFinished()) return;

        qDebug() << process.readAllStandardError();

        edit = new QMessageBox();
        edit->setText("IP-address added to the whitelist");
        edit->setStyleSheet("font: 12pt;");
        edit->show();
    }
}

void widget::remove_from_blacklist() {
    QProcess process;

    bool bOk;
    QString str = QInputDialog::getText(0,"Input","IP-address",QLineEdit::Normal,"0.0.0.0",&bOk);

    if (bOk) {
        process.start((SCRIPTS_DIR + "list.sh").c_str(),QStringList() << NGINX_LISTS_CONF << "--rm-black" << QString(str));

        if (!process.waitForStarted()||!process.waitForFinished()) return;

        qDebug() << process.readAllStandardError();

        edit = new QMessageBox();
        QByteArray b = process.readAllStandardOutput();
        edit->setText(QString(b));
        edit->setStyleSheet("font: 12pt;");
        edit->show();
    }
}

void widget::remove_from_whitelist() {
    QProcess process;

    bool bOk;
    QString str = QInputDialog::getText(0,"Input","IP-address",QLineEdit::Normal,"0.0.0.0",&bOk);

    if (bOk) {
        process.start((SCRIPTS_DIR + "list.sh").c_str(),QStringList() << NGINX_LISTS_CONF << "--rm-white" << QString(str));

        if (!process.waitForStarted()||!process.waitForFinished()) return;
        qDebug() << process.readAllStandardError();

        edit = new QMessageBox();
        QByteArray b = process.readAllStandardOutput();
        edit->setText(QString(b));
        edit->setStyleSheet("font: 12pt;");
        edit->show();
    }
}

void widget::make_waf_proxy() {
    QProcess process;

    bool bOk;
    QString str = QInputDialog::getText(0,"Input","IP-address",QLineEdit::Normal,"0.0.0.0",&bOk);

    if (bOk) {
        process.start("/home/katze/Downloads/Security/scripts/mode.sh",QStringList() << "--add-prox" << "--ip" << QString(str));

        if (!process.waitForStarted()||!process.waitForFinished()) return;

        qDebug() << process.readAllStandardError();

        edit = new QMessageBox();
        QByteArray b = process.readAllStandardOutput();
        edit->setText(QString(b));
        edit->setStyleSheet("font: 12pt;");
        edit->show();
    }   
}

void widget::make_waf_server() {
    QProcess process;

    process.start("/home/katze/Downloads/Security/scripts/mode.sh",QStringList() << "--add-serv");

    if (!process.waitForStarted()||!process.waitForFinished()) return;

    qDebug() << process.readAllStandardError();

    edit = new QMessageBox();
    QByteArray b = process.readAllStandardOutput();
    edit->setText(QString(b));
    edit->setStyleSheet("font: 12pt;");
    edit->show();
}

void widget::change_paranoia_level() {
    QProcess process;

    bool bOk;
    QString str = QInputDialog::getText(0,"Input","Paranoia level",QLineEdit::Normal,"0",&bOk);

    if (bOk) {
        process.start("/home/katze/Downloads/Security/scripts/par.sh",QStringList() << MODSECURITY_CONF << "--paranoia" << QString(str));

        if (!process.waitForStarted()||!process.waitForFinished()) return;

        qDebug() << process.readAllStandardError();

        edit = new QMessageBox();
        QByteArray b = process.readAllStandardOutput();
        edit->setText(QString(b));
        edit->setStyleSheet("font: 12pt;");
        edit->show();
    }
}

void widget::change_ms_state() {
    QProcess process;
    process.start((SCRIPTS_DIR + "modsecurity_change_state.sh").c_str(),QStringList());

    if (!process.waitForStarted()||!process.waitForFinished()) return;

    qDebug() << process.readAllStandardError();

    edit = new QMessageBox();
    QByteArray b = process.readAllStandardOutput();
    edit->setText(QString(b));
    edit->setStyleSheet("font: 12pt;");
    edit->show();
}

void widget::send_request() {
    QProcess process;
    process.start((SCRIPTS_DIR + "send_request.sh").c_str(),QStringList() << "--request" << line->text());
    line->setText("");

    if (!process.waitForStarted()||!process.waitForFinished()) return;

    qDebug() << process.readAllStandardError();

    edit = new QMessageBox();
    QByteArray b = process.readAllStandardOutput();
    edit->setText(QString(b));
    edit->setStyleSheet("font: 12pt;");
    edit->show();
}

void widget::clean_the_log() {
    QProcess process;
    process.start((SCRIPTS_DIR + "clean_log.sh").c_str(),QStringList() << NGINX_ERROR_LOG);

    if (!process.waitForStarted()||!process.waitForFinished()) return;

    qDebug() << process.readAllStandardError();

    edit = new QMessageBox();
    QByteArray b = process.readAllStandardOutput();
    edit->setText(QString(b));
    edit->setStyleSheet("font: 12pt;");
    edit->show();
}

widget::~widget() {
    delete ui;
}
