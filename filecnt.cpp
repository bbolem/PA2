#include <iostream>
#include <utility>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

void isDirectory(const string&);
void subDirectory(struct dirent *dirContents);

struct stat statBuffer;

string path;
int numOfDirectory = 0, numOfFiles = 0, numOfBytes = 0;

struct dirent* dirContents;

int main(int argc, char *argv[]) {
    if(argv == nullptr)
        path = ".";
    else
        path = argv[1];
    string dir;
    isDirectory(dir);
    cout << "The total number of directories in directory " << dir << " is " << numOfDirectory-1 << endl;
    cout << "The total number of files in directory " << dir << " is " << numOfFiles << endl;
    cout << "The total number of bytes occupied by all files in directory " << dir << " is " << numOfBytes << endl;
    return 0;
}

void isDirectory(const string& dirString) {
    string openDirectory = path + dirString;
    auto dir = opendir(openDirectory.c_str());
    path = openDirectory + "/";

    if(dir == nullptr) {
        return;
    } else {
        numOfDirectory++;
    }

    dirContents = readdir(dir);

    while(dirContents != nullptr) {
        subDirectory(dirContents);
        if(stat(dirContents->d_name, &statBuffer) >= 0)
            numOfBytes += statBuffer.st_size;
        dirContents = readdir(dir);
    }
}

void subDirectory(struct dirent* dirContent) {
    if(dirContent->d_type == DT_DIR) {
        if(dirContent->d_name[0] == '.')  {
            return;
        }
        isDirectory(string(dirContent->d_name));
        return;
    }
    if(dirContent->d_type == DT_REG) {
        numOfFiles++; // add to fileCount
        return;
    }
}
