## 📁 Project Structure

The project follows a modular structure, with code organized into:

- `src/` – Contains all `.cpp` source files  
- `include/` – Contains all `.h` header files  

This separation improves clarity, supports easier debugging, and ensures better scalability and maintenance.

---

## 🔧 How to Run (Header + Source Structure)

1. Clone this repository.
2. Open the project in **VS Code** with the **PlatformIO** extension installed.
3. Ensure the following lines are included in your `platformio.ini`:
   ```ini
   src_dir = src
   include_dir = include
