#ifndef __FILECONTENTS__
#define __FILECONTENTS__

#include <vector>

class FileContents
{
public:
    FileContents(const char *file);
    int getLine(int line, char *dest, int len);
    int getField(int line, int field, char *dest, int len);
    int numLines();
    int nextLine(int userId);
    void dump();
    void index(int field);
    int lookup(char *key);
    void insert(char *value);
    void replace(int line, char *value);
private:
    void reIndex(int line);
    void deIndex(int line);

    typedef enum {
        InputFileSequentialOrder = 0,
        InputFileRandomOrder,
        InputFileUser
    } InputFileUsage;
    int usage;
    int lineCounter;

    std::vector<std::string> fileLines;
    const char *fileName;
    bool printfFile;
    int printfOffset;
    int printfMultiple;
    int numLinesInFile;
    int realLinesInFile;

    int indexField;
    //str_int_map *indexMap;
};

#endif
