# Student Record System (C++17)

A high-performance command-line interface (CLI) for managing academic profiles. This project features a custom-built persistence layer, robust **CRUD (Create, Read, Update, Delete)** operations, and defensive memory management.

---

## 🚀 Key Engineering Features
* **Persistent CRUD Engine**: Architected a complete lifecycle management system capable of Creating, Reading, Updating, and Deleting records with $O(1)$ lookup time for ID-based retrieval.
* **Custom Serialization Protocol**: Engineered a manual CSV parser with **quoted-field support** and **escape sequence handling**, ensuring data integrity even when fields contain delimiters (e.g., complex course lists).
* **Defensive I/O Architecture**: Utilized `std::filesystem` to automatically manage directory structures (`data/`) and `std::numeric_limits` for safe input stream flushing, preventing runtime crashes during invalid user entry.
* **Optimized Search Logic**: Implemented vector-based traversal for partial matching (e.g., "Search by Last Name") while maintaining pointer safety to avoid dangling references.

---

## 🛡 Security & Defensive Design
* **Input Sanitization**: Centralized all user interaction within an `Input` header, enforcing strict type checking (`isDigitsOnly`) and range validation before data ever touches the core business logic.
* **Memory Safety**: Utilized **const-correctness** throughout the `StudentDatabase` API to protect internal state, returning `const Student*` pointers to prevent unauthorized modification of cached data.
* **Exception Resilience**: Wrapped string conversions (`std::stoi`, `std::stod`) in `try-catch` blocks during file loading to ensure the application recovers gracefully from corrupted external data files.

---

## 🛠 Tech Stack
| Category | Technologies |
| :--- | :--- |
| **Language** | C++17 |
| **Data Structures** | Vectors, String Streams, Structs |
| **Systems Programming** | File I/O (`<fstream>`), Filesystem API |
| **Build System** | CMake |
| **Development Tools** | CLion / Git / VS Code |

---

## 📂 Project Structure
```text
student-record-system/
├── src/
│   ├── main.cpp              # CLI Controller & Event Loop
│   ├── Student.h/cpp         # Data Model & Profile Logic
│   ├── StudentDatabase.h/cpp # Persistence & CRUD Implementation
│   ├── Input.h               # Input Validation Namespace
├── data/
│   └── .gitkeep              # Data persistence folder
├── CMakeLists.txt            # Build Configuration
├── .gitignore                # Version Control Optimization
```

## 🚀 Build & Run
Ensure you have **CMake 3.20+** and a **C++17** compatible compiler installed.

### 1. Configure and Build
```bash
# Generate build files
cmake -S . -B build

# Compile the project
cmake --build build
```

### 2. Execute the Application
```bash
# Run the binary
./build/student_record_system
