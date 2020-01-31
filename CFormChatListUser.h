#pragma once

#include "CFormChat.h"
#include <vector>
#include <map>

using namespace std;

// CFormChatListUser 대화 상자

class CFormChatListUser : public CDialogEx
{
	DECLARE_DYNAMIC(CFormChatListUser)

public:
	CFormChatListUser(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFormChatListUser();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_CHAT_LIST_USER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox		m_listChatListUser;
	vector<CString>				chatId;
	map<CString, CFormChat*>	chatDlgMap;

	afx_msg void OnLbnDblclkChatListUser();
	LRESULT OnUserChatListGet(WPARAM wParam, LPARAM lParam);
	LRESULT OnChatSentenceGet(WPARAM wParam, LPARAM lParam);
};
