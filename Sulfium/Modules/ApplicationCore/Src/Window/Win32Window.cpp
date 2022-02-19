#include "ApplicationCore/Pch.h"
#include "ApplicationCore/Window/Win32Window.h"
#include "ApplicationCore/Input/Input.h"
#include "Core/Printer/Printer.h"

namespace SFM
{
	Win32Window::Win32Window() :
		m_title(L""),
		m_className(L"SulfiumAppWindow"),
		m_handle(nullptr),
		m_windowClose(false),
		m_widthInPx(0),
		m_heightInPx(0),
		m_maximized(false),
		m_minimized(false),
		m_resizing(false)
	{}

	void Win32Window::Initialize(std::weak_ptr<Engine> engine, const std::wstring& title, std::weak_ptr<Input> input, UINT width, UINT height, bool showWindow)
	{
		HINSTANCE appModule = (HINSTANCE)GetModuleHandle(NULL);
		
		m_input = input;
		m_engine = engine;
		//m_engine.lock()->GetEventMessenger().AddMessenger<SFM::ResizeEventArgs&>("OnWindowResize");

		m_widthInPx = width;
		m_heightInPx = height;

		//Register the window.
		WNDCLASSEXW windowClass =
		{
			sizeof(WNDCLASSEXW),
			CS_HREDRAW | CS_VREDRAW,
			&Win32Window::WindowProc,
			0,
			0,
			appModule,
			LoadIcon(appModule, IDI_APPLICATION),		//101 = the default window icon
			LoadCursor(NULL, IDC_ARROW),
			(HBRUSH)(COLOR_WINDOW + 1),
			NULL,
			m_className.c_str(),
			LoadIcon(appModule, IDI_APPLICATION)		//101 = the default window icon
		};

		ATOM atom = RegisterClassExW(&windowClass);
		assert(atom > 0);

		//Calculate the window size and position properties.
		RECT windowCanvas = { 0, 0, static_cast<LONG>(m_widthInPx), static_cast<LONG>(m_heightInPx)};
		AdjustWindowRect(&windowCanvas, WS_OVERLAPPEDWINDOW, false);
		int windowX = std::max<int>(0, (GetSystemMetrics(SM_CXSCREEN) - m_widthInPx) / 2);
		int windowY = std::max<int>(0, (GetSystemMetrics(SM_CYSCREEN) - m_heightInPx) / 2);

		//Create the window.
		m_handle = CreateWindowExW(
			NULL,
			m_className.c_str(),
			m_title.c_str(),
			WS_OVERLAPPEDWINDOW,
			windowX,
			windowY,
			m_widthInPx,
			m_heightInPx,
			NULL,
			NULL,
			appModule,
			this
		);

		assert(m_handle && "Failed to create render window!");

		//Show the window, if the user has specified to do so (default behavior).
		if (showWindow)
		{
			Show();
			UpdateWindow(m_handle);
		}
	}

	void Win32Window::Destroy()
	{
		if (m_handle != nullptr)
		{
			DestroyWindow(m_handle);
		}
	}

	void Win32Window::PollEvents()
	{
		MSG msg;
		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				m_windowClose = true;
				return;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
		}
	}

	HWND Win32Window::GetWindowHandle() const
	{
		return m_handle;
	}

	UINT Win32Window::GetWindowWidth() const
	{
		return m_widthInPx;
	}

	UINT Win32Window::GetWindowHeight() const
	{
		return m_heightInPx;
	}

	bool Win32Window::DoesWindowClose() const
	{
		return m_windowClose;
	}

	const std::wstring& Win32Window::GetWindowTitle() const
	{
		return m_title;
	}

	void Win32Window::Show()
	{
		ShowWindow(m_handle, SW_SHOW);
		SetFocus(m_handle);
	}

	void Win32Window::Hide()
	{
		ShowWindow(m_handle, SW_HIDE);
	}

	LRESULT CALLBACK Win32Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		Win32Window* windowInstance = NULL;

		switch (message)
		{
		case WM_CREATE:
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			windowInstance = (Win32Window*)pCreate->lpCreateParams;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)windowInstance);
			break;
		}
		default:
			windowInstance = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			break;
		}

		return windowInstance != nullptr
			? windowInstance->LocalWindowProc(hWnd, message, wParam, lParam)
			: DefWindowProc(hWnd, message, wParam, lParam);
	}

	LRESULT CALLBACK Win32Window::LocalWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		//All events will get triggered, instead of enqueued, due to multithreaded OS event polling.
		EventDispatcher& dispatcher = m_engine.lock()->GetEventSystem().GetEventDispatcher("Window");

		switch (message)
		{

		case WM_MOUSEHWHEEL: //Redefined mouse wheel points to the wrong windows version, ms bug or SDK bug?
		case 0x020A:
		{
			float wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			if (abs(wheelDelta) >= WHEEL_DELTA)
			{
				MouseWheelEventArgs e(wheelDelta);
				m_input.lock()->OnMouseScrollWheelChanged(e);
			}
			return 0;
		}

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			// All painting occurs here, between BeginPaint and EndPaint.
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(hwnd, &ps);

			return 0;
		}

		case WM_LBUTTONDOWN:
		{
			MouseButtonEventArgs e(MouseButtonEventArgs::MouseButton::Left, MouseButtonEventArgs::ButtonState::Pressed);
			m_input.lock()->OnMouseButtonChanged(e);
			SetCapture(m_handle);
			return 0;
		}
		case WM_MBUTTONDOWN:
		{
			MouseButtonEventArgs e(MouseButtonEventArgs::MouseButton::Middle, MouseButtonEventArgs::ButtonState::Pressed);
			m_input.lock()->OnMouseButtonChanged(e);
			SetCapture(m_handle);
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			MouseButtonEventArgs e(MouseButtonEventArgs::MouseButton::Right, MouseButtonEventArgs::ButtonState::Pressed);
			m_input.lock()->OnMouseButtonChanged(e);
			SetCapture(m_handle);
			return 0;
		}
		case WM_LBUTTONUP:
		{
			MouseButtonEventArgs e(MouseButtonEventArgs::MouseButton::Left, MouseButtonEventArgs::ButtonState::Released);
			m_input.lock()->OnMouseButtonChanged(e);
			ReleaseCapture();
			return 0;
		}
		case WM_MBUTTONUP:
		{
			MouseButtonEventArgs e(MouseButtonEventArgs::MouseButton::Middle, MouseButtonEventArgs::ButtonState::Released);
			m_input.lock()->OnMouseButtonChanged(e);
			ReleaseCapture();
			return 0;
		}
		case WM_RBUTTONUP:
		{
			MouseButtonEventArgs e(MouseButtonEventArgs::MouseButton::Right, MouseButtonEventArgs::ButtonState::Released);
			m_input.lock()->OnMouseButtonChanged(e);
			ReleaseCapture();
			return 0;
		}
		case WM_MOUSEMOVE:
		{
			MouseMotionEventArgs e(LOWORD(lParam), HIWORD(lParam));
			m_input.lock()->OnMouseMoveChanged(e);
			return 0;
		}
		case WM_KEYDOWN:
		{
			MSG charMsg;
			// Get the Unicode character (UTF-16)
			unsigned int c = 0;
			// For printable characters, the next message will be WM_CHAR.
			// This message contains the character code we need to send the KeyPressed event.
			// Inspired by the SDL 1.2 implementation.
			if (PeekMessage(&charMsg, m_handle, 0, 0, PM_NOREMOVE) && charMsg.message == WM_CHAR)
			{
				GetMessage(&charMsg, m_handle, 0, 0);
				c = static_cast<unsigned int>(charMsg.wParam);
			}
			KeyCode key = static_cast<KeyCode>(wParam);
			if (key == KeyCode::Escape) m_windowClose = true; //Escape = close application.

			bool shift = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
			bool control = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
			bool alt = (GetAsyncKeyState(VK_MENU) & 0x8000) != 0;
			unsigned int scanCode = (lParam & 0x00FF0000) >> 16;
			KeyEventArgs e(key, c, KeyEventArgs::KeyState::Pressed, shift, control, alt);
			m_input.lock()->OnKeyboardStateChanged(e);
			return 0;
		}
		case WM_KEYUP:
		{
			KeyCode key = (KeyCode)wParam;

			bool shift = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
			bool control = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
			bool alt = (GetAsyncKeyState(VK_MENU) & 0x8000) != 0;
			unsigned int c = 0;
			unsigned int scanCode = (lParam & 0x00FF0000) >> 16;

			// Determine which key was released by converting the key code and the scan code
			// to a printable character (if possible).
			// Inspired by the SDL 1.2 implementation.
			unsigned char keyboardState[256];
			if (!GetKeyboardState(keyboardState))
				printf("Unrecognized key!\n");
			wchar_t translatedCharacters[4];
			if (int result = ToUnicodeEx(static_cast<UINT>(wParam), scanCode, keyboardState, translatedCharacters, 4, 0, NULL) > 0)
			{
				c = translatedCharacters[0];
			}

			KeyEventArgs e(key, c, KeyEventArgs::KeyState::Released, shift, control, alt);
			m_input.lock()->OnKeyboardStateChanged(e);
			return 0;
		}
		case WM_ACTIVATE:
		{
			if (LOWORD(wParam) == WA_INACTIVE)
			{
				dispatcher.trigger<SFM::WindowPauseEventArgs>(true);
			}
			else
			{
				dispatcher.trigger<SFM::WindowPauseEventArgs>(false);
			}
			return 0;
		}

		case WM_SIZE:
		{
			m_widthInPx = LOWORD(lParam);
			m_heightInPx = HIWORD(lParam);

			WindowResizeEventArgs resizeArgs(m_widthInPx, m_heightInPx);

			if (wParam == SIZE_MINIMIZED)
			{
				dispatcher.trigger<SFM::WindowPauseEventArgs>(false);
				m_minimized = true;
				m_maximized = false;
			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				dispatcher.trigger<SFM::WindowPauseEventArgs>(true);
				m_minimized = false;
				m_maximized = true;
				dispatcher.trigger<SFM::WindowResizeEventArgs>(resizeArgs);
			}
			else if (wParam == SIZE_RESTORED)
			{
				if (m_minimized) // Restoring from minimized state?
				{
					dispatcher.trigger<SFM::WindowPauseEventArgs>(true);
					m_minimized = false;
					dispatcher.trigger<SFM::WindowResizeEventArgs>(resizeArgs);
				}
				else if (m_maximized) // Restoring from maximized state?
				{
					dispatcher.trigger<SFM::WindowPauseEventArgs>(true);
					m_maximized = false;
					dispatcher.trigger<SFM::WindowResizeEventArgs>(resizeArgs);
				}
				else if (!m_resizing)
				{
					dispatcher.trigger<SFM::WindowResizeEventArgs>(resizeArgs);
				}
			}
			return 0;
		}

		// WM_ENTERSIZEMOVE is sent when the user grabs the resize bars.
		case WM_ENTERSIZEMOVE:
		{
			dispatcher.trigger<SFM::WindowPauseEventArgs>(true);
			m_resizing = true;
			return 0;
		}

		// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
		// Here we reset everything based on the new window dimensions.
		case WM_EXITSIZEMOVE:
		{
			dispatcher.trigger<SFM::WindowPauseEventArgs>(false);
			m_resizing = false;
			WindowResizeEventArgs resizeArgs(m_widthInPx, m_heightInPx);
			dispatcher.trigger<SFM::WindowResizeEventArgs>(resizeArgs);
			return 0;
		}
		
		// Don't beep when we alt-enter.
		case WM_MENUCHAR:
			return MAKELRESULT(0, MNC_CLOSE);

			// Catch this message so to prevent the window from becoming too small.
		case WM_GETMINMAXINFO:
			((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
			((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
			return 0;

			//Catch the window destruction flag.
		case WM_DESTROY:
			m_windowClose = true;
			PostQuitMessage(0);
			return 0;

		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
	}
}