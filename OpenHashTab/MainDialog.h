//    Copyright 2019-2020 namazso <admin@namazso.eu>
//    This file is part of OpenHashTab.
//
//    OpenHashTab is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    OpenHashTab is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with OpenHashTab.  If not, see <https://www.gnu.org/licenses/>.
#pragma once
#include "utl.h"
#include "wnd.h"

class Exporter;
class FileHashTask;
class Coordinator;

class MainDialog
{
  static constexpr auto k_status_update_timer_id = (UINT_PTR)0x7c253816f7ef92ea;

  HWND _hwnd{};
  Coordinator* _prop_page;
  wnd::WindowLayoutAdapter _adapter{ _hwnd, IDD_OPENHASHTAB_PROPPAGE };

  MAKE_IDC_MEMBER(_hwnd, HASH_LIST);
  MAKE_IDC_MEMBER(_hwnd, EDIT_HASH);
  MAKE_IDC_MEMBER(_hwnd, COMBO_EXPORT);
  MAKE_IDC_MEMBER(_hwnd, BUTTON_EXPORT);
  MAKE_IDC_MEMBER(_hwnd, STATIC_CHECK_AGAINST);
  MAKE_IDC_MEMBER(_hwnd, STATIC_EXPORT_TO);
  MAKE_IDC_MEMBER(_hwnd, STATIC_CHECK_RESULT);
  MAKE_IDC_MEMBER(_hwnd, STATIC_SUMFILE);
  MAKE_IDC_MEMBER(_hwnd, STATIC_PROCESSING);
  MAKE_IDC_MEMBER(_hwnd, BUTTON_CLIPBOARD);
  MAKE_IDC_MEMBER(_hwnd, BUTTON_SETTINGS);
  MAKE_IDC_MEMBER(_hwnd, BUTTON_CANCEL);
  MAKE_IDC_MEMBER(_hwnd, ALGORITHM_LIST);
  MAKE_IDC_MEMBER(_hwnd, PROGRESS);
  MAKE_IDC_MEMBER(_hwnd, BUTTON_VT);

  unsigned _count_error{};
  unsigned _count_match{};
  unsigned _count_mismatch{};
  unsigned _count_unknown{};

  bool _temporary_status{};
  bool _finished{};

  enum ColIndex : int
  {
    ColIndex_Filename,
    ColIndex_Algorithm,
    ColIndex_Hash
  };

  static INT_PTR CustomDrawListView(LPARAM lparam, HWND list);

  std::string GetSumfileAsString(const Exporter* exporter, bool for_clipboard);
  void AddItemToFileList(LPCWSTR filename, LPCWSTR algorithm, LPCWSTR hash, LPARAM lparam);
  void SetTempStatus(LPCWSTR status, UINT time);
  void UpdateDefaultStatus(bool force_reset = false);

  void InitDialog();

  void OnFileFinished(FileHashTask* file);
  void OnAllFilesFinished();
  void OnExportClicked();
  void OnHashEditChanged();
  void OnListDoubleClick(int item, int subitem);
  void OnListRightClick(bool dblclick = false);

public:
  MainDialog(HWND hwnd, void* prop_page);
  ~MainDialog();

  INT_PTR DlgProc(UINT msg, WPARAM wparam, LPARAM lparam);
};
