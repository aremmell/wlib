#include "stdafx.h"
#include "listview.hpp"

bool ListView::Create(DWORD dwStyleEx, DWORD dwStyle, INT_PTR x, INT_PTR y,
                      INT_PTR cx, INT_PTR cy, HWND hWndParent, INT_PTR iID, HINSTANCE hInst)
{
  bool r = false;

  Window::Create(dwStyleEx,
                 WC_LISTVIEW,
                 _T(""),
                 dwStyle,
                 x,
                 y,
                 cx,
                 cy,
                 hWndParent,
                 iID,
                 hInst);

  if (NULL != m_hWnd) {

    r = true;

  }

  return r;
}

void ListView::SetExtendedStyles(DWORD dwStyleEx) {

  ListView_SetExtendedListViewStyle(m_hWnd, dwStyleEx);
}

DWORD ListView::GetExtendedStyles(void) {

  return ListView_GetExtendedListViewStyle(m_hWnd);
}

int ListView::AddNode(PLVNODE plvn) {
  
  INT_PTR i = -1;

  if (NULL != plvn) {
    
    LVITEM lvi = {0};
    
    _LVNODE2LVITEM(plvn, &lvi);

    if (-1 != (i = ListView_InsertItem(m_hWnd, &lvi))) {

      plvn->iItem = i;

    }

  }

  return i;
}

bool ListView::SetNode(PLVNODE plvn) {

  bool r = false;

  if (NULL != plvn) {
    
    LVITEM lvi = {0};

    _LVNODE2LVITEM(plvn, &lvi);

    if (TRUE == ListView_SetItem(m_hWnd, &lvi)) {

      r = true;

    }

  }

  return r;
}

bool ListView::GetNode(PLVNODE plvn) {

  bool r = false;

  if (NULL != plvn) {
    
    LVITEM lvi = {0};
  
    _LVNODE2LVITEM(plvn, &lvi);

    if (TRUE == ListView_GetItem(m_hWnd, &lvi)) {

      _LVITEM2LVNODE(&lvi, plvn);

      r = true;

    }

  }

  return r;
}

bool ListView::RemNode(INT_PTR i) {

  return WND_TRUE(ListView_DeleteItem(m_hWnd, i));
}

bool ListView::RemAllNodes(void) {

  return WND_TRUE(ListView_DeleteAllItems(m_hWnd));
}

bool ListView::EnsureVisible(INT_PTR i, bool bEntire) {
  
  BOOL bArg = bEntire ? FALSE : TRUE;
  
  return WND_TRUE(ListView_EnsureVisible(m_hWnd, i, bArg));
}

INT_PTR ListView::GetTopIndex(void) {

  return ListView_GetTopIndex(m_hWnd);
}

void ListView::SetCheck(INT_PTR i, bool bCheck) {

  ListView_SetCheckState(m_hWnd, i, bCheck ? TRUE : FALSE);
}

bool ListView::IsChecked(INT_PTR i) {

  return WND_TRUE(ListView_GetCheckState(m_hWnd, i));
}

INT_PTR ListView::SetSelMark(INT_PTR i) {

  return ListView_SetSelectionMark(m_hWnd, i);
}

INT_PTR ListView::GetSelMark(void) {

  return ListView_GetSelectionMark(m_hWnd);
}

INT_PTR ListView::GetSelCount(void) {

  return ListView_GetSelectedCount(m_hWnd);
}

#if (_WIN32_IE >= 0x560)

void ListView::MoveNodeToGroup(INT_PTR i, INT_PTR iID) {

  ListView_MoveItemToGroup(m_hWnd, i, iID);

}

#endif

HWND ListView::BeginNodeEdit(INT_PTR i) {

  return ListView_EditLabel(m_hWnd, i);

}

#if (_WIN32_IE >= 0x560)

void ListView::EndNodeEdit(void) {

  ListView_CancelEditLabel(m_hWnd);

}

#endif

INT_PTR ListView::GetCount(void) {

  return ListView_GetItemCount(m_hWnd);
}

INT_PTR ListView::FindNode(INT_PTR iStart, LVFINDINFO *plvfi) {

  return ListView_FindItem(m_hWnd, iStart, plvfi);
}

bool ListView::UpdateNode(INT_PTR i) {

  return WND_TRUE(ListView_Update(m_hWnd, i));
}

INT_PTR ListView::SetHotItem(INT_PTR i) {

  return ListView_SetHotItem(m_hWnd, i);
}

INT_PTR ListView::GetHotItem(void) {

  return ListView_GetHotItem(m_hWnd);
}

bool ListView::GetPosition(INT_PTR i, PPOINT pp) {

  bool r = false;
  
  if (NULL != pp) {

    if (TRUE == ListView_GetItemPosition(m_hWnd, i, pp)) {

      r = true;

    }

  }

  return r;
}

bool ListView::InsertColumn(INT_PTR i, LVCOLUMN *plvc) {

  bool r = false;

  if (NULL != plvc) {

    if (-1 != ListView_InsertColumn(m_hWnd, i, plvc)) {

      r = true;

    }

  }

  return r;
}

bool ListView::RemColumn(INT_PTR i) {

  return WND_TRUE(ListView_DeleteColumn(m_hWnd, i));
}

bool ListView::SetColumn(INT_PTR i, LVCOLUMN *plvc) {

  bool r = false;

  if (NULL != plvc) {

    if (TRUE == ListView_SetColumn(m_hWnd, i, plvc)) {

      r = true;

    }

  }

  return r;
}

bool ListView::GetColumn(INT_PTR i, LVCOLUMN *plvc) {
  
  bool r = false;
  
  if (NULL != plvc) {

    if (TRUE == ListView_GetColumn(m_hWnd, i, plvc)) {

      r = true;

    }

  }

  return r;
}

HWND ListView::GetHeader(void) {

  return ListView_GetHeader(m_hWnd);
}

bool ListView::SetColumnWidth(INT_PTR i, INT_PTR cx) {

  return WND_TRUE(ListView_SetColumnWidth(m_hWnd, i, cx));
}

INT_PTR ListView::GetColumnWidth(INT_PTR i) {

  return ListView_GetColumnWidth(m_hWnd, i);
}

#if (_WIN32_IE >= 0x560)

void ListView::SetSelectedColumn(INT_PTR i) {

  ListView_SetSelectedColumn(m_hWnd, i);

}

UINT_PTR ListView::GetSelectedColumn(void) {

  return ListView_GetSelectedColumn(m_hWnd);
}

int ListView::AddGroup(INT_PTR i, LVGROUP *plvg) {

  int r = -1;

  if (NULL != plvg) {

    r = ListView_InsertGroup(m_hWnd, i, plvg);

  }

  return r;
}

bool ListView::RemGroup(INT_PTR iID) {

  bool r = false;

  if (-1 != ListView_RemoveGroup(m_hWnd, iID)) {

    r = true;

  }

  return r;
}

bool ListView::SetGroup(INT_PTR iID, LVGROUP *plvg) {

  bool r = false;
  
  if (NULL != plvg) {

    if (-1 != ListView_SetGroupInfo(m_hWnd, iID, plvg)) {

      r = true;

    }

  }

  return r;
}

bool ListView::GetGroup(INT_PTR iID, LVGROUP *plvg) {

  bool r = false;

  if (NULL != plvg) {

    if (-1 != ListView_GetGroupInfo(m_hWnd, iID, plvg)) {

      r = true;

    }

  }

  return r;
}

bool ListView::SetGroupMetrics(LVGROUP *plvg) {

  bool r = false;

  if (NULL != plvg) {

    ListView_SetGroupMetrics(m_hWnd, plvg);

    r = true;

  }

  return r;
}

bool ListView::GetGroupMetrics(LVGROUP *plvg) {

  bool r = false;

  if (NULL != plvg) {

    ListView_GetGroupMetrics(m_hWnd, plvg);

    r = true;

  }

  return r;
}

void ListView::RemAllGroups(void) {

  ListView_RemoveAllGroups(m_hWnd);

}

bool ListView::IsGroup(INT_PTR iID) {

  return WND_TRUE(ListView_HasGroup(m_hWnd, iID));
}

void ListView::MoveGroup(INT_PTR iID, INT_PTR i) {

  ListView_MoveGroup(m_hWnd, iID, i);

}

#endif // Groups

COLORREF ListView::SetBkColor(COLORREF clr) {

  return ListView_SetBkColor(m_hWnd, clr);
}

COLORREF ListView::GetBkColor(void) {

  return ListView_GetBkColor(m_hWnd);
}

COLORREF ListView::SetTextColor(COLORREF clr) {

  return ListView_SetTextColor(m_hWnd, clr);
}

COLORREF ListView::GetTextColor(void) {

  return ListView_GetTextColor(m_hWnd);
}

COLORREF ListView::SetTextBkColor(COLORREF clr) {

  return ListView_SetTextBkColor(m_hWnd, clr);
}

COLORREF ListView::GetTextBkColor(void) {

  return ListView_GetTextBkColor(m_hWnd);
}

#if (_WIN32_IE >= 0x560)

COLORREF ListView::SetOutlineColor(COLORREF clr) {

  return ListView_SetOutlineColor(m_hWnd, clr);
}

COLORREF ListView::GetOutlineColor(void) {

  return ListView_GetOutlineColor(m_hWnd);
}

#endif

DWORD ListView::SetHoverTime(DWORD dwTime) {

  return ListView_SetHoverTime(m_hWnd, dwTime);
}

DWORD ListView::GetHoverTime(void) {

  return ListView_GetHoverTime(m_hWnd);
}

HCURSOR ListView::SetHotCursor(HCURSOR hCur) {

  return ListView_SetHotCursor(m_hWnd, hCur);
}

HCURSOR ListView::GetHotCursor(void) {

  return ListView_GetHotCursor(m_hWnd);
}

DWORD ListView::SetIconSpacing(INT_PTR cx, INT_PTR cy) {

  return ListView_SetIconSpacing(m_hWnd, cx, cy);
}

bool ListView::Scroll(INT_PTR cx, INT_PTR cy) {

  return WND_TRUE(ListView_Scroll(m_hWnd, cx, cy));
}

INT_PTR ListView::HitTest(LPLVHITTESTINFO plvhi) {

  return ListView_HitTest(m_hWnd, plvhi);
}

INT_PTR ListView::SubHitTest(LPLVHITTESTINFO plvhi) {

  return ListView_SubItemHitTest(m_hWnd, plvhi);
}

bool ListView::SetImageList(ImageList &ImgList, int type) {

  bool r = false;

  if (NULL != ListView_SetImageList(m_hWnd, ImgList.Handle(), type)) {

    switch (type) {

      case LVSIL_NORMAL:
        m_pNormImgList   = &ImgList;
      break;

      case LVSIL_SMALL:
        m_pSmlImgList    = &ImgList;
      break;

      case LVSIL_STATE:
        m_pStateImgList  = &ImgList;
      break;

    }

  }

  return r;
}

ImageList *ListView::GetNormalImgList(void) {

  return m_pNormImgList;
}

ImageList *ListView::GetSmallImgList(void) {

  return m_pSmlImgList;
}

ImageList *ListView::GetStateImgList(void) {

  return m_pStateImgList;
}


//
// ListView : Private
//
void ListView::_LVITEM2LVNODE(LPLVITEM pi, PLVNODE pn) {

  pn->iImage      = pi->iImage;
  pn->iIndent     = pi->iIndent;
  pn->iItem       = pi->iItem;
  pn->iSubItem    = pi->iSubItem;
  pn->fMask       = pi->mask;
  pn->szText      = pi->pszText;
  pn->lParam      = pi->lParam;
#if (_WIN32_IE >= 0x560)

  pn->iGroupId    = pi->iGroupID;
  pn->puiColumns  = pi->puColumns;
  pn->uiColumns   = pi->cColumns;

#endif
  pn->fState      = pi->state;
  pn->fStateMask  = pi->stateMask;
}

void ListView::_LVNODE2LVITEM(PLVNODE pn, LPLVITEM pi) {

  pi->cchTextMax  = pn->uiMaxChars;
  pi->iImage      = pn->iImage;
  pi->iIndent     = pn->iIndent;
  pi->iItem       = pn->iItem;
  pi->iSubItem    = pn->iSubItem;
  pi->mask        = pn->fMask;
  pi->pszText     = pn->szText;
  pi->lParam      = pn->lParam;
#if (_WIN32_IE >= 0x560)

  pi->iGroupId    = pn->iGroupID;
  pi->puColumns   = pn->puiColumns;
  pi->cColumns    = pn->uiColumns;

#endif
  pi->state       = pn->fState;
  pi->stateMask   = pn->fStateMask;
}
