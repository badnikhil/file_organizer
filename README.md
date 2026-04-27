#  File Organizer

A lightweight, efficient command-line utility written in C that organizes clutter in your directories by moving files into subfolders based on their file extensions.

##  Features

- **Blazing Fast**: Uses `uthash` for O(1) extension lookup.
- **Automatic Sorting**: Automatically categorizes files into common folders like `Documents`, `Images`, `Videos`, and `Code`.
- **Configurable**: Use a `config.ini` file to customize extension-to-folder mappings without recompiling.
- **Cross-Platform**: Runs on Linux and 64-bit Windows 10/11.
- **Lightweight**: No external runtime dependencies, minimal memory footprint.

##  Supported Extensions

Currently, the organizer supports the following mappings out-of-the-box:

| Category | Extensions |
| :--- | :--- |
| **Documents** | `.pdf`, `.docx`, `.doc`, `.txt`, `.pptx`, `.ppt`, `.xlsx`, `.xls`, `.csv`, `.json`, `.yaml`, `.xml`, `.epub`, `.mobi`, `.ttf`, `.woff`, `.otf` |
| **Images** | `.jpg`, `.jpeg`, `.png`, `.gif`, `.svg`, `.webp`, `.bmp`, `.ico`, `.tiff`, `.tif`, `.eps` |
| **Videos** | `.mp4`, `.mkv`, `.avi`, `.mov`, `.wmv`, `.flv`, `.webm`, `.m4v` |
| **Music** | `.mp3`, `.wav`, `.flac`, `.m4a`, `.ogg`, `.aac`, `.wma` |
| **Code** | `.c`, `.cpp`, `.h`, `.py`, `.js`, `.ts`, `.java`, `.go`, `.rs`, `.php`, `.html`, `.css`, `.sql` |
| **Archives** | `.zip`, `.tar`, `.rar`, `.7z`, `.gz`, `.bz2`, `.iso`, `.dmg` |
| **Executables** | `.exe`, `.sh`, `.bat`, `.msi` |

##  Project Structure

- `main.c`: Entry point and command-line argument handling.
- `file_utils.c`: Handles directory traversal and file movement.
- `hashmap_services.c`: Manages the extension-to-folder mapping using `uthash`.
- `extensions.c`: Defines the default list of extensions and their target folders.
- `include.h`: Header file containing constants and struct definitions.
- `compile`: A script to compile the project.

##  Prerequisites

- **Linux**: GCC and CMake
- **Windows (cross-compile from Linux)**: `mingw-w64` — install with:
  ```bash
  sudo apt install mingw-w64
  ```

## Building the Project

### Linux

```bash
mkdir build && cd build
cmake -S .. -B .
make
```

This produces `file_organizer` in the project root.

### Windows (cross-compile from Linux)

```bash
cmake -B build-win -DCMAKE_TOOLCHAIN_FILE=mingw-toolchain.cmake
cmake --build build-win
```

This produces `file_organizer.exe` in the project root.

## 📖 Usage

```
file_organizer [-c <config_path>] <target_directory>
```

### Linux

```bash
# Organize a folder using auto-detected config
./file_organizer ~/Downloads

# Organize using a custom config file
./file_organizer -c ~/myconfig.ini ~/Downloads

# Organize current directory
./file_organizer .
```

### Windows (Command Prompt)

```cmd
:: Organize your Downloads folder
file_organizer.exe %USERPROFILE%\Downloads

:: Organize using a custom config
file_organizer.exe -c C:\path\to\config.ini %USERPROFILE%\Downloads

:: Easiest — open CMD inside the folder you want to organize, (also paste the config there for customizing things) then:
file_organizer.exe .
```
(for paths you can just drag and drop files / folders)
> **Tip (Windows):** You can also drag and drop a folder onto `file_organizer.exe` in Explorer to organize it without opening a terminal.

### Example

Given a folder with:
- `report.pdf`
- `vacation.jpg`
- `main.c`

After running, it becomes:
- `Documents/report.pdf`
- `Images/vacation.jpg`
- `Code/main.c`

## ⚙️ Configuration

The organizer looks for a `config.ini` file in this order:
1. Same directory as the executable
2. `~/.config/file-organizer/config.ini` (Linux) / `%USERPROFILE%\.config\file-organizer\config.ini` (Windows)
3. Built-in defaults (if no config file is found)

You can also pass a config explicitly with the `-c` flag.

### Config Format

Each line maps a folder name to a comma-separated list of extensions:

```ini
Documents: docx,doc,pdf,txt,pptx,xlsx,csv
Images: jpg,jpeg,png,gif,svg,bmp
Videos: mp4,mkv,avi,mov
Music: mp3,wav,flac,ogg
Code: c,cpp,h,py,js,ts
Archives: zip,tar,rar,7z,gz
```

##  How to Add More Extensions

Contributors can easily expand the organizer's capabilities by following these steps:

1.  **Locate `extensions.c`**: This is where the core mapping between file extensions and destination folders resides.
2.  **Update the `defaults` array**: Add a new entry to the `defaults` struct array. Each entry follows this format:
    ```c
    {"extension", "DestinationFolder"}
    ```
    *   **Extension**: The file extension (without the dot, e.g., `"pdf"`, `"mp3"`). Max length is 10 characters.
    *   **DestinationFolder**: The name of the folder where these files should be moved (e.g., `"Documents"`, `"Music"`). Max length is 20 characters.

    **Example**:
    ```c
    struct Mapping defaults[] = {
        {"pdf", "Documents"},
        {"mp3", "Music"},      // Added New Extension
        // ... other entries
    };
    ```

3.  **Recompile**: After editing the file, run the compilation script to apply your changes:
    ```bash
    ./compile
    ```

## 📄 License

This project is open-source. Feel free to use and modify it!
