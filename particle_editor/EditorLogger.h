#ifndef EDITORLOGGER_H
#define EDITORLOGGER_H

#include "core/Logger.h"

class QTextEdit;

namespace particle_editor {

    class EditorLogger : public core::LoggerInterface
    {
    public:
        explicit EditorLogger(QTextEdit* text_edit);
        ~EditorLogger();

        EditorLogger(const EditorLogger&) = delete;
        EditorLogger& operator=(const EditorLogger&) = delete;

        EditorLogger(EditorLogger&&) = default;
        EditorLogger& operator=(EditorLogger&&) = default;

        void WriteLog(core::LogLevel level, const char* file_name, int line, const char* format, ...) override;

    private:
        QTextEdit* text_edit_;
    };

}


#endif // EDITORLOGGER_H
