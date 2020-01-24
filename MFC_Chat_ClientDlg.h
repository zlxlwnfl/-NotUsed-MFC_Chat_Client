
// MFC_Chat_ClientDlg.h: 헤더 파일
//

#pragma once

#include "CConnectSocket.h"

// CMFCChatClientDlg 대화 상자
class CMFCChatClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCChatClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CConnectSocket socket;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CHAT_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
