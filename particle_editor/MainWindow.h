#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

namespace Ui {
    class MainWindow;
}

class QElapsedTimer;
class QTimer;

namespace particle_editor {

    class EditorView;
    class PropertiesModel;

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    private slots:
        void Update();

    private:
        void SetupTree();

        std::unique_ptr<Ui::MainWindow> ui_;
        std::unique_ptr<EditorView>     editor_view_;
        std::unique_ptr<QElapsedTimer>  elapsed_timer_;
        int64_t         last_update_time_;
        QTimer*         timer_;

        std::unique_ptr<PropertiesModel> properties_model_;
    };

}

#endif // MAINWINDOW_H
