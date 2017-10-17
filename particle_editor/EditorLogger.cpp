#include "EditorLogger.h"

#include <QTextEdit>

#include <cstdio>
#include <cstdarg>

namespace particle_editor {

    EditorLogger::EditorLogger(QTextEdit* text_edit)
        : text_edit_(text_edit)
    {

    }

    EditorLogger::~EditorLogger()
    {

    }

    void EditorLogger::WriteLog(core::LogLevel level, const char* file_name, int line, const char* format, ...)
    {
        va_list arg_list;
        va_start(arg_list, format);

        char message[1024];
        vsnprintf(message, sizeof(message), format, arg_list);

        QString str("<p>%1(%2): <font color='%3'>%4:</font> %5</p>");
        switch (level) {
        case core::LogLevel::Error:
            str = str.arg(file_name, QString::number(line), "red", "ERROR", message);
            break;
        case core::LogLevel::Warning:
            str = str.arg(file_name, QString::number(line), "orange", "WARNING", message);
            break;
        case core::LogLevel::Info:
            str = str.arg(file_name, QString::number(line), "lightblue", "INFO", message);
            break;
        case core::LogLevel::Debug:
            str = str.arg(file_name, QString::number(line), "lightgray", "DEBUG", message);
            break;
        default:
            str = str.arg(file_name, QString::number(line), "black", "?", message);
            break;
        }

        text_edit_->insertHtml(str);

        va_end(arg_list);
    }

}
