#ifndef __USB_TYPE_HEADER__
#define __USB_TYPE_HEADER__ 

#include <ntddk.h> 
#include "Hidport.h"
#include "usb.h" 
#include "TList.h"
#include "hidpddi.h"


//--------------------------------------//

typedef struct _HID_DEVICE_LIST
{
	TChainListHeader*					  	 head;
	ULONG							  currentSize;
	ULONG								 RefCount;
} HID_DEVICE_LIST, *PHID_DEVICE_LIST;


typedef struct _HID_USB_DEVICE_EXTENSION {
	ULONG64							   status;			//+0x0	
	PUSB_DEVICE_DESCRIPTOR		    DeviceDesc;			//+0x8
	PUSBD_INTERFACE_INFORMATION		InterfaceDesc;		//+0x10
	USBD_CONFIGURATION_HANDLE 		ConfigurationHandle;//+0x18
	ULONG                           NumPendingRequests;
	KEVENT                          AllRequestsCompleteEvent;
	ULONG                           DeviceFlags;
	PIO_WORKITEM                    ResetWorkItem;
	HID_DESCRIPTOR				    HidDescriptor;
	PDEVICE_OBJECT                  functionalDeviceObject;
}HID_USB_DEVICE_EXTENSION, *PHID_USB_DEVICE_EXTENSION;



typedef struct _EXTRACT_DATA
{
	union
	{
		struct
		{

			USHORT ByteOffsetX;
			USHORT BitOffsetX;
			USHORT XOffsetSize;

			USHORT ByteOffsetY;
			USHORT BitOffsetY;
			USHORT YOffsetSize;

			USHORT ByteOffsetZ;
			USHORT BitOffsetZ;
			USHORT ZOffsetSize;

			USHORT ByteOffsetBtn;
			USHORT BitOffsetBtn;
			USHORT BtnOffsetSize;
			//
			ULONG  IsAbsolute;
			USHORT ReportId;
		}MOUDATA;

		struct
		{
			UCHAR  SpecialKeyOffset;
			UCHAR  SpecialKeySize;
			UCHAR  NormalKeyOffset;
			UCHAR  NormalKeySize;
			UCHAR  LedKeyOffset;
			UCHAR  LedKeySize;
		}KBDDATA;

	};

}EXTRACTDATA, *PEXTRACTDATA;

#pragma pack(push, 4)
typedef struct _HID_DEVICE_NODE
{
	PDEVICE_OBJECT					device_object;
	HID_USB_DEVICE_EXTENSION*		mini_extension;
	HIDP_DEVICE_DESC				parsedReport;
	EXTRACTDATA* 					InputExtractData;
	EXTRACTDATA* 					OuptputExtractData;
	EXTRACTDATA* 					FeactureputExtractData;
	PHIDP_COLLECTION_DESC 			Collection;
}HID_DEVICE_NODE, *PHID_DEVICE_NODE;
#pragma pack(pop)


#pragma pack(push, 4)
typedef struct _USER_CONFIG_EX
{
	ULONG 	  Version;
	ULONG	  ProtocolVersion;
	ULONGLONG UserData;
	ULONG	  UserDataLen;
	ULONG 	  Flags;
}USERCONFIGEX, *PUSERCONFIGEX;
#pragma pack(pop)


#define MOUSE_FLAGS						 0x1
#define KEYBOARD_FLAGS					 0x2


#define CHANNEL_DUMP_ATTRIBUTE_RELATED					1
#define CHANNEL_DUMP_REPORT_REALTED						2
#define CHANNEL_DUMP_REPORT_BYTE_OFFSET_REALTED			4 
#define CHANNEL_DUMP_RANGE_RELATED						8
#define CHANNEL_DUMP_LINK_COL_RELATED					16
#define CHANNEL_DUMP_ALL  CHANNEL_DUMP_ATTRIBUTE_RELATED | CHANNEL_DUMP_REPORT_REALTED | CHANNEL_DUMP_RANGE_RELATED | CHANNEL_DUMP_LINK_COL_RELATED | CHANNEL_DUMP_REPORT_BYTE_OFFSET_REALTED

//--------------------------------------//
#endif