/*
 * Bootloader.h
 *
 *  Created on: 9 Dec 2019
 *      Author: podonoghue
 */

#ifndef XSVFLOADER_H_
#define XSVFLOADER_H_

#include "libusb.h"
#include "UsbCommandMessage.h"

class XsvfLoader {

public:
   XsvfLoader();
   virtual ~XsvfLoader();

private:
   XsvfLoader(const XsvfLoader &other) = delete;
   XsvfLoader(XsvfLoader &&other) = delete;
   XsvfLoader& operator=(const XsvfLoader &other) = delete;
   XsvfLoader& operator=(XsvfLoader &&other) = delete;

   libusb_device_handle *device = nullptr;

   uint32_t flashStart        = 0;
   uint32_t flashSize         = 0;
   uint16_t hardwareVersion   = 0;
   uint16_t bootloaderVersion = 0;

   /**
    * Locate USB device to program
    *
    * @return nullptr   => failed
    * @return !=nullptr => LIBUSB device handle
    */
   static libusb_device_handle *findDevice();

   /**
    * Program a block to device
    *
    * @param message Information to send to device
    *
    * @return nullptr   => success
    * @return !=nullptr => failed, error message
    */
   const char *downloadXsvfBlock(unsigned xsvf_size, uint8_t *xsvf_data);

   /**
    * Download XSVF data to opened device
    *
    * @param xsvf_size
    * @param xsvf_data
    *
    * @return nullptr   => success
    * @return !=nullptr => failed, error message
    */
   const char *downloadXsvf(unsigned xsvf_size, uint8_t *xsvf_data);

public:
   /**
    * Download XSVF data to device
    *
    * @param xsvf_size
    * @param xsvf_data
    *
    * @return nullptr   => success
    * @return !=nullptr => failed, error message
    */
   const char *sendSxvfFile(unsigned xsvf_size, uint8_t *xsvf_data);

   /**
    * Read IDCODE from device
    *
    * @param idcode  IDCODE read from target
    *
    * @return nullptr   => success
    * @return !=nullptr => failed, error message
    */
   const char *readIdcode(uint32_t &idcode);

   /**
    * Check target Vref is present
    *
    * @return nullptr   => success
    * @return !=nullptr => failed, error message
    */
   const char *checkTargetVref();

};

#endif /* XSVFLOADER_H_ */
