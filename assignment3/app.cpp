#include <thread>
#include <sstream>
#include "Windowsx.h"

#include "app.hpp"

const int App::zoomForRoadRank[] = { 100, 80, 60, 50, 40, 30 };

App::App()
  : m_hwnd(nullptr)
  , m_pDirect2dFactory(nullptr)
  , m_pRenderTarget(nullptr)
  , m_pLightSlateGrayBrush(nullptr)
  , m_pCornflowerBlueBrush(nullptr)
  , m_center(0, 0)
  , m_zoomLevel(0)
  , m_clickedPoint(0, 0)
  , m_beginPoint(0, 0)
  , m_endPoint(0, 0)
  , m_selectedPaths()
  , m_beginNode(0)
  , m_endNode(0)
{
}

App::~App()
{
}

// Register the window class and call methods for instantiating drawing resources
HRESULT App::Initialize()
{
  HRESULT hr;

  // Initialize device-indpendent resources, such
  // as the Direct2D factory.
  hr = CreateDeviceIndependentResources();

  if (SUCCEEDED(hr))
  {
    // Register the window class.
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = App::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = sizeof(LONG_PTR);
    wcex.hInstance = nullptr;
    wcex.hbrBackground = nullptr;
    wcex.lpszMenuName = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDI_APPLICATION);
    wcex.lpszClassName = "Assignment3";

    RegisterClassEx(&wcex);


    // Because the CreateWindow function takes its size in pixels,
    // obtain the system DPI and use it to scale the window size.
    FLOAT dpiX, dpiY;

    // The factory returns the current system DPI. This is also the value it will use
    // to create its own windows.
    m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);


    // Create the window.
    m_hwnd = CreateWindow(
      "Assignment3",
      "Assignment3",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      static_cast<UINT>(ceil(640.f * dpiX / 96.f)),
      static_cast<UINT>(ceil(480.f * dpiY / 96.f)),
      NULL,
      NULL,
      NULL,
      this
    );
    hr = m_hwnd ? S_OK : E_FAIL;
    if (SUCCEEDED(hr))
    {
      ShowWindow(m_hwnd, SW_SHOWNORMAL);
      UpdateWindow(m_hwnd);

      SetTimer(m_hwnd, ID_TIMER_REFRESH_SCREEN, 100 / 60, nullptr);
      loadData();
    }
  }

  return hr;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void App::RunMessageLoop() const
{
  MSG msg;

  while (GetMessage(&msg, nullptr, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

// Initialize device-independent resources.
HRESULT App::CreateDeviceIndependentResources()
{
  auto hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
  if (SUCCEEDED(hr))
  {
    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
      __uuidof(m_pWriteFactory),
      reinterpret_cast<IUnknown**>(&m_pWriteFactory));
  }

  return hr;
}

// Initialize device-dependent resources.
HRESULT App::CreateDeviceResources()
{
  auto hr = S_OK;

  if (!m_pRenderTarget)
  {
    RECT rc;
    GetClientRect(m_hwnd, &rc);

    auto size = D2D1::SizeU(
      rc.right - rc.left,
      rc.bottom - rc.top
    );

    // Create a Direct2D render target.
    hr = m_pDirect2dFactory->CreateHwndRenderTarget(
      D2D1::RenderTargetProperties(),
      D2D1::HwndRenderTargetProperties(m_hwnd, size),
      &m_pRenderTarget
    );


    if (SUCCEEDED(hr))
    {
      // Create a gray brush.
      hr = m_pRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::LightSlateGray),
        &m_pLightSlateGrayBrush
      );
    }
    if (SUCCEEDED(hr))
    {
      // Create a blue brush.
      hr = m_pRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
        &m_pCornflowerBlueBrush
      );
    }
    if (SUCCEEDED(hr))
    {
      // Create a blue brush.
      hr = m_pRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::Crimson),
        &m_pCrimsonBrush
      );
    }
    if (SUCCEEDED(hr))
    {
      // Create a blue brush.
      hr = m_pRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::MediumOrchid),
        &m_pMediumOrchidBrush
      );
    }
    if (SUCCEEDED(hr))
    {
      hr = m_pWriteFactory->CreateTextFormat(
        L"Arial",
        nullptr,
        DWRITE_FONT_WEIGHT_EXTRA_BOLD,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        30,
        L"",
        &m_loadingTextFormat);
    }
    if (SUCCEEDED(hr))
    {
      m_loadingTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

      m_loadingTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }
    if (SUCCEEDED(hr))
    {
      hr = m_pWriteFactory->CreateTextFormat(
        L"Arial",
        nullptr,
        DWRITE_FONT_WEIGHT_EXTRA_BOLD,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        10,
        L"",
        &m_infoTextFormat);
    }
    if (SUCCEEDED(hr))
    {
      m_infoTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

      m_infoTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    }
  }

  return hr;
}

// Release device-dependent resource.
void App::DiscardDeviceResources()
{
  m_pRenderTarget.reset();
  m_pLightSlateGrayBrush.reset();
  m_pCornflowerBlueBrush.reset();
}

// Draw content.
HRESULT App::OnRender()
{
  auto hr = CreateDeviceResources();

  if (SUCCEEDED(hr))
  {
    m_pRenderTarget->BeginDraw();

    m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

    m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

    if (!m_loaded)
    {
      auto renderTargetSize = m_pRenderTarget->GetSize();
      std::wstring str = L"Loading";
      for (uint8_t i = 0; i < m_loadingPeriodCount; ++i)
      {
        str.push_back('.');
      }
      m_pRenderTarget->DrawText(
        str.c_str(), str.length(),
        m_loadingTextFormat, D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
        m_pLightSlateGrayBrush);
    }
    else
    {
      DrawNode();
      DrawPath();
      DrawInfo();
    }

    hr = m_pRenderTarget->EndDraw();
  }

  if (hr == D2DERR_RECREATE_TARGET)
  {
    hr = S_OK;
    DiscardDeviceResources();
  }

  return hr;
}

// Resize the render target.
void App::OnResize(
  UINT width,
  UINT height
)
{
  if (m_pRenderTarget)
  {
    // Note: This method can fail, but it's okay to ignore the
    // error here, because the error will be returned again
    // the next time EndDraw is called.
    m_pRenderTarget->Resize(D2D1::SizeU(width, height));
    UpdateRenderSize();
    UpdateRenderArea();
  }
}

// The windows procedure.
LRESULT App::WndProc(
  HWND hWnd,
  UINT message,
  WPARAM wParam,
  LPARAM lParam
)
{
  LRESULT result = 0;

  if (message == WM_CREATE)
  {
    auto pcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
    auto pDemoApp = static_cast<App *>(pcs->lpCreateParams);

    ::SetWindowLongPtr(
      hWnd,
      GWLP_USERDATA,
      PtrToUlong(pDemoApp)
    );

    result = 1;
  }
  else
  {
    auto app = reinterpret_cast<App *>(static_cast<LONG_PTR>(
      ::GetWindowLongPtr(
        hWnd,
        GWLP_USERDATA
      )));

    auto wasHandled = false;

    if (app)
    {
      switch (message)
      {
      case WM_SIZE:
      {
        UINT width = LOWORD(lParam);
        UINT height = HIWORD(lParam);
        app->OnResize(width, height);
      }
      result = 0;
      wasHandled = true;
      break;

      case WM_DISPLAYCHANGE:
      {
        InvalidateRect(hWnd, nullptr, FALSE);
      }
      result = 0;
      wasHandled = true;
      break;

      case WM_PAINT:
      {
        app->OnRender();
        ValidateRect(hWnd, nullptr);
      }
      result = 0;
      wasHandled = true;
      break;

      case WM_TIMER:
      {
        switch (wParam)
        {
        case App::ID_TIMER_REFRESH_SCREEN:
          InvalidateRect(hWnd, nullptr, FALSE);
          break;
        case App::ID_TIMER_LOADING_UPDATE:
          app->m_loadingPeriodCount = (app->m_loadingPeriodCount + 1) % 5;
          break;
        default: break;
        }
      }
      break;
      case WM_RBUTTONUP:
      {
        if (app->m_loaded)
        {
          auto hPopupMenu = CreatePopupMenu();
          InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_MENU_BEGIN_POINT, "출발지점");
          InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_MENU_END_POINT, "도착지점");
          SetForegroundWindow(hWnd);
          POINT point = {
            GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)
          };
          app->SetMenuOpenedPoint(point.x, point.y);
          ClientToScreen(hWnd, &point);
          TrackPopupMenu(hPopupMenu, TPM_TOPALIGN | TPM_LEFTALIGN, point.x, point.y, 0, hWnd, nullptr);
        }
      }
      break;

      case WM_LBUTTONDOWN:
      {
        app->UpdateCenter(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), true);
      }
      break;

      case WM_MOUSEMOVE:
      {
        // left button is down
        // drag
        if (wParam & MK_LBUTTON)
        {
          app->UpdateCenter(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), false);
        }
      }
      break;

      case WM_MOUSEWHEEL:
      {
        if (!(wParam & (MK_CONTROL | MK_LBUTTON | MK_RBUTTON | MK_SHIFT | MK_XBUTTON1 | MK_XBUTTON2)))
        {
          auto wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
          app->UpdateZoomLevel(wheelDelta);
        }
      }
      break;

      case WM_DESTROY:
      {
        PostQuitMessage(0);
      }
      result = 1;
      wasHandled = true;
      break;

      case WM_COMMAND:
      {
        if (wParam == ID_MENU_BEGIN_POINT)
        {
          app->SetUserPoint(true);
        }
        else if (wParam == ID_MENU_END_POINT)
        {
          app->SetUserPoint(false);
        }
      }
      break;

      default: break;
      }
    }

    if (!wasHandled)
    {
      result = DefWindowProc(hWnd, message, wParam, lParam);
    }
  }

  return result;
}

void App::loadData()
{
  std::thread([this]()
  {
    SetTimer(m_hwnd, ID_TIMER_LOADING_UPDATE, 300, nullptr);
    World world{ "./data/MOCT_NODE.shp" , "./data/MOCT_LINK.shp" };
    m_world = std::move(world);
    m_loaded = true;
    m_center = m_world.center();
    m_zoomLevel = 5;
    KillTimer(m_hwnd, ID_TIMER_LOADING_UPDATE);
    UpdateRenderSize();
    UpdateRenderArea();
    m_world.BeginFinders();
  }).detach();
}

void App::DrawInfo()
{
  std::wstringstream stream;
  stream << "zoom : " << m_zoomLevel << std::endl;
  stream << "center :" << std::endl <<
    "  " << m_center.x << std::endl <<
    "  " << m_center.y << std::endl;
  if (_pathFinding)
  {
    stream << "Path finding...";
  }
  auto infoText = stream.str();
  m_pRenderTarget->DrawTextA(infoText.c_str(), infoText.length(),
    m_infoTextFormat, D2D1::RectF(0, 0, 100, 100), m_pLightSlateGrayBrush);
}

void App::DrawNode()
{
  if (m_beginPointIsValid)
  {
    DrawNode(m_beginPoint, m_pCrimsonBrush);
  }
  if (m_endPointIsValid)
  {
    DrawNode(m_endPoint, m_pMediumOrchidBrush);
  }
}

void App::DrawNode(const PointD &worldPoint, ID2D1SolidColorBrush* pen)
{
  auto nodeCenter = WorldToScreenPos(worldPoint);
  m_pRenderTarget->DrawRoundedRectangle(
    D2D1::RoundedRect(
      D2D1::RectF(
        static_cast<float>(nodeCenter.x - 2),
        static_cast<float>(nodeCenter.y - 2),
        static_cast<float>(nodeCenter.x + 2),
        static_cast<float>(nodeCenter.y + 2)),
      3, 3), pen);
}

void App::DrawPath()
{
  auto type = 101;
  for (const auto & zoom : zoomForRoadRank)
  {
    if (zoom < m_zoomLevel)
    {
      break;
    }
    ++type;
  }

  std::set<const Node *> nodes;

  for (auto x = m_renderInfo.mostLeft; x <= m_renderInfo.mostRight; ++x)
  {
    for (auto y = m_renderInfo.mostBottom; y <= m_renderInfo.mostTop; ++y)
    {
      for (const auto &path : m_world.PathsByChunk(x, y))
      {
        if (path.second->rank() > type)
        {
          continue; 
        }
        ID2D1Brush *pen = m_pLightSlateGrayBrush;
        if (m_selectedPaths.find(path.second->id()) != m_selectedPaths.end())
        {
          pen = m_pCrimsonBrush;
        }

        nodes.insert(path.second->begin());
        nodes.insert(path.second->end());
        auto pointItr = path.second->points().begin(), pointEnd = path.second->points().end();
        auto prevPoint = WorldToScreenPos(*pointItr);
        for (++pointItr; pointItr != pointEnd; ++pointItr)
        {
          auto curPoint = WorldToScreenPos(*pointItr);
          m_pRenderTarget->DrawLine(
            D2D1::Point2F(
              static_cast<float>(prevPoint.x),
              static_cast<float>(prevPoint.y)),
            D2D1::Point2F(
              static_cast<float>(curPoint.x),
              static_cast<float>(curPoint.y)),
            pen);
          prevPoint = curPoint;
        }
      }
    }
  }

  for (const auto &node : nodes)
  {
    DrawNode(node->point(), m_pCornflowerBlueBrush);
    ID2D1Brush *pen = nullptr;
    PointD point{0, 0};
    if (node->id() == m_beginNode)
    {
      pen = m_pCrimsonBrush;
      point = m_beginPoint;
    }
    else if (node->id() == m_endNode)
    {
      pen = m_pMediumOrchidBrush;
      point = m_endPoint;
    }

    if (pen != nullptr)
    {
      point = WorldToScreenPos(point);
      auto nearNode = WorldToScreenPos(node->point());
      m_pRenderTarget->DrawLine(
        D2D1::Point2F(
          static_cast<float>(point.x),
          static_cast<float>(point.y)),
        D2D1::Point2F(
          static_cast<float>(nearNode.x),
          static_cast<float>(nearNode.y)),
        pen);
    }
  }
}

void App::UpdateRenderSize()
{
  auto renderTargetSize = m_pRenderTarget->GetSize();
  auto ratio = World::chunkSize / mapRatio * m_zoomLevel;
  m_renderSize = std::make_pair(ratio * renderTargetSize.width, ratio * renderTargetSize.height);
}

void App::UpdateRenderArea()
{
  auto minX = m_center.x - m_renderSize.first / 2;
  auto maxX = m_center.x + m_renderSize.first / 2;
  auto minY = m_center.y - m_renderSize.second / 2;
  auto maxY = m_center.y + m_renderSize.second / 2;

  m_renderInfo.mostLeft = static_cast<int>(minX / World::chunkSize);
  m_renderInfo.mostRight = static_cast<int>(ceill(maxX / World::chunkSize));
  m_renderInfo.mostBottom = static_cast<int>(minY / World::chunkSize);
  m_renderInfo.mostTop = static_cast<int>(ceill(maxY / World::chunkSize));
}

PointD App::WorldToScreenPos(PointD worldPos) const
{
  auto renderTargetSize = m_pRenderTarget->GetSize();
  auto x = worldPos.x - m_center.x;
  auto y = worldPos.y - m_center.y;
  return PointD{
    renderTargetSize.width / 2 + x / m_renderSize.first * renderTargetSize.width,
    renderTargetSize.height / 2 + y / m_renderSize.second * renderTargetSize.height };
}

PointD App::ScreenToWorld(PointD screenPos) const
{
  auto renderTargetSize = m_pRenderTarget->GetSize();
  auto x = screenPos.x - renderTargetSize.width / 2;
  auto y = screenPos.y - renderTargetSize.height / 2;
  return PointD{
    m_center.x + x / renderTargetSize.width * m_renderSize.first,
    m_center.y + y / renderTargetSize.height * m_renderSize.second };
}

void App::UpdateZoomLevel(short delta)
{
  delta /= 100;
  auto prevLevel = m_zoomLevel;
  m_zoomLevel += delta;
  m_zoomLevel = min(m_zoomLevel, zoomMax);
  m_zoomLevel = max(m_zoomLevel, zoomMin);
  if (prevLevel != m_zoomLevel)
  {
    UpdateRenderSize();
    UpdateRenderArea();
    InvalidateRect(m_hwnd, nullptr, TRUE);
  }
}

void App::UpdateCenter(int x, int y, bool down)
{
  if (!down)
  {
    auto deltaX = x - m_prevMousePos.first;
    auto deltaY = y - m_prevMousePos.second;
    auto renderTargetSize = m_pRenderTarget->GetSize();
    m_center.x -= deltaX / renderTargetSize.width * m_renderSize.first;
    m_center.y -= deltaY / renderTargetSize.height * m_renderSize.second;
    UpdateRenderArea();
    InvalidateRect(m_hwnd, nullptr, TRUE);
  }
  m_prevMousePos.first = x;
  m_prevMousePos.second = y;
}

void App::SetMenuOpenedPoint(double x, double y)
{
  m_clickedPoint = ScreenToWorld(PointD{ x, y });
}

void App::SetUserPoint(bool isBeginPoint)
{
  if (isBeginPoint)
  {
    m_beginPoint = m_clickedPoint;
    m_beginPointIsValid = true;
  }
  else
  {
    m_endPoint = m_clickedPoint;
    m_endPointIsValid = true;
  }
  if (m_beginPointIsValid && m_endPointIsValid)
  {
    std::thread([this]() {
      _pathFinding = true;
      m_selectedPaths.clear();
      m_beginNode = 0;
      m_endNode = 0;
      InvalidateRect(m_hwnd, nullptr, true);

      auto beginNode = m_world.FindNearNode(m_beginPoint);
      auto endNode = m_world.FindNearNode(m_endPoint);
      auto paths = m_world.FindPath(beginNode, endNode);

      try {
        for (const auto &path : paths.get())
        {
          m_selectedPaths.insert(path->id());
        }
        m_beginNode = beginNode->id();
        m_endNode = endNode->id();
        InvalidateRect(m_hwnd, nullptr, true);
        _pathFinding = false;
      }
      catch (const std::exception &)
      {
        _pathFinding = false;
        // Do nothing
      }
    }).detach();
  }
}