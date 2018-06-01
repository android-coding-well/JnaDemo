#ifndef _GSAUDIORECORDER_H_
#define _GSAUDIORECORDER_H_

#ifdef __cplusplus
#define EXT_C extern "C"
#else
#define EXT_C
#endif

#ifdef _WIN32
#	ifdef  GSAUDIORECORDER_API_EXPORTS
#		define GSAUDIORECORDER_API EXT_C __declspec(dllexport)
#	else // GSAUDIORECORDER_API_EXPORTS
#		ifdef GSAUDIORECORDERR_STATIC
#			define GSAUDIORECORDER_API 
#		else
#			define GSAUDIORECORDER_API EXT_C __declspec(dllimport)
#		endif
#	endif // GSAUDIORECORDER_API_EXPORTS
#elif defined(__ANDROID__) || defined(__APPLE__)  // _WIN32
#	define GSAUDIORECORDER_API EXT_C __attribute__ ((visibility ("default")))
#else
#	error "Undefined Platform"
#endif // _WIN32

// 录音句柄
typedef void* GS_AUDREC_HANDLE;

// 录音PCM数据的回调
typedef void (*PCMDataCallBack)(char* data, int size, void* userdata);

enum EnumAudRecErr{
	kAudRecSuccess,		//成功
	kAudRecNoDevice,	//找不到设备
	kAudRecBadParams,	//错误参数
	kAudRecInnerError,	//内部错误
	kAudRecUnInit,		//未初始化
};

typedef struct _StruAudRecParams{
	int DeviceNum;		//选择录音设备，0表示默认
	int SamplePerSec;	//采样率
	int BitsPerSample;	//位数
	int Channels;		//通道数
	int ChunkSize;		//回调数据的大小，影响延迟
	void* ExtraData;
}StruAudRecParams;

/*!
 * Method		GS_AudioRecorder_Init
 * @brief		全局初始化录音库，只用初始化一次
 * @return		EnumAudRecErr
 */
GSAUDIORECORDER_API EnumAudRecErr GS_AudioRecorder_Init();

/*!	
 * Method		GS_AudioRecorder_Cleanup
 * @brief		全局反初始化录音库，全局调用一次
 * @return		EnumAudRecErr
 */
GSAUDIORECORDER_API EnumAudRecErr GS_AudioRecorder_Cleanup();

/*!
 * Method		GS_AudioRecorder_Create
 * @brief		创建录音库
 * @param[in]   handle	录音库句柄地址
 * @param[in]   params	录音参数
 * @return		EnumAudRecErr
 */
GSAUDIORECORDER_API EnumAudRecErr GS_AudioRecorder_Create(GS_AUDREC_HANDLE *handle, StruAudRecParams &params);

/*!
 * Method		GS_AudioRecorder_Destroy
 * @brief		销毁录音库
 * @param[in]   handle	录音库句柄
 * @return		EnumAudRecErr
 */
GSAUDIORECORDER_API EnumAudRecErr GS_AudioRecorder_Destroy(GS_AUDREC_HANDLE handle);

/*!
 * Method		GS_AudioRecorder_SetDataCallback
 * @brief		设置录音库的PCM数据回调
 * @param[in]   handle	录音库句柄
 * @param[in]   cb		录音数据回调函数
 * @param[in]   userdata	用户数据
 * @return		EnumAudRecErr
 */
GSAUDIORECORDER_API EnumAudRecErr GS_AudioRecorder_SetDataCallback(GS_AUDREC_HANDLE handle, PCMDataCallBack cb, void* userdata);

/*!
 * Method		GS_AudioRecorder_Start
 * @brief		开始录音
 * @param[in]   handle	录音库句柄
 * @return		EnumAudRecErr
 */
GSAUDIORECORDER_API EnumAudRecErr GS_AudioRecorder_Start(GS_AUDREC_HANDLE handle);

/*!
 * Method		GS_AudioRecorder_Stop
 * @brief		停止录音
 * @param[in]   handle	录音库句柄
 * @return		EnumAudRecErr
 */
GSAUDIORECORDER_API EnumAudRecErr GS_AudioRecorder_Stop(GS_AUDREC_HANDLE handle);

#endif
