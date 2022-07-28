#include <Utils/File.h>

namespace Utils {
    std::string ReadFile(const char* path) {
        FILE* file = fopen(path, "rt");

        fseek(file, 0, SEEK_END);
        auto len = ftell(file);

        std::string data(len + 1, 0);

        fseek(file, 0, SEEK_SET);
        fread(data.data(), 1, len, file);
        fclose(file);

        return data;
    }
}