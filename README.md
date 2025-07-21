# Exam Scheduling System

A simple yet powerful C++ application for scheduling university examinations. This tool automates the process of creating a conflict-free exam timetable, assigning classrooms based on capacity, and generating seating arrangements.

## Features

- **Automated Scheduling:** Uses a graph-coloring algorithm to create a conflict-free exam schedule, ensuring no student has multiple exams in the same time slot.
- **Classroom Assignment:** Intelligently assigns exams to available classrooms based on student enrollment and room capacity.
- **Seating Plan Generation:** Creates and displays a seating arrangement for any given exam, promoting social distancing by placing students at alternating seats.
- **Menu-Driven Interface:** A user-friendly command-line interface makes it easy to navigate and use the different features of the application.
- **Save to CSV:** Allows the user to save the complete, detailed exam schedule to a `exam_schedule.csv` file for easy distribution and reference.
- **Robust Error Handling:** Includes validation for user input and graceful handling of malformed data in the input CSV files.

## File Structure

- `main.cpp`: The entry point of the application, containing the main menu logic.
- `scheduler.h` / `scheduler.cpp`: Manages the core exam scheduling logic, including building the conflict graph and assigning classrooms.
- `seating.h` / `seating.cpp`: Handles the generation and display of seating arrangements.
- `utils.h` / `utils.cpp`: Contains utility functions for parsing CSV files, saving the schedule, and clearing the screen.
- `student.h`, `exam.h`, `classroom.h`: Header files defining the data models for the application.
- `*.csv`: Data files containing information about students, exams, and classrooms.
  - `students.csv`: `Name,EnrollmentNo,Year,Batch`
  - `exam.csv`: `ExamCode,SubjectName,Semester`
  - `classrooms.csv`: `RoomID,SeatsStart,SeatsEnd,Capacity`
- `CMakeLists.txt`: The build configuration file for CMake.

## How to Compile and Run

### Prerequisites

- A C++ compiler that supports C++11 or later (e.g., g++, Clang).

### Using g++

1.  **Open a terminal** in the project's root directory.
2.  **Compile the source files** using the following command:

    ```sh
    g++ -o main main.cpp scheduler.cpp seating.cpp utils.cpp
    ```

3.  **Run the application:**

    ```sh
    ./main
    ```
    (On Windows, you might run `main.exe`)

### Using CMake (Recommended)

If you have CMake installed, you can use it to build the project.

1.  **Create a build directory:**

    ```sh
    mkdir build
    cd build
    ```

2.  **Generate the build files:**

    ```sh
    cmake ..
    ```

3.  **Compile the project:**

    ```sh
    cmake --build .
    ```

4.  **Run the executable** from the `build` directory.
