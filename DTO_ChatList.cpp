#pragma once

#include "pch.h"
#include "afxstr.h"
#include <vector>

using namespace std;

class DTOChatList {
public:
	CString chatId;
	CString type;
	CString title;
	vector<CString> participant;

	DTOChatList() { }

	DTOChatList(CString chatId, CString type, CString title,
					vector<CString> participant) {
		this->chatId = chatId;
		this->type = type;
		this->title = title;
		this->participant = participant;
	}
};