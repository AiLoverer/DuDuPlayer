package com.example.libcore_ui.net.request;

import android.content.Context;

import com.example.libcore.net.netapi.BaseNetApi;

import org.xmlpull.v1.XmlPullParser;

import java.util.Map;

/**
 * Description: 对基础netapi类的完善，可以在request包下添加自定义的request，并且
 * 在这个类里添加相应的函数
 *
 * Created by xuqiang on 2018/1/8 0008.
 */

public class NetApi extends BaseNetApi {
    private volatile static NetApi instance;

    public static NetApi getInstance(){
        if (instance == null){
            synchronized (NetApi.class){
                if (instance == null){
                    instance = new NetApi();
                }
            }
        }
        return instance;
    }

    public void xmlRequest(Context context, String url, Map<String, String> params, OnNetCallback<XmlPullParser> callback){
        makeRequest(context, XMLRequest.class, url, params, callback);
    }
}
