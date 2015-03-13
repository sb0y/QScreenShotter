#include "mousespy.h"

mouseSpy::mouseSpy(QObject *parent) : QObject(parent)
{

}

mouseSpy::~mouseSpy()
{

}

HHOOK hMouseHook;

static
LRESULT CALLBACK mouseProc (int nCode, WPARAM wParam, LPARAM lParam)
{
    qDebug() << "here";
    MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
    if (pMouseStruct != NULL){
        if(wParam == WM_LBUTTONDOWN)
        {
            printf( "clicked" );
        }
        printf("Mouse position X = %ld  Mouse Position Y = %ld\n", pMouseStruct->pt.x,pMouseStruct->pt.y);
    }

    return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

void WINAPI mouseSpy::myMouseLogger()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    // here I put WH_MOUSE instead of WH_MOUSE_LL
    hMouseHook = SetWindowsHookEx ( WH_MOUSE, mouseProc, hInstance, ((DWORD)QThread::currentThreadId()) );

    MSG message;
    while ( GetMessage ( &message, NULL, 0, 0 ) )
    {
         TranslateMessage( &message );
         DispatchMessage( &message );
    }

    UnhookWindowsHookEx ( hMouseHook );
}


void mouseSpy::start()
{
    myMouseLogger();
}
