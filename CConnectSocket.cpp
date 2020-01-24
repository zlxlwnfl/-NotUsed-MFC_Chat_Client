#include "pch.h"
#include "CConnectSocket.h"
#include "MFC_Chat_Client.h"
#include "MFC_Chat_ClientDlg.h"

#define BUF_SIZE 1024

CConnectSocket::CConnectSocket()
{
}

CConnectSocket::~CConnectSocket()
{
}

void CConnectSocket::OnClose(int nErrorCode)
{
	ShutDown();
	Close();

	AfxMessageBox(_T("socket closed..."));
	
	CSocket::OnClose(nErrorCode);
}

void CConnectSocket::OnReceive(int nErrorCode)
{
	TCHAR szBuffer[BUF_SIZE];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	CSocket::OnReceive(nErrorCode);
}
