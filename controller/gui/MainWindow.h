#pragma once
#include <QMainWindow>
#include <QTabWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QListWidget>
#include "../../ClinicDatabase.h"
#include "../../controller/SearchEngine.h"
#include "../../controller/SortEngine.h"

namespace scapms {
namespace gui {

class MainWindow : public QMainWindow {
    Q_OBJECT 

public:
    MainWindow(model::ClinicDatabase* db, QWidget *parent = nullptr);
    ~MainWindow();

private:
    model::ClinicDatabase* database;
    QTabWidget* tabWidget;

    // Added: Store pointers to the input fields so our button can read them
    QLineEdit* idInput;
    QLineEdit* nameInput;
    QLineEdit* ageInput;
    QLineEdit* searchInput;
    QTableWidget* searchResultTable;
    QTableWidget* patientTable;

    QListWidget* queueList;

    QWidget* createPatientTab();
    QWidget* createAppointmentTab();
    QWidget* createQueueTab();
    QWidget* createSearchSortTab();

    void refreshPatientTable();
    void refreshQueueList();

private slots:
    void onAddPatientClicked();
    void onSearchClicked();
    void onSortByNameClicked();
    void onSortByIDClicked();
    void onCallNextPatientClicked();
    void onSaveDatabaseClicked();
};

} // namespace gui
} // namespace scapms