// CFormChatListUser.cpp: 구현 파일
//
#pragma once

#include "pch.h"
#include "MFC_Chat_Client.h"
#include "CFormChatListUser.h"
#include "afxdialogex.h"
#include "MFC_Chat_ClientDlg.h"
#include "DTO_ChatList.cpp"

using namespace std;


// CFormChatListUser 대화 상자

IMPLEMENT_DYNAMIC(CFormChatListUser, CDialogEx)

CFormChatListUser::CFormChatListUser(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FORM_CHAT_LIST_USER, pParent)
{
}

CFormChatListUser::~CFormChatListUser()
{
}

void CFormChatListUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHAT_LIST_USER, m_listChatListUser);
}


BEGIN_MESSAGE_MAP(CFormChatListUser, CDialogEx)
	ON_LBN_DBLCLK(IDC_CHAT_LIST_USER, &CFormChatListUser::OnLbnDblclkChatListUser)
	ON_MESSAGE(UM_CHATLISTUSERGET, &CFormChatListUser::OnUserChatListGet)
	ON_MESSAGE(UM_CHATSENTENCEGET, &CFormChatListUser::OnChatSentenceGet)
END_MESSAGE_MAP()


// CFormChatListUser 메시지 처리기

LRESULT CFormChatListUser::OnUserChatListGet(WPARAM wParam, LPARAM lParam) {
	if (GetSafeHwnd() != NULL) {
		CMFCChatClientDlg* clientDlg = (CMFCChatClientDlg*)AfxGetMainWnd();
		map<CString, DTOChatList>& userChatMap = clientDlg->userChatMap;

		CString title;
		map<CString, DTOChatList>::iterator iter;
		for (iter = userChatMap.begin(); iter != userChatMap.end(); iter++) {
			chatId.push_back(iter->first);

			title = iter->second.title;

			m_listChatListUser.AddString(title);
		}
	}

	return 0;
}


void CFormChatListUser::OnLbnDblclkChatListUser()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_listChatListUser.GetCurSel();

	AfxMessageBox(_T("유저 채팅 리스트 항목을 선택하였습니다."));

	CFormChat* chatDlg = new CFormChat;
	chatDlg->Create(IDD_FORM_CHAT);
	chatDlg->ShowWindow(SW_SHOW);

	CString cstr = chatId[index];
	chatDlgMap[cstr] = chatDlg;

	chatDlg->SendMessage(UM_CHATDEMAND, (WPARAM)(LPSTR)(LPCTSTR)cstr);
}

LRESULT CFormChatListUser::OnChatSentenceGet(WPARAM wParam, LPARAM lParam) {
	// chatId 파싱해서 그에 맞는 map의 second로 대화상자 포인터 얻고 거기에 채팅데이터 얻었다고 메시지 보내기
	CString cstr;
	BSTR bstr = SysAllocString((BSTR)wParam);
	cstr = bstr;
	SysFreeString(bstr);

	string recvMessage = string(CT2CA(cstr.operator LPCWSTR()));

	Json::Reader reader;
	Json::Value value;
	reader.parse(recvMessage, value);

	CString chatId;
	chatId = value["chatId"].asCString();

	CFormChat* chatDlg = chatDlgMap[chatId];
	chatDlg->SendMessage(UM_CHATSENTENCEGET, wParam);

	return 0;
}