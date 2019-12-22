/*
 * BootloaderDialogue.cpp
 *
 *  Created on: 9 Dec 2019
 *      Author: podonoghue
 */

#include "ProgrammerDialogue.h"

#include "wx/file.h"
#include "wx/filedlg.h"
#include "wx/msgdlg.h"

#include "XsvfLoader.h"

ProgrammerDialogue::ProgrammerDialogue() : ProgrammerDialogueSkeleton(nullptr) {
}

ProgrammerDialogue::~ProgrammerDialogue() {
}

/**
 * Load XSVF file
 *
 * @param filePath
 *
 * @return
 */
bool ProgrammerDialogue::loadXsvfFile(wxString filePath) {
   wxFile file;
   if (file.Open(filePath, wxFile::read)) {
      wxFileOffset size = file.Length();
      if (size > sizeof(xsvf_data)) {
         wxMessageBox("File is unexpectedly large", "Failed to load file");
         xsvf_size = 0;
         return false;
      }
      file.Read(xsvf_data, size);
      xsvf_size = (unsigned)size;
   }
   else {
      loadedFile_static->SetLabel("-- No file loaded --");
      programDevice_button->Enable(false);
      wxMessageBox("", "Failed to load file");
   }
   file.Close();
   return true;
}

void ProgrammerDialogue::onLoadFile(wxCommandEvent &event) {
   wxString caption  = _("Select Binary File to Load");
   wxString wildcard = _(
         "Compressed SVF (*.xsvf)|*.xsvf|"
         "Jedec Files(*.jed)|*.jed|"
         "All Files|*");
   wxString defaultFilename  = wxEmptyString;
   wxString currentDirectory = wxEmptyString;
   wxFileDialog openFileDialog(this, caption, currentDirectory, defaultFilename, wildcard, wxFD_OPEN);
   int getCancelOK = openFileDialog.ShowModal();
   if (getCancelOK != wxID_OK) {
      // Ignore
      return;
   }
   wxString filePath = openFileDialog.GetPath();
   wxString fileName = openFileDialog.GetFilename();
   if (loadXsvfFile(filePath)) {
      loadedFile_static->SetLabel(wxString::Format("%s (%i bytes)", fileName, xsvf_size));
      programDevice_button->Enable(true);
      programAction_static->SetLabel("");
      idcode_static->SetLabel("");
   }
   else {
      loadedFile_static->SetLabel("-- No file loaded --");
      programDevice_button->Enable(false);
   }
}

/**
 * Get device name from IDCODE
 *
 * @param idcode
 * @return
 */
const char *ProgrammerDialogue::getDeviceName(uint32_t idcode) {
   struct DeviceId {
      uint32_t mask;
      uint32_t idcode;
      const char *name;
   };

   static const DeviceId deviceIds[] = {
         { 0x0FFF8FFF, 0xF6E5F093, "XC2C64A"},
   };

   static const char *name = "Unknown";

   for(unsigned index=0; index<(sizeof(deviceIds)/sizeof(deviceIds[0])); index++) {
      fprintf(stderr, "m=0x%08X, i=0x%08X\n",
            deviceIds[index].idcode&deviceIds[index].mask, idcode&deviceIds[index].mask);
      fflush(stderr);
      if ((idcode&deviceIds[index].mask) == (deviceIds[index].idcode&deviceIds[index].mask)) {
         name = deviceIds[index].name;
         break;
      }
   }
   return name;
}

void ProgrammerDialogue::onConfirmId( wxCommandEvent& event ) {
   XsvfLoader loader;
   uint32_t idcode;

   const char *res = nullptr;
   do {
      res = loader.checkTargetVref();
      if (res != nullptr) {
         break;
      }
      res = loader.readIdcode(idcode);
      if (res != nullptr) {
         break;
      }
   } while (false);

   if (res != nullptr) {
      wxMessageBox(res, "Failed to read IDCODE from device");
      idcode_static->SetLabel("Failed to read IDCODE");
   }
   else {
      idcode_static->SetLabel(wxString::Format("%s (IDCODE = 0x%08X)", getDeviceName(idcode), idcode));
   }
}

void ProgrammerDialogue::onProgramDevice(wxCommandEvent &event) {
   programAction_static->SetLabel("Busy");
   XsvfLoader loader;
   const char *res = nullptr;
   do {
      res = loader.checkTargetVref();
      if (res != nullptr) {
         break;
      }

      res = loader.sendSxvfFile(xsvf_size, xsvf_data);
      if (res != nullptr) {
         break;
      }
   } while (false);

   if (res != nullptr) {
      wxMessageBox(res, "Failed to program device");
      programAction_static->SetLabel("Programming Failed");
   }
   else {
      programAction_static->SetLabel("Programming Succeeded");
   }
}
