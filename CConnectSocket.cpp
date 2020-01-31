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
		AfxMessageBox(_T("서버로부터 메시지를 받았습니다."));

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
			AfxMessageBox(_T("중복되는 아이디가 존재합니다."));
			break;
		case TYPE::signUp_success:
			AfxMessageBox(_T("회원가입에 성공하였습니다."));
			AfxGetMainWnd()->SendMessage(UM_CHANGEFORM, (WPARAM)1);
			break;
		case TYPE::signIn_failure:
			AfxMessageBox(_T("아이디 및 비밀번호를 다시 확인해주십시오."));
			break;
		case TYPE::signIn_success:
			AfxMessageBox(_T("로그인에 성공하였습니다."));
			AfxGetMainWnd()->SendMessage(UM_CHANGEFORM, (WPARAM)3, (LPARAM)1);
			break;
		case TYPE::chat_sentence:
			AfxMessageBox(_T("채팅 대화 데이터를 가져왔습니다."));
			AfxGetMainWnd()->SendMessage(UM_CHATSENTENCEGET, (WPARAM)(LPSTR)(LPCTSTR)CString::CStringT(CA2CT(recvMessage.c_str())));	// string -> CString
			break;
		case TYPE::chatList_user:
			AfxMessageBox(_T("유저 채팅방 리스트를 가져왔습니다."));
			AfxGetMainWnd()->SendMessage(UM_CHATLISTUSERGET, (WPARAM)(LPSTR)(LPCTSTR)CString::CStringT(CA2CT(recvMessage.c_str())));	// string -> CString
			break;
		}
	}
	
	CSocket::OnReceive(nErrorCode);
}
