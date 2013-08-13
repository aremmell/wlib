#ifndef _LISTVIEW_H
#define _LISTVIEW_H

#include "window.hpp"
#include <commctrl.h>
#include "imagelist.hpp"

//
// Data structures
//
typedef struct tagLVNODE {

  tagLVNODE() {

    fMask       = 0U;
    iItem       = 0;
    iSubItem    = 0;
    fState      = 0U;
    fStateMask  = 0U;
    szText      = NULL;
    uiMaxChars  = 0U;
    iImage      = 0;
    iIndent     = 0;
    lParam      = 0;
#if (_WIN32_IE >= 0x560)
    iGroupID    = 0;
    uiColumns   = 0U;
    puiColumns  = NULL;
#endif

  }

  UINT_PTR fMask;
  INT_PTR iItem;
  INT_PTR iSubItem;
  UINT_PTR fState;
  UINT_PTR fStateMask;
  TCHAR *szText;
  UINT_PTR uiMaxChars;
  INT_PTR iImage;
  INT_PTR iIndent;
  LPARAM lParam;
#if (_WIN32_IE >= 0x560)
  INT_PTR iGroupID;
  UINT_PTR uiColumns;
  PUINT_PTR puiColumns;
#endif

} LVNODE, *PLVNODE;

//
// Type defines
//
class ListView : public Window {

public:
  ListView() {

    m_pSmlImgList   = NULL;
    m_pNormImgList  = NULL;
    m_pStateImgList = NULL;

  }
  virtual ~ListView() { }

  bool Create(DWORD dwStyleEx, DWORD dwStyle, INT_PTR x, INT_PTR y,
              INT_PTR cx, INT_PTR cy, HWND hWndParent, INT_PTR iID, HINSTANCE hInst);

  // Sets extended styles
  void SetExtendedStyles(DWORD dwStyleEx);

  // Retreives extended styles
  DWORD GetExtendedStyles(void);

  // Inserts a node into the listview
  int AddNode(PLVNODE plvn);

  // Sets the state of a node
  bool SetNode(PLVNODE plvn);

  // Retrieves the state of a node
  bool GetNode(PLVNODE plvn);

  // Removes a node from the listview
  bool RemNode(INT_PTR i);

  // Removes all items from the listview
  bool RemAllNodes(void);

  // Ensures a node is visible
  bool EnsureVisible(INT_PTR i, bool bEntire);

  // Retrieves the index of the topmost
  // visible node in report view
  INT_PTR GetTopIndex(void);

  // Sets the checked/unchecked state
  // of a node
  void SetCheck(INT_PTR i, bool bCheck);

  // Determines if a node is checked
  bool IsChecked(INT_PTR i);

  // Sets the selection mark
  INT_PTR SetSelMark(INT_PTR i);

  // Retreives the selection mark
  INT_PTR GetSelMark(void);

  // Retreives count of selected nodes
  INT_PTR GetSelCount(void);

  // Moves a node to a group
  void MoveNodeToGroup(INT_PTR i, INT_PTR iID);

  // Begins in-place editing of a node
  HWND BeginNodeEdit(INT_PTR i);

  // Ends in-place editing of a node
  void EndNodeEdit(void);

  // Returns the number of nodes in the listview
  INT_PTR GetCount(void);

  // Returns the index of a node that
  // matches the search criteria
  INT_PTR FindNode(INT_PTR iStart, LVFINDINFO *plvfi);

  // Causes a node to be updated
  bool UpdateNode(INT_PTR i);

  // Sets the hot item
  INT_PTR SetHotItem(INT_PTR i);

  // Retreives the hot item
  INT_PTR GetHotItem(void);

  // Retreives coordinates of a node
  bool GetPosition(INT_PTR i, PPOINT pp);

  // Inserts a column
  bool InsertColumn(INT_PTR i, LVCOLUMN *plvc);

  // Removes a column
  bool RemColumn(INT_PTR i);

  // Sets the state of a column
  bool SetColumn(INT_PTR i, LVCOLUMN *plvc);

  // Retreives the state of a column
  bool GetColumn(INT_PTR i, LVCOLUMN *plvc);

  // Retreives the handle of the header in report view
  HWND GetHeader(void);

  // Sets the width of a column
  bool SetColumnWidth(INT_PTR i, INT_PTR cx);

  // Retreives the width of a column
  INT_PTR GetColumnWidth(INT_PTR i);

  // Sets the currently selected column
  void SetSelectedColumn(INT_PTR i);

  // Retreives the currently selected column
  UINT_PTR GetSelectedColumn(void);

#if (_WIN32_IE >= 0x560)

  // Adds a group to the listview
  int AddGroup(INT_PTR i, LVGROUP *plvg);

  // Removes a group
  bool RemGroup(INT_PTR iID);

  // Sets the state of a group
  bool SetGroup(INT_PTR iID, LVGROUP *plvg);

  // Retreives the state of a group
  bool GetGroup(INT_PTR iID, LVGROUP *plvg);

  // Sets the metrics groups
  bool SetGroupMetrics(LVGROUP *plvg);

  // Retreives the metrics of a group
  bool GetGroupMetrics(LVGROUP *plvg);

  // Removes all groups
  void RemAllGroups(void);

  // Determines if a group exists
  bool IsGroup(INT_PTR iID);

  // Moves a group to a new index
  void MoveGroup(INT_PTR iID, INT_PTR i);

#endif

  // Sets the background color of the control
  COLORREF SetBkColor(COLORREF clr);

  // Retreives the background color of the control
  COLORREF GetBkColor(void);

  // Sets the text color of the control
  COLORREF SetTextColor(COLORREF clr);

  // Retreives the text color of the control
  COLORREF GetTextColor(void);

  // Sets the text background color of the control
  COLORREF SetTextBkColor(COLORREF clr);

  // Retreives the text background color of the control
  COLORREF GetTextBkColor(void);

  // Sets the outline color of the control
  COLORREF SetOutlineColor(COLORREF clr);

  // Retreives the outline color of the control
  COLORREF GetOutlineColor(void);

  // Sets the hover time for the control
  DWORD SetHoverTime(DWORD dwTime);

  // Retreives the hover time for the control
  DWORD GetHoverTime(void);

  // Sets the hot cursor for the control
  HCURSOR SetHotCursor(HCURSOR hCur);

  // Retreives the hot cursor for the control
  HCURSOR GetHotCursor(void);

  // Sets the icon spacing for the control
  DWORD SetIconSpacing(INT_PTR cx, INT_PTR cy);

  // Scrolls the view the specified amount
  bool Scroll(INT_PTR cx, INT_PTR cy);

  // Determines if a point is on a node
  INT_PTR HitTest(LPLVHITTESTINFO plvhi);

  // Determines if a point is on a node
  // or sub node
  INT_PTR SubHitTest(LPLVHITTESTINFO plvhi);

  // Sets the image list associated with the list
  bool SetImageList(ImageList &ImgList, int type);

  // Retreives image lists pointers, if applicable
  ImageList *GetNormalImgList(void);
  ImageList *GetSmallImgList(void);
  ImageList *GetStateImgList(void);

private:
  ImageList *m_pSmlImgList;
  ImageList *m_pNormImgList;
  ImageList *m_pStateImgList;
  
  void _LVITEM2LVNODE(LPLVITEM pi, PLVNODE pn);
  void _LVNODE2LVITEM(PLVNODE pn, LPLVITEM pi);

};

#endif // !_LISTVIEW_H
