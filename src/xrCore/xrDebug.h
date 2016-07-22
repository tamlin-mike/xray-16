#pragma once
#include "xrCore/_types.h"
#include "xrCore/xrCore_impexp.h"
#include <string>

struct StackTraceInfo
{
    static const size_t Capacity = 100;
    static const size_t LineCapacity = 256;
    char Frames[Capacity*LineCapacity];
    size_t Count;

    char *operator[](size_t i) { return Frames+i*LineCapacity; }
};

class ErrorLocation
{
public:
    const char *File = nullptr;
    int Line = -1;
    const char *Function = nullptr;

    ErrorLocation(const char *file, int line, const char *function)
    {
        File = file;
        Line = line;
        Function = function;
    }

    ErrorLocation &operator=(const ErrorLocation &rhs)
    {
        File = rhs.File;
        Line = rhs.Line;
        Function = rhs.Function;
        return *this;
    }
};

class XRCORE_API xrDebug
{
public:
    using OutOfMemoryCallbackFunc = void (*)();
    using CrashHandler = void (*)();
    using DialogHandler = void (*)(bool);

private:
    static OutOfMemoryCallbackFunc OutOfMemoryCallback;
    static CrashHandler OnCrash;
    
public:
    xrDebug() = delete;
    static void Initialize(const bool &dedicated);
//    static void Destroy();
    static void OnThreadSpawn();
    static OutOfMemoryCallbackFunc GetOutOfMemoryCallback() { return OutOfMemoryCallback; }
    static void SetOutOfMemoryCallback(OutOfMemoryCallbackFunc cb) { OutOfMemoryCallback = cb; }
    static CrashHandler GetCrashHandler() { return OnCrash; }
    static void SetCrashHandler(CrashHandler handler) { OnCrash = handler; }
	static DialogHandler GetDialogHandler();
	static void SetDialogHandler(DialogHandler handler);
    static const char *ErrorToString(long code);
    static void SetBugReportFile(const char *fileName);
    static void LogStackTrace(const char *header);
    static size_t BuildStackTrace(char *buffer, size_t capacity, size_t lineCapacity);
    static void GatherInfo(char *assertionInfo, const ErrorLocation &loc, const char *expr,
        const char *desc, const char *arg1 = nullptr, const char *arg2 = nullptr);
    static void Fatal(const ErrorLocation &loc, const char *format, ...);
    static void Fail(bool &ignoreAlways, const ErrorLocation &loc, const char *expr,
        long hresult, const char *arg1 = nullptr, const char *arg2 = nullptr);
    static void Fail(bool &ignoreAlways, const ErrorLocation &loc, const char *expr,
        const char *desc = "assertion failed", const char *arg1 = nullptr, const char *arg2 = nullptr);
    static void Fail(bool &ignoreAlways, const ErrorLocation &loc, const char *expr,
        const std::string &desc, const char *arg1 = nullptr, const char *arg2 = nullptr);
    static void DoExit(const char* message);

private:
//    static void FormatLastError(char *buffer, const size_t &bufferSize);
    static void SetupExceptionHandler(const bool dedicated);
};

// for debug purposes only
std::string XRCORE_API make_string(const char *format, ...);

#include "xrDebug_macros.h"
