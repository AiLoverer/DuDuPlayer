package com.example.libcore_ui.dialog;

import android.app.Dialog;
import android.content.Context;
import android.widget.TextView;

import com.example.libcore_ui.R;

/**
 * Description: 默认应用加载框，可自定义
 *
 * Created by xuqiang on 2018/1/8 0008.
 */

public class LoadingDialog extends Dialog {
    private TextView tv_loading_text;

    public LoadingDialog(Context context) {
        this(context, 0);
    }

    public LoadingDialog(Context context, int themeResId) {
        super(context, R.style.theme_dialog);
        setContentView(R.layout.loading_dialog_layout);
        tv_loading_text = (TextView) findViewById(R.id.tv_loading_text);
    }

    public void setLoadingText(String text){
        tv_loading_text.setText(text);
    }
}
