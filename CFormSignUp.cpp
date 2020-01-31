// CFormSignUp.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_Chat_Client.h"
#include "CFormSignUp.h"
#include "afxdialogex.h"


// CFormSignUp 대화 상자

IMPLEMENT_DYNAMIC(CFormSignUp, CDialog)

CFormSignUp::CFormSignUp(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_FORM_SIGNUP, pParent)
	, m_strEditSignUpPassword(_T(""))
	, m_strEditSignUpPasswordCheck(_T(""))
{

}

CFormSignUp::~CFormSignUp()
{
}

void CFormSignUp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SIGNUP_ID, m_strEditSignUpId);
	DDX_Text(pDX, IDC_EDIT_SIGNUP_PASSWORD, m_strEditSignUpPassword);
	DDX_Text(pDX, IDC_EDIT_SIGNUP_PASSWORD_CHECK, m_strEditSignUpPasswordCheck);
}


BEGIN_MESSAGE_MAP(CFormSignUp, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SIGNUP_OK, &CFormSignUp::OnBnClickedButtonSignupOk)
	ON_BN_CLICKED(IDC_BUTTON_SIGNUP_CANCEL, &CFormSignUp::OnBnClickedButtonSignupCancel)
	ON_MESSAGE(UM_SIGNUPFORMAT, &CFormSignUp::EditControlReset)
END_MESSAGE_MAP()


// CFormSignUp 메시지 처리기


void CFormSignUp::OnBnClickedButtonSignupOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(); // 윈도우에서 변수로 데이터 이동

	if (m_strEditSignUpId.IsEmpty() || m_strEditSignUpPassword.IsEmpty() || m_strEditSignUpPasswordCheck.IsEmpty()) {
		AfxMessageBox(_T("ID 혹은 PASSWORD를 입력해주세요."));
		return;
	}

	if (m_strEditSignUpPassword != m_strEditSignUpPasswordCheck) {
		AfxMessageBox(_T("'PASSWORD'와 'PASSWORD CHECK'의 값이 다릅니다."));
		return;
	}

	Json::Value value;
	value["type"] = 1;
	value["userId"] = string(CT2CA(m_strEditSignUpId.operator LPCWSTR()));	// CString -> string
	value["userPassword"] = string(CT2CA(m_strEditSignUpPassword.operator LPCWSTR()));
	value["userPasswordCheck"] = string(CT2CA(m_strEditSignUpPasswordCheck.operator LPCWSTR()));

	Json::FastWriter fastWriter;
	string str = fastWriter.write(value);

	CString cstr = CString::CStringT(CA2CT(str.c_str()));	// string -> CString

	AfxMessageBox(cstr);
	AfxGetMainWnd()->SendMessage(UM_SOCKETSEND, (WPARAM)(LPSTR)(LPCTSTR)cstr);
}

void CFormSignUp::OnBnClickedButtonSignupCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxGetMainWnd()->SendMessage(UM_CHANGEFORM, (WPARAM)1);
}

LRESULT CFormSignUp::EditControlReset(WPARAM wParam, LPARAM lParam) {
	m_strEditSignUpId = "";
	m_strEditSignUpPassword = "";
	m_strEditSignUpPasswordCheck = "";

	UpdateData(false);
	
	return 0;
}