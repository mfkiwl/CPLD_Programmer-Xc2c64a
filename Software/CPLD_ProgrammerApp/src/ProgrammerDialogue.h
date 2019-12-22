/*
 * BootloaderDialogue.h
 *
 *  Created on: 9 Dec 2019
 *      Author: podonoghue
 */

#ifndef PROGRAMMERDIALOGUE_H_
#define PROGRAMMERDIALOGUE_H_

#include "ProgrammerDialogueSkeleton.h"
#include "XsvfLoader.h"

class ProgrammerDialogue : public ProgrammerDialogueSkeleton {
private:
   ProgrammerDialogue(const ProgrammerDialogue &other) = delete;
   ProgrammerDialogue(ProgrammerDialogue &&other) = delete;
   ProgrammerDialogue& operator=(const ProgrammerDialogue &other) = delete;
   ProgrammerDialogue& operator=(ProgrammerDialogue &&other) = delete;

   uint8_t     xsvf_data[40000];
   unsigned    xsvf_size = 0;

public:
   ProgrammerDialogue();
   virtual ~ProgrammerDialogue();

protected:
   /**
    * Get device name from IDCODE
    *
    * @param idcode
    * @return
    */
   const char *getDeviceName(uint32_t idcode);

   /**
    * Load XSVF file
    *
    * @param filePath
    *
    * @return
    */
   bool loadXsvfFile(wxString filepath);

   virtual void onLoadFile(wxCommandEvent &event) override;
   virtual void onConfirmId( wxCommandEvent& event ) override;
   virtual void onProgramDevice(wxCommandEvent &event) override;
};

#endif /* PROGRAMMERDIALOGUE_H_ */
