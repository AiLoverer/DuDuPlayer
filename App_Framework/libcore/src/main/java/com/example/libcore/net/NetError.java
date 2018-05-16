package com.example.libcore.net;

import com.android.volley.VolleyError;

/**
 * Created by xuqiang on 2018/1/8 0008.
 */

public class NetError extends Exception {
    public int errorCode;
    public String errorMessage;

    /**
     * 将volley的错误信息转换成通用的信息
     */
    public void transferVolleyError(VolleyError error){
        if (error.networkResponse != null)
            this.errorCode = error.networkResponse.statusCode;
        this.errorMessage = error.toString();
    }
}
