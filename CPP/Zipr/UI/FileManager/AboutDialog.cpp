// AboutDialog.cpp

#include "StdAfx.h"

#include "../../../../C/CpuArch.h"

#include "../../MyVersion.h"

#include "../Common/LoadCodecs.h"

#include "AboutDialog.h"
#include "PropertyNameRes.h"

#include "HelpUtils.h"
#include "LangUtils.h"
#include "App.h"
#include "resource.h"

static const UInt32 kLangIDs[] =
{
  IDT_ABOUT_INFO
};

#define kHomePageURL  TEXT("https://www.zipr.cn")
#define kHomePageURL2 TEXT("https://www.zipr.cn/Zipr/")
#define kHelpTopic "start.htm"

#define LLL_(quote) L##quote
#define LLL(quote) LLL_(quote)

extern CCodecs *g_CodecsObj;

bool CAboutDialog::OnInit()
{
  #ifdef EXTERNAL_CODECS
  if (g_CodecsObj)
  {
    UString s;
    g_CodecsObj->GetCodecsErrorMessage(s);
    if (!s.IsEmpty())
      MessageBoxW(GetParent(), s, L"Zipr", MB_ICONERROR);
  }
  #endif

  LangSetDlgItems(*this, kLangIDs, ARRAY_SIZE(kLangIDs));
  SetItemText(IDT_ABOUT_VERSION, UString("Zipr " MY_VERSION_CPU));
  SetItemText(IDT_ABOUT_DATE, LLL(MY_DATE));

  UString fileName = fs2us(NWindows::NDLL::GetModuleDirPrefix());
  fileName += "reg.txt";
  HANDLE hFile = CreateFileW(
        fileName,                 
        GENERIC_READ,                  
        0,                             
        NULL,                          
        OPEN_EXISTING,                 
        FILE_ATTRIBUTE_NORMAL,         
        NULL                           
  );
 
  if (hFile != INVALID_HANDLE_VALUE) 
  {
      DWORD dwSize = GetFileSize(hFile, NULL);
      LPWSTR lpBuffer = new WCHAR[dwSize / sizeof(WCHAR) + 1];
      DWORD dwRead;
      UString activateCode;
      UString activateDate;

      if (!ReadFile(hFile, lpBuffer, dwSize, &dwRead, NULL)) {
         
          CloseHandle(hFile);
          delete[] lpBuffer;
      }
      else {
          lpBuffer[dwSize / sizeof(WCHAR)] = L'\0';
          LPCWSTR lpcwszBuffer = lpBuffer;
          activateCode = lpcwszBuffer;
          activateDate = lpcwszBuffer;
          SetItemText(IDT_ABOUT_INFO, LangString(IDS_ACTIVATE_SOFTWAR_ERROR3) + activateCode);
          SetItemText(IDT_ABOUT_INFO2, LangString(IDS_ACTIVATE_SOFTWAR_ERROR4) + activateDate);

          //CloseHandle(hFile);
          delete[] lpBuffer;
      }
  }
 
  CloseHandle(hFile); 
  LangSetWindowText(*this, IDD_ABOUT);
  NormalizePosition();
  return CModalDialog::OnInit();
}

void CAboutDialog::OnHelp()
{
  ShowHelpWindow(kHelpTopic);
}

bool CAboutDialog::OnButtonClicked(int buttonID, HWND buttonHWND)
{
  LPCTSTR url = kHomePageURL;
  switch (buttonID)
  {
    case IDB_ABOUT_HOMEPAGE: url = kHomePageURL; break;
    case IDB_ABOUT_ACTIVATION: 
        {
          CModalDialog::OnButtonClicked(IDCLOSE, buttonHWND);
          g_App.GetFocusedPanel().ActivateSoftware();
          return true;
        }
    default:
      return CModalDialog::OnButtonClicked(buttonID, buttonHWND);
  }

  SHELLEXECUTEINFO s;
  memset(&s, 0, sizeof(s));
  s.cbSize = sizeof(s);
  s.lpFile = url;
  ::ShellExecuteEx(&s);

  return true;
}
