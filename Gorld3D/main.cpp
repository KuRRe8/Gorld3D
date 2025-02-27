#include "Gorld3D.h"

char *logger_tag = "     ";

void crtsignalHandler(int signum)
{
	std::fprintf(stderr,"signalHandler catched SIG%d", signum);
#ifdef _DEBUG
	while (true)
	{
		typedef int(*A) (char32_t, float);
		register auto __declspec(deprecated)  B = reinterpret_cast<wchar_t*> (0);
		void* __vectorcall C();
	}
#endif // _DEBUG
	exit(signum);
}

UCHAR load_ini()
{
	return static_cast<UCHAR> (0);
}

int APIENTRY main(int argc, char *argv[])
{
#pragma region(c runtime)
	signal(SIGFPE, crtsignalHandler);
	int ret_chk;
	SYSTEMTIME st;
	GetLocalTime(&st);
#pragma endregion

#pragma region(easy logger)
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("System"));
	setbuf(stdout, NULL);
	/* initialize EasyLogger */
	elog_init();
	/* set EasyLogger log format */
	elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
	elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
	elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
	elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
	elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
	elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
	/* start EasyLogger */
	elog_start();
	log_i("app initiating at %4d/%2d/%2d %2d:%2d:%2d.%3d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#pragma endregion

	QApplication protogonus(argc, argv);
	protogonus.setFont(QFont("simsun", 20));

	QCoreApplication::setApplicationName("Gorld3D");
	QCoreApplication::setOrganizationName("ZKRZ");
	QCoreApplication::setApplicationVersion(G3D_INTERNAL_VERSION);


	QPixmap pmp;
	ret_chk = pmp.load(":/image/splash.png");
	QSplashScreen splash(pmp);
	splash.show();
	QString qs;
	qs = ("     Gorld3D Print     v0.0.2");
	splash.showMessage(qs, Qt::AlignLeft | Qt::AlignVCenter | Qt::AlignJustify, Qt::black);
	protogonus.processEvents();

#pragma region(QOpenGL related)
	///load qrc after splash
	//Q_INIT_RESOURCE(textures);

	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);//Stencil Test
	QSurfaceFormat::setDefaultFormat(format);

#pragma endregion

#pragma region(localization)
	QTranslator *translator = new QTranslator();
	bool loadFlag = translator->load("Gorld3D_zh.qm", ".");
	if (loadFlag == true) {
		log_v("load translate success");
		bool installFlag = protogonus.installTranslator(translator);
		if (installFlag == true) {
			log_i("install Gorld3D_zh.qm success");
		}
	}
	else
	{
		log_w("install Gorld3D_zh.qm failed ");
	}

	QTranslator *qtranslator = new QTranslator();
	bool qloadFlag = qtranslator->load("qt_zh_CN.qm", ".");
	if (qloadFlag == true) {
		log_v("load qtranslate success");
		bool qinstallFlag = protogonus.installTranslator(qtranslator);
		if (qinstallFlag == true) {
			log_i("install general translation success");
		}
	}
	else
	{
		log_w("install general translation failed ");
	}
#pragma endregion

#pragma region(singleton)
	HANDLE hMutex = CreateMutex(NULL, TRUE, L"Protogonus"); // instance mutex
	if (hMutex != NULL)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			QMessageBox::critical(qApp->activeWindow(), QObject::tr("Run simultaneously prohibited"), QObject::tr("Only one instance can be run at a time!"));
			log_e("forbidden multiple instances.");
			return 1;
		}
	}
#pragma endregion

	//get screen size
	QScreen *screen = QGuiApplication::primaryScreen();
	QRect mm = screen->availableGeometry();
	qint32 screen_width = mm.width();
	qint32 screen_height = mm.height();

	Gorld3D w;
	w.resize(screen_width*0.7, screen_height*0.8);
	w.show();

	protogonus.setFont(QFont("simsun", 10));
	splash.finish(&w);

	GetLocalTime(&st);
	log_i("app initiated at %4d/%2d/%2d %2d:%2d:%2d.%3d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	log_i("    ");
	return protogonus.exec();
}
