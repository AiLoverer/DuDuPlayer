package com.example.xuqiang.app_framework.View.Test.test_netapi;

import com.example.libcore.net.NetError;
import com.example.libcore.net.imageloader.ImageLoader;
import com.example.libcore.net.netapi.BaseNetApi;
import com.example.libcore_ui.activity.BaseActivity;
import com.example.libcore_ui.dialog.LoadingDialog;
import com.example.libcore_ui.net.request.NetApi;
import com.example.xuqiang.app_framework.R;

import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import org.json.JSONObject;
import org.xmlpull.v1.XmlPullParser;

import java.util.HashMap;

/**
 * Created by xuqiang on 2018/1/9 0009.
 */

public class NetActivity extends BaseActivity implements View.OnClickListener {
    public TextView tv_result;
    public ImageView iv_content;
    private LoadingDialog ld;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initView();
        initData();
    }
    public void initView(){
        setContentView(R.layout.activity_test_net);
        addNavigationOnBottom((ViewGroup) $(R.id.ll_content));
        tv_result = $(R.id.tv_result);
        iv_content = $(R.id.iv_content);

        $(R.id.btn_string).setOnClickListener(this);
        $(R.id.btn_jsonObject).setOnClickListener(this);
        $(R.id.btn_jsonArray).setOnClickListener(this);
        $(R.id.btn_xml).setOnClickListener(this);
        $(R.id.btn_image).setOnClickListener(this);

        ld = new LoadingDialog(this);
    }
    public void initData(){

    }

    @Override
    public void onClick(View v) {
        ld.show();
        switch (v.getId()){
            case R.id.btn_string:
                NetApi.getInstance().stringRequest(this, "https://www.baidu.com", new HashMap<String, String>(),
                        new BaseNetApi.OnNetCallback<String>() {
                            @Override
                            public void onSuccess(String result) {
                                ld.dismiss();
                                tv_result.setText(result);
                            }

                            @Override
                            public void onFail(NetError error) {
                                ld.dismiss();
                                tv_result.setText(error.errorMessage);
                            }
                        });
                break;
            case R.id.btn_jsonObject:
                NetApi.getInstance().jsonObjectRequest(this, "http://www.weather.com.cn/data/sk/101280601.html", new HashMap<String, String>(),
                        new BaseNetApi.OnNetCallback<JSONObject>() {
                            @Override
                            public void onSuccess(JSONObject result) {
                                ld.dismiss();
                                tv_result.setText(result.toString());
                            }

                            @Override
                            public void onFail(NetError error) {
                                ld.dismiss();
                                tv_result.setText(error.errorMessage);
                            }
                        });
                break;
            case R.id.btn_jsonArray:
                ld.dismiss();
                break;
            case R.id.btn_xml:
                NetApi.getInstance().xmlRequest(this, "https://www.baidu.com/", new HashMap<String, String>(),
                        new BaseNetApi.OnNetCallback<XmlPullParser>() {
                            @Override
                            public void onSuccess(XmlPullParser result) {
                                ld.dismiss();
                                tv_result.setText(result.toString());
                            }

                            @Override
                            public void onFail(NetError error) {
                                ld.dismiss();
                                tv_result.setText(error.errorMessage);
                            }
                        });
                break;
            case R.id.btn_image:
                ld.dismiss();
//                ImageLoader.getInstance().loadImage("http://www.baidu.com/img/bdlogo.png", iv_content);
//                ImageLoader.getInstance().loadImage("http://www.baidu.com/img/bdlogo.png", new ImageLoader.OnLoadCallBack() {
//                    @Override
//                    public void onLoadSuccess(Bitmap bitmap, String url) {
//                        iv_content.setImageBitmap(bitmap);
//                    }
//
//                    @Override
//                    public void onLoadFail(NetError error) {
//
//                    }
//                });
//                ImageLoader.getInstance().loadImage("http://www.baidu.com/img/bdlogo.png",
//                        iv_content.getMeasuredWidth(), iv_content.getMeasuredHeight(), new ImageLoader.OnLoadCallBack() {
//                            @Override
//                            public void onLoadSuccess(Bitmap bitmap, String url) {
//                                iv_content.setImageBitmap(bitmap);
//                            }
//
//                            @Override
//                            public void onLoadFail(NetError error) {
//
//                            }
//                        });
                ImageLoader.getInstance().loadImage("http://www.baidu.com/img/bdlogo.png", iv_content.getMeasuredWidth(), iv_content.getMeasuredHeight(), iv_content,
                        R.mipmap.ic_refresh, R.mipmap.ic_refresh_close);
                break;
        }
    }
}
