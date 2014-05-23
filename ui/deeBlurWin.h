
#ifndef DEE_BLUR_WIN_H
#define DEE_BLUR_WIN_H

#include <QWidget>

namespace dee{

	class WindowNotifier;

	class BlurWin : public QObject
	{
		Q_OBJECT
	public:
		static bool enableBlurBehindWindow( QWidget *a_widget, bool a_enable = true );
		static bool isCompositionEnabled();

	private:
		static WindowNotifier *windowNotifier();
	};
}

#endif
