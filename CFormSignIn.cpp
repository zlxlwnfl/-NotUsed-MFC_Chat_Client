// CFormSignIn.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_Chat_Client.h"
#include "CFormSignIn.h"
#include "afxdialogex.h"
#include "MFC_Chat_ClientDlg.h"

// CFormSignIn 대화 상자

IMPLEMENT_DYNAMIC(CFormSignIn, CDialog)

CFormSignIn::CFormSignIn(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_FORM_SIGNIN, pParent)
{
}

CFormSignIn::~CFormSignIn()
{
}

void CFormSignIn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SIGNIN_ID, m_strEditSignInId);
	DDX_Text(pDX, IDC_EDIT_SIGNIN_PASSWORD, m_strEditSignInPassword);
}


BEGIN_MESSAGE_MAP(CFormSignIn, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SIGNUP, &CFormSignIn::OnBnClickedButtonSignup)
	ON_BN_CLICKED(IDC_BUTTON_SIGNIN, &CFormSignIn::OnBnClickedButtonSignin)
	ON_MESSAGE(UM_SIGNINFORMAT, &CFormSignIn::EditControlReset)
END_MESSAGE_MAP()


// CFormSignIn 메시지 처리기


void CFormSignIn::OnBnClickedButtonSignup()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxGetMainWnd()->SendMessage(UM_CHANGEFORM, (WPARAM)0);
}


void CFormSignIn::OnBnClickedButtonSignin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(); // 윈도우에서 변수로 데이터 이동

	if (m_strEditSignInId.IsEmpty() || m_strEditSignInPassword.IsEmpty()) {
		AfxMessageBox(_T("ID 혹은 PASSWORD를 입력해주세요."));
		return;
	}

	Json::Value value;
	value["type"] = 2;
	value["userId"] = string(CT2CA(m_strEditSignInId.operator LPCWSTR()));	// CString -> string
	value["userPassword"] = string(CT2CA(m_strEditSignInPassword.operator LPCWSTR()));

	Json::FastWriter fastWriter;
	string str = fastWriter.write(value);
	
	CString cstr = CString::CStringT(CA2CT(str.c_str()));	// string -> CString

	AfxGetMainWnd()->SendMessage(UM_SOCKETSEND, (WPARAM)(LPSTR)(LPCTSTR)cstr);
}

LRESULT CFormSignIn::EditControlReset(WPARAM wParam, LPARAM lParam) {
	if ((int)wParam == 1) {
		CMFCChatClientDlg* clientDlg = (CMFCChatClientDlg*)AfxGetMainWnd();
		clientDlg->userId.SetString(m_strEditSignInId);
	}

	m_strEditSignInId = "";
	m_strEditSignInPassword = "";

	UpdateData(false); // 변수에서 윈도우로 데이터 이동

	return 0;
}