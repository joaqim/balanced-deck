from conans import ConanFile, CMake, tools, errors

def get_version():
    version = ""
    try:
        version = tools.Git().run("describe --tags")
        tools.save("VERSION", version)
    except:
        version = tools.load("VERSION")
    return version[1:]


class BalancedDeckConan(ConanFile):
    name = "balanced-deck"
    version = get_version()
    description = """A basic C++ implementation of two 2-sided dice as a 36 length deck of dice pairs."""
    settings = "os", "compiler", "build_type", "arch"
    license = "AGPL-3.0-or-later"
    generators = "cmake_find_package", "cmake_paths"
    exports = "VERSION"
    exports_sources = "lib/*", "test/*", "cmake/*", "VERSION", "LICENSE", "CMakeLists.txt"
    author = "Joaqim Planstedt"
    options = {
        "shared": [True, False],
        "fPIC": [True, False]
    }
    default_options = {
        "shared": False,
        "fPIC": True
    }

    build_requires = (
        "catch2/2.13.6"
    )

    def build(self):
        cmake = CMake(self)
        if not tools.get_env("CONAN_RUN_TESTS", True):
            cmake.definitions["BUILD_TESTING"] = "OFF"
        cmake.configure()
        cmake.build()
        if tools.get_env("CONAN_RUN_TESTS", True):
            cmake.test()
        cmake.install()

    def package_info(self):
        self.cpp_info.names["cmake_find_package"] = "BalancedDeck"
        self.cpp_info.names["cmake_find_package_multi"] = "BalancedDeck"
        self.cpp_info.libs = ["BalancedDeck"]