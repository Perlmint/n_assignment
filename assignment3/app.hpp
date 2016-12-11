#pragma once
#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <atomic>
#include <thread>
#include <set>
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

  void loadData();

private:
  HWND m_hwnd;
  unique_interface<ID2D1Factory> m_pDirect2dFactory;
  unique_interface<ID2D1HwndRenderTarget> m_pRenderTarget;
  unique_interface<ID2D1SolidColorBrush> m_pLightSlateGrayBrush;
  unique_interface<ID2D1SolidColorBrush> m_pCornflowerBlueBrush;
  unique_interface<ID2D1SolidColorBrush> m_pCrimsonBrush;
  unique_interface<ID2D1SolidColorBrush> m_pMediumOrchidBrush;
  unique_interface<IDWriteFactory> m_pWriteFactory;

  static const UINT ID_TIMER_REFRESH_SCREEN = 1;
  static const UINT ID_TIMER_LOADING_UPDATE = 2;
  static const UINT ID_MENU_BEGIN_POINT = 3;
  static const UINT ID_MENU_END_POINT = 4;

  World m_world;
  std::atomic_bool m_loaded = false;
  uint8_t m_loadingPeriodCount = 1;
  unique_interface<IDWriteTextFormat> m_loadingTextFormat;

  static const int mapRatio = 500;
  static const int zoomMax = 120;
  static const int zoomMin = 1;
  static const int zoomForRoadRank[];
  struct
  {
    int mostLeft;
    int mostRight;
    int mostTop;
    int mostBottom;
  } m_renderInfo;
  PointD m_center;
  double m_zoomLevel;
  std::pair<double, double> m_renderSize;
  void DrawInfo();
  unique_interface<IDWriteTextFormat> m_infoTextFormat;
  void DrawNode();
  void DrawNode(const PointD &worldPoint, ID2D1SolidColorBrush* pen);
  void DrawPath();
  void UpdateRenderSize();
  void UpdateRenderArea();
  PointD WorldToScreenPos(PointD worldPos) const;
  PointD ScreenToWorld(PointD screenPos) const;
  void UpdateZoomLevel(short delta);

  std::pair<int, int> m_prevMousePos;
  void UpdateCenter(int x, int y, bool down);

  PointD m_clickedPoint;
  PointD m_beginPoint;
  bool m_beginPointIsValid = false;
  PointD m_endPoint;
  bool m_endPointIsValid = false;
  void SetMenuOpenedPoint(double x, double y);
  void SetUserPoint(bool isBeginPoint);

  std::set<uint64_t> m_selectedPaths;
  uint64_t m_beginNode;
  uint64_t m_endNode;

  void * m_pathFindingThread = nullptr;
};
