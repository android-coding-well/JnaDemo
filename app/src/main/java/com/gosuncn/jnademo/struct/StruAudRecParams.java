package com.gosuncn.jnademo.struct;

import com.sun.jna.Pointer;
import com.sun.jna.Structure;

import java.util.ArrayList;
import java.util.List;

/**
 * 与c结构体相对应
 */
public class StruAudRecParams extends Structure {
    //用于引用传递
    public static class ByReference extends StruAudRecParams implements Structure.ByReference {
    }
    //用于值传递
    public static class ByValue extends StruAudRecParams implements Structure.ByValue {
    }

    public int DeviceNum;        //选择录音设备，0表示默认
    public int SamplePerSec;    //采样率
    public int BitsPerSample;    //位数
    public int Channels;        //通道数
    public int ChunkSize;        //回调数据的大小，影响延迟
    public Pointer ExtraData;

    @Override
    protected List<String> getFieldOrder() {
        //以下顺序必须与c中结构体顺序对应
        List<String> list = new ArrayList<>();
        list.add("DeviceNum");
        list.add("SamplePerSec");
        list.add("BitsPerSample");
        list.add("Channels");
        list.add("ChunkSize");
        list.add("ExtraData");
        return list;
    }
}
