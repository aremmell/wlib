#ifndef _COMBOBOX_H
#define _COMBOBOX_H

#include "window.hpp"

class ComboBox : public Window {

public:
  ComboBox() {}
  virtual ~ComboBox() {}

  // Creates the control
  HWND Create(DWORD_PTR dwStyleEx, CTSTRING &tsTitle, DWORD_PTR dwStyle, INT_PTR x, INT_PTR y, INT_PTR cx, INT_PTR cy,
              HWND hWndParent, INT_PTR iID, HINSTANCE hInst = 0);

  // Adds a string
  bool AddString(CTSTRING &tsStr);

  // Deletes a string, specified by index
  bool DelString(INT_PTR iIndex);

  // Finds a string (case-insensitive)
  INT_PTR FindString(CTSTRING &tsSearch);

  // Finds a string (case-sensitive)
  INT_PTR FindStringExact(CTSTRING &tsSearch);

  // Gets information about the combo box
  bool GetComboBoxInfo(PCOMBOBOXINFO pcbi);

  // Returns the 1-based count of items in the combo box
  INT_PTR GetCount(void);

  // Returns the 0-based index of the currently selected
  // item, or CB_ERR if no item is selected
  INT_PTR GetCurSel(void);

  // Returns the width, in pixels, of the dropped-down
  // rectangle of the combo box, or CB_ERR if an error
  // occurs
  INT_PTR GetDroppedWidth(void);

  // Determines if the combo box is currently in the
  // dropped-down state
  bool IsDroppedDown(void);

  // Returns the beginning and ending character indexes
  // of the edit box in the combo box if a selection exists
  bool GetEditSel(DWORD_PTR *pStart, DWORD_PTR *pEnd);

  // Returns user data associated with an item
  LONG_PTR GetItemData(INT_PTR iItem);

  // Returns the height of the selection field or
  // a combo box item in the combo box
  // -1 is used to get the height of the selection field
  INT_PTR GetItemHeight(INT_PTR iItem = 0);

  // Retrieves the text of an item in the combo box
  bool GetItemText(INT_PTR iItem, TSTRING &tsText);

  // Retrieves the length of the text of an item in the
  // combo box (in TCHARs)
  INT_PTR GetItemTextLen(INT_PTR iItem);

  // Returns the locale code for the combo box
  DWORD_PTR GetLocale(void);

  // Returns the minimum number of visible items
  // displayable without a scroll bar
  INT_PTR GetMinVisible(void);

  // Returns the 0-based index of the first visible
  // item in the combo box
  INT_PTR GetTopIndex(void);

  // Use to allocate memory for items before adding
  // a large amount of items
  bool InitStorage(DWORD_PTR dwItems, DWORD_PTR dwBytes);

  // Inserts an item at a specified index, and does
  // not cause the combo box to re-sort
  // The default behaviour is to add the item at the end
  // of the list
  bool InsertString(CTSTRING &tsItem, INT_PTR iIndex = -1);

  // Sets the amount of characters the user may type in
  // the edit box of the combo box
  // The default behaviour is to limit the text to 0x7FFFFFFE chars
  void LimitText(INT_PTR iChars = 0);

  // Removes all items from the combo box
  void ResetContent(void);

  // Searches the combo box for a string,
  // and if it is found, sets it as the selected item
  bool SelectString(CTSTRING &tsSearch);

  // Sets the current selection in the combo box based
  // on an item index. if -1 is passed, all selections are cleared
  bool SetCurSel(INT_PTR iItem);

  // Sets the maximum width, in pixels, of the listbox
  // in the combo box
  bool SetDroppedWidth(DWORD_PTR dwWidth);

  // Sets the range of selection in the edit box in the combo box
  // use -1 for either to unselect the text in the edit box
  bool SetEditSel(WORD wStart, WORD wEnd);

  // Sets the user data associated with an item in the combo box
  bool SetItemData(INT_PTR iItem, DWORD_PTR dwData);

  // Sets the height of the selection field or items in the combo box
  // If the combo box is ownerdrawn, iItem is the index of the item to
  // set the height for. Otherwise, it should be zero. Set to -1
  // for selection field height
  bool SetItemHeight(INT_PTR iHeight, INT_PTR iItem = 0);

  // Sets the locale code for the combo box
  bool SetLocale(DWORD_PTR dwLocale);

  // Sets the minimum number of visible items in the drop down list
  bool SetMinVisible(DWORD_PTR dwItems);

  // Ensures that an item is visible in the drop down list
  bool SetTopIndex(INT_PTR iItem);

  // Shows or hides the drop down list
  void ShowDropdown(bool bShow = true);

};

#endif // !_COMBOBOX_H
