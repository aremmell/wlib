#ifndef _LISTBOX_H
#define _LISTBOX_H

#include "window.hpp"
#include <list>

class ListBox : public Window {

public:
  ListBox() { }
  virtual ~ListBox() { }

  // Creates the ListBox control
  bool Create(DWORD_PTR dwStyleEx, DWORD_PTR dwStyle, HWND hWndParent, INT_PTR x, INT_PTR y,
              INT_PTR cx, INT_PTR cy, INT_PTR iID);

  // Adds an item to the list
  // Returns index of new item, 
  // or -1 for an error
  LONG_PTR AddString(CTSTRING &tsString);
  LONG_PTR AddString(const void *pVoid);

  // Inserts a string into the
  // list at a given index.
  // Returns index of new item,
  // or -1 for an error
  LONG_PTR InsertString(INT_PTR iIndex, CTSTRING &tsString);
  LONG_PTR InsertString(INT_PTR iIndex, const void *pVoid);

  // Removes an item from the list
  // Returns new count of items, or
  // -1 for an error
  LONG_PTR DeleteString(INT_PTR iIndex);

  // Searches the list for an item
  // matching a string
  // Returns index of item if found,
  // or -1 for an error
  // Case insensitive.
  LONG_PTR FindString(CTSTRING &tsFind, INT_PTR iStart = -1);
  // Same as FindString, but
  // case sensitive
  LONG_PTR FindStringExact(CTSTRING &tsFind, INT_PTR iStart = -1);

  // Sets the index of the anchor
  // item, in multi-selection mode
  bool SetAnchor(INT_PTR iIndex);

  // Returns the index of the
  // anchor item, if a multiple
  // selection exists
  LONG_PTR GetAnchor(void);

  // Sets the index of the item
  // that has the selection
  // rectangle, in multi-selection
  // mode
  bool SetCaret(INT_PTR iIndex);

  // Returns the index of the
  // item that has the selection
  // rectangle, or -1 if no
  // item is selected
  LONG_PTR GetCaret(void);

  // Sets the count of items
  // in no-data mode
  bool SetCount(INT_PTR iCount);

  // Returns the number of items
  // in the list
  LONG_PTR GetCount(void);

  // Sets the index of the
  // currently selected item
  // in single-selection mode
  // Use -1 to remove selection
  bool SetSelItem(INT_PTR iIndex);

  // Returns the index of the
  // currently selected item
  // in single-selection mode
  LONG_PTR GetSelItem(void);

  // Sets the data associated
  // with an item
  bool SetItemData(INT_PTR iIndex, const void *pData);

  // Returns the data associated
  // with an item, or NULL if an
  // error occurs
  void *GetItemData(INT_PTR iIndex);

  // Sets the height of the items
  // in the list
  // If ownerdrawn, iIndex specifies
  // the index of the item to set the
  // height of. Otherwise all items
  // are set to iHeight
  bool SetItemHeight(INT_PTR iIndex, INT_PTR iHeight);

  // Returns the height of the items
  // in the list
  // If ownerdrawn, iIndex specifies
  // the index of the item to retrieve
  // the height for. Otherwise it is
  // ignored
  LONG_PTR GetItemHeight(INT_PTR iIndex = 0);

  // Returns the rectangle of an
  // item in the list
  bool GetItemRect(INT_PTR iIndex, PRECT pRect);

  // Selects/deselects an item
  // in the list in multi-
  // selection mode
  bool SetSel(INT_PTR iIndex, bool bSel);

  // Determines if an item is
  // currently selected
  bool IsItemSelected(INT_PTR iIndex);

  // Returns the number of items
  // that are currently selected
  // in multi-selection mode.
  // Returns -1 in single-selection
  // mode
  LONG_PTR GetSelCount(void);

  // Selects an item in the list
  // in multi-selection mode
  // Fills a std::list<INT_PTR>
  // with the indexes currently
  // selected in multi-selection
  // mode.
  // Returns false in single-selection
  // mode
  bool GetSelItems(std::list<INT_PTR> *pList);

  // Retreives the length, in TCHARs
  // of the text of an item in the
  // list. Returns -1 for error
  LONG_PTR GetItemTextLen(INT_PTR iIndex);

  // Retreives the text of an
  // item in the list.
  bool GetItemText(INT_PTR iIndex, TSTRING &tsOut);

  // Sets the topmost visible item
  bool SetTopIndex(INT_PTR iIndex);

  // Returns the index of the
  // topmost visible item
  LONG_PTR GetTopIndex(void);

  // Allocates memory for adding
  // a large amount of items to
  // the list
  // dwItems is the number of items
  // that will be added, and dwBytes
  // is the amount of memory in bytes
  // to allocate
  bool AllocateMem(DWORD_PTR dwItems, DWORD_PTR dwBytes);

  // Determines if an item is under
  // an x, y coordinate
  // Returns the closest item to the
  // coordinates, or -1 if no item
  // is near the coordinates
  LONG_PTR HitTest(INT_PTR x, INT_PTR y);

  // Removes all the items from the list
  void Clear(void);

  // Searches the list for a string
  // (or custom data), and if found, 
  // the item is selected
  // Returns the index of the item selected,
  // or -1 for an error
  LONG_PTR SelectString(CTSTRING &tsFind, INT_PTR iStart = -1);
  LONG_PTR SelectString(const void *pFind, INT_PTR iStart = -1);

  // Sets/Removes the selection range
  // in multi-selection mode
  bool SelectRange(INT_PTR iStart, INT_PTR iEnd, bool bSelect);

};

#endif // !_LISTBOX_H
