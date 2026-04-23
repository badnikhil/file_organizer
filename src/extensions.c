#include "include.h"


#define MAX_EXT_CHAR 10
#define MAX_FOLDER_CHAR 20
#define M(ext, folder) {{ext},{folder},{NULL}}
struct Mapping defaults[] = {
  // Documents 
  M("pdf", "Documents"),
  M("docx", "Documents"),
  M("doc", "Documents"),
  M("txt", "Documents"),
  M("pptx", "Documents"),
  M("ppt", "Documents"),
  M("xlsx", "Documents"),
  M("xls", "Documents"),
  M("csv", "Documents"),
  M("json", "Documents"),
  M("yaml", "Documents"),
  M("xml", "Documents"),
  M("epub", "Documents"),
  M("mobi", "Documents"),
  M("ttf", "Documents"),
  M("woff", "Documents"),
  M("otf", "Documents" ),

  // Images  
  M("jpg", "Images"),
  M("jpeg", "Images"),
  M("png", "Images"),
  M("gif", "Images"),
  M("svg", "Images"),
  M("webp", "Images"),
  M("bmp", "Images" ),
  M("ico", "Images" ),
  M("tiff", "Images"),
  M("tif", "Images" ),
  M("eps", "Images"),

  // Videos 
  M("mp4", "Videos" ),
  M("mkv", "Videos" ),
  M("avi", "Videos" ),
  M("mov", "Videos" ),
  M("wmv", "Videos" ),
  M("flv", "Videos" ),
  M("webm", "Videos"),
  M("m4v", "Videos" ),
  
    // Music 
  M("mp3", "Music" ),
  M("wav", "Music" ),
  M("flac", "Music"),
  M("m4a", "Music" ),
  M("ogg", "Music" ),
  M("aac", "Music" ),
  M("wma", "Music" ),

  // Code
  M("c", "Code"),
  M("cpp", "Code"),
  M("h", "Code"),
  M("py", "Code"),
  M("js", "Code"),
  M("ts", "Code"),
  M("java", "Code"),
  M("go", "Code"),
  M("rs", "Code"),
  M("php", "Code"),
  M("html", "Code"),
  M("css", "Code"),
  M("sql", "Code"),
  
  // Archives (Includes Disk Images)
  M("zip", "Archives"),
  M("tar", "Archives"),
  M("rar", "Archives"),
  M("7z", "Archives"),
  M("gz", "Archives"),
  M("bz2", "Archives"),
  M("iso", "Archives"),
  M("dmg", "Archives"),

  //Executables
  M("exe", "Executables"),
  M("sh", "Executables"),
  M("bat", "Executables"),
  M("msi", "Executables")
};

size_t defaults_size = sizeof(defaults)/sizeof(defaults[0]);
