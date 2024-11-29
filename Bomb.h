
// Bomb.h : main header file for the Bomb application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CBombApp:
// See Bomb.cpp for the implementation of this class
//

class CBombApp : public CWinApp
{
public:
	CBombApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBombApp theApp;
