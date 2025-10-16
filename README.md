# Phonebook
This was an old project from a course in the second semester of the first year of my degree

# 📒 Phonebook in C

## 🧾 Project Description
This university project implements a **Phonebook** in the C programming language. The system allows users to manage personal contacts with features such as search, edit, delete, and save to binary files. It is designed to be modular, readable, and easily extendable.

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
- OS: Windows/Linux
- Compiler: GCC (for implementation)
- Support files: text interfaces, message and error files

## 🧪 Test Cases
The project includes detailed test cases for all operations:
- Valid and invalid input handling
- File existence and error management
- Edge cases for contact insertion, deletion, modification
- Sorting and display logic

## 🎓 Educational Purpose
The project was developed to practice:
- Complex data structures
- Code modularization
- Textual and binary I/O management
- User interface design
- Input validation and error handling
