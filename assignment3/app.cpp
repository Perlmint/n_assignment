#include "app.hpp"

App::App() :
  m_hwnd(nullptr),
  m_pDirect2dFactory(nullptr),
  m_pRenderTarget(nullptr),
  m_pLightSlateGrayBrush(nullptr),
  m_pCornflowerBlueBrush(nullptr)
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
  auto hr = S_OK;

  // Create a Direct2D factory.
  hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

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
  auto hr = S_OK;

  hr = CreateDeviceResources();

  if (SUCCEEDED(hr))
  {
    m_pRenderTarget->BeginDraw();

    m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

    m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

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

    ::SetWindowLongPtrW(
      hWnd,
      GWLP_USERDATA,
      PtrToUlong(pDemoApp)
    );

    result = 1;
  }
  else
  {
    App *pDemoApp = reinterpret_cast<App *>(static_cast<LONG_PTR>(
      ::GetWindowLongPtrW(
        hWnd,
        GWLP_USERDATA
      )));

    bool wasHandled = false;

    if (pDemoApp)
    {
      switch (message)
      {
      case WM_SIZE:
      {
        UINT width = LOWORD(lParam);
        UINT height = HIWORD(lParam);
        pDemoApp->OnResize(width, height);
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
        pDemoApp->OnRender();
        ValidateRect(hWnd, nullptr);
      }
      result = 0;
      wasHandled = true;
      break;

      case WM_DESTROY:
      {
        PostQuitMessage(0);
      }
      result = 1;
      wasHandled = true;
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

std::future<World> App::loadData()
{
  return std::async(std::launch::async, []()
  {
    return World{ "./data/MOCT_NODE.shp" , "./data/MOCT_LINK.shp" };
  });
}