#####################################################################################
#                                                                                   #
#   By: Torin Middlebrooks                                                          #
#   GitHub: https://github.com/Legendarylion1/Personal-Projects                     #
#                                                                                   #
#                   ~ README ~                                                      #
#                                                                                   #
#   This file needs to be placed in the solution directory not the src directory    #
#   All .cpp files need to have the same name prefix as their .h counterpart        #
#                                                                                   #
#   I am not optimizing this code. Its just to help build my makefile               #
#                                                                                   #
#####################################################################################

from io import TextIOWrapper
from os import getcwd
from pathlib import Path

# Project Variables
WORKING_DIRECTORY = ""
INCLUDE_DIRECTORIES = ["Dependencies/GLFW/include/", "Dependencies/GLEW/include/", "Dependencies/", "vendor/"]
LINKER_DIRECTORIES = ["Dependencies/GLFW/lib-static-ucrt", "Dependencies/GLEW/lib/Release/Win32/"] 
LINKER_STATIC_LIBS = ["opengl32.lib", "glew32s.lib"]#, "User32.lib","Gdi32.lib","Shell32.lib" ] #TODO: May need to include inherited dependencies
LINKER_DYNAMIC_LIBS = ["Dependencies/GLFW/lib-mingw-w64/glfw3.dll"]
PREPROCESSOR_DEFINITIONS = ["WIN32","GLEW_STATIC", "GLFW_DLL"]
EXECUTABLE_NAME = "PokemonAdventure.exe"

# Makefile Variable Names
MAKE_COMPILER = "CC"
MAKE_FLAGS = "FLAGS"
MAKE_BIT_VERSION = "BIT_VERSION"
MAKE_PREPROCESSOR = "PREPROCESSOR"
MAKE_INCLUDE_DIRECTORIES = "INCLUDE_DIRECTORIES"
MAKE_LINKER_DIRECTORIES = "LINKER_DIRECTORIES"
MAKE_LINKER_STATIC_LIBS = "LINKER_STATC_LIBS"
MAKE_LINKER_DYNAMIC_LIBS = "LINKER_DYNAMIC_LIBS"
MAKE_CPP_FILES = "CPP_FILES"
MAKE_EXECUTABLE = "EXECUTABLE"

# Make Variable Values
CPP_VERSION = "c++14"
MACHINE_ARCHITECTURE = "x86-64"     #https://gcc.gnu.org/onlinedocs/gcc/x86-Options.html
COMPILER = "i686-w64-mingw32-g++"
FLAGS = "-std=" + CPP_VERSION + " -w"
BIT_VERSION = "32"



def checkIncludeDirectory(path: str):
    global INCLUDE_DIRECTORIES

    for dir in INCLUDE_DIRECTORIES:
        samplePath = Path(dir + path)
        if samplePath.exists():
            return dir + path
    return ""

def followedPath(filePath: str, includeLine: str) -> str:
    includePath = includeLine.split("\"")[-2]
    pathToFollow = includePath

    pathList = filePath.split("/")[0:-1]
    pathInstructions = pathToFollow.split("/")

    for instruction in pathInstructions:
        if (instruction == ".."):
            pathList.pop(-1)
            continue

        pathList.append(instruction)

    pathToFollow = ""

    for count, path in enumerate(pathList):
        if (count == len(pathList) - 1):
            pathToFollow += path
            break
        pathToFollow += path + "/"

    pathTest = Path(pathToFollow)

    if pathTest.exists():
        return pathToFollow
    
    return checkIncludeDirectory(includePath)

def findFiles(filePath: str, filesFound: list[str]):

    if filePath in filesFound:
        return
    else:
        filesFound.append(filePath)

    try:
        with open(filePath) as openFile:

            for line in openFile:
                if len(line) != 1 and "#" not in line:
                    break

                if "#include" not in line or "<" in line:
                    continue

                includeLine = line
                subPath = followedPath(filePath, includeLine)

                if (subPath == ""):
                    return -1

                if (findFiles(subPath, filesFound) == -1):
                    print("\nError Searching from line: \t", line, "\n\tSubpath:\t", subPath)
                    return -1
    except:
        print("Error opening File")
        return -1
    
    return 0

def replaceHeaderFiles(files: list):
    for i in range(len(files) - 1, -1, -1):
        if (".h" in files[i]):
            cppPath = files[i].split(".h")[0] + ".cpp"

            if (Path(cppPath).exists()):
                files.append(cppPath)
            files.pop(i)
    pass

def trimWorkingDirectory(files: list):
    global WORKING_DIRECTORY

    dirList = WORKING_DIRECTORY.split("/")
    dirList.pop(-1)

    basePath = ""
    for dir in dirList:
        basePath += dir + "/"

    for i in range(len(files)):
        files[i] = files[i].split(WORKING_DIRECTORY)[-1]
        files[i] = files[i].split(basePath)[-1]
    pass

def setWorkingDirectory():
    global WORKING_DIRECTORY

    directory = getcwd().split("\\")

    for path in directory:
        WORKING_DIRECTORY += path + "/"
    pass

def addIncludeDirectories():

    dirList = WORKING_DIRECTORY.split("/")
    dirList.pop(-1)

    dirPath = ""
    for dir in dirList:
        dirPath += dir + "/"

    for i in range(len(INCLUDE_DIRECTORIES)):
        INCLUDE_DIRECTORIES[i] = dirPath + INCLUDE_DIRECTORIES[i]
        
    pass

def writeCompiler(file: TextIOWrapper):
    file.write(MAKE_COMPILER + " = " + COMPILER)
    file.write("\n")

def writeFlags(file: TextIOWrapper):
    #Flags
    # https://bytes.usc.edu/cs104/wiki/gcc

    file.write(MAKE_FLAGS + " = " + FLAGS)
    file.write("\n")

def writeBitVersion(file: TextIOWrapper):
    file.write(MAKE_BIT_VERSION + " = -m" + BIT_VERSION)
    file.write("\n")
    pass

def writeIncludeDirectories(file: TextIOWrapper):
    # https://gcc.gnu.org/onlinedocs/gcc/Directory-Options.html

    includeDirectories = []
    value = ""

    for dir in INCLUDE_DIRECTORIES:
        includeDirectories.append(dir.split(WORKING_DIRECTORY)[-1].rstrip('/'))

    for dir in includeDirectories:
        value += "-I" + dir + " "

    value.rstrip()

    file.write(MAKE_INCLUDE_DIRECTORIES + " = " + value)
    file.write("\n")

def writeLinkerDirectories(file: TextIOWrapper):
    value = ""
    for dir in LINKER_DIRECTORIES:
        value += "-L/" + dir + " "
    value.rstrip()

    file.write(MAKE_LINKER_DIRECTORIES + " = " + value)
    file.write("\n")
    pass

def writeLinkerStaticLibs(file: TextIOWrapper):
    value = ""

    for lib in LINKER_STATIC_LIBS:
        value += "-l:" + lib + " "
    value.rstrip()

    file.write(MAKE_LINKER_STATIC_LIBS + " = " + value)
    file.write("\n")
    pass

def writeCPPFiles(file: TextIOWrapper, cppFiles: list[str]):
    value = ""

    for path in cppFiles:
        value += path + " "
    value.rstrip()

    file.write(MAKE_CPP_FILES + " = " + value)
    file.write("\n")
    pass

def writeLinkerDynamicLibs(file: TextIOWrapper):
    value = ""

    for path in LINKER_DYNAMIC_LIBS:
        value += path + " "
    
    value.rstrip()
    file.write(MAKE_LINKER_DYNAMIC_LIBS + " = " + value)
    file.write("\n")

def writePreprocessor(file: TextIOWrapper):
    #https://gcc.gnu.org/onlinedocs/gcc-2.95.3/gcc_2.html

    value = ""
    for definition in PREPROCESSOR_DEFINITIONS:
        value += "-D" + definition + " "

    value.rstrip()

    file.write(MAKE_PREPROCESSOR + " = " + value)
    file.write("\n")
    pass

def writeExecutable(file: TextIOWrapper):
    file.write(MAKE_EXECUTABLE + " = -o " + EXECUTABLE_NAME)
    file.write("\n")
    pass

def wrapValue(value: str) -> str:
    return "${" + value + "}"

def writeMakefileTarget(file: TextIOWrapper):
    file.write("\n")
    file.write("target:\n")
    file.write("\t" + wrapValue(MAKE_COMPILER) + " " + wrapValue(MAKE_FLAGS) + " " + wrapValue(MAKE_BIT_VERSION) + " " + wrapValue(MAKE_INCLUDE_DIRECTORIES) + " " + wrapValue(MAKE_LINKER_DIRECTORIES) + " " + wrapValue(MAKE_LINKER_STATIC_LIBS) + " " + wrapValue(MAKE_CPP_FILES)+ " " + wrapValue(MAKE_LINKER_DYNAMIC_LIBS) + " " + wrapValue(MAKE_PREPROCESSOR) + " " + wrapValue(MAKE_EXECUTABLE))
    pass

def writeMakeFile(cppFiles: list):
    # CC = g++
    # FLAGS = -Wall
    # BIT_VERSION = -m32
    # LINKER_DEPENDENCIES = -L{Dependencies}
    # LINKER_LIBS = ${LINKER_DEPENDENCIES} -L{Path to libs} -l{lib name}
    # CPP_FILES = {CPP FILES}
    # PREPROCESSOR = -D{name and repeat as needed}

    #g++ -Wall -L{LinkerDirectories repeat for additional directories} -o EXECUTABLE_NAME {All cpp Files} 

    #${CC} ${FLAGS} ${PREPROCESSOR} ${LINKER_DEPENDENCIES} ${LINKER_LIBS} ${CPP_FILES} ${EXECUTABLE}

    with open("Makefile", "w") as file:

        writeCompiler(file)
        writeFlags(file)
        writeBitVersion(file)
        writeIncludeDirectories(file)
        writeLinkerDirectories(file)
        writeLinkerStaticLibs(file)
        writeCPPFiles(file, cppFiles)
        writeLinkerDynamicLibs(file)
        writePreprocessor(file)
        writeExecutable(file)

        writeMakefileTarget(file)
    pass

if __name__ == "__main__":
    cppFiles = []

    setWorkingDirectory()
    addIncludeDirectories()

    if (findFiles(WORKING_DIRECTORY + "src/main.cpp", cppFiles) == -1):
        print("Error Detected Shutting Down")
        exit(-1)

    replaceHeaderFiles(cppFiles)
    trimWorkingDirectory(cppFiles)

    writeMakeFile(cppFiles)