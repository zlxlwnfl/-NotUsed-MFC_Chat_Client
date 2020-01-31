#pragma once

#include "json.h"

using namespace std;


// CFormSignUp 대화 상자

class CFormSignUp : public CDialog
{
	DECLARE_DYNAMIC(CFormSignUp)

public:
	CFormSignUp(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFormSignUp();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_SIGNUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strEditSignUpId;
	CString m_strEditSignUpPassword;
	CString m_strEditSignUpPasswordCheck;

	afx_msg void OnBnClickedButtonSignupOk();
	afx_msg void OnBnClickedButtonSignupCancel();
	LRESULT EditControlReset(WPARAM wParam, LPARAM lParam);
};
