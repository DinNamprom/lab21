#include <windows.h>
#include <stdio.h>

#define ID_EDIT1 1
#define ID_EDIT2 2
#define ID_RESULT 3
#define ID_ADD 4
#define ID_SUB 5
#define ID_MUL 6
#define ID_DIV 7

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(179, 0, 0));
    wc.lpszClassName = "Calculator";

    if (!RegisterClass(&wc)) return 0;

    HWND hwnd = CreateWindow("Calculator", "My Calculator",WS_SYSMENU | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, NULL, NULL, hInstance, NULL);
    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hEdit1, hEdit2, hResult;
    static HWND hBtnAdd, hBtnSub, hBtnMul, hBtnDiv;
    char buffer1[256], buffer2[256];
    double num1, num2, result;

    switch (msg) {
        case WM_CREATE:
            hEdit1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 10, 20, 100, 20, hwnd, (HMENU)ID_EDIT1, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 130, 20, 100, 20, hwnd, (HMENU)ID_EDIT2, NULL, NULL);
            
            hBtnAdd = CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE, 10, 60, 50, 30, hwnd, (HMENU)ID_ADD, NULL, NULL);
            hBtnSub = CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE, 70, 60, 50, 30, hwnd, (HMENU)ID_SUB, NULL, NULL);
            hBtnMul = CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE, 130, 60, 50, 30, hwnd, (HMENU)ID_MUL, NULL, NULL);
            hBtnDiv = CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE, 190, 60, 50, 30, hwnd, (HMENU)ID_DIV, NULL, NULL);
            
            hResult = CreateWindow("STATIC", "Result: ", WS_CHILD | WS_VISIBLE, 20, 110, 200, 20, hwnd, (HMENU)ID_RESULT, NULL, NULL);
            break;
        
        case WM_COMMAND:
            GetWindowText(hEdit1, buffer1, sizeof(buffer1));
            GetWindowText(hEdit2, buffer2, sizeof(buffer2));
            num1 = atof(buffer1);
            num2 = atof(buffer2);
            
            switch (LOWORD(wParam)) {
                case ID_ADD:
                    result = num1 + num2;
                    break;
                case ID_SUB:
                    result = num1 - num2;
                    break;
                case ID_MUL:
                    result = num1 * num2;
                    break;
                case ID_DIV:
                    if (num2 != 0)
                        result = num1 / num2;
                    else
                        MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
                    break;
            }
            
            char resultText[256];
            sprintf(resultText, "Result: %.2f", result);
            SetWindowText(hResult, resultText);
            break;
        
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
