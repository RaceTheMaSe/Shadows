cmake_minimum_required(VERSION 3.3...3.10)
project(Shadows)
file(GLOB_RECURSE SOURCES    Shadows/*.cpp)
file(GLOB_RECURSE INCLUDES   Shadows/*.h)
file(GLOB_RECURSE SHADERS    Shadows/*.hlsl)
file(GLOB_RECURSE SHADERS_SF Shadows/SampleFramework11/Shaders/*.*)
file(GLOB_RECURSE IMAGES_SF  Shadows/SampleFramework11/Images/*.*)
LIST(APPEND       SHADERS    Shadows/SharedConstants.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES})

include(FetchContent)
FetchContent_Declare(DirectXMath
  GIT_REPOSITORY https://github.com/microsoft/DirectXMath.git
  GIT_TAG dec2020 # DirectXMath_SOURCE_DIR is set since this tag
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(DirectXMath)

set(ANTWEAKBAR_DIR Externals/AntTweakBar)
target_include_directories(${PROJECT_NAME} PRIVATE 
    Shadows Shadows/SampleFramework11
    ${ANTWEAKBAR_DIR}/include
    ${DirectXMath_SOURCE_DIR}/Inc
)

target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE)
target_link_directories(${PROJECT_NAME} PRIVATE ${ANTWEAKBAR_DIR}/lib/)
target_link_libraries(${PROJECT_NAME} 
    kernel32 user32 gdi32 gdiplus winspool comctl32 comdlg32 advapi32 shell32 ole32 oleaut32 uuid odbc32 odbccp32
    dxgi d3d9 d3d11 d3dcompiler
    AntTweakBar64
)
if(MSVC)
    target_link_options(${PROJECT_NAME} PRIVATE /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)
else()
    target_link_options(${PROJECT_NAME} PRIVATE -mwindows)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION .)
install(FILES ${SHADERS} DESTINATION .)
install(FILES ${SHADERS_SF} DESTINATION ./SampleFramework11/Shaders)
install(FILES ${IMAGES_SF} DESTINATION ./SampleFramework11/Images)
install(FILES ${ANTWEAKBAR_DIR}/bin/AntTweakBar64.dll DESTINATION .)
