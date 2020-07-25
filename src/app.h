#pragma once
#include "./ui_mainwindow.h"
#include "engine.h"
#include <QMainWindow>
#include <fstream>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QProgressDialog>
#ifdef __linux__
#define HOSTS           "/etc/hosts"
#define TIME_MULTIPLIER 0
#elif ifdef _WIN32
#define TIME_MULTIPLIER 400
#define HOSTS           "C:/Windows/System32/drivers/etc/hosts"
#endif
#define VERSION            "3.0.0"
#define CONFIG_FNAME       "custom.txt"
//CONFIG has >CUSTOM, >FILES, >URLS in exactly this order!
#define FILEERRORMSG                                                           \
    "Couldn't process your file! Select another location or launch the app "   \
    "with admin privileges."
#define SPLIT_CHAR '>'

QT_BEGIN_NAMESPACE
namespace Ui {
class App;
} // namespace Ui
QT_END_NAMESPACE

class App : public QMainWindow {
    Q_OBJECT
public:
    App& operator=(const App& ) = delete;
    App(const App& src) = delete;
    explicit App(QWidget* parent = nullptr);
    ~App() override;

public slots:
    void upd_stats(const Stats&); // Updates the stats text field
    void apply_clicked(); //if the user clickss "apply to system"
    void save_to_clicked(); //user clicks "save to..."
    void upd_pending_state();   //updates the availability of the save buttons
    void upd_progress_bar(int); // Sets the value
    void on_engine_ready();
    void engine_failed();
    void del_url_clicked();
    void del_file_clicked();
    void del_custom_clicked();
    void add_custom_clicked(); //adds a new custom entry
    void add_file_clicked(); //adds a new file
    void add_url_clicked(); //adds a new url
    void about_clicked();   // displays about message
//signals:


private:
    void add_url(const QString&);
    void add_file(const QString&); //just adds the file to both lists
    void add_custom(const QString&);
    void msg(const QString& msg); //Displays message in the statusbar
    void sys_load(); //Loads the system hosts file
    void check_and_add_file(const QString& fname); // checks if the file is writable&readable and then calls add_file
    void save_config();                   // Saves the data
    void load_config();                   // Loads user data
    void start_engine(const QString& path); //Starts the engine with the given path

    Engine e; //Background processing
    void closeEvent(QCloseEvent*) override; //Save files before exit
    bool                           sys_loaded = false; //Is the system hosts file loaded
    Ui::App*                ui;
};
