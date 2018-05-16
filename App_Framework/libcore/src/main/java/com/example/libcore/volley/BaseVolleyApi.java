package com.example.libcore.volley;

import com.android.volley.RequestQueue;
import com.android.volley.toolbox.ImageLoader;
import com.android.volley.toolbox.Volley;
import com.example.libcore.application.RootApplication;
import com.example.libcore.net.imageloader.VolleyLruCache;

/**
 * Description: 封装的volley的请求
 * Created by xuqiang on 2018/1/8 0008.
 */

public abstract class BaseVolleyApi {
    private static RequestQueue requestQueue;
    private static ImageLoader imageLoader;

    public static RequestQueue getRequestQueue() {
        if (requestQueue == null) {
            synchronized (BaseVolleyApi.class){
                if (requestQueue == null)
                    requestQueue = Volley.newRequestQueue(RootApplication.getInstance());
            }
        }
        return requestQueue;
    }

    public static ImageLoader getImageLoader() {
        if (imageLoader == null) {
            synchronized (BaseVolleyApi.class) {
                if (imageLoader == null){
                    VolleyLruCache cache = new VolleyLruCache();
                    imageLoader = new ImageLoader(getRequestQueue(), cache);
                }
            }
        }
        return imageLoader;
    }
}
