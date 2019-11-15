#ifndef ZKFVAPI_H
#define ZKFVAPI_H

#ifndef ZKINTERFACE
#define ZKINTERFACE
#endif

#ifndef APICALL
#define APICALL __stdcall
#endif


#ifdef __cplusplus
extern "C"
{
#endif
	ZKINTERFACE int APICALL ZKFingerVein_GetSDKVersion(char* version,int *length);

	ZKINTERFACE int APICALL ZKFingerVein_Init();

	ZKINTERFACE int APICALL ZKFingerVein_Terminate();

	ZKINTERFACE int APICALL ZKFingerVein_GetDeviceCount();

	ZKINTERFACE int APICALL ZKFingerVein_SeneorReOpen(void *handle);

	ZKINTERFACE void* APICALL ZKFingerVein_OpenDevice(int index);

	ZKINTERFACE int APICALL ZKFingerVein_CloseDevice(void* handle);

	ZKINTERFACE int APICALL ZKFingerVein_SetParameter(void* handle, int paramCode, unsigned char* paramValue, int size);

	ZKINTERFACE int APICALL ZKFingerVein_GetParameter(void* handle, int paramCode, unsigned char* paramValue, int* size);

	ZKINTERFACE int APICALL ZKFingerVein_CaptureFingerVeinImage(void* handle, unsigned char* fpImage, int* cbFPImage, unsigned char* fvImage, int* cbFVImage);

	ZKINTERFACE int APICALL ZKFingerVein_CaptureFingerVeinImageAndTemplate(void* handle, unsigned char* fpImage, int* cbFPImage, unsigned char* fvImage, int* cbFVImage, unsigned char* fpTemplate, int* cbFPTemplate, unsigned char* fvTemplate, int* cbFVTemplate);

	ZKINTERFACE int APICALL ZKFingerVein_Verify(void* handle, int type, unsigned char* regTemplate, int cbRegTemplate, unsigned char* verTemplate, int cbVerTemplate);

	ZKINTERFACE int APICALL ZKFingerVein_MergeFP(void* handle, unsigned char** tmp, int count, unsigned char* regTmp, int* cbRegTmp);

	ZKINTERFACE void* APICALL ZKFingerVein_DBInit(void* handle);

	ZKINTERFACE int APICALL ZKFingerVein_DBFree(void* dbHandle);

	ZKINTERFACE int APICALL ZKFingerVein_DBAdd(void* dbHandle, int type, char* fvid, unsigned char** tmp, int count);

	ZKINTERFACE int APICALL ZKFingerVein_DBDel(void* dbHandle, int type, char* fvid);

	ZKINTERFACE int APICALL ZKFingerVein_DBClear(void* dbHandle, int type);

	ZKINTERFACE int APICALL ZKFingerVein_DBCount(void* dbHandle, int type);

	ZKINTERFACE int APICALL ZKFingerVein_DBIdentify(void* dbHandle, int type, unsigned char* verTemplate, int cbVerTemplate, char* id, int* score);

	ZKINTERFACE int APICALL ZKFingerVein_DBHybridIdentify(void* dbHandle, int mode, unsigned char* verFPTemplate, int cbVerFPTemplate, unsigned char* verFVTemplate, int cbVerFVTemplate, char* id, int* score);

	ZKINTERFACE int APICALL ZKFingerVein_SetThreshold(void* hDBCache, int code, int value);
	ZKINTERFACE int APICALL ZKFingerVein_GetThreshold(void* hDBCache, int code, int* value);
#ifdef __cplusplus
};
#endif

#endif