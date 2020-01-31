
// MFC_Chat_ClientDlg.cpp: 구현 파일
//
#pragma once

#include "pch.h"
#include "framework.h"
#include "MFC_Chat_Client.h"
#include "MFC_Chat_ClientDlg.h"
#include "afxdialogex.h"
#include "json.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCChatClientDlg 대화 상자



CMFCChatClientDlg::CMFCChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_CHAT_CLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pwndShow = NULL;
}

void CMFCChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_tabMain);
}

BEGIN_MESSAGE_MAP(CMFCChatClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_CHANGEFORM, &CMFCChatClientDlg::OnChangeForm)
	ON_MESSAGE(UM_SOCKETSEND, &CMFCChatClientDlg::OnSocketSend)
	ON_MESSAGE(UM_CHATSENTENCEGET, &CMFCChatClientDlg::OnChatSentenceGet)
	ON_MESSAGE(UM_CHATLISTUSERDEMAND, &CMFCChatClientDlg::OnUserChatListDemand)
	ON_MESSAGE(UM_CHATLISTUSERGET, &CMFCChatClientDlg::OnUserChatListGet)
	ON_WM_DESTROY()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CMFCChatClientDlg::OnTcnSelchangeTabMain)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMFCChatClientDlg 메시지 처리기

BOOL CMFCChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	// 소켓 설정
	socket.Create();
	if (socket.Connect(_T("192.168.242.133"), 8080) == FALSE) {
		if (GetLastError() != WSAEWOULDBLOCK) {
			AfxMessageBox(_T("failed to connect server!"));
			PostQuitMessage(0);
			return FALSE;
		}
	}
	
	// 대화상자 폼 설정
	CRect Rect;
	this->GetClientRect(&Rect);
	
	m_formSignIn.Create(IDD_FORM_SIGNIN);
	m_formSignIn.SetWindowPos(NULL, 0, 0, Rect.Width(), Rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
	m_formSignUp.Create(IDD_FORM_SIGNUP);
	m_formSignUp.SetWindowPos(NULL, 0, 0, Rect.Width(), Rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);
	
	// 메인 탭 설정
	m_tabMain.InsertItem(0, _T("친구 목록"));
	m_tabMain.InsertItem(1, _T("채팅 목록"));
	m_tabMain.InsertItem(2, _T("설정"));

	m_tabMain.GetClientRect(&Rect);
	m_formChatList.Create(IDD_FORM_CHAT_LIST, &m_tabMain);
	m_formChatList.SetWindowPos(NULL, -10, -10, Rect.Width() + 10, Rect.Height() - 15, SWP_NOZORDER);

	// 보일 폼 설정
	m_pwndShow = &m_formSignIn;
	m_pwndShow->ShowWindow(SW_SHOW);
	m_pwndShow = &m_formSignUp;
	m_pwndShow->ShowWindow(SW_HIDE);
	m_pwndShow = &m_tabMain;
	m_pwndShow->ShowWindow(SW_HIDE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCChatClientDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCChatClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CMFCChatClientDlg::OnChangeForm(WPARAM wParam, LPARAM lParam) {
	int index = (int)wParam;

	switch (index)
	{
	case 0:	// SignUp on
		m_pwndShow = &m_formSignUp;
		m_pwndShow->ShowWindow(SW_SHOW);
		m_pwndShow = &m_formSignIn;
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = &m_tabMain;
		m_pwndShow->ShowWindow(SW_HIDE);
		m_formSignIn.SendMessage(UM_SIGNINFORMAT);
		break;
	case 1:	// SignIn on
		m_pwndShow = &m_formSignIn;
		m_pwndShow->ShowWindow(SW_SHOW);
		m_pwndShow = &m_formSignUp;
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = &m_tabMain;
		m_pwndShow->ShowWindow(SW_HIDE);
		m_formSignUp.SendMessage(UM_SIGNUPFORMAT);
		break;
	case 2: // Chat on
		m_pwndShow = &m_formSignUp;
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = &m_formSignIn;
		m_pwndShow->ShowWindow(SW_HIDE);
		break;
	case 3: // Main on
		m_pwndShow = &m_tabMain;
		m_pwndShow->ShowWindow(SW_SHOW);
		m_pwndShow = &m_formSignUp;
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = &m_formSignIn;
		m_pwndShow->ShowWindow(SW_HIDE);

		if ((int)lParam == 1)
			m_formSignIn.SendMessage(UM_SIGNINFORMAT, (WPARAM)1);

		m_formSignIn.SendMessage(UM_SIGNINFORMAT);
		break;
	}

	return 0;
}

LRESULT CMFCChatClientDlg::OnSocketSend(WPARAM wParam, LPARAM lParam) {
	CString cstr;
	BSTR bstr = SysAllocString((BSTR)wParam);
	cstr = bstr;
	SysFreeString(bstr);

	//WideCharToMultiByte() 는 변환에 필요한 길이를 반환한다
	int len = WideCharToMultiByte(CP_ACP, 0, cstr, -1, NULL, 0, NULL, NULL);
	char* cTemp = new char[sizeof(char) * len + 1];
	WideCharToMultiByte(CP_ACP, 0, cstr, -1, cTemp, len, NULL, NULL);
	
	socket.Send(cTemp, sizeof(char) * len + 1);
	
	delete[] cTemp;
	
	return 0;
}

LRESULT CMFCChatClientDlg::OnChatSentenceGet(WPARAM wParam, LPARAM lParam) {
	m_formChatList.m_formChatListUser.SendMessage(UM_CHATSENTENCEGET, wParam);

	return 0;
}

LRESULT CMFCChatClientDlg::OnUserChatListDemand(WPARAM wParam, LPARAM lParam) {
	Json::Value value;
	value["type"] = 6;
	value["userId"] = string(CT2CA(userId.operator LPCWSTR()));	// CString -> string

	Json::FastWriter fastWriter;
	string str = fastWriter.write(value);

	CString cstr = CString::CStringT(CA2CT(str.c_str()));	// string -> CString

	SendMessage(UM_SOCKETSEND, (WPARAM)(LPSTR)(LPCTSTR)cstr);
	
	return 0;
}

void CMFCChatClientDlg::OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int nIndex = m_tabMain.GetCurSel();

	if(nIndex == 1) { // 채팅 목록
		m_pwndShow = &m_formChatList;
		m_pwndShow->ShowWindow(SW_SHOW);
		this->SendMessage(UM_CHATLISTUSERDEMAND);
	}
}

LRESULT CMFCChatClientDlg::OnUserChatListGet(WPARAM wParam, LPARAM lParam) {
	CString cstr;
	BSTR bstr = SysAllocString((BSTR)wParam);
	cstr = bstr;
	SysFreeString(bstr);

	string recvMessage = string(CT2CA(cstr.operator LPCWSTR()));

	Json::Reader reader;
	Json::Value value;
	reader.parse(recvMessage, value);

	CString chatId;
	CString type;
	CString title;
	vector<CString> participant;
	CString tmp;

	Json::Value chatInfo = value["chatInfo"];
	for (Json::Value::ArrayIndex i = 0; i != chatInfo.size(); i++) {
		chatId = chatInfo[i]["_id"]["$oid"].asCString();
		type = chatInfo[i]["type"].asCString();
		title = chatInfo[i]["title"].asCString();

		if (title == _T(""))
			title = _T("채팅방 제목이 없습니다.");

		for (Json::Value::ArrayIndex j = 0; j != chatInfo[i]["participant"].size(); j++) {
			tmp = chatInfo[i]["participant"][j].asCString();
			participant.push_back(tmp);
		}
	}

	DTOChatList DTO(chatId, type, title, participant);
	userChatMap[chatId] = DTO;
	m_formChatList.m_formChatListUser.SendMessage(UM_CHATLISTUSERGET);

	return 0;
}

void CMFCChatClientDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	socket.OnClose(0);

	CDialogEx::OnClose();
}
