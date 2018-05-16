package com.example.xuqiang.app_framework.View.Test.test_utils;

import android.os.Bundle;
import android.widget.TextView;

import com.example.libcore.utils.CommonUtils;
import com.example.libcore_ui.activity.BaseActivity;
import com.example.xuqiang.app_framework.R;

/**
 * Description: 测试{@link com.android.libcore.utils.CommonUtils}类
 *
 * Created by xuqiang on 2018/1/9 0009.
 */

public class CommonActivity extends BaseActivity {
    TextView getScreenWidth;
    TextView getScreenHeight;
    TextView isNetworkWifi;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initView();
        initData();
    }

    protected void initView() {
        setContentView(R.layout.activity_test_common);
        getScreenWidth = $(R.id.getScreenWidth);
        getScreenHeight = $(R.id.getScreenHeight);
        isNetworkWifi = $(R.id.isNetworkWifi);
        getScreenWidth.setText(CommonUtils.getScreenWidth()+"");
        getScreenHeight.setText(CommonUtils.getScreenHeight()+"");
        isNetworkWifi.setText(CommonUtils.isNetworkWifi()+"");
    }

    protected void initData() {

    }
}
