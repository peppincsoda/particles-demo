#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

class QElapsedTimer;
class QTimer;
class QSlider;

namespace particle_editor {

    class EditorView;
    class PropertiesModel;
    class PropertiesTreeView;

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    private slots:
        void Update();

    private:
        void AddPropertiesDockWidget();
        void AddControlsDockWidget();

        std::unique_ptr<EditorView>     editor_view_;
        std::unique_ptr<QElapsedTimer>  elapsed_timer_;
        int64_t         last_update_time_;
        QTimer*         timer_;

        std::unique_ptr<PropertiesModel> properties_model_;
        PropertiesTreeView* properties_view_;

        QSlider* speed_slider_;
    };

}

#endif // MAINWINDOW_H
