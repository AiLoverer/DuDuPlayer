package com.example.xuqiang.app_framework.View.Test.test_widget;

import com.example.libcore_ui.activity.BaseActivity;
import com.example.xuqiang.app_framework.R;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

/**
 * Description: 测试导入控件的activity
 *
 * Created by xuqiang on 2018/1/9 0009.
 */

public class WidgetActivity extends BaseActivity implements View.OnClickListener {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_test_widget);
        findViewById(R.id.btn_test_gridlayout).setOnClickListener(this);
        findViewById(R.id.btn_test_flowlayout).setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        if (v.getId() == R.id.btn_test_gridlayout)
            startActivity(new Intent(this, GridLayoutActivity.class));
        else if (v.getId() == R.id.btn_test_flowlayout)
            startActivity(new Intent(this, FlowLayoutActivity.class));
    }
}
