#include <QCalendarWidget>
#include "MainWindow.h"
#include <QMessageBox>
#include <stdexcept>
#include <fstream>
#include "../../GeneralPatient.h"
#include "../SearchEngine.h"
#include "../SortEngine.h"

namespace scapms {
namespace gui {

MainWindow::MainWindow(model::ClinicDatabase* db, QWidget *parent) 
    : QMainWindow(parent), database(db) {
    
    setWindowTitle("Smart Clinic Appointment System (SCAPMS)");
    resize(800, 600);

    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    tabWidget->addTab(createPatientTab(), "Patient Records");
    tabWidget->addTab(createAppointmentTab(), "Appointments");
    tabWidget->addTab(createQueueTab(), "Waiting Queue");
    tabWidget->addTab(createSearchSortTab(), "Search & Sort");
}

MainWindow::~MainWindow() {}

QWidget* MainWindow::createPatientTab() {
    QWidget* tab = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(tab); 
    QFormLayout* formLayout = new QFormLayout(); 
    
    idInput = new QLineEdit();
    nameInput = new QLineEdit();
    ageInput = new QLineEdit();
    
    formLayout->addRow("Patient ID:", idInput);
    formLayout->addRow("Full Name:", nameInput);
    formLayout->addRow("Age:", ageInput);
    
    QPushButton* addButton = new QPushButton("Register Patient");
    QPushButton* saveButton = new QPushButton("Save Database to File");

    patientTable = new QTableWidget(0, 4);
    patientTable->setHorizontalHeaderLabels({"Patient ID", "Full Name", "Age", "Category"});
    patientTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(addButton);
    mainLayout->addWidget(saveButton);
    mainLayout->addWidget(patientTable);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddPatientClicked);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveDatabaseClicked);

    return tab;
}

QWidget* MainWindow::createAppointmentTab() {
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);

    // Creates a form layout for the Patient ID input
    QFormLayout* formLayout = new QFormLayout();
    QLineEdit* appointmentIdInput = new QLineEdit();
    appointmentIdInput->setPlaceholderText("Enter Patient ID...");
    formLayout->addRow("Patient ID:", appointmentIdInput);

    // Keep the Calendar widget
    QCalendarWidget* calendar = new QCalendarWidget();
    calendar->setGridVisible(true);

    QPushButton* bookBtn = new QPushButton("Schedule Appointment for Selected Date");

    // Add elements to the main tab layout
    layout->addLayout(formLayout);
    layout->addWidget(calendar);
    layout->addWidget(bookBtn);

    // Connect the button to schedule the appointment
    connect(bookBtn, &QPushButton::clicked, [this, appointmentIdInput, calendar]() {
        QString patID = appointmentIdInput->text();
        if (patID.isEmpty()) {
             QMessageBox::warning(this, "Missing Input", "Please enter a Patient ID to schedule an appointment.");
             return;
        }

        QString date = calendar->selectedDate().toString("yyyy-MM-dd");
        
        // Using custom linear search to verify the patient exists in the database
        model::PatientRecord* patient = controller::SearchEngine::linearSearchByID(database->getPatients(), patID.toStdString());
        
        if (patient) {
            QString msg = "Appointment successfully scheduled for " + QString::fromStdString(patient->getName()) + " on " + date;
            QMessageBox::information(this, "Appointment Scheduled", msg);
            appointmentIdInput->clear();
        } else {
            QMessageBox::warning(this, "Not Found", "Cannot schedule: No patient found with ID " + patID);
        }
    });

    return tab;
}

QWidget* MainWindow::createQueueTab() {
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QPushButton* callNextBtn = new QPushButton("Call Next Patient (FIFO)");
    queueList = new QListWidget();

    layout->addWidget(callNextBtn);
    layout->addWidget(queueList);

    connect(callNextBtn, &QPushButton::clicked, this, &MainWindow::onCallNextPatientClicked);

    return tab;
}

QWidget* MainWindow::createSearchSortTab() {
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);

    // Search Section
    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchInput = new QLineEdit();
    searchInput->setPlaceholderText("Enter Patient ID or Name...");
    QPushButton* searchBtn = new QPushButton("Search (Linear/Recursive)");
    
    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(searchBtn);

    // Sort Section
    QHBoxLayout* sortLayout = new QHBoxLayout();
    QPushButton* sortNameBtn = new QPushButton("Sort Alphabetically (Selection)");
    QPushButton* sortIDBtn = new QPushButton("Sort by ID (Insertion)");
    
    sortLayout->addWidget(sortNameBtn);
    sortLayout->addWidget(sortIDBtn);

    // Results Table
    searchResultTable = new QTableWidget(0, 4);
    searchResultTable->setHorizontalHeaderLabels({"Patient ID", "Full Name", "Age", "Category"});
    searchResultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    layout->addLayout(searchLayout);
    layout->addLayout(sortLayout);
    layout->addWidget(searchResultTable);

    connect(searchBtn, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
    connect(sortNameBtn, &QPushButton::clicked, this, &MainWindow::onSortByNameClicked);
    connect(sortIDBtn, &QPushButton::clicked, this, &MainWindow::onSortByIDClicked);

    return tab;
}

void MainWindow::onAddPatientClicked() {
    try {
        QString idStr = idInput->text();
        QString nameStr = nameInput->text();
        QString ageStr = ageInput->text();

        if (idStr.isEmpty() || nameStr.isEmpty() || ageStr.isEmpty()) {
            throw std::invalid_argument("Error: All fields must be filled.");
        }

        bool isNumber;
        int age = ageStr.toInt(&isNumber);
        
        if (!isNumber || age < 0 || age > 120) {
            throw std::out_of_range("Error: Patient age must be a valid number between 0 and 120.");
        }

        model::GeneralPatient* newPatient = new model::GeneralPatient(
            idStr.toStdString(), 
            nameStr.toStdString(), 
            age, 
            "N/A"
        );

        database->addPatientRecord(newPatient);
        database->addPatientToQueue(newPatient);

        QMessageBox::information(this, "Success", "Patient registered successfully!");
        idInput->clear();
        nameInput->clear();
        ageInput->clear();
        
        refreshPatientTable();
        refreshQueueList();

    } 
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Input Validation Failed", e.what());
    }
}

void MainWindow::onSearchClicked() {
    QString query = searchInput->text();
    if (query.isEmpty()) return;

    searchResultTable->setRowCount(0);
    
    model::PatientRecord* result = controller::SearchEngine::linearSearchByID(database->getPatients(), query.toStdString());
    
    if (!result) {
         result = controller::SearchEngine::recursiveSearchByName(database->getPatients(), query.toStdString());
    }

    if (result) {
        searchResultTable->insertRow(0);
        searchResultTable->setItem(0, 0, new QTableWidgetItem(QString::fromStdString(result->getPatientID())));
        searchResultTable->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(result->getName())));
        searchResultTable->setItem(0, 2, new QTableWidgetItem(QString::number(result->getAge())));
        searchResultTable->setItem(0, 3, new QTableWidgetItem("Found")); 
    } else {
        QMessageBox::information(this, "Search Result", "No patient found matching that query.");
    }
}

void MainWindow::onSortByNameClicked() {
    // 1. Runs the custom Selection Sort algorithm to organize the backend data
    controller::SortEngine::selectionSortByName(database->getPatientsMutable());
    
    // 2. Clears the table and redraw the newly sorted list
    searchResultTable->setRowCount(0);
    const auto& patients = database->getPatients();
    
    for (int i = 0; i < patients.size(); ++i) {
        searchResultTable->insertRow(i);
        searchResultTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(patients[i]->getPatientID())));
        searchResultTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(patients[i]->getName())));
        searchResultTable->setItem(i, 2, new QTableWidgetItem(QString::number(patients[i]->getAge())));
        searchResultTable->setItem(i, 3, new QTableWidgetItem("Sorted by Name")); 
    }
    
    // 3. Keeps the main Patient Records tab updated too
    refreshPatientTable(); 
}

void MainWindow::onSortByIDClicked() {
    // 1. Runs the custom Insertion Sort algorithm
    controller::SortEngine::insertionSortByID(database->getPatientsMutable());
    
    // 2. Clears the table and redraw the newly sorted list
    searchResultTable->setRowCount(0);
    const auto& patients = database->getPatients();
    
    for (int i = 0; i < patients.size(); ++i) {
        searchResultTable->insertRow(i);
        searchResultTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(patients[i]->getPatientID())));
        searchResultTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(patients[i]->getName())));
        searchResultTable->setItem(i, 2, new QTableWidgetItem(QString::number(patients[i]->getAge())));
        searchResultTable->setItem(i, 3, new QTableWidgetItem("Sorted by ID")); 
    }
    
    refreshPatientTable(); 
}

void MainWindow::refreshPatientTable() {
    patientTable->setRowCount(0);
    const auto& patients = database->getPatients();
    
    for (int i = 0; i < patients.size(); ++i) {
        patientTable->insertRow(i);
        patientTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(patients[i]->getPatientID())));
        patientTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(patients[i]->getName())));
        patientTable->setItem(i, 2, new QTableWidgetItem(QString::number(patients[i]->getAge())));
        patientTable->setItem(i, 3, new QTableWidgetItem("General")); 
    }
}

void MainWindow::onCallNextPatientClicked() {
    // Uses the custom std::queue implementation in ClinicDatabase to call the next patient
    model::PatientRecord* nextPatient = database->callNextPatient();
    
    if (nextPatient) {
        QString msg = "Now serving: " + QString::fromStdString(nextPatient->getName());
        QMessageBox::information(this, "Doctor Available", msg);
        refreshQueueList(); 
    } else {
        QMessageBox::information(this, "Queue Empty", "There are no patients waiting.");
    }
}

void MainWindow::onSaveDatabaseClicked() {
    std::ofstream outFile("clinic_database.txt");
    if (!outFile.is_open()) {
        QMessageBox::critical(this, "Error", "Could not open file for saving.");
        return;
    }

    const auto& patients = database->getPatients();
    outFile << "--- SCAPMS Database Export ---\n";
    for (const auto* patient : patients) {
        outFile << "ID: " << patient->getPatientID() 
                << " | Name: " << patient->getName() 
                << " | Age: " << patient->getAge() << "\n";
    }
    
    outFile.close();
    QMessageBox::information(this, "Saved", "Database exported to clinic_database.txt successfully.");
}

void MainWindow::refreshQueueList() {
    queueList->clear();
    
    int count = database->getPatients().size(); // Simplified for demo purposes
    queueList->addItem(QString("Total patients processed today: %1").arg(count));
    queueList->addItem("Click 'Call Next Patient' to process the First-In-First-Out logic.");
}

} // namespace gui
} // namespace scapms