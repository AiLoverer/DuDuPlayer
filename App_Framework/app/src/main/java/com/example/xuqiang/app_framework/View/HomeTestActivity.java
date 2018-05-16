package com.example.xuqiang.app_framework.View;

import com.example.libcore.toast.T;
import com.example.libcore_ui.activity.BaseActivity;
import com.example.xuqiang.app_framework.R;
import com.example.xuqiang.app_framework.View.Test.test_activity.ActivityTestHomePage;
import com.example.xuqiang.app_framework.View.Test.test_cache.CacheActivity;
import com.example.xuqiang.app_framework.View.Test.test_db.DBActivity;
import com.example.xuqiang.app_framework.View.Test.test_dialog.DialogActivity;
import com.example.xuqiang.app_framework.View.Test.test_download.DownloadActivity;
import com.example.xuqiang.app_framework.View.Test.test_guide.GuideActivity;
import com.example.xuqiang.app_framework.View.Test.test_imageloader.ImageActivity;
import com.example.xuqiang.app_framework.View.Test.test_netapi.NetActivity;
import com.example.xuqiang.app_framework.View.Test.test_opengles.GLESActivity;
import com.example.xuqiang.app_framework.View.Test.test_utils.UtilsActivity;
import com.example.xuqiang.app_framework.View.Test.test_volley.VolleyActivity;
import com.example.xuqiang.app_framework.View.Test.test_webview.WebViewActivity;
import com.example.xuqiang.app_framework.View.Test.test_widget.WidgetActivity;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.TextView;

import java.util.Date;

/**
 * Description: homepage
 *
 * Created by xuqiang on 2018/1/9 0009.
 */

public class HomeTestActivity extends BaseActivity implements View.OnClickListener {
    public static final String ACTION = "action_from_activity_test_home_page";

    /** 测试activity */
    private Button btn_test_activity;
    /** 测试网络请求 */
    private Button btn_test_net;
    /** 测试图片加载 */
    private Button btn_test_imageloder;
    /** 测试volley */
    private Button btn_test_volley;
    /** 测试蒙版 */
    private Button btn_test_guide;
    /** 测试dialog */
    private Button btn_test_dialog;
    /** 测试数据库 */
    private Button btn_test_db;
    /** 测试cache */
    private Button btn_test_cache;
    /** 测试webview */
    private Button btn_test_webview;
    /** 测试断点续传 */
    private Button btn_test_download;
    /** 测试utils */
    private Button btn_test_utils;
    /** 测试widget */
    private Button btn_test_widget;
    /** 测试OpenGL ES**/
    private Button btn_test_opengles;
    /** 底部的代替navigation bar */
    private FrameLayout fl_navigation;
    private TextView tv_info;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        initView();
        initData();
        initLoadTime();
    }

    protected void initView() {
        setContentView(R.layout.activity_home_test);
        btn_test_activity = $(R.id.btn_test_activity);
        btn_test_net = $(R.id.btn_test_net);
        btn_test_imageloder = $(R.id.btn_test_imageloder);
        btn_test_volley = $(R.id.btn_test_volley);
        btn_test_guide = $(R.id.btn_test_guide);
        btn_test_dialog = $(R.id.btn_test_dialog);
        btn_test_db = $(R.id.btn_test_db);
        btn_test_cache = $(R.id.btn_test_cache);
        btn_test_webview = $(R.id.btn_test_webview);
        btn_test_download = $(R.id.btn_test_download);
        btn_test_utils = $(R.id.btn_test_utils);
        fl_navigation = (FrameLayout) findViewById(R.id.fl_navigation);
        btn_test_widget = $(R.id.btn_test_widget);
        btn_test_opengles = $(R.id.btn_test_opengles);

        btn_test_activity.setOnClickListener(this);
        btn_test_net.setOnClickListener(this);
        btn_test_imageloder.setOnClickListener(this);
        btn_test_volley.setOnClickListener(this);
        btn_test_guide.setOnClickListener(this);
        btn_test_dialog.setOnClickListener(this);
        btn_test_db.setOnClickListener(this);
        btn_test_cache.setOnClickListener(this);
        btn_test_webview.setOnClickListener(this);
        btn_test_utils.setOnClickListener(this);
        btn_test_download.setOnClickListener(this);
        btn_test_widget.setOnClickListener(this);
        btn_test_opengles.setOnClickListener(this);
        tv_info = (TextView) findViewById(R.id.tv_info);
        //http://stackoverflow.com/questions/2444040/naming-my-application-in-android
        setTitle("主页");
        addNavigationOnBottom(fl_navigation);
    }

    protected void initData() {
        registerReceiver(ACTION);
    }

    @Override
    protected void onReceive(Context context, Intent intent) {
        if (intent.getAction().equalsIgnoreCase(ACTION)){
            tv_info.setText("有一个从activity_home_page来的广播");
        }
    }

    @Override
    public void onClick(View v) {
        Intent intent = new Intent();
        switch (v.getId()){
            case R.id.btn_test_activity:
                intent.setClass(this, ActivityTestHomePage.class);
                break;
            case R.id.btn_test_net:
                intent.setClass(this, NetActivity.class);
                break;
            case R.id.btn_test_imageloder:
                intent.setClass(this, ImageActivity.class);
                break;
            case R.id.btn_test_volley:
                intent.setClass(this, VolleyActivity.class);
                break;
            case R.id.btn_test_guide:
                intent.setClass(this, GuideActivity.class);
                break;
            case R.id.btn_test_dialog:
                intent.setClass(this, DialogActivity.class);
                break;
            case R.id.btn_test_db:
                intent.setClass(this, DBActivity.class);
                break;
            case R.id.btn_test_cache:
                intent.setClass(this, CacheActivity.class);
                break;
            case R.id.btn_test_webview:
                intent.setClass(this, WebViewActivity.class);
                break;
            case R.id.btn_test_download:
                intent.setClass(this, DownloadActivity.class);
                break;
            case R.id.btn_test_utils:
                intent.setClass(this, UtilsActivity.class);
                break;
            case R.id.btn_test_widget:
                intent.setClass(this, WidgetActivity.class);
                break;
            case R.id.btn_test_opengles:
                intent.setClass(this, GLESActivity.class);
                break;
            default:
                return;
        }
        startActivity(intent);
    }
    protected void initLoadTime(){
        SharedPreferences sp = this.getSharedPreferences("bn", Context.MODE_PRIVATE);
        String lastLoginTime = sp.getString("time", null);
        if (lastLoginTime == null){
            lastLoginTime = "用户你好，欢迎你第一次光临本软件";
        }else {
            lastLoginTime = "用户你好，你上次进入时间为:"+lastLoginTime;
        }
        SharedPreferences.Editor editor = sp.edit();
        editor.putString("time", new Date().toLocaleString());
        editor.commit();
        T.getInstance().showShort(lastLoginTime);
    }
}
