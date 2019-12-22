/*! \file
    \brief Bootloader for Kinetis devices

    XsvfLoader.cpp

    \verbatim
    Copyright (C) 20019 Peter O'Donoghue

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
    \endverbatim

    \verbatim
   Change History
   -=========================================================================================
   | 10 Dec 2019 | Initial work                                              - pgo
   +=========================================================================================
   \endverbatim
 */
#include <stdio.h>

#include "libusb.h"
#include "XsvfLoader.h"
#include "UsbCommandMessage.h"

static constexpr uint8_t   EP_OUT      = LIBUSB_ENDPOINT_OUT|1;  // EP #1 OUT
static constexpr uint8_t   EP_IN       = LIBUSB_ENDPOINT_IN |2;  // EP #2 IN

static constexpr uint16_t  VENDOR_ID   = 0x16D0;    // Vendor (actually MCS)
static constexpr uint16_t  PRODUCT_ID  = 0x4331;    // Product ID

XsvfLoader::XsvfLoader() {
}

XsvfLoader::~XsvfLoader() {
}

/**
 * Locate USB device to program
 *
 * @return nullptr   => failed
 * @return !=nullptr => LIBUSB device handle
 */
libusb_device_handle *XsvfLoader::findDevice() {

   libusb_device **devs;
   int rc;

   ssize_t cnt = libusb_get_device_list(NULL, &devs);
   if (cnt <= 0){
      return nullptr;
   }

   libusb_device_handle *device = nullptr;
   libusb_device *dev;
   unsigned i=0;
   while ((dev = devs[i++]) != NULL) {
      struct libusb_device_descriptor desc;
      rc = libusb_get_device_descriptor(dev, &desc);
      if (rc < 0) {
         fprintf(stderr, "findDevice - Failed to get device descriptor");
         return nullptr;
      }
      //      fprintf(stderr, "%04x:%04x (bus %d, device %d)\n",
      //            desc.idVendor, desc.idProduct,
      //            libusb_get_bus_number(dev), libusb_get_device_address(dev));
      if ((desc.idVendor == VENDOR_ID) && (desc.idProduct == PRODUCT_ID)) {
         rc = libusb_open(dev, &device);
         break;
      }
   }
   if (device != nullptr) {
      rc = libusb_set_configuration(device, 1);
      if (rc < 0) {
         libusb_close(device);
         device = nullptr;
      }
      rc = libusb_claim_interface(device, 0);
      if (rc < 0) {
         libusb_close(device);
         device = nullptr;
      }
   }
   if (cnt > 0) {
      libusb_free_device_list(devs, 1);
   }
   if (device == nullptr) {
      fprintf(stderr, "findDevice - Device failed to open\n");
   }
   return device;
}

/**
 * Check target Vref is present
 *
 * @return nullptr   => success
 * @return !=nullptr => failed, error message
 */
const char *XsvfLoader::checkTargetVref() {
   const char *errorMessage = nullptr;

   int rc = libusb_init(NULL);
   if (rc < 0) {
      return "sendSxvfFile - Libusb failed initialisation";
   }
   do {
      device = findDevice();
      if (device == nullptr) {
         errorMessage = "Programmer not found";
         break;
      }

      UsbCommandIdentifyMessage  command = {
            /* command      */ UsbCommand_CheckVref,
            /* byteLength   */ 0,
      };

      int bytesSent = 0;
      int rc = libusb_bulk_transfer(device, EP_OUT, (uint8_t*)&command, sizeof(command), &bytesSent, 10000);
      if (rc < 0) {
         errorMessage = libusb_error_name(rc);
         break;
      }
      if ((unsigned)bytesSent != sizeof(command)) {
         errorMessage = "checkTargetVref - Incomplete transmission";
         break;
      }

      SimpleResponseMessage response = {};

      int bytesReceived = 0;
      rc = libusb_bulk_transfer(device, EP_IN, (uint8_t*)&response, sizeof(response), &bytesReceived, 10000);
      if (rc < 0) {
         errorMessage = libusb_error_name(rc);
         break;
      }
      if ((unsigned)bytesReceived < sizeof(response)) {
         errorMessage = "checkTargetVref - Incomplete reception";
         break;
      }
      if (response.status != UsbCommandStatus_OK) {
         errorMessage = "checkTargetVref - No Vref on device";
         break;
      }

   } while(false);

   if (device != nullptr) {
      libusb_close(device);
      device = nullptr;
   }

   libusb_exit(nullptr);
   return errorMessage;
}

/**
 * Read IDCODE from device
 *
 * @param idcode  IDCODE read from target
 *
 * @return nullptr   => success
 * @return !=nullptr => failed, error message
 */
const char *XsvfLoader::readIdcode(uint32_t &idcode) {
   const char *errorMessage = nullptr;

   int rc = libusb_init(NULL);
   if (rc < 0) {
      return "sendSxvfFile - Libusb failed initialisation";
   }
   do {
      device = findDevice();
      if (device == nullptr) {
         errorMessage = "Programmer not found";
         break;
      }

      UsbCommandIdentifyMessage  command = {
            /* command      */ UsbCommand_Identify,
            /* byteLength   */ 0,
      };

      int bytesSent = 0;
      int rc = libusb_bulk_transfer(device, EP_OUT, (uint8_t*)&command, sizeof(command), &bytesSent, 10000);
      if (rc < 0) {
         errorMessage = libusb_error_name(rc);
         break;
      }
      if ((unsigned)bytesSent != sizeof(command)) {
         errorMessage = "readIdcode - Incomplete transmission";
         break;
      }

      ResponseIdentifyMessage response = {};

      int bytesReceived = 0;
      rc = libusb_bulk_transfer(device, EP_IN, (uint8_t*)&response, sizeof(response), &bytesReceived, 10000);
      if (rc < 0) {
         errorMessage = libusb_error_name(rc);
         break;
      }
      if ((unsigned)bytesReceived < sizeof(response)) {
         errorMessage = "readIdcode - Incomplete reception";
         break;
      }
      if (response.status != UsbCommandStatus_OK) {
         errorMessage = "readIdcode - Operation failed on device";
         break;
      }
      fprintf(stderr, "IDCODE = 0x%08X\n", response.idcode);
      fflush(stderr);
      idcode = response.idcode;

   } while(false);

   if (device != nullptr) {
      libusb_close(device);
      device = nullptr;
   }

   libusb_exit(nullptr);
   return errorMessage;
}

/**
 * Download XSVF data to opened device
 *
 * @param xsvf_size
 * @param xsvf_data
 *
 * @return nullptr   => success
 * @return !=nullptr => failed, error message
 */
const char *XsvfLoader::downloadXsvfBlock(unsigned xsvf_size, uint8_t *xsvf_data) {
   int rc = 0;

   UsbSendXsvfBlockMessage message = {
         /* command      */ UsbCommand_XSVF_data,
         /* byteLength   */ xsvf_size,
         /* data         */ {},
   };
   for (unsigned index=0; index<xsvf_size; index++) {
      message.data[index] = xsvf_data[index];
   }
   int bytesSent   = 0;
   int bytesToSend = sizeof(SimpleCommandMessage)+message.byteLength;
   rc = libusb_bulk_transfer(device, EP_OUT, (uint8_t*)&message, bytesToSend, &bytesSent, 10000);
   if (rc < 0) {
      return libusb_error_name(rc);
   }
   if (bytesSent != bytesToSend) {
      return "downloadXsvfBlock - Incomplete transmission";
   }
   SimpleResponseMessage response = {};

   int bytesReceived = 0;
   rc = libusb_bulk_transfer(device, EP_IN, (uint8_t*)&response, sizeof(response), &bytesReceived, 10000);
   if (rc < 0) {
      return libusb_error_name(rc);
   }
   if ((unsigned)bytesReceived < sizeof(response)) {
      fprintf(stderr, "downloadXsvfBlock - bytesReceived = %d\n", bytesReceived);
      return "downloadXsvfBlock - Incomplete reception";
   }
   if (response.status != UsbCommandStatus_OK) {
      return "downloadXsvfBlock - Operation failed on device";
   }
   return nullptr;
}

/**
 * Download XSVF data to device
 *
 * @param xsvf_size
 * @param xsvf_data
 *
 * @return nullptr   => success
 * @return !=nullptr => failed, error message
 */
const char *XsvfLoader::downloadXsvf(unsigned xsvf_size, uint8_t *xsvf_data) {

   // OK for empty image
   if (xsvf_size==0) {
      return nullptr;
   }

   fprintf(stderr, "downloadXsvf - Sending header for SXVF Data (%d bytes)]\n", xsvf_size);

   UsbStartXsvfMessage command = {
         /* command      */ UsbCommand_XSVF,
         /* byteLength   */ sizeof(command.xsvfSize),
         /* xsvfSize     */ xsvf_size,
   };

   int bytesSent = 0;
   int rc = libusb_bulk_transfer(device, EP_OUT, (uint8_t*)&command, sizeof(command), &bytesSent, 10000);
   if (rc < 0) {
      return libusb_error_name(rc);
   }
   if ((unsigned)bytesSent != sizeof(command)) {
      return "downloadXsvf - Incomplete transmission";
   }

   SimpleResponseMessage response = {};

   int bytesReceived = 0;
   rc = libusb_bulk_transfer(device, EP_IN, (uint8_t*)&response, sizeof(response), &bytesReceived, 10000);
   if (rc < 0) {
      return libusb_error_name(rc);
   }
   if ((unsigned)bytesReceived < sizeof(response)) {
      return "downloadXsvf - Incomplete reception";
   }
   if (response.status != UsbCommandStatus_OK) {
      return "downloadXsvf - Operation failed on device";
   }

   // Maximum size of data to write
   unsigned int maxSplitBlockSize = sizeof(UsbSendXsvfBlockMessage::data);

   const char *errrorMessage  = nullptr;
   uint32_t offset            = 0;
   uint32_t bytesToProgram    = xsvf_size;

   while (bytesToProgram>0) {
      uint32_t splitBlockSize = bytesToProgram;
      if (splitBlockSize>maxSplitBlockSize) {
         splitBlockSize = maxSplitBlockSize;
      }
      fprintf(stderr, "downloadXsvf - Sending splitBlock [0x%06X..0x%06X]\n",
            offset, offset+maxSplitBlockSize-1);
      fflush(stderr);

      errrorMessage = downloadXsvfBlock(splitBlockSize, xsvf_data+offset);
      if (errrorMessage != nullptr) {
         break;
      }
      offset          += splitBlockSize;
      bytesToProgram  -= splitBlockSize;
   }
   fprintf(stderr, "downloadXsvf - Sent %d bytes\n", offset);
   fflush(stderr);

   return errrorMessage;
}

/**
 * Download XSVF data to device
 *
 * @param xsvf_size
 * @param xsvf_data
 *
 * @return nullptr   => success
 * @return !=nullptr => failed, error message
 */
const char *XsvfLoader::sendSxvfFile(unsigned xsvf_size, uint8_t *xsvf_data) {

   const char *errorMessage = nullptr;

   int rc = libusb_init(NULL);
   if (rc < 0) {
      return "sendSxvfFile - Libusb failed initialisation";
   }
   do {
      device = findDevice();
      if (device == nullptr) {
         errorMessage = "Programmer not found";
         break;
      }
      errorMessage = downloadXsvf(xsvf_size, xsvf_data);
      if (errorMessage != nullptr) {
         break;
      }
   } while(false);

   if (device != nullptr) {
      libusb_close(device);
      device = nullptr;
   }

   libusb_exit(nullptr);

   return errorMessage;
}

