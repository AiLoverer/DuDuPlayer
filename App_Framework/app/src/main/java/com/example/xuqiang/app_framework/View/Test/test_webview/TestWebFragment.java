package com.example.xuqiang.app_framework.View.Test.test_webview;


import android.webkit.WebView;

import com.example.libcore_ui.web.WebFragment;

/**
 * Created by xuqiang on 2018/1/9 0009.
 */

public class TestWebFragment extends WebFragment {
    public WebView mWebView;

    @Override
    protected void initView() {
        super.initView();
        mWebView = webView;
    }
}
