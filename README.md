#  File Organizer

A lightweight, efficient command-line utility written in C that organizes clutter in your directories by moving files into subfolders based on their file extensions.

##  Features

- **Blazing Fast**: Uses `uthash` for O(1) extension lookup.
- **Automatic Sorting**: Automatically categorizes files into common folders like `Documents`, `Images`, `Videos`, and `Code`.
- **Lightweight**: Minimal dependencies and small memory footprint.

##  Supported Extensions

Currently, the organizer supports the following mappings out-of-the-box:

| Extension | Target Folder |
| :--- | :--- |
| `.pdf` | Documents |
| `.jpg`, `.png` | Images |
| `.mp4` | Videos |
| `.c` | Code |

##  Prerequisites

To compile this project, you need:
- **GCC** (or any C compiler)
- **uthash**: This project expects the `uthash` library to be available at `../libraries/`. You can find it at [troydhanson/uthash](https://github.com/troydhanson/uthash).

##  Building the Project

You can build the project using the provided compilation script:

```bash
chmod +x compile
./compile
```

This will generate an executable named `run`.

## 📖Usage

Run the program by providing the path to the folder you want to organize:

```bash
./run "/path/to/your/cluttered/folder"
```

### Example

If you have a folder with the following files:
- `report.pdf`
- `vacation.jpg`
- `main.c`

Running the organizer will sort them into:
- `Documents/report.pdf`
- `Images/vacation.jpg`
- `Code/main.c`

##  Configuration

Currently, the extension-to-folder mapping is defined in `extensions.c`:

```c
struct Mapping defaults[] = {
    {"pdf", "Documents"},
    {"jpg", "Images"},
    {"png", "Images"},
    {"c", "Code"},
    {"mp4", "Videos"}
};
```

You can modify this file and recompile to customize your organization logic.

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
