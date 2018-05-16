package com.example.xuqiang.app_framework.View.Test.test_utils;

import com.example.libcore_ui.activity.BaseActivity;
import com.example.xuqiang.app_framework.R;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

/**
 * Description: utils测试类
 *
 * Created by xuqiang on 2018/1/9 0009.
 */

public class UtilsActivity extends BaseActivity implements View.OnClickListener {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initView();
        initData();
    }

    protected void initView() {
        setContentView(R.layout.activity_test_utils);
        $(R.id.btn_test_file).setOnClickListener(this);
        $(R.id.btn_test_image).setOnClickListener(this);
        $(R.id.btn_test_common).setOnClickListener(this);
    }

    protected void initData() {

    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.btn_test_file:
                startActivity(new Intent(this, FileActivity.class));
                break;
            case R.id.btn_test_image:
                startActivity(new Intent(this, ImageActivity.class));
                break;
            case R.id.btn_test_common:
                startActivity(new Intent(this, CommonActivity.class));
                break;
        }
    }
}
