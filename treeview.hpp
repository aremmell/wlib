#ifndef _TREEVIEW_H
#define _TREEVIEW_H

#include "window.hpp"
#include "imagelist.hpp"
#include <map>

#define TV_MAXITEMTEXT  1024
#define TV_DEFICONY     16
#define TV_DEFICONX     16

template<typename _Ty> class TreeView : public Window {

public:
  TreeView() { }
  virtual ~TreeView() { }

  //
  // Public Data Types
  //
  typedef struct tagTVDATA {

    tagTVDATA() {

      dwUser1 = 0UL;
      dwUser2 = 0UL;
      hItem   = NULL;

    }

    _Ty Key;            // User-defined key
    DWORD_PTR dwUser1;  // Custom value
    DWORD_PTR dwUser2;  // Custom value
    HTREEITEM hItem;    // Handle of node

  } TVDATA, *PTVDATA;

  typedef struct tagTVNODE {

    tagTVNODE() {

      hOwner      = TVI_ROOT;
      hIns        = TVI_LAST;
      fMask       = 0U;
      fState      = 0U;
      fStateMask  = 0U;
      tsText      = _T("");
      iImage      = -1;
      iSelImg     = -1;
      iChildren   = 0;

    }

    TVDATA Data;          // User-defined data for this item
    HTREEITEM hOwner;     // Handle of owner item
    HTREEITEM hIns;       // Handle of item to insert after
    UINT_PTR  fMask;      // Flag bitmask
    UINT_PTR  fState;     // State flags
    UINT_PTR  fStateMask; // State mask
    TSTRING tsText;       // Caption of item
    INT_PTR iImage;       // Index of image to use
    INT_PTR iSelImg;      // Index of selected image
    INT_PTR iChildren;    // Child item flag

  } TVNODE, *PTVNODE;

  //
  // Public Functions
  //
  bool Create(DWORD_PTR dwStyleEx, DWORD_PTR dwStyle, INT_PTR x, INT_PTR y, INT_PTR cx, 
              INT_PTR cy, HWND hWndParent, INT_PTR iID, HINSTANCE hInst)
  {
    bool r = false;

    if (m_ImgList.Create(TV_DEFICONX, TV_DEFICONY, ILC_COLOR32 | ILC_MASK, 1, 1, hInst)) {
      
      Window::Create(dwStyleEx,
                     WC_TREEVIEW,
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

        TreeView_SetImageList(m_hWnd, m_ImgList.Handle(), TVSIL_NORMAL);
        r = true;

      }

    }

    return r;
  }

  HTREEITEM AddNode(PTVNODE pNode) {

    HTREEITEM r = NULL;

    if (NULL != pNode) {

      if (NULL != KeyToHandle(pNode->Data.Key)) { return r; }

      TVINSERTSTRUCT tvis = {0};

      tvis.hInsertAfter         = pNode->hIns;
      tvis.hParent              = pNode->hOwner;
      tvis.item.cChildren       = static_cast<int>(pNode->iChildren);
      tvis.item.cchTextMax      = static_cast<int>(pNode->tsText.size());
      tvis.item.iImage          = static_cast<int>(pNode->iImage);
      tvis.item.iSelectedImage  = static_cast<int>(pNode->iSelImg);
      tvis.item.mask            = static_cast<UINT>(pNode->fMask);
      tvis.item.pszText         = const_cast<PTSTR>(pNode->tsText.c_str());
      tvis.item.state           = static_cast<UINT>(pNode->fState);
      tvis.item.stateMask       = static_cast<UINT>(pNode->fStateMask);

      r = TreeView_InsertItem(m_hWnd, &tvis);

      if (NULL == r) { return r; }

      pNode->Data.hItem = r;
      m_Map[r] = pNode->Data;

    }

    return r;
  }

  bool RemNode(_Ty Key) {

    HTREEITEM hItem  = KeyToHandle(Key);

    if (NULL != hItem) {

      if (TRUE == TreeView_DeleteItem(m_hWnd, hItem)) {

        return _RemNode(hItem);

      }

    }

    return false;
  }

  bool RemAllNodes(void) {

    bool r = false;
    
    if (TRUE == TreeView_DeleteAllItems(m_hWnd)) {

      m_Map.clear();
      r = true;

    }

    return r;
  }

  bool ExpandNode(_Ty Key, UINT fMask) {
    
    HTREEITEM hItem = KeyToHandle(Key);

    if (NULL != hItem) {

      return WND_TRUE(TreeView_Expand(m_hWnd, hItem, fMask));

    }

    return false;
  }

  bool GetNodeInfo(LPTVITEM pNode) {

    bool r = false;

    if (NULL != pNode) {

      if (WND_TRUE(TreeView_GetItem(m_hWnd, pNode))) {

        r = true;

      }

    }

    return r;
  }

  bool GetNodeText(_Ty Key, TSTRING &tsText) {
    
    bool r = false;
    
    HTREEITEM hItem = KeyToHandle(Key);

    if (NULL != hItem) {

      TCHAR pBuf[TV_MAXITEMTEXT]  = {0};
      TVITEM tvi                  = {0};

      tvi.cchTextMax  = TV_MAXITEMTEXT;
      tvi.pszText     = pBuf;
      tvi.mask        = TVIF_TEXT;
      tvi.hItem       = hItem;

      if (GetNodeInfo(&tvi)) {

        tsText  = pBuf;
        r       = true;

      }

    }

    return r;
  }

  UINT GetNodeCount(void) { return TreeView_GetCount(m_hWnd); }

  PTVDATA GetSelectedNode(void) {

    HTREEITEM hItem = TreeView_GetSelection(m_hWnd);
    PTVDATA r       = NULL;

    if (NULL != hItem) {

      r = HandleToData(hItem);

    }

    return r;
  }

  bool SetSelectedNode(_Ty Key, UINT fMask) {

    HTREEITEM hItem = KeyToHandle(Key);

    if (NULL != hItem) {

      return WND_TRUE(TreeView_Select(m_hWnd, hItem, fMask));

    }

    return false;
  }

  bool SelectSetFirstNode(_Ty Key) {

    HTREEITEM hItem = KeyToHandle(Key);

    if (NULL != hItem) {

      return WND_TRUE(TreeView_SelectSetFirstVisible(m_hWnd, hItem));

    }

    return false;
  }

  bool SetCheck(_Ty Key, bool bSel) {

    HTREEITEM hItem = KeyToHandle(Key);

    if (NULL != hItem) {

      TreeView_SetCheckState(m_hWnd, hItem, bSel ? TRUE : FALSE);
      return true;

    }

    return false;
  }

  bool IsNodeChecked(_Ty Key) {

    bool r          = false;
    HTREEITEM hItem = KeyToHandle(Key);

    if (NULL != hItem) {

      if (1L == TreeView_GetCheckState(m_hWnd, hItem)) {

        r = true;

      }

    }

    return r;
  }

  bool EnsureNodeVisible(_Ty Key) {

    HTREEITEM hItem = KeyToHandle(Key);

    if (NULL != hItem) {

      return WND_TRUE(TreeView_EnsureVisible(m_hWnd, hItem));  

    }

    return false;
  }

  PTVDATA GetFirstVisible(void) {

    PTVDATA r       = NULL;
    HTREEITEM hItem = TreeView_GetFirstVisible(m_hWnd);

    if (NULL != hItem) {

      r = HandleToData(hItem);

    }

    return r;
  }

  PTVDATA GetLastVisible(void) {

    PTVDATA r       = NULL;
    HTREEITEM hItem = TreeView_GetLastVisible(m_hWnd);

    if (NULL != hItem) {

      r = HandleToData(hItem);

    }

    return r;
  }

  HWND EditNode(_Ty Key) {
    
    HTREEITEM hItem = KeyToHandle(Key);

    if (NULL != hItem) {

      return TreeView_EditLabel(m_hWnd, hItem);

    } else {

      return NULL;

    }

  }

  bool EndNodeEdit(bool bCancel) {
    
    BOOL bArg = bCancel ? TRUE : FALSE;

    return WND_TRUE(TreeView_EndEditLabelNow(m_hWnd, bArg));
  }

  PTVDATA GetFirstChild(_Ty Key) {

    PTVDATA r       = NULL;
    HTREEITEM hItem = KeyToHandle(Key);

    if (NULL != hItem) {

      r = HandleToData(TreeView_GetChild(m_hWnd, hItem));

    }

    return r;
  }

  PTVDATA GetNextSibling(_Ty Key) {

    PTVDATA r       = NULL;
    HTREEITEM hItem = KeyToHandle(Key);

    if (NULL != hItem) {

      r = HandleToData(TreeView_GetNextSibling(m_hWnd, hItem));

    }

    return r;
  }

  PTVDATA GetNextVisible(_Ty Key) {

    PTVDATA r       = NULL;
    HTREEITEM hItem = KeyToHandle(Key);

    if (NULL != hItem) {

      r = HandleToData(TreeView_GetNextVisible(m_hWnd, hItem));

    }

    return r;
  }

  PTVDATA GetPreviousSibling(_Ty Key) {

    PTVDATA r       = NULL;
    HTREEITEM hItem = KeyToHandle(Key);

    if (NULL != hItem) {

      r = HandleToData(TreeView_GetPrevSibling(m_hWnd, hItem));

    }

    return r;
  }

  PTVDATA GetPreviousVisible(_Ty Key) {

    PTVDATA r       = NULL;
    HTREEITEM hItem = KeyToHandle(Key);

    if (NULL != hItem) {

      r = HandleToData(TreeView_GetPrevVisible(m_hWnd, hItem));

    }

    return r;
  }

  PTVDATA GetParentNode(_Ty Key) {

    PTVDATA r       = NULL;
    HTREEITEM hItem = KeyToHandle(Key);

    if (NULL != hItem) {

      r = HandleToData(TreeView_GetParent(m_hWnd, hItem));

    }

    return r;
  }

  PTVDATA GetRootNode(void) {

    PTVDATA r = NULL;

    r = HandleToData(TreeView_GetRoot(m_hWnd));

    return r;
  }
  
  bool GetNodeRect(_Ty Key, PRECT pRc) {

    bool r          = false;
    HTREEITEM hItem = KeyToHandle(Key);

    if (NULL != hItem) {

      if (TRUE == TreeView_GetItemRect(m_hWnd, hItem, pRc, FALSE)) {

        r = true;

      }

    }

    return r;
  }

  PTVDATA GetDropTarget(void) {

    PTVDATA r       = NULL;
    HTREEITEM hItem = TreeView_GetDropHilight(m_hWnd);

    if (NULL != hItem) {

      r = HandleToData(hItem);

    }

    return r;
  }

  bool SetDropTarget(_Ty Key) {

    bool r          = false;
    HTREEITEM hItem = KeyToHandle(Key);

    if (NULL != hItem) {

      if (TRUE == TreeView_SelectDropTarget(m_hWnd, hItem)) {

        r = true;

      }

    }

    return r;
  }

  COLORREF SetBackColor(COLORREF clr) {

    return TreeView_SetBkColor(m_hWnd, clr);
  }

  COLORREF GetBackColor(void) {

    return TreeView_GetBkColor(m_hWnd);
  }

  COLORREF SetTextColor(COLORREF clr) {

    return TreeView_SetTextColor(m_hWnd, clr);
  }

  COLORREF GetTextColor(void) {

    return TreeView_GetTextColor(m_hWnd);
  }

  COLORREF SetLineColor(COLORREF clr) {

    return TreeView_SetLineColor(m_hWnd, clr);
  }

  COLORREF GetLineColor(void) {

    return TreeView_GetLineColor(m_hWnd);
  }

  HTREEITEM KeyToHandle(_Ty Key) {

    HTREEITEM hItem = NULL;
    TVNMAPITER it   = m_Map.begin();

    for (; it != m_Map.end(); it++) {

      if ((*it).second.Key == Key) {

        hItem = (*it).second.hItem;
        break;

      }

    }

    return hItem;
  }

  PTVDATA HandleToData(HTREEITEM hItem) {

    TVNMAPITER it = m_Map.find(hItem);

    if (m_Map.end() != it) {

      return &(*it).second;

    }

    return NULL;
  }

  ImageList &GetImageList(void) { return m_ImgList; }

protected:
  typedef std::map<HTREEITEM, TVDATA> TVNMAP, *PTVNMAP;
  typedef typename TVNMAP::iterator TVNMAPITER;
  TVNMAP      m_Map;
  TVNMAPITER  m_Iter;
  ImageList   m_ImgList;

private:
  
  bool _RemNode(HTREEITEM hItem) {

    bool r        = false;
    TVNMAPITER it = m_Map.find(hItem);

    if (m_Map.end() != it) {

      m_Map.erase(it);
      r = true;

    }

    return r;
  }

};

#endif // _TREEVIEW_H
