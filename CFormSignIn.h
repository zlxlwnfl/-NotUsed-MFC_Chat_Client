#pragma once

#include "json.h"

// CFormSignIn 대화 상자

class CFormSignIn : public CDialog
{
	DECLARE_DYNAMIC(CFormSignIn)

public:
	CFormSignIn(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFormSignIn();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_SIGNIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString	m_strEditSignInId;
	CString	m_strEditSignInPassword;

	afx_msg void OnBnClickedButtonSignup();
	afx_msg void OnBnClickedButtonSignin();
	LRESULT EditControlReset(WPARAM wParam, LPARAM lParam);
};
