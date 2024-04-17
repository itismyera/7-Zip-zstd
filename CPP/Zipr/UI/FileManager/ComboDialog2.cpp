// ComboDialog.cpp

#include "StdAfx.h"
#include "ComboDialog2.h"

#include "../../../Windows/Control/Static.h"

#ifdef LANG
#include "LangUtils.h"
#endif

using namespace NWindows;

bool CComboDialog2::OnInit()
{
  #ifdef LANG
  LangSetDlgItems(*this, NULL, 0);
  #endif
  _comboBox1.Attach(GetItem(IDC_COMBO2_1));
  _comboBox2.Attach(GetItem(IDC_COMBO2_2));

  /*
  // why it doesn't work ?
  DWORD style = _comboBox.GetStyle();
  if (Sorted)
    style |= CBS_SORT;
  else
    style &= ~CBS_SORT;
  _comboBox.SetStyle(style);
  */
  SetText(Title);
  
  NControl::CStatic staticContol1;
  staticContol1.Attach(GetItem(IDT_COMBO2_1));
  staticContol1.SetText(Static1);
  _comboBox1.SetText(Value1);
  FOR_VECTOR (i, Strings1)
    _comboBox1.AddString(Strings1[i]);
  NormalizeSize();

  NControl::CStatic staticContol2;
  staticContol2.Attach(GetItem(IDT_COMBO2_2));
  staticContol2.SetText(Static2);
  _comboBox2.SetText(Value2);
  FOR_VECTOR (i, Strings2)
    _comboBox2.AddString(Strings2[i]);
  NormalizeSize();

  return CModalDialog::OnInit();
}

bool CComboDialog::OnSize(WPARAM /* wParam */, int xSize, int ySize)
{
  int mx, my;
  GetMargins(8, mx, my);
  int bx1, bx2, by;
  GetItemSizes(IDCANCEL, bx1, by);
  GetItemSizes(IDOK, bx2, by);
  int y = ySize - my - by;
  int x = xSize - mx - bx1;

  InvalidateRect(NULL);

  MoveItem(IDCANCEL, x, y, bx1, by);
  MoveItem(IDOK, x - mx - bx2, y, bx2, by);
  ChangeSubWindowSizeX(_comboBox1, xSize - mx * 2);
  ChangeSubWindowSizeX(_comboBox2, xSize - mx * 2 - 40);
  return false;
}

void CComboDialog::OnOK()
{
  _comboBox1.GetText(Value1);
  _comboBox2.GetText(Value2);
  CModalDialog::OnOK();
}
