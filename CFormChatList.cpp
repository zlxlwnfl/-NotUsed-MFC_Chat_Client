// CFormChatList.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_Chat_Client.h"
#include "CFormChatList.h"
#include "afxdialogex.h"


// CFormChatList 대화 상자

IMPLEMENT_DYNAMIC(CFormChatList, CDialogEx)

CFormChatList::CFormChatList(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FORM_CHAT_LIST, pParent)
{
}

CFormChatList::~CFormChatList()
{
}

void CFormChatList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDD_TAB_CHAT_LIST, m_tabChatList);
}


BEGIN_MESSAGE_MAP(CFormChatList, CDialogEx)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CFormChatList 메시지 처리기

void CFormChatList::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (GetSafeHwnd() != NULL) {
		m_tabChatList.InsertItem(0, _T("친구 채팅"));
		m_tabChatList.InsertItem(1, _T("오픈 채팅"));

		CRect Rect;
		m_tabChatList.GetClientRect(&Rect);
		m_formChatListUser.Create(IDD_FORM_CHAT_LIST_USER, &m_tabChatList);
		m_formChatListUser.SetWindowPos(NULL, -10, -10, Rect.Width(), Rect.Height() - 15, SWP_SHOWWINDOW | SWP_NOZORDER);
	}
}
