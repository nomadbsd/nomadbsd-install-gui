#include <QApplication>
#include <QTranslator>

#include "defs.h"
#include "wizard.h"

int
main(int argc, char *argv[])
{
	QApplication app(argc, argv);  
	QTranslator translator;
	if (translator.load(QLocale(), QLatin1String(PROGRAM),
	    QLatin1String("_"), QLatin1String(":/i18n")))
		qApp->installTranslator(&translator);
	InstallWizard *wiz = new InstallWizard;
	wiz->show();

	return (app.exec());
}

