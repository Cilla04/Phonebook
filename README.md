# 📒 Phonebook in C

> This was an old project from a course in the second semester of the first year of my degree.

## 🧾 Project Description
This university project implements a **Phonebook** in the C programming language. The system allows users to manage personal contacts with features such as search, edit, delete, and save to binary files. It is designed to be modular, readable, and easily extendable.

## 🗂️ Repository Structure
```text
Phonebook/
├── src/              C source code (one .c/.h pair per module)
├── resources/        files the program reads at runtime
│   ├── Interfacce/   text screens, messages and error strings
│   └── Rubrica/      sample phonebook (binary file used by import/export)
├── docs/             design documents (in Italian)
│   └── pseudocodice/ pseudocode of each module
├── Makefile          command-line build
└── .project, .cproject, .settings/   Eclipse CDT project files
```

## 🧩 System Architecture
The project is divided into functional modules:

### 🧠 Types and Structures
- **Rubrica**: array of contacts with current length
- **Contatto**: name, surname, phone number, status
- **Stato**: favorite/blocked
- **File** and **File_Binario**: I/O management
- **Stringa** and **Vettore**: support for text and array operations

### 📂 File Management
- Import and export of the phonebook
- File existence check
- Binary read/write

### 🖥️ Screen Management
- Screen clearing
- Interface, line, message and error printing

### 👤 Contact Management
- Insertion with validation
- Field editing
- Deletion
- Favorite/blocked status management

### 🔍 Search
- Search by name or surname
- Filters: all, favorites only, blocked only
- Result selection and display

### 📊 Sorting
- Sort by name or surname
- Ascending or descending order

### 👁️ Display
- Full, favorites only or blocked only view
- Paginated navigation (max 10 contacts per screen)

### 📋 Main Menu
Text interface with 9 options:
1. Insert new contact  
2. Delete contact  
3. Search contact  
4. Edit contact  
5. Sort phonebook  
6. View phonebook  
7. Manage statuses  
8. Import phonebook  
9. Export phonebook

## ⚙️ Global Constants
- Max/min lengths for name, surname, number
- Max phonebook size: `250`
- Error codes and default messages

## 📦 Requirements
- Language: C (structured pseudocode)
- OS: Windows (the console handling relies on `<windows.h>`)
- Compiler: GCC (for implementation)
- Support files: text interfaces, message and error files

## 🚀 Build and Run

### With `make` (MinGW-w64 / MSYS2 shell)
```bash
make
```
The executable is created in `build/`, together with a copy of `resources/`: the program looks for the `Interfacce/` and `Rubrica/` folders next to the executable. `make clean` removes `build/`.

Then start `build\Rubrica_Telefonica.exe` (double-click, or from `cmd`/PowerShell with that path). The program finds its resource folders starting from the path it was launched with, so run it with its path rather than from inside `build/` by name only.

### With Eclipse CDT
1. *File → Import → Existing Projects into Workspace*, then select the repository folder.
2. Build the project (Debug configuration).
3. Copy the `Interfacce` and `Rubrica` folders from `resources/` into `Debug/`, next to the generated executable.
4. Run it.

## 🧪 Test Cases
The project includes detailed test cases for all operations:
- Valid and invalid input handling
- File existence and error management
- Edge cases for contact insertion, deletion, modification
- Sorting and display logic

## 📚 Documentation
The design documents (in Italian) are in [`docs/`](docs/):
- [Operazioni](docs/Operazioni_Rubrica_Telefonica.pdf): operations allowed by the system
- [Architettura](docs/Architettura_Rubrica_Telefonica.pdf): diagram of how the modules depend on each other
- [Pseudocodice](docs/pseudocodice/): pseudocode of every module, mirroring `src/`
- [Casi di Test](docs/Casi_Di_Test_Rubrica_Telefonica.pdf): test cases for every function (equivalence classes and edge cases)

## 🎓 Educational Purpose
The project was developed to practice:
- Complex data structures
- Code modularization
- Textual and binary I/O management
- User interface design
- Input validation and error handling
