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

// ¼�����
typedef void* GS_AUDREC_HANDLE;

// ¼��PCM���ݵĻص�
typedef void (*PCMDataCallBack)(char* data, int size, void* userdata);

enum EnumAudRecErr{
	kAudRecSuccess,		//�ɹ�
	kAudRecNoDevice,	//�Ҳ����豸
	kAudRecBadParams,	//�������
	kAudRecInnerError,	//�ڲ�����
	kAudRecUnInit,		//δ��ʼ��
};

typedef struct _StruAudRecParams{
	int DeviceNum;		//ѡ��¼���豸��0��ʾĬ��
	int SamplePerSec;	//������
	int BitsPerSample;	//λ��
	int Channels;		//ͨ����
	int ChunkSize;		//�ص����ݵĴ�С��Ӱ���ӳ�
	void* ExtraData;
}StruAudRecParams;

/*!
 * Method		GS_AudioRecorder_Init
 * @brief		ȫ�ֳ�ʼ��¼���⣬ֻ�ó�ʼ��һ��
 * @return		EnumAudRecErr
 */
GSAUDIORECORDER_API EnumAudRecErr GS_AudioRecorder_Init();

/*!	
 * Method		GS_AudioRecorder_Cleanup
 * @brief		ȫ�ַ���ʼ��¼���⣬ȫ�ֵ���һ��
 * @return		EnumAudRecErr
 */
GSAUDIORECORDER_API EnumAudRecErr GS_AudioRecorder_Cleanup();

/*!
 * Method		GS_AudioRecorder_Create
 * @brief		����¼����
 * @param[in]   handle	¼��������ַ
 * @param[in]   params	¼������
 * @return		EnumAudRecErr
 */
GSAUDIORECORDER_API EnumAudRecErr GS_AudioRecorder_Create(GS_AUDREC_HANDLE *handle, StruAudRecParams &params);

/*!
 * Method		GS_AudioRecorder_Destroy
 * @brief		����¼����
 * @param[in]   handle	¼������
 * @return		EnumAudRecErr
 */
GSAUDIORECORDER_API EnumAudRecErr GS_AudioRecorder_Destroy(GS_AUDREC_HANDLE handle);

/*!
 * Method		GS_AudioRecorder_SetDataCallback
 * @brief		����¼�����PCM���ݻص�
 * @param[in]   handle	¼������
 * @param[in]   cb		¼�����ݻص�����
 * @param[in]   userdata	�û�����
 * @return		EnumAudRecErr
 */
GSAUDIORECORDER_API EnumAudRecErr GS_AudioRecorder_SetDataCallback(GS_AUDREC_HANDLE handle, PCMDataCallBack cb, void* userdata);

/*!
 * Method		GS_AudioRecorder_Start
 * @brief		��ʼ¼��
 * @param[in]   handle	¼������
 * @return		EnumAudRecErr
 */
GSAUDIORECORDER_API EnumAudRecErr GS_AudioRecorder_Start(GS_AUDREC_HANDLE handle);

/*!
 * Method		GS_AudioRecorder_Stop
 * @brief		ֹͣ¼��
 * @param[in]   handle	¼������
 * @return		EnumAudRecErr
 */
GSAUDIORECORDER_API EnumAudRecErr GS_AudioRecorder_Stop(GS_AUDREC_HANDLE handle);

#endif
