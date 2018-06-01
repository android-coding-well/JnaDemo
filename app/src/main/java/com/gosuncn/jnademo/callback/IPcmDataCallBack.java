package com.gosuncn.jnademo.callback;

import com.sun.jna.Callback;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.ByteByReference;

/**
 * 回调只要保持返回值和参数类型个数正确即可
 * 对名称无要求
 */
public interface IPcmDataCallBack extends Callback {

     void pcmDataCallBack(ByteByReference data, int size, Pointer userdata);
}
