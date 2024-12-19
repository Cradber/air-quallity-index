cmake_minimum_required(VERSION 3.16)

project(air-quallity-index LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluir FetchContent para gestionar dependencias
include(FetchContent)

# Descargar y agregar nlohmann/json
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(json)

# Descargar y agregar CPR
FetchContent_Declare(
    cpr GIT_REPOSITORY
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.11.1
) # Replace with your desired git commit from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(air-quallity-index main.cpp
    models/models.h
    serialization/json_serialization.h
    serialization/nlohmann/jsonserializernlohmann.h
    serialization/nlohmann/attributionsserializer.h
    serialization/nlohmann/cityserialization.h
    serialization/nlohmann/debugserialization.h
    serialization/nlohmann/metricsserializer.h
    serialization/nlohmann/dailyserializer.h
    serialization/nlohmann/forecastserializer.h
    serialization/nlohmann/ParamAdapterDSerializer.h
    serialization/nlohmann/IaqiSerializer.h
    serialization/nlohmann/TimeSerializer.h
    serialization/nlohmann/DataSerializer.h
)

# Incluir directorios
target_include_directories(air-quallity-index PRIVATE include)

# Vincular la biblioteca nlohmann/json
target_link_libraries(air-quallity-index
    PRIVATE
    nlohmann_json::nlohmann_json
    cpr::cpr
)

include(GNUInstallDirs)
install(TARGETS air-quallity-index
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
