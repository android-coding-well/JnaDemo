package com.gosuncn.jnademo

import android.Manifest
import android.content.pm.PackageManager
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v4.app.ActivityCompat
import android.util.Log
import android.widget.Toast
import com.gosuncn.jnademo.callback.IPcmDataCallBack
import com.gosuncn.jnademo.jna.JnaTest
import com.gosuncn.jnademo.struct.StruAudRecParams
import com.sun.jna.Pointer
import com.sun.jna.ptr.*
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    val TAG = "MainActivity"
    lateinit var handle: PointerByReference

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
        sample_text.text = stringFromJNI()

        checkPermission()
        var ret = JnaTest.INSTANCE.GS_AudioRecorder_Init()
        if (ret != 0) {
            Toast.makeText(this, "GS_AudioRecorder_Init failed", Toast.LENGTH_SHORT);
        }

    }

    private fun checkPermission() {
        var res = ActivityCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO)
        if (res != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.RECORD_AUDIO), 0)
        }
    }


    override fun onStart() {
        super.onStart()
        var StruAudRecParams = StruAudRecParams.ByReference()
        StruAudRecParams.DeviceNum = 0
        StruAudRecParams.SamplePerSec = 8000
        StruAudRecParams.BitsPerSample = 16
        StruAudRecParams.Channels = 1
        StruAudRecParams.ChunkSize = 640
        StruAudRecParams.ExtraData = Pointer.NULL
        handle = PointerByReference(Pointer.NULL)
        var ret = JnaTest.INSTANCE.GS_AudioRecorder_Create(handle, StruAudRecParams)
        if (ret != 0) {
            Toast.makeText(this, "GS_AudioRecorder_Create failed", Toast.LENGTH_SHORT)
        }
        Log.i(TAG, "ret=" + ret + handle.value)


        ret = JnaTest.INSTANCE.GS_AudioRecorder_SetDataCallback(handle.value, object : IPcmDataCallBack {

            override fun pcmDataCallBack(data: ByteByReference, size: Int, userdata: Pointer) {
                Log.i(TAG, "PCMDataCallBack:data=" + data.pointer.getByteArray(0, size).size + ",size=" + size + ",userdate=" + userdata.getString(0))
            }
        }, "123456")
        if (ret != 0) {
            Toast.makeText(this, "GS_AudioRecorder_SetDataCallback failed", Toast.LENGTH_SHORT)
        }
        ret = JnaTest.INSTANCE.GS_AudioRecorder_Start(handle.value)
        if (ret != 0) {
            Toast.makeText(this, "GS_AudioRecorder_Start failed", Toast.LENGTH_SHORT)
        }
    }

    override fun onStop() {
        var ret = JnaTest.INSTANCE.GS_AudioRecorder_Stop(handle.value)
        if (ret != 0) {
            Toast.makeText(this, "GS_AudioRecorder_Stop failed", Toast.LENGTH_SHORT)
        }
        ret = JnaTest.INSTANCE.GS_AudioRecorder_Destroy(handle.value)
        if (ret != 0) {
            Toast.makeText(this, "GS_AudioRecorder_Destroy failed", Toast.LENGTH_SHORT)
        }
        super.onStop()

    }

    override fun onDestroy() {
        var ret = JnaTest.INSTANCE.GS_AudioRecorder_Cleanup()
        if (ret != 0) {
            Toast.makeText(this, "GS_AudioRecorder_Cleanup failed", Toast.LENGTH_SHORT)
        }
        super.onDestroy()
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }

    }
}
