#pragma once

// CFormChat 대화 상자

class CFormChat : public CDialog
{
	DECLARE_DYNAMIC(CFormChat)

public:
	CFormChat(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFormChat();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_CHAT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox	m_listChat;
	CString		m_strEditChat;
	CString		chatId;

	afx_msg void OnBnClickedButtonChat();
	LRESULT OnChatDemand(WPARAM wParam, LPARAM lParam);
	LRESULT OnChatSentenceGet(WPARAM wParam, LPARAM lParam);
	void PostNcDestroy();
};
