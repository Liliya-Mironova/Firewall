#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include <QImage>
#include <QPushButton>
#include <QProcess>
#include <QTextEdit>
#include <QInputDialog>

namespace Ui {
    class widget;
}

class widget : public QMainWindow {
    Q_OBJECT

public:
    explicit widget(QWidget *parent = 0);
    ~widget();
    QMessageBox *message;
    QLabel *label;
    QLabel *label_2;
    QLabel *main_label;
    QLabel *black_label;
    QLabel *white_label;
    QLabel *par_label;
    QLabel *line_label;
    QLabel *mode_label;
    QLabel *logs_label;
    QLineEdit *line;
    QImage *start_page;
    QImage *base_page;
    QImage podgon_2;
    QImage podgon;
    QPushButton *exit_button;
    QPushButton *start_button;
    QPushButton *blacklist_button;
    QPushButton *whitelist_button;
    QPushButton *logs_button;
    QPushButton *about_us;
    QPushButton *get_blacklist;
    QPushButton *get_whitelist;
    QPushButton *remove_blacklist;
    QPushButton *remove_whitelist;
    QPushButton *make_proxy;
    QPushButton *make_server;
    QPushButton *paranioa_level;
    QPushButton *reload_nginx_button;
    //QPushButton *stop_nginx_button;
    QPushButton *is_run_nginx_button;
    QPushButton *change_ms_button;
    QPushButton *clean_log;
    QProcess process;
    QMessageBox *edit;

private:
    Ui::widget *ui;

private slots:
    void want_to_exit();
    void start();
    void exiting();
    void watch_logs();
    void add_in_the_blacklist();
    void add_in_the_whitelist();
    void info();
    void get_blacklist_info();
    void get_whitelist_info();
    void remove_from_blacklist();
    void remove_from_whitelist();
    void make_waf_proxy();
    void make_waf_server();
    void change_paranoia_level();
    void reload_nginx();
    //void stop_nginx();
    void is_run_nginx();
    void change_ms_state();
    void send_request();
    void clean_the_log();
};

#endif // WIDGET_H
