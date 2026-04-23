#  File Organizer

A lightweight, efficient command-line utility written in C that organizes clutter in your directories by moving files into subfolders based on their file extensions.

##  Features

- **Blazing Fast**: Uses `uthash` for O(1) extension lookup.
- **Automatic Sorting**: Automatically categorizes files into common folders like `Documents`, `Images`, `Videos`, and `Code`.
- **Lightweight**: Minimal dependencies and small memory footprint.

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

## 📄 License

This project is open-source. Feel free to use and modify it!
