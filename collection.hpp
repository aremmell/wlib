#ifndef _COLLECTION_H
#define _COLLECTION_H

#include <list>

template <typename _Ty> class Collection {

protected:
  typedef std::list<_Ty>                      EnumTypeList;
  typedef typename std::list<_Ty>::iterator   EnumTypeListIter;

public:
  Collection() { }

  virtual ~Collection() {

    m_List.clear();

  }

  void AddItem(_Ty i) { m_List.push_back(i); }

  bool RemItem(_Ty i) {

    EnumTypeListIter it;

    for (it = m_List.begin(); it != m_List.end(); it++) {

      if (*it == i) {

        m_List.erase(it);
        return true;

      }

    }

    return false;
  }

  bool Enum(_Ty **pOut) {

    if (NULL != pOut) {

      *pOut = &(*m_Iter);

      if (m_Iter == m_List.end()) {

        m_Iter = m_List.begin();
        return false;

      }

      m_Iter++;
    }

    return true;
  }

  bool Enum(_Ty *pOut) {

    if (NULL != pOut) {

      *pOut = (*m_Iter);

      if (m_Iter == m_List.end()) {

        m_Iter = m_List.begin();
        return false;

      }

      m_Iter++;
    }

    return true;
  }

  void Reset(void) { m_Iter = m_List.begin(); }
  void Clear(void) { m_List.clear(); }
  size_t Count(void) { return m_List.size(); }

protected:
  EnumTypeList      m_List;
  EnumTypeListIter  m_Iter;

};

#endif // !_COLLECTION_H
