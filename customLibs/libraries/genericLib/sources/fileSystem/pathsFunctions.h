#ifndef GENERIC_LIB_PATHS_FUNCTIONS_H
#define GENERIC_LIB_PATHS_FUNCTIONS_H

#include "fileSystem/fileSystem.h"

namespace pathFunc{

fs::path getLastDirectoryName(const fs::path& path);

}

#endif //GENERIC_LIB_PATHS_FUNCTIONS_H