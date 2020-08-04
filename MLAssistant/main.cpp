#include "MLAssistant.h"
#include <QtWidgets/QApplication>
#include "../CGALib/gameinterface.h"

//CGA::CGAInterface *g_CGAInterface = NULL;
//CProcessWorker *g_pProcessWorker;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//g_CGAInterface = CGA::CreateInterface();
	//g_pProcessWorker = new CProcessWorker(NULL);

	MLAssistant w;
	w.show();
	return a.exec();
}
