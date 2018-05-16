package com.example.xuqiang.app_framework.View.Test.test_widget;

import android.os.Bundle;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.libcore.utils.CommonUtils;
import com.example.libcore_ui.activity.BaseActivity;
import com.example.libcore_ui.widget.SimpleGridLayout;
import com.example.xuqiang.app_framework.R;

/**
 * Created by xuqiang on 2018/1/9 0009.
 */

public class GridLayoutActivity extends BaseActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_test_grid);
        SimpleGridLayout gll_content = findViewById(R.id.gll_content);
        ViewGroup.LayoutParams lp = new ViewGroup.LayoutParams(CommonUtils.dp2px(100), CommonUtils.dp2px(100));

        for (int i=2; i<20; i++){
            TextView textView = new TextView(this);
            textView.setLayoutParams(lp);
            textView.setText(i + "");
            textView.setTextSize(20);
            textView.setGravity(Gravity.CENTER);
            gll_content.addView(textView);
        }
    }
}
