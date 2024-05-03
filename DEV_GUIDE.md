# Build Settings

---

Project Directory Structure:

```bash
project/
│
├── include/
│   ├── UI/
│   └── App/
│   └── lib/
│
├── src/
│   ├── UI/
│   └── App/
│
└── thirdparty/
    └── imgui/
		    .
		    .
```

This is the Visual Studio configuration:

### **Include Directories**

- **`include/UI`**: Contains header files for the UI.
- **`include/App`**: Contains header files for the App.
- **`include/lib`**: Directory for external library `.lib` files.

### **Additional Include Directories**

- **`thirdparty`**: Directory for third-party library header files.
- **`thirdparty/imgui`**: Specific directory for ImGui header files.

### **Source Directories**

- **`src/UI`**: Contains source files for the UI module.
- **`src/App`**: Contains source files for the App module.
- **`src`**: Contains main file.

### **Linker Dependencies**

- **`glfw3.lib`**: Library for handling windows, contexts, and inputs in OpenGL applications.
- **`opengl32.lib`**: Import library for OpenGL API on Windows.
- **/NODEFAULTLIB:MSVCRTD:** instructs the linker to exclude the default MSVC runtime library for the debug configuration (**`MSVCRTD`**) from the linking process.
- **`%(AdditionalDependencies)`**: This placeholder is used to include additional dependencies specified in the project settings. It ensures that any additional libraries specified as dependencies are included in the linking process for the release build.

### **Development Notes**

- Make sure to link against **`glfw3.lib`** and **`opengl32.lib`** in your linker settings to resolve dependencies during compilation.
- The source files should follow a similar directory structure as the include directories, with source files located in the **`src`** directory.
- **`Cpr`** has been installed using the NuGet package manager.
- **`C++17`** is the minimum required version of C++ otherwise `Cpr` will throw a bunch of errors.