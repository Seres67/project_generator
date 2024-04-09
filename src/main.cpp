#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

std::string setup_dirs(std::string path)
{
    std::filesystem::create_directory(path);
    std::filesystem::create_directory(path + "/src");
    std::filesystem::create_directory(path + "/include");
    return path;
}

void setup_meson(const std::string &path, char *lang)
{
    std::ofstream meson(path + "/meson.build");
    meson << "project('" << path << "', '" << lang
          << "', default_options: ['warning_level=2'])\n";
    meson << "subdir('src')\n";
    meson << "include_dir = include_directories('include')\n";
    meson << "executable('" << path
          << "', sources, include_directories: include_dir)\n";
    meson.close();
    std::ofstream meson_sources(path + "/src/meson.build");
    meson_sources << "sources = files('main." << lang << "')";
    meson_sources.close();
}

void main_c(const std::string &path)
{
    std::ofstream main(path + "/src/main.c");
    main << "#include <stdio.h>\n\nint main(int ac, char **av)\n{\n    "
            "printf(\"Hello world!\");\n    return 0;\n}";
    main.close();
}

void main_cpp(const std::string &path)
{
    std::ofstream main(path + "/main.cpp");
    main << "#include <iostream>\n\nint main(int ac, char *av[])\n{\n    "

            "std::cout << \"Hello world!\n\";\n    return 0;\n}";
    main.close();
}

void readme(const std::string &path)
{
    std::ofstream readme(path + "/README.md");
    readme << "# " << path << std::endl;
    readme.close();
}

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cout << "wrong input, expected 2 arguments.\n";
        return 1;
    }
    std::cout << av[2] << std::endl;
    if (std::strcmp(av[2], "c") != 0 && std::strcmp(av[2], "cpp") != 0) {
        std::cout << "only c and cpp are supported.\n";
        return 1;
    }
    std::string path = setup_dirs(av[1]);
    setup_meson(path, av[2]);
    if (!strcmp(av[2], "c"))
        main_c(path);
    else if (!strcmp(av[2], "cpp"))
        main_cpp(path);
    readme(path);
    return 0;
}
