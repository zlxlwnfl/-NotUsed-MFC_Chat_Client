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
	Json::Value value;
	value["type"] = 0;

	Json::FastWriter fastWriter;
	string str = fastWriter.write(value);

	CString cstr = CString::CStringT(CA2CT(str.c_str()));	// string -> CString

	AfxGetMainWnd()->SendMessage(UM_SOCKETSEND, (WPARAM)(LPSTR)(LPCTSTR)cstr);

	ShutDown();
	Close();
	
	CSocket::OnClose(nErrorCode);
}

void CConnectSocket::OnReceive(int nErrorCode)
{
	char buf[BUF_SIZE];
	string recvMessage;
	CString tmp;

	if (Receive(buf, sizeof(buf)) > 0) {
		AfxMessageBox(_T("�����κ��� �޽����� �޾ҽ��ϴ�."));

		buf[BUF_SIZE - 1] = 0;
		recvMessage = buf;

		Json::Reader reader;
		Json::Value value;
		reader.parse(recvMessage, value);

		int type = value["type"].asInt();

		tmp.Format(_T("%d"), type);
		AfxMessageBox(tmp);

		switch (type) {
		case TYPE::signUp_idOverlap:
			AfxMessageBox(_T("�ߺ��Ǵ� ���̵� �����մϴ�."));
			break;
		case TYPE::signUp_success:
			AfxMessageBox(_T("ȸ�����Կ� �����Ͽ����ϴ�."));
			AfxGetMainWnd()->SendMessage(UM_CHANGEFORM, (WPARAM)1);
			break;
		case TYPE::signIn_failure:
			AfxMessageBox(_T("���̵� �� ��й�ȣ�� �ٽ� Ȯ�����ֽʽÿ�."));
			break;
		case TYPE::signIn_success:
			AfxMessageBox(_T("�α��ο� �����Ͽ����ϴ�."));
			AfxGetMainWnd()->SendMessage(UM_CHANGEFORM, (WPARAM)3, (LPARAM)1);
			break;
		case TYPE::chat_sentence:
			AfxMessageBox(_T("ä�� ��ȭ �����͸� �����Խ��ϴ�."));
			AfxGetMainWnd()->SendMessage(UM_CHATSENTENCEGET, (WPARAM)(LPSTR)(LPCTSTR)CString::CStringT(CA2CT(recvMessage.c_str())));	// string -> CString
			break;
		case TYPE::chatList_user:
			AfxMessageBox(_T("���� ä�ù� ����Ʈ�� �����Խ��ϴ�."));
			AfxGetMainWnd()->SendMessage(UM_CHATLISTUSERGET, (WPARAM)(LPSTR)(LPCTSTR)CString::CStringT(CA2CT(recvMessage.c_str())));	// string -> CString
			break;
		}
	}
	
	CSocket::OnReceive(nErrorCode);
}
