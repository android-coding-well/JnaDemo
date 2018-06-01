package com.gosuncn.jnademo.jna;

import com.gosuncn.jnademo.callback.IPcmDataCallBack;
import com.gosuncn.jnademo.struct.StruAudRecParams;
import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.PointerByReference;

/**
 * 使用音频录制库进行测试
 */
public interface JnaTest extends Library {
    JnaTest INSTANCE = (JnaTest)
            Native.loadLibrary("GSAudioRecorder",
                    JnaTest.class);

    int GS_AudioRecorder_Init();

    int GS_AudioRecorder_Cleanup();

    int GS_AudioRecorder_Create(PointerByReference handle, StruAudRecParams.ByReference params);

    int GS_AudioRecorder_Destroy(Pointer handle);

    int GS_AudioRecorder_SetDataCallback(Pointer handle, IPcmDataCallBack cb, Object userdata);

    int GS_AudioRecorder_Start(Pointer handle);

    int GS_AudioRecorder_Stop(Pointer handle);


}
