/**
 * \file    lernen.c
 *
 * \date    2020-07-27
 *
 * \author  settstep
 *
 * \section sec_lernen_c_history Historie
 *
 * \par     2020-08-06 settstep
 * - Es wird jetzt ein (leeres) Fenster erzeugt
 * \par     2020-07-27 settstep
 * - Datei erstellt
 */

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

const char g_szClassName[] = "myWindowClass";   ///< Name der zu registrierenden Fensterklasse

/**
 *  \brief   Windows Main Funktion
 *  \param   hInstance
 *  \param   hPrevInstance
 *  \param   lpCmdLine
 *  \param   nCmdShow
 *  \details Einstiegsfunktion für Windows Programme.
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    /// Im ersten Schritt wird die Fensterklasse mit RegisterClassEx registriert.
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Wenn die Klasse erfolgreich registriert wurde, wird im nächsten Schritt das Fenster mit CreateWindowEx erzeugt.
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Lernen",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    /// Nach erfolgreicher Erzeugung des Fensters wird es mit ShowWindow() und UpdateWindow() angezeigt.
    ShowWindow(hwnd, nCmdShow | SW_SHOWMAXIMIZED);
    UpdateWindow(hwnd);

    /// Zum Schluß wird die Endlosschleife gestartet, wo die "Nachrichten" des Fenster bearbeitet werden.
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

/**
 *  \brief Reaktion auf Ereignisse bearbeiten
 *  \param hwnd
 *  \param msg
 *  \param wParam
 *  \param lParam
 *  \details Hier werden die "Nachrichten" des Fenster abgearbeitet.
 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_LBUTTONDOWN:
        {
            /// Bei einem Linksklick wird eine Textbox mit dem Pfad und Dateinamen des Programms angezeigt.
            char szFileName[MAX_PATH];
            HINSTANCE hInstance = GetModuleHandle(NULL);

            GetModuleFileName(hInstance, szFileName, MAX_PATH);
            MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
        }
        break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
