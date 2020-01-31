#pragma once

#include <afxsock.h>

class CConnectSocket : public CSocket
{
private:
	enum TYPE {
		signUp_idOverlap,
		signUp_success,
		signIn_failure,
		signIn_success,
		chat_sentence,
		chatList_user
	};
public:
	CConnectSocket();
	virtual ~CConnectSocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};

