#pragma once

#include "CFormChatListUser.h"

// CFormChatList 대화 상자

class CFormChatList : public CDialogEx
{
	DECLARE_DYNAMIC(CFormChatList)

public:
	CFormChatList(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFormChatList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_CHAT_LIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CFormChatListUser	m_formChatListUser;
	CWnd*				m_pwndShow;
	CTabCtrl m_tabChatList;
	
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
