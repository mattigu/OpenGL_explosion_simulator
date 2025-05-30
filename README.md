# GKOM - 2025L

## Dependencies
### Assimp
Configured in vcpkg, it should automatically download a .dll when building
If there are problems follow the steps below.

Get this release https://github.com/assimp/assimp/releases/tag/v5.4.3 or just git clone.

Go to the assimp directory

    cmake CMakeLists.txt -A Win32
    cmake --build .

Find the assimp-vc143-mtd.dll file in bin/debug and paste it into the debug and release directories

## Temat 12. - Geometry Shader

