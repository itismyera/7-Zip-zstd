// AboutDialog.cpp

#include "StdAfx.h"

#include "../../../../C/CpuArch.h"
extern "C"{
  #include "../../../../C/aesCode.h"
}

#include "../../MyVersion.h"

#include "../Common/LoadCodecs.h"

#include "AboutDialog.h"
#include "PropertyNameRes.h"

#include "HelpUtils.h"
#include "LangUtils.h"
#include "App.h"
#include "resource.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

static const UInt32 kLangIDs[] =
{
  IDT_ABOUT_INFO
};

#define kHomePageURL  TEXT("https://www.zipr.cn")
#define kHomePageURL2 TEXT("https://www.zipr.cn/Zipr/")
#define kHelpTopic "start.htm"

#define LLL_(quote) L##quote
#define LLL(quote) LLL_(quote)
#define  AES_ENC_MAX_LEN    (512)

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
      BOOL bResult = ReadFile(hFile, lpBuffer, dwSize, &dwRead, NULL);
      if (!bResult || dwRead == 0) {
         
          //CloseHandle(hFile);
          delete[] lpBuffer;
      }
      else {
          lpBuffer[dwSize / sizeof(WCHAR)] = L'\0';
          char* bufferRead = new char[dwSize + 1];
          WideCharToMultiByte(CP_ACP, 0, lpBuffer, -1, bufferRead, dwSize+1, NULL, NULL);
          char outDate[80];
          int success = getEndDate(bufferRead, outDate);
          if(success == 1){
              printf("end date is: %s\n", outDate);
              char* newActiveCode = getNewActiveCode(bufferRead);
              LPCWSTR outCodeStr = ConvertToLPCWSTR(newActiveCode);
              free(newActiveCode); 
              
              LPCWSTR outDateStr = ConvertToLPCWSTR(outDate);
              SetItemText(IDT_ABOUT_INFO, LangString(IDS_ACTIVATE_SOFTWAR_ERROR3) + outCodeStr);
              SetItemText(IDT_ABOUT_INFO2, LangString(IDS_ACTIVATE_SOFTWAR_ERROR4) + outDateStr);
          } else {
              printf("invalidCode");
          }

          //CloseHandle(hFile);
          delete[] bufferRead;
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
    case IDS_ACTIVATE_SOFTWARE: 
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

LPCWSTR CAboutDialog::ConvertToLPCWSTR(char* outShowStr) {
    // Step 1: Convert uint8_t* to char*
    // char* charString = reinterpret_cast<char*>(input);
    char* charString = outShowStr;
    OutputDebugStringA(charString);
    // Step 2: Convert char* to LPCWSTR using MultiByteToWideChar
    int len = MultiByteToWideChar(CP_ACP, 0, charString, -1, NULL, 0);
    wchar_t* wideString = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, charString, -1, wideString, len);

    return wideString;
}

char* CAboutDialog::getNewActiveCode(char* activeCode)
{
    int originalLength = strlen(activeCode);
    char *newStr = (char*)malloc(originalLength + 2); 
    int positionToInsert = 32;
    strncpy(newStr, activeCode, positionToInsert);
    newStr[positionToInsert] = '\n';
    strcpy(newStr + positionToInsert + 1, activeCode + positionToInsert);
    return newStr;
}

int CAboutDialog::getEndDate(char* activeCode, char* outDate)
{
    int sucess = 1;
    uint16_t i=0;
    char in[AES_ENC_MAX_LEN];
    memset(in, 0x00, AES_ENC_MAX_LEN);
    uint16_t length1 = strlen(activeCode);
    uint16_t length2 = length1/2;
    uint8_t activeU8[AES_ENC_MAX_LEN];

    for (i = 0; i < length2; i++) {
        sscanf(&activeCode[i * 2], "%2hhx", &activeU8[i]);
    }

    for (i = 0; i < length2; i++) {
        printf("%02x", activeU8[i]);
    }
    // printf("\n");
    // printf("origin info = %s \n", activeU8);
    memset(in, 0x00, AES_ENC_MAX_LEN);
    bool isSucess = DecryptCipherTxtToData(activeU8,(uint8_t*)in,length2);
    if (!isSucess) {
        sucess = 0;
        return sucess;
    }
    // printf("\n");
    // printf("input info = %s \n", in);
    
    // split char*
    const char delimiter[2] = "|";
    char* token[10];
    int index = 0;
    token[index] = strtok(in, delimiter);
    
    while (token[index] != NULL) {
        // printf("spilt char* = %s, %d\n", token[index], index);
        index ++ ;
        token[index] = strtok(NULL, delimiter);
    }
    // printf("%d\n", index);
    if (index != 4) {
        sucess = 0;
        return sucess;
    }
    double endDate = strtod(token[2], NULL)*100;
    // printf("%f\n", endDate);
    if (endDate <= 0) {
        sucess = 0;
        return sucess;
    }
    // timestamp to date
    time_t timestamp = endDate;
    struct tm* timeinfo;
    
    timeinfo = localtime(&timestamp);
    strftime(outDate, 80, "%Y-%m-%d", timeinfo);
    // printf("end date: %s\n", outDate);
    return sucess;
}

