#include "MLAssistant.h"
#include <QButtonGroup>
#include <windows.h>
#include "psworker.h"
#include <QDebug>
#include <QMessageBox>
#include "mainwindow.h"
static HHOOK g_hHook = 0;
static QList<HWND> g_attachHwndList;		//ע��ɹ��ľ�� �����ж��Ƿ��Ѿ�ע�룬ע���˾Ͳ���Ӧ��ݼ���
MLAssistant* g_assistant;
MLAssistant::MLAssistant(QWidget *parent)
	: QWidget(parent)
{
	g_assistant = this;
	ui.setupUi(this);
	QButtonGroup *buttonGround = new QButtonGroup();
	buttonGround->addButton(ui.pushButton);
	buttonGround->addButton(ui.pushButton_2);
	buttonGround->addButton(ui.pushButton_3);
	buttonGround->addButton(ui.pushButton_4);
	buttonGround->setExclusive(true);
	initHook();
	connect(this,SIGNAL(sig_OnQueueAttachProcess(quint32, quint32, quint32, QString)),this,SLOT(slotOnQueueAttachProcess(quint32, quint32, quint32,QString)), Qt::QueuedConnection);

	//connect(this,SIGNAL(sig_OnQueueAttachProcess(quint32, quint32, quint32, QString)),g_pProcessWorker,SLOT(OnQueueAttachProcess(quint32, quint32, quint32,QString)), Qt::QueuedConnection);
	//connect(g_pProcessWorker, &CProcessWorker::NotifyAttachProcessFailed, this, &MLAssistant::OnNotifyAttachProcessFailed, Qt::QueuedConnection);
	//connect(g_pProcessWorker, &CProcessWorker::NotifyAttachProcessOk, this, &MLAssistant::OnNotifyAttachProcessOk, Qt::QueuedConnection);
	//connect(g_pProcessWorker, &CProcessWorker::NotifyQueryProcess, this, &MLAssistant::OnNotifyQueryProcess, Qt::QueuedConnection);

}

// Hook callback   ���ӻص�����
LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode != HC_ACTION)
		return ::CallNextHookEx(g_hHook, nCode, wParam, lParam);
	LPKBDLLHOOKSTRUCT pKeyBoardHook = (KBDLLHOOKSTRUCT  FAR*)lParam;
	if (wParam == WM_KEYDOWN)
	{
		KBDLLHOOKSTRUCT *  keyNum = (KBDLLHOOKSTRUCT *)lParam;
		if (keyNum->vkCode == VK_INSERT)
		{//��ȡ��ǰ��Ϸ���� ����ע��
			POINT pi;
			::GetCursorPos(&pi);
			HWND hWnd = WindowFromPoint(pi);
			//����ע��
			if (!g_attachHwndList.contains(hWnd))
			{
				g_attachHwndList.append(hWnd);
				//ע�뺯������
				DWORD pid, tid;
				tid=GetWindowThreadProcessId(hWnd, (LPDWORD)&pid);
				qDebug() << pid;
				g_assistant->OnQueueAttachProcess(pid,tid,(quint32)hWnd, QString("cgahook.dll"));
			}
		}
	}
	return ::CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

void MLAssistant::OnQueueAttachProcess(quint32 ProcessId, quint32 ThreadId, quint32 hWnd, QString dllPath)
{
	emit g_assistant->sig_OnQueueAttachProcess(ProcessId, ThreadId, hWnd, dllPath);
//	g_pProcessWorker->OnQueueAttachProcess(ProcessId, ThreadId, hWnd, dllPath);
}
//����hook��ⰴ�� ע����Ϸ
void MLAssistant::initHook()
{
	HMODULE curModle = NULL;
	curModle = GetModuleHandle(NULL);
	g_hHook = ::SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, (HMODULE)curModle, 0);
}

void MLAssistant::unHook()
{
	UnhookWindowsHookEx(g_hHook);
}


void MLAssistant::on_pushButton_clicked()
{

}

void MLAssistant::on_pushButton_2_clicked()
{

}

void MLAssistant::on_pushButton_3_clicked()
{

}

void MLAssistant::on_pushButton_4_clicked()
{

}


void MLAssistant::OnNotifyAttachProcessOk(quint32 ProcessId, quint32 port, quint32 hwnd)
{

}

void MLAssistant::OnNotifyAttachProcessFailed(quint32 ProcessId, int errorCode, QString errorString)
{
	QMessageBox::critical(this, tr("Error"), tr("Failed to attach to process.\n%1").arg(errorString), QMessageBox::Ok, 0);
}

void MLAssistant::OnNotifyQueryProcess(CProcessItemList list)
{
	
}

void MLAssistant::slotOnQueueAttachProcess(quint32 ProcessId, quint32 ThreadId, quint32 hWnd, QString dllPath)
{
	MainWindow* pGameWnd = new MainWindow;
	pGameWnd->show();
}
