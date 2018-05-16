package com.example.xuqiang.app_framework.View.Test.test_webview;

import com.example.libcore.toast.T;
import com.example.libcore.utils.FileUtils;
import com.example.libcore.utils.ImageUtils;
import com.example.libcore_ui.activity.BaseActivity;
import com.example.libcore_ui.web.WebFragment;
import com.example.libcore_ui.web.webactivity.WebActivity;
import com.example.xuqiang.app_framework.R;

import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.view.View;
import android.webkit.WebView;

/**
 * Description: 测试WebView
 *
 * Created by xuqiang on 2018/1/9 0009.
 */

public class WebViewActivity extends BaseActivity implements View.OnClickListener {
    private WebView webView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initView();
        initData();
    }

    protected void initView() {
        //http://stackoverflow.com/questions/30078157/webview-draw-not-properly-working-on-latest-android-system-webview-update
        if (Build.VERSION.SDK_INT >= 21)
            WebView.enableSlowWholeDocumentDraw();
        setContentView(R.layout.activity_test_webview);
        $(R.id.btn_webview).setOnClickListener(this);
        $(R.id.btn_screenshot).setOnClickListener(this);
    }

    protected void initData() {
        final TestWebFragment webFragment = new TestWebFragment();
        webFragment.setCallback(new WebFragment.WebCallback() {
            @Override
            public void onPageFinished(String url) {
                T.getInstance().showShort("加载完成");
                webView = webFragment.mWebView;
            }
        });
        FragmentManager fm = getSupportFragmentManager();
        FragmentTransaction ft = fm.beginTransaction();
        ft.add(R.id.fl_webfragment, webFragment);
        ft.commit();
        Bundle bundle = new Bundle();
        bundle.putString(WebFragment.EXTRA_URL, "http://www.bilibili.com");
        webFragment.setArguments(bundle);
    }

    @Override
    public void onClick(View v) {
        if (v.getId() == R.id.btn_webview) {
            Intent intent = new Intent(this, WebActivity.class);
            intent.putExtra(WebActivity.EXTRA_URL, "https://www.baidu.com");
            //加载assets文件
//        intent.putExtra(WebActivity.EXTRA_URL, "file:///android_asset/1.html");
//        intent.putExtra(WebActivity.EXTRA_URL, "file:///android_asset/baidu.html");
            //加载SD卡文件
//        intent.putExtra(WebActivity.EXTRA_URL, "file:///sdcard/FrameWork/html/baidu.html");
            startActivity(intent);
        }else{
            ImageUtils.saveBitmap(ImageUtils.viewShot(webView), FileUtils.getExternalStorageImagePath()+"bitmap.png", new Runnable() {
                @Override
                public void run() {
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            T.getInstance().showShort("图片位于" + FileUtils.getExternalStorageImagePath() + "bitmap.png");
                        }
                    });
                }
            });
        }
    }
}
