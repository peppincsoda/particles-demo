#include <QApplication>
#include "MainWindow.h"

#include "core/FileSystem.h"

#include <QMessageBox>

#include <cstdlib>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    const char* assets_dir = getenv("PARTICLES_DEMO_ASSETS_DIR");
    if (assets_dir == nullptr) {
        QMessageBox::critical(nullptr, "ERROR",
                              "Please set PARTICLES_DEMO_ASSETS_DIR to point to the assets subdirectory.");
        return 1;
    }

    core::InitFileSystem(assets_dir);

    particle_editor::MainWindow window;
    window.show();

    return application.exec();
}
