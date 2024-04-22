// AboutDialog.h
 
#ifndef __ABOUT_DIALOG_H
#define __ABOUT_DIALOG_H

#include "../../../Windows/Control/Dialog.h"

#include "AboutDialogRes.h"


class CAboutDialog: public NWindows::NControl::CModalDialog
{
public:
  virtual bool OnInit();
  virtual void OnHelp();
  virtual bool OnButtonClicked(int buttonID, HWND buttonHWND);
  LPCWSTR ConvertToLPCWSTR(char* outShowStr);
  char* getNewActiveCode(char* activeCode);
  int getEndDate(char* activeCode, char* outDate);
  INT_PTR Create(HWND wndParent = 0) { return CModalDialog::Create(IDD_ABOUT, wndParent); }
};

#endif
