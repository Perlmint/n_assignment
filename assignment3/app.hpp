#pragma once
#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <future>
#include "World.hpp"

template<typename T>
class unique_interface
{
public:
  explicit unique_interface(T*val = nullptr): _val(val) {}
  ~unique_interface() { reset(); }
  unique_interface &operator=(T*val) { reset(val); return *this; }
  T* operator->() { return _val; }
  const T* operator->() const { return _val; }
  T &operator*() { return *_val; }
  const T &operator*() const { return *_val; }
  // ReSharper disable once CppNonExplicitConversionOperator
  operator bool() { return _val != nullptr; }
  // ReSharper disable once CppNonExplicitConversionOperator
  operator T*() { return _val; }
  T** operator&() { return &_val; }
  void reset(T* val = nullptr)
  {
    if (_val != nullptr)
    {
      _val->Release();
    }
    _val = val;
  }
private:
  T* _val = nullptr;
};


class App
{
public:
  App();
  ~App();

  // Register the window class and call methods for instantiating drawing resources
  HRESULT Initialize();

  // Process and dispatch messages
  void RunMessageLoop() const;

private:
  // Initialize device-independent resources.
  HRESULT CreateDeviceIndependentResources();

  // Initialize device-dependent resources.
  HRESULT CreateDeviceResources();

  // Release device-dependent resource.
  void DiscardDeviceResources();

  // Draw content.
  HRESULT OnRender();

  // Resize the render target.
  void OnResize(
    UINT width,
    UINT height
  );

  // The windows procedure.
  static LRESULT CALLBACK WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
  );

  std::future<World> loadData();

private:
  HWND m_hwnd;
  unique_interface<ID2D1Factory> m_pDirect2dFactory;
  unique_interface<ID2D1HwndRenderTarget> m_pRenderTarget;
  unique_interface<ID2D1SolidColorBrush> m_pLightSlateGrayBrush;
  unique_interface<ID2D1SolidColorBrush> m_pCornflowerBlueBrush;
};
