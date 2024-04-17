// ComboDialog.h

#ifndef __COMBO_DIALOG2_H
#define __COMBO_DIALOG2_H

#include "../../../Windows/Control/ComboBox.h"
#include "../../../Windows/Control/Dialog.h"

#include "ComboDialogRes2.h"

class CComboDialog2: public NWindows::NControl::CModalDialog
{
  NWindows::NControl::CComboBox _comboBox1;
  NWindows::NControl::CComboBox _comboBox2;
  virtual void OnOK();
  virtual bool OnInit();
  virtual bool OnSize(WPARAM wParam, int xSize, int ySize);
public:
  // bool Sorted;
  UString Title;
  UString Static1;
  UString Value1;
  UString Static2;
  UString Value2;
  UStringVector Strings1;
  UStringVector Strings2;
  
  // CComboDialog(): Sorted(false) {};
  INT_PTR Create(HWND parentWindow = 0) { return CModalDialog::Create(IDD_COMBO2, parentWindow); }
};

#endif
