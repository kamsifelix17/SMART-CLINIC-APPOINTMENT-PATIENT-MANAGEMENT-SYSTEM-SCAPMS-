#include <QApplication>
#include "controller/gui/MainWindow.h"
#include "ClinicDatabase.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // 1. Initialize the backend engine
    scapms::model::ClinicDatabase database;
    
    // 2. Launch the GUI dashboard, passing the database into it
    scapms::gui::MainWindow window(&database);
    window.show();
    
    return app.exec();
}