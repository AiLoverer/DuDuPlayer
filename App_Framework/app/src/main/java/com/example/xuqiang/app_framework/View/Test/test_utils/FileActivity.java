package com.example.xuqiang.app_framework.View.Test.test_utils;

import com.example.libcore.log.L;
import com.example.libcore.toast.T;
import com.example.libcore.utils.FileUtils;
import com.example.libcore_ui.activity.BaseActivity;
import com.example.xuqiang.app_framework.R;

import android.os.Bundle;
import android.view.View;

/**
 * Description: 测试FileUtils
 *
 * Created by xuqiang on 2018/1/9 0009.
 */

public class FileActivity extends BaseActivity implements View.OnClickListener {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initView();
        initData();
    }

    protected void initView() {
        setContentView(R.layout.activity_test_file);
        $(R.id.btn_test_file).setOnClickListener(this);
    }

    protected void initData() {

    }

    @Override
    public void onClick(View v) {
        T.getInstance().showShort("请查看framework目录");
        FileUtils.createFileInTempDirectory("temp.temp");
        FileUtils.createFileInImageDirectory("a.png");
        FileUtils.createFileInVideoDirectory("a.mp4");
        FileUtils.createFileInVoiceDirectory("a.mp3");
        FileUtils.createFileInHtmlDirectory("a.html");
        L.i("sbsb",getApplicationContext().getFilesDir().getAbsolutePath());
        L.e("size" + FileUtils.getFileOrDirectorySize(FileUtils.getExternalStoragePath()));
    }
}
