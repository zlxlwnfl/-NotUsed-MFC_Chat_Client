// CFormChat.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_Chat_Client.h"
#include "CFormChat.h"
#include "afxdialogex.h"
#include "json.h"
#include "MFC_Chat_ClientDlg.h"


// CFormChat 대화 상자

IMPLEMENT_DYNAMIC(CFormChat, CDialog)

CFormChat::CFormChat(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_FORM_CHAT, pParent)
	, m_strEditChat(_T(""))
{
}

CFormChat::~CFormChat()
{
}

void CFormChat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CHAT, m_listChat);
	DDX_Text(pDX, IDC_EDIT_CHAT, m_strEditChat);
}


BEGIN_MESSAGE_MAP(CFormChat, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CHAT, &CFormChat::OnBnClickedButtonChat)
	ON_MESSAGE(UM_CHATDEMAND, &CFormChat::OnChatDemand)
	ON_MESSAGE(UM_CHATSENTENCEGET, &CFormChat::OnChatSentenceGet)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CFormChat 메시지 처리기


void CFormChat::OnBnClickedButtonChat()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(); // 윈도우에서 변수로 데이터 이동

	if (m_strEditChat.IsEmpty()) {
		return;
	}

	CMFCChatClientDlg* clientDlg = (CMFCChatClientDlg*)AfxGetMainWnd();

	Json::Value value;
	value["type"] = 5;
	value["chatId"] = string(CT2CA(chatId.operator LPCWSTR()));
	value["userId"] = string(CT2CA(clientDlg->userId.operator LPCWSTR()));
	value["chatStr"] = string(CT2CA(m_strEditChat.operator LPCWSTR()));	// CString -> string

	Json::FastWriter fastWriter;
	string str = fastWriter.write(value);

	CString cstr = CString::CStringT(CA2CT(str.c_str()));	// string -> CString

	AfxMessageBox(cstr);
	AfxGetMainWnd()->SendMessage(UM_SOCKETSEND, (WPARAM)(LPSTR)(LPCTSTR)cstr);
}

LRESULT CFormChat::OnChatSentenceGet(WPARAM wParam, LPARAM lParam) {
	CString cstr;
	BSTR bstr = SysAllocString((BSTR)wParam);
	cstr = bstr;
	SysFreeString(bstr);

	string recvMessage = string(CT2CA(cstr.operator LPCWSTR()));

	Json::Reader reader;
	Json::Value value;
	reader.parse(recvMessage, value);

	// 대화 데이터 파싱
	CString userId;
	CString chatStr;
	long date;
	CString result;

	Json::Value sentence = value["sentence"];
	Json::Value tmp;
	for (Json::Value::ArrayIndex i = 0; i != sentence.size(); i++) {
		userId = sentence[i]["userId"].asCString();
		date = sentence[i]["date"].asLargestInt();
		chatStr = sentence[i]["chatStr"].asCString();

		result = userId + _T(" : ") + chatStr;
		m_listChat.AddString(result);
	}
	
	return 0;
}

void CFormChat::PostNcDestroy() {
	delete this;

	CDialog::PostNcDestroy();
}

LRESULT CFormChat::OnChatDemand(WPARAM wParam, LPARAM lParam) {
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString cstr;
	BSTR bstr = SysAllocString((BSTR)wParam);
	cstr = bstr;
	SysFreeString(bstr);

	chatId = cstr;

	Json::Value value;
	value["type"] = 4;
	value["chatId"] = string(CT2CA(cstr.operator LPCWSTR()));	// CString -> string

	Json::FastWriter fastWriter;
	string str = fastWriter.write(value);

	cstr = CString::CStringT(CA2CT(str.c_str()));	// string -> CString

	AfxMessageBox(cstr);
	AfxGetMainWnd()->SendMessage(UM_SOCKETSEND, (WPARAM)(LPSTR)(LPCTSTR)cstr);
	
	return 0;
}