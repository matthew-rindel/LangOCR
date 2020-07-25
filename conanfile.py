from conans import ConanFile, CMake, tools

class LangOcrConan(ConanFile):
    build_requires = "cmake/3.17.3"
    settings = "os", "compiler", "build_type", "arch"
    requires = "qt/5.14.2@bincrafters/stable", "tesseract/4.1.1", "leptonica/1.79.0", "zstd/1.4.5"
    generators = "cmake", "cmake_find_package"
    build_folder = "build"

    def build(self):
        self.build_folder = "build"
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

