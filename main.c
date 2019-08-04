#include <vlc/vlc.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

libvlc_instance_t* vlc;
libvlc_media_t* media[2];
HANDLE exitEvent;
HWND hwnd;

DWORD switchingThread(void* args)
{
    int i = 0;
    DWORD waitResult = WAIT_TIMEOUT;
    while(waitResult == WAIT_TIMEOUT)
    { // Continue until the exitEvent is signaled
        libvlc_media_player_t* media_player = libvlc_media_player_new(vlc);
        libvlc_media_player_set_hwnd(media_player, hwnd);
        libvlc_media_player_set_media(media_player, media[i]);
        libvlc_media_player_play(media_player);
        waitResult = WaitForSingleObject(exitEvent, 3000);
        libvlc_media_player_release(media_player);
        i = (i + 1)%2;
    }

    return 0;
}

const TCHAR CLASS_NAME[]  = TEXT("TestLibVlcNative Window");


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);



            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

            EndPaint(hwnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    /*
    const char* options[] = { "-vv" };
    vlc = libvlc_new(1, options);
    */
    vlc = libvlc_new(0, NULL);

    media[0] = libvlc_media_new_location(vlc, "rtsp://localhost:8555/");
    media[1] = libvlc_media_new_location(vlc, "rtsp://localhost:8556/");
    exitEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("EXIT"));
    HANDLE thread = CreateThread(NULL, 0, switchingThread, NULL, 0, NULL);

    WNDCLASS wc = {};

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        TEXT("Test LibVLC native"),     // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    SetEvent(exitEvent);

    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    CloseHandle(exitEvent);

    libvlc_media_release(media[0]);
    libvlc_media_release(media[1]);

    libvlc_release(vlc); 
    return 0;
}