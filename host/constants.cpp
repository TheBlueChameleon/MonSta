#include <sstream>
#include <string>
using namespace std::string_literals;

#include "versionservice/versionservice.hpp"

#include "constants.hpp"

const std::string APP_NAME = "MonSta";
const std::string APP_VERSION = VersionService::to_string(HOST_VERSION);

const Version HOST_VERSION       = {0, 1, 0, 0};
const Version MIN_CLIENT_VERSION = {0, 1, 0, 0};
const Version MAX_CLIENT_VERSION = {2, 0, 0, 0};
