#pragma once

#include <QtWidgets/QWidget>
#include "ui_MLAssistant.h"
#include "psworker.h"
#include <QMainWindow>
class MLAssistant : public QWidget
{
	Q_OBJECT

public:
	MLAssistant(QWidget *parent = Q_NULLPTR);

	void initHook();
	void unHook();
	static void OnQueueAttachProcess(quint32 ProcessId, quint32 ThreadId, quint32 hWnd, QString dllPath);
signals:
	void sig_OnQueueAttachProcess(quint32 ProcessId, quint32 ThreadId, quint32 hWnd, QString dllPath);
public slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void OnNotifyAttachProcessOk(quint32 ProcessId, quint32 port, quint32 hwnd);
	void OnNotifyAttachProcessFailed(quint32 ProcessId, int errorCode, QString errorString);
	void OnNotifyQueryProcess(CProcessItemList list);
	void slotOnQueueAttachProcess(quint32 ProcessId, quint32 ThreadId, quint32 hWnd, QString dllPath);
private:
	Ui::MLAssistantClass ui;
	QMap<DWORD, int> m_processForPort;	//进程id和通信端口 注入成功后，有个通信端口
	QMap<DWORD, QMainWindow*> m_processForMainWindow;
};
