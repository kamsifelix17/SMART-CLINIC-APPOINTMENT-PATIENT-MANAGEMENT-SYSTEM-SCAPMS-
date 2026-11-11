========================================================================
SMART CLINIC APPOINTMENT & PATIENT MANAGEMENT SYSTEM (SCAPMS)
========================================================================~

PROJECT OVERVIEW:
This mid-semester lab assessment is a fully functional, event-driven 
C++ desktop application built using the Qt framework (Qt 6.12.0) and CMake. 

KEY FEATURES IMPLEMENTED:
1. Object-Oriented Programming (Phase 1): Utilized abstract base classes 
   and inheritance to model PatientRecords (General, Emergency, FollowUp).
2. Data Structures (Phase 2): Managed records using std::vector and 
   implemented a First-In-First-Out (FIFO) waiting room queue.
3. Custom Searching (Phase 3): Engineered manual Linear and Recursive 
   search engines (bypassing standard libraries).
4. Custom Sorting (Phase 4): Engineered manual Selection Sort and 
   Insertion Sort algorithms for alphabetical and ID-based sorting.
5. Graphical User Interface (Phase 5): Built a comprehensive multi-tab 
   dashboard with layout managers and event-driven signals/slots.
6. Robust Input Validation: Implemented try-catch exception handling 
   for UI data entry fields.
7. File Persistence: Enabled the exportation of the clinic database to 
   a local text file.

INSTRUCTIONS FOR COMPILING (For the Assessor):
1. Ensure MinGW (13.1.0 64-bit) and Qt 6.12.0 are installed.
2. Ensure the CMAKE_PREFIX_PATH in CMakeLists.txt matches your Qt installation.
3. Configure the project using CMake and build the executable.
========================================================================
