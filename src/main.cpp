#include "antiGLFW_lib.h"


//############################################
//              Platform Global
//#############################################
static bool running = true;


//############################################
//              Platform functions
//#############################################

bool platform_create_window(int width, int height, char* title);
void platform_update_window();

//############################################
//              win Platform
//#############################################
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
//what is nominmax
#include <Windows.h>

//############################################
//              win gOLBALS
//#############################################

static HWND window;

//############################################
//               Platform Implemntations
//#############################################
LRESULT CALLBACK windows_window_callback(HWND window, UINT msg,
                                         WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0; 

    switch(msg){
        case WM_CLOSE:
        {running =false;
            break;
        }
        default:{

            //letting windows handle shit
            result = DefWindowProcA(window, msg, wParam, lParam);
        }
    }
    return result;

}

bool platform_create_window(int width, int height, char* title){
    HINSTANCE instance = GetModuleHandleA(0);\

    WNDCLASSA wc = {};

    wc.hInstance =instance;
    wc.hIcon = LoadIcon(instance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = title;            //not title just unqiue id??
    wc.lpfnWndProc = windows_window_callback;     //Callback for input into the window

    if(!RegisterClassA(&wc)){
        return false;
    }

    //wtf??? 
    //style to window??
    //WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX 
    int dwStyle =WS_OVERLAPPEDWINDOW;


    window = CreateWindowExA(0, title, //refernces lpfnWndProc id
                                    title, //actual title??? lmao
                                    dwStyle,
                                    100,
                                    100,
                                    width,
                                    height,
                                    NULL,   //parent???
                                    NULL,   //menu??
                                    instance,
                                    NULL);  //what is lparam

        if(window == NULL){
            return false;
        }

        ShowWindow(window, SW_SHOW);

        return true;
}


//to update the window with inputs we send to it
void platform_update_window(){
    MSG msg;

    while(PeekMessageA(&msg, window, 0, 0, PM_REMOVE)){
        TranslateMessage(&msg);
        DispatchMessageA(&msg); //calls callback when creating window???
    }
}

#endif

int main(){
   //i cant do this in vscode?? cout<<"hello"<<endl;
    //cout<<"hello"<<endl;

    platform_create_window(1280, 720, "openGL");
    
    while(running){
        platform_update_window();
        SM_TRACE("TEST");
        SM_WARN("WARN");
        SM_ERROR("ERROR");
    }
    return 0;
}