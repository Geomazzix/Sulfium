#pragma once
#include "ApplicationCore/Window/WindowEventArgs.h"
#include "ApplicationCore/Input/InputEventArgs.h"
#include "ApplicationCore/Input/Input.h"

namespace SFM
{
	/// <summary>
	/// Window specifically created for the Windows OS.
	/// Other window implementation are to follow when that platform will be supported.
	/// </summary>
	class Win32Window
	{
	public:
		Win32Window();
		~Win32Window() = default;

		void Initialize(std::weak_ptr<Engine> engine, const std::wstring& title, std::weak_ptr<Input> input, UINT width, UINT height, bool showWindow = true);
		void Destroy();

		void PollEvents();

		HWND GetWindowHandle() const;
		UINT GetWindowWidth() const;
		UINT GetWindowHeight() const;
		const std::wstring& GetWindowTitle() const;

		void Show();
		void Hide();

		bool DoesWindowClose() const;

		void UpdateWindowTitleStats(uint32_t frameCountPerSec);

	protected:
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK LocalWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HWND m_handle;
		UINT m_widthInPx;
		UINT m_heightInPx;
		std::wstring m_title;
		std::wstring m_className;
		
		std::weak_ptr<Input> m_input;
		std::weak_ptr<Engine> m_engine;

		bool m_windowClose;
		bool m_minimized;
		bool m_maximized;
		bool m_resizing;
	};
}