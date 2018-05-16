package com.example.xuqiang.app_framework.View.Test.test_opengles;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.example.libcore_ui.activity.BaseActivity;
import com.example.xuqiang.app_framework.R;

public class GLESActivity extends BaseActivity implements View.OnClickListener{
    private Button btn_test_sound;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_test_opengles);

        initView();

    }
    protected void initView(){
        btn_test_sound = $(R.id.btn_test_sound);

        btn_test_sound.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        Intent intent = new Intent();
        switch (v.getId()){
            case R.id.btn_test_sound:
                intent.setClass(this, GLESSoundActivity.class);
                break;
                default:
                    break;
        }
        startActivity(intent);
    }
}
