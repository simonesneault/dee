
#include "deeBlurWin.h"

#include <QLibrary>
#include <QApplication>
#include <QWidget>
#include <QList>
#include <QPointer>

// Linux 
#ifdef Q_WS_X11
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <QX11Info>
#endif

// OSX
// this should do it -> http://blog.steventroughtonsmith.com/2008/03/using-core-image-filters-onunder.html 


// WINDOW 7
#ifdef Q_WS_WIN
#include <qt_windows.h>

#define DWM_BB_ENABLE                 0x00000001  // fEnable has been specified
#define DWM_BB_BLURREGION             0x00000002  // hRgnBlur has been specified
#define DWM_BB_TRANSITIONONMAXIMIZED  0x00000004  // fTransitionOnMaximized has been specified
#define WM_DWMCOMPOSITIONCHANGED        0x031E    // Composition changed window message

typedef struct _DWM_BLURBEHIND
{
	DWORD dwFlags;
	BOOL fEnable;
	HRGN hRgnBlur;
	BOOL fTransitionOnMaximized;
} DWM_BLURBEHIND, *PDWM_BLURBEHIND;

typedef struct _MARGINS
{
	int cxLeftWidth;
	int cxRightWidth;
	int cyTopHeight;
	int cyBottomHeight;
} MARGINS, *PMARGINS;

typedef HRESULT (WINAPI *PtrDwmIsCompositionEnabled)(BOOL* pfEnabled);
typedef HRESULT (WINAPI *PtrDwmExtendFrameIntoClientArea)(HWND hWnd, const MARGINS* pMarInset);
typedef HRESULT (WINAPI *PtrDwmEnableBlurBehindWindow)(HWND hWnd, const DWM_BLURBEHIND* pBlurBehind);
typedef HRESULT (WINAPI *PtrDwmGetColorizationColor)(DWORD *pcrColorization, BOOL *pfOpaqueBlend);

static PtrDwmIsCompositionEnabled pDwmIsCompositionEnabled= 0;
static PtrDwmEnableBlurBehindWindow pDwmEnableBlurBehindWindow = 0;
static PtrDwmExtendFrameIntoClientArea pDwmExtendFrameIntoClientArea = 0;
static PtrDwmGetColorizationColor pDwmGetColorizationColor = 0;

#endif

namespace dee{

    #ifdef Q_WS_WIN

    class WindowNotifier : public QWidget
    {
    public:
        WindowNotifier() { winId(); }
        void addWidget(QWidget *widget) { widgets.append(widget); }
        void removeWidget(QWidget *widget) { widgets.removeAll(widget); }
        bool winEvent(MSG *message, long *result);

    private:
        QWidgetList widgets;
    };

    static bool resolveLibs()
    {
        if (!pDwmIsCompositionEnabled) {
            QLibrary dwmLib(QString::fromAscii("dwmapi"));
            pDwmIsCompositionEnabled =(PtrDwmIsCompositionEnabled)dwmLib.resolve("DwmIsCompositionEnabled");
            pDwmExtendFrameIntoClientArea = (PtrDwmExtendFrameIntoClientArea)dwmLib.resolve("DwmExtendFrameIntoClientArea");
            pDwmEnableBlurBehindWindow = (PtrDwmEnableBlurBehindWindow)dwmLib.resolve("DwmEnableBlurBehindWindow");
            pDwmGetColorizationColor = (PtrDwmGetColorizationColor)dwmLib.resolve("DwmGetColorizationColor");
        }
        return pDwmIsCompositionEnabled != 0;
    }
    #endif

    bool BlurWin::isCompositionEnabled(){
        #ifdef Q_WS_WIN
        if (resolveLibs()) {
            HRESULT hr = S_OK;
            BOOL isEnabled = false;
            hr = pDwmIsCompositionEnabled(&isEnabled);
            if (SUCCEEDED(hr))
                return isEnabled;

        }
        #endif

        #ifdef Q_WS_X11
        return true;
        #endif

        return false;
    }

    bool BlurWin::enableBlurBehindWindow(QWidget *widget, bool enable)
    {
        Q_ASSERT(widget);
        bool result = false;

#ifdef Q_WS_X11
        Display *dpy = QX11Info::display();
        Atom atom = XInternAtom(dpy, "_KDE_NET_WM_BLUR_BEHIND_REGION", False);

        if (enable) {
            QRegion region = QRegion();
            QVector<QRect> rects = region.rects();
            QVector<quint32> data;
            for (int i = 0; i < rects.count(); i++) {
                const QRect r = rects[i];
                data << r.x() << r.y() << r.width() << r.height();
            }

            XChangeProperty( dpy, widget->winId(), atom, XA_CARDINAL, 32, PropModeReplace, reinterpret_cast<const unsigned char *>(data.constData()), data.size() );
        } else {
            XDeleteProperty( dpy, widget->winId(), atom );
        }
        result=true;
#endif

#ifdef Q_WS_WIN

        if (resolveLibs()) {

            DWM_BLURBEHIND bb = {0};
            HRESULT hr = S_OK;
            bb.fEnable = enable;
            bb.dwFlags = DWM_BB_ENABLE;
            bb.hRgnBlur = NULL;
            widget->setAttribute(Qt::WA_TranslucentBackground, enable);
            widget->setAttribute(Qt::WA_NoSystemBackground, enable);
            hr = pDwmEnableBlurBehindWindow(widget->winId(), &bb);
            if (SUCCEEDED(hr)) {
                result = true;
                windowNotifier()->addWidget(widget);
            }
        }
#endif
     //   if( stl::getPlatformName().contains( "_8") )
       //     return false;
        return result;
    }

#ifdef Q_WS_WIN
    WindowNotifier *BlurWin::windowNotifier(){
        static WindowNotifier *windowNotifierInstance = 0;
        if (!windowNotifierInstance)
            windowNotifierInstance = new WindowNotifier;
        return windowNotifierInstance;
    }

    bool WindowNotifier::winEvent(MSG *message, long *result){
        if (message && message->message == WM_DWMCOMPOSITIONCHANGED) {
            bool compositionEnabled = BlurWin::isCompositionEnabled();
            foreach(QWidget * widget, widgets) {
                if (widget) {
                    widget->setAttribute(Qt::WA_NoSystemBackground, compositionEnabled);
                }
                widget->update();
            }
        }
        return QWidget::winEvent(message, result);
    }
#endif
}
